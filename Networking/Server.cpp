#include "Server.h"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include <filesystem>
#include <fstream>
#include "../tiny_obj_loader.h"
#include "../stb_image.h"

grpc::Status Server::GetScene(grpc::ServerContext* context, const SceneRequest* request, SceneResponse* response)
{
	int sceneID = request->sceneid();

	switch (sceneID)
	{
		case 1:
			response->add_modelnames("S1M1");
			response->add_modelnames("S1M2");
			break;

		case 2:
			response->add_modelnames("S2M1");
			response->add_modelnames("S2M2");
			break;

		case 3:
			response->add_modelnames("S3M1");
			response->add_modelnames("S3M2");
			break;

		case 4:
			response->add_modelnames("S4M1");
			response->add_modelnames("S4M2");
			break;

		case 5:
			response->add_modelnames("S5M1");
			response->add_modelnames("S5M2");
			break;

		default:
			return grpc::Status(grpc::StatusCode::NOT_FOUND, "Scene not found.");
	}

	return grpc::Status::OK;
}


grpc::Status Server::GetModel(grpc::ServerContext* context, const ModelRequest* request, ModelResponse* response)
{
	std::string modelName = request->modelname();

	std::string filePath = "";

	if (modelName == "S1M1")
	{
		filePath = "./3D/Obstacles/Car/Tractor.obj";
	}

	std::ifstream file(filePath);
	if (!file)
	{
		return grpc::Status(grpc::StatusCode::NOT_FOUND, "Model not found.");
	}
	std::ostringstream buffer;
	buffer << file.rdbuf();  
	file.close();

	response->set_modeldata(buffer.str());

	return grpc::Status::OK;
}

grpc::Status Server::GetTransformTex(grpc::ServerContext* context, const TransformTexRequest* request, TransformTexResponse* response)
{
	std::string modelName = request->modelname();

	if (modelName == "S1M1")
	{
		response->set_posx(-100.0f);
		response->set_posy(0.0f);
		response->set_posz(0.0f);

		response->set_pitch(0.0f);
		response->set_yaw(60.0f);
		response->set_roll(0.0f);

		response->set_scalex(3.0f);
		response->set_scaley(3.0f);
		response->set_scalez(3.0f);

		std::string texturePath = "./3D/Obstacles/Car/TractorTex.jpg";
		int texWidth, texHeight;
		std::vector<uint8_t> textureData = readTextureFromFile(texturePath, texWidth, texHeight);

		response->set_texwidth(texWidth);
		response->set_texheight(texHeight);
		response->set_texture(reinterpret_cast<const char*>(textureData.data()), textureData.size());
	}
	else
	{
		return grpc::Status(grpc::StatusCode::NOT_FOUND, "Model not found.");
	}

	return grpc::Status::OK;
}

void Server::RunServer(uint16_t port)
{
	std::string serverAddress = absl::StrFormat("localhost:%d", port);
	Server service;

	grpc::EnableDefaultHealthCheckService(true);
	grpc::reflection::InitProtoReflectionServerBuilderPlugin();
	grpc::ServerBuilder builder;

	builder.SetMaxReceiveMessageSize(64 * 1024 * 1024);

	// Listen on the given address without any authentication mechanism.
	builder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());

	// Register "service" as the instance through which we'll communicate with
	// clients. In this case it corresponds to an *synchronous* service.
	builder.RegisterService(static_cast<SceneViewer::Service*>(&service));
	builder.RegisterService(static_cast<ModelLoader::Service*>(&service));
	builder.RegisterService(static_cast<TransformTexSync::Service*>(&service));

	// Finally assemble the server.
	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << serverAddress << std::endl;

	// Wait for the server to shutdown. Note that some other thread must be
	// responsible for shutting down the server for this call to ever return.
	server->Wait();
}


void Server::run()
{
	RunServer(50051);
}

std::vector<uint8_t> Server::readTextureFromFile(const std::string& path, int& width, int& height)
{
	int channels;

	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

	if (!data)
	{
		std::cerr << "Failed to load texture: " << path << std::endl;
		return {};
	}

	size_t dataSize = width * height * channels;

	std::vector<uint8_t> textureData(data, data + dataSize);

	stbi_image_free(data);

	return textureData;
}

