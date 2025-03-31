#pragma once
#include <cstdint>

#include "../Proto/scene.pb.h"
#include "../Proto/scene.grpc.pb.h"

#include "../Proto/model.pb.h"
#include "../Proto/model.grpc.pb.h"

#include "../Proto/transformtex.pb.h"
#include "../Proto/transformtex.grpc.pb.h"

#include "../Thread/IETThread.h"

class Server final : public SceneViewer::Service, public ModelLoader::Service, public TransformTexSync::Service, public IETThread {
public:

	// Scene
	grpc::Status GetScene(grpc::ServerContext* context, const SceneRequest* request, SceneResponse* response) override;

	// Model
	//grpc::Status GetModel(grpc::ServerContext* context, const ModelRequest* request, ModelResponse* response) override;
	grpc::Status GetModel(grpc::ServerContext* context, const ModelRequest* request, grpc::ServerWriter<ModelResponse>* writer) override;

	// Transform Tex
	//grpc::Status GetTransformTex(grpc::ServerContext* context, const TransformTexRequest* request, TransformTexResponse* response) override;
	grpc::Status GetTransformTex(grpc::ServerContext* context, const TransformTexRequest* request, grpc::ServerWriter<TransformTexResponse>* writer) override;

	static void RunServer(uint16_t port);

	void run() override;

private:
	std::vector<uint8_t> readTextureFromFile(const std::string& path, int& width, int& height);

};
