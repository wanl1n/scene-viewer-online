#include "Client.h"
#include <imgui.h>
#include <grpcpp/create_channel.h>
#include "../Model/Model.hpp"

Client::Client(const int& sceneID)
{
    grpc::ChannelArguments channel_args;
    this->channel_ = grpc::CreateCustomChannel("localhost:50051", grpc::InsecureChannelCredentials(), channel_args);
    this->stub_ = SceneViewer::NewStub(this->channel_);
    this->modelStub_ = ModelLoader::NewStub(this->channel_);
    this->transformStub_ = TransformTexSync::NewStub(this->channel_);
    this->sceneID = sceneID;
}

std::unordered_map<std::string, ModelData> Client::getSceneModels()
{
    SceneRequest request;
    request.set_sceneid(sceneID);
    SceneResponse reply;
    grpc::ClientContext context;

    std::chrono::time_point deadline = std::chrono::system_clock::now() + std::chrono::milliseconds(2000);
    context.set_deadline(deadline);

    grpc::Status status = stub_->GetScene(&context, request, &reply);
    if (status.ok())
    {
        std::unordered_map<std::string, ModelData> modelDataMap;
        for (int i = 0; i < reply.modelnames_size(); ++i)
        {
            std::string modelName = reply.modelnames(i);
            ModelRequest modelRequest;
            modelRequest.set_modelname(modelName);
            grpc::ClientContext modelContext;

            std::unique_ptr<grpc::ClientReader<ModelResponse>> reader(modelStub_->GetModel(&modelContext, modelRequest));

            ModelData modelData;
            ModelResponse modelReply;
            std::string fullModelData;
            while (reader->Read(&modelReply))
            {
                fullModelData += modelReply.modeldata();
            }
            modelData.modelData = fullModelData;

            TransformTexRequest transformRequest;
            transformRequest.set_modelname(modelName);
            grpc::ClientContext transformContext;

            std::unique_ptr<grpc::ClientReader<TransformTexResponse>> texReader = transformStub_->GetTransformTex(&transformContext, transformRequest);

            TransformTexResponse transformReply;
            std::vector<uint8_t> accumulatedTextureData;
            while (texReader->Read(&transformReply))
            {
                modelData.position = glm::vec3(transformReply.posx(), transformReply.posy(), transformReply.posz());
                modelData.rotation = glm::vec3(transformReply.pitch(), transformReply.yaw(), transformReply.roll());
                modelData.scale = glm::vec3(transformReply.scalex(), transformReply.scaley(), transformReply.scalez());
                modelData.texSize = glm::vec2(transformReply.texwidth(), transformReply.texheight());

                if (!transformReply.texture().empty())
                {
                    accumulatedTextureData.insert(accumulatedTextureData.end(),
                        transformReply.texture().begin(),
                        transformReply.texture().end());
                }
            }

            modelData.textureData = std::move(accumulatedTextureData);

            modelDataMap[modelName] = modelData;
        }

        this->sceneLoaded_ = true;
        return modelDataMap;
    }
    else
    {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return {};
    }
}

void Client::runClient()
{
    this->modelDataMap_ = this->getSceneModels();
}

void Client::createModels()
{
    if (!this->modelDataMap_.empty())
    {
        for (const auto& [name, data] : this->modelDataMap_)
        {
            if (data.modelData.empty() || data.textureData.empty())
            {
                continue;
            }

            models::Model model(std::move(std::string(data.modelData)), data.textureData, data.texSize.x, data.texSize.y);
            model.setPosition(data.position);
            model.setRotation(data.rotation);
            model.setScale(data.scale);
            this->models_.push_back(model);
        }
    }

    this->sceneLoaded_ = false;
}

void Client::RenderUI()
{
    ImGui::Begin(("Client " + std::to_string(sceneID)).c_str());
    ImGui::Text("Scene ID: %d", sceneID);
    ImGui::Text("Model Names:");
    for (const auto& [name, modelData] : this->modelDataMap_)
    {
        ImGui::BulletText("%s", name.c_str());
    }
    ImGui::End();
}

std::vector<models::Model> Client::getModels()
{
    return this->models_;
}

std::unordered_map<std::string, ModelData> Client::getModelDataMap()
{
    return this->modelDataMap_;
}

bool Client::isSceneLoaded()
{
    return this->sceneLoaded_;
}
