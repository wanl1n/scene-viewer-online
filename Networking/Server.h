#pragma once
#include <cstdint>
#include "../Proto/scene.pb.h"
#include "../Proto/scene.grpc.pb.h"
#include "../Thread/IETThread.h"

class Server final : public SceneViewer::Service, public IETThread {
public:
	grpc::Status GetScene(grpc::ServerContext* context, const SceneRequest* request, SceneResponse* response) override;


	static void RunServer(uint16_t port);

	void run() override;
};
