#pragma once
#include <string>

#include "../Model/Model.hpp"
#include "../Proto/scene.grpc.pb.h"
#include "../Proto/model.grpc.pb.h"
#include "../Proto/transformtex.grpc.pb.h"

#include "../Model/ModelManager.h"
#include "../Thread/IETThread.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class Client : public IETThread
{
public:
	Client(const int& sceneID);

	void createModels();
	void deleteModels();

	void runClient();
	void RenderUI();

	void showModels();
	void hideModels();

	void reloadModels();

	std::vector<models::Model*> getModels();
	std::unordered_map<std::string, ModelData> getModelDataMap();

	bool isSceneLoaded();

	void run() override;

	void setViewing(bool view) { this->viewing = view; }

private:
	std::unordered_map<std::string, ModelData> getSceneModels();


private:
	int sceneID;
	bool viewing = false;

	std::shared_ptr<grpc::Channel> channel_;
	std::unique_ptr<SceneViewer::Stub> stub_;
	std::unique_ptr<ModelLoader::Stub> modelStub_;
	std::unique_ptr<TransformTexSync::Stub> transformStub_;

	std::vector<models::Model*> models_;
	std::unordered_map<std::string, ModelData> modelDataMap_;

	bool sceneLoaded_ = false;
	bool modelsLoaded_ = false;
	bool initialized = false;
};

