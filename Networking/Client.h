#pragma once
#include <string>
#include "../Proto/scene.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class Client
{
public:
	Client(std::shared_ptr<grpc::ChannelInterface> channel, const int& sceneID);
	std::vector<std::string> GetSceneModel();

	static void runClient();

private:
	std::unique_ptr<SceneViewer::Stub> stub_;
	int sceneID;
};

