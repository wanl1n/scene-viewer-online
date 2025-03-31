#include "Client.h"

#include <imgui.h>
#include <glm/vec3.hpp>
#include <grpcpp/create_channel.h>

#include "../Model/Model.hpp"

Client::Client(const int& sceneID)
{
    grpc::ChannelArguments channel_args;
    channel_args.SetMaxReceiveMessageSize(64 * 1024 * 1024);  

    this->channel_ = grpc::CreateCustomChannel("localhost:50051", grpc::InsecureChannelCredentials(), channel_args);

    this->stub_ = SceneViewer::NewStub(this->channel_);
    this->modelStub_ = ModelLoader::NewStub(this->channel_);
    this->transformStub_ = TransformTexSync::NewStub(this->channel_);

    this->sceneID = sceneID;
}


std::unordered_map<std::string, ModelData> Client::GetSceneModels()
{
    SceneRequest request;
    request.set_sceneid(sceneID);
    SceneResponse reply;
    grpc::ClientContext context;

    std::chrono::time_point deadline = std::chrono::system_clock::now() +
        std::chrono::milliseconds(2000);
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
            ModelResponse modelReply;
            grpc::ClientContext modelContext;

            grpc::Status modelStatus = modelStub_->GetModel(&modelContext, modelRequest, &modelReply);

            if (modelStatus.ok())
            {
                ModelData modelData;
                modelData.modelData = modelReply.modeldata();

                TransformTexRequest transformRequest;
                transformRequest.set_modelname(modelName);
                TransformTexResponse transformReply;
                grpc::ClientContext transformContext;

                grpc::Status transformStatus = transformStub_->GetTransformTex(&transformContext, transformRequest, &transformReply);

                if (transformStatus.ok())
                {
                    modelData.position = glm::vec3(transformReply.posx(), transformReply.posy(), transformReply.posz());
                    modelData.rotation = glm::vec3(transformReply.pitch(), transformReply.yaw(), transformReply.roll());
                    modelData.scale = glm::vec3(transformReply.scalex(), transformReply.scaley(), transformReply.scalez());

                    std::string textureStr = transformReply.texture();  
                    modelData.texSize = glm::vec2(transformReply.texwidth(), transformReply.texheight());
                    modelData.textureData = std::vector<uint8_t>(textureStr.begin(), textureStr.end());
                }
                else
                {
                    std::cout << transformStatus.error_code() << ": " << transformStatus.error_message() << std::endl;
                }

                modelDataMap[modelName] = modelData;
            }
            else
            {
                std::cout << modelStatus.error_code() << ": " << modelStatus.error_message() << std::endl;
            }
        }
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
    this->modelDataMap_ = this->GetSceneModels();

    if (!this->modelDataMap_.empty())
    {
        for (const auto& [name, data] : this->modelDataMap_)
        {
            models::Model model(std::move(std::string(data.modelData)), data.textureData, data.texSize.x, data.texSize.y);

            model.setPosition(data.position);
            model.setRotation(data.rotation);
            model.setScale(data.scale);

            this->models_.push_back(model);
        }
    }
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
