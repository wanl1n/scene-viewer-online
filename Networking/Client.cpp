#include "Client.h"

#include <imgui.h>
#include <glm/vec3.hpp>
#include <grpcpp/create_channel.h>

#include "../Model/Model.hpp"

Client::Client(const int& sceneID)
{
    this->channel_ = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());

    this->stub_ = SceneViewer::NewStub(this->channel_);
    this->modelStub_ = ModelLoader::NewStub(this->channel_);


    this->sceneID = sceneID;
}

std::unordered_map<std::string, std::string> Client::GetSceneModels()
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
        std::unordered_map<std::string, std::string> modelDataMap;
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

                modelDataMap[modelName] = modelReply.modeldata();
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
    std::unordered_map<std::string, std::string> modelDataMap = this->GetSceneModels();

    std::cout << "Client " << this->sceneID << " received: ";
    for (const auto& [name, data] : modelDataMap) 
    {
        std::cout << name << " ";
    }
    std::cout << std::endl;
}

void Client::RenderUI()
{
    std::unordered_map<std::string, std::string> modelDataMap = this->GetSceneModels();

    if (!modelDataMap.empty())
    {
        auto it = modelDataMap.begin();  
        const std::string& name = it->first;
        const std::string& data = it->second;

        models::Model tractor(std::move(std::string(data)), "", "", true);
        tractor.setPosition(glm::vec3(-100.f, 0.f, 0.f));
        tractor.setScale(glm::vec3(3.0f));
        tractor.setRotation(glm::vec3(0.f, 60.f, 0.f));

        models.push_back(tractor);
    }
}