#include "Client.h"
#include <grpcpp/create_channel.h>

Client::Client(std::shared_ptr<grpc::ChannelInterface> channel, const int& sceneID)
{
	this->stub_ = SceneViewer::NewStub(channel);
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
    Client sceneClient(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()), 1);

    std::vector<std::string> modelNames = sceneClient.GetSceneModel();

    std::cout << "Client 1 received: ";
    for (const auto& name : modelNames) {
        std::cout << name << " ";
    }
    std::cout << std::endl;
}
