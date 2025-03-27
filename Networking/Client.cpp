#include "Client.h"

#include <imgui.h>
#include <grpcpp/create_channel.h>

Client::Client(const int& sceneID)
{
    this->channel_ = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()); 
	this->stub_ = SceneViewer::NewStub(this->channel_);
    this->sceneID = sceneID;
}

std::vector<std::string> Client::GetSceneModel()
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
        std::vector<std::string> modelNames;
        for (int i = 0; i < reply.modelnames_size(); ++i) {
            modelNames.push_back(reply.modelnames(i));
        }
        return modelNames;
    }

    else 
    {
        std::cout << status.error_code() << ": " << status.error_message()
            << std::endl;
        return {}; 
    }
}



void Client::runClient()
{
    std::vector<std::string> modelNames = this->GetSceneModel();

    std::cout << "Client " << this->sceneID << " received: ";
    for (const auto& name : modelNames) {
        std::cout << name << " ";
    }
    std::cout << std::endl;

}

void Client::RenderUI()
{
    ImGui::Begin(("Client " + std::to_string(sceneID)).c_str());  

    ImGui::Text("Scene ID: %d", sceneID);

    std::vector<std::string> modelNames = this->GetSceneModel();

    ImGui::Text("Model Names:");
    for (const auto& name : modelNames) 
    {
        ImGui::BulletText("%s", name.c_str());
    }

    ImGui::End();
}