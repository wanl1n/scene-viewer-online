#pragma once
#include <string>

#include "../Model/Model.hpp"
#include "../Proto/scene.grpc.pb.h"
#include "../Proto/model.grpc.pb.h"
#include "../Proto/transformtex.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

struct ModelData
{
	std::string modelData;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::vec2 texSize;
	std::vector<uint8_t> textureData;
};

class Client
{
public:
	Client(const int& sceneID);
	std::unordered_map<std::string, ModelData> GetSceneModels();

	void runClient();
	void RenderUI();

	std::vector<models::Model> getModels();
	std::unordered_map<std::string, ModelData> getModelDataMap();

private:
	int sceneID;

	std::shared_ptr<grpc::Channel> channel_;
	std::unique_ptr<SceneViewer::Stub> stub_;
	std::unique_ptr<ModelLoader::Stub> modelStub_;
	std::unique_ptr<TransformTexSync::Stub> transformStub_;

	std::vector<models::Model> models_;
	std::unordered_map<std::string, ModelData> modelDataMap_;
};

