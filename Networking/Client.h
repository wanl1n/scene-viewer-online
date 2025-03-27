#pragma once
#include <string>
#include "../Proto/scene.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class Client
{
public:
	Client(const int& sceneID);
	std::vector<std::string> GetSceneModel();

	void runClient();
	void RenderUI();

private:
	int sceneID;

	std::shared_ptr<grpc::Channel> channel_;
	std::unique_ptr<SceneViewer::Stub> stub_;
};

