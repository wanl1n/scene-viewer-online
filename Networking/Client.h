#pragma once
#include <string>

#include "../Model/Model.hpp"
#include "../Proto/scene.grpc.pb.h"
#include "../Proto/model.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class Client
{
public:
	Client(const int& sceneID);
	std::unordered_map<std::string, std::string> GetSceneModels();

	void runClient();
	void RenderUI();

	std::vector<models::Model> models;

private:
	int sceneID;

	std::shared_ptr<grpc::Channel> channel_;
	std::unique_ptr<SceneViewer::Stub> stub_;
	std::unique_ptr<ModelLoader::Stub> modelStub_;
};

