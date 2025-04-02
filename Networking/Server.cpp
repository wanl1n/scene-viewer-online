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

#include "../Model/Model.hpp"
#include "../Model/ModelManager.h"
#include "../Scene/SceneManager.h"

grpc::Status Server::GetScene(grpc::ServerContext* context, const SceneRequest* request, SceneResponse* response)
{
	int sceneID = request->sceneid();

	std::vector<Scene*> scenes = SceneManager::getInstance()->getScenes();

    std::vector<Model*> models = scenes[sceneID]->getModels();

    for (auto model : models)
    {
        response->add_modelnames(model->getName());
    }

	return grpc::Status::OK;
}


grpc::Status Server::GetModel(grpc::ServerContext* context, const ModelRequest* request,
    grpc::ServerWriter<ModelResponse>* writer)
{
    std::string modelName = request->modelname();

    models::Model* model = ModelManager::getInstance()->findObjectByName(modelName);
    if (!model)
    {
        return grpc::Status(grpc::StatusCode::NOT_FOUND, "Model not found.");
    }

    std::string modelData = model->getModelData();


    const size_t chunkSize = 1024 * 1024;  // 1MB chunks
    size_t totalSize = modelData.size();
    size_t offset = 0;

    while (offset < totalSize)
    {
        size_t currentChunkSize = std::min(chunkSize, totalSize - offset);

        ModelResponse response;
        response.set_modeldata(modelData.data() + offset, currentChunkSize);
        writer->Write(response);

        offset += currentChunkSize;
    }

    return grpc::Status::OK;
}

grpc::Status Server::GetTransformTex(grpc::ServerContext* context, const TransformTexRequest* request, grpc::ServerWriter<TransformTexResponse>* writer)
{
    std::string modelName = request->modelname();

    models::Model* model = ModelManager::getInstance()->findObjectByName(modelName);
    if (!model)
    {
        return grpc::Status(grpc::StatusCode::NOT_FOUND, "Model not found.");
    }

    std::vector<uint8_t> textureData = model->getTextureData();

    if (textureData.empty())
    {
        return grpc::Status(grpc::StatusCode::NOT_FOUND, "Texture data not found.");
    }

    const size_t chunkSize = 1024 * 1024;
    size_t totalSize = textureData.size();

    for (size_t offset = 0; offset < totalSize; offset += chunkSize)
    {
        size_t chunkEnd = std::min(offset + chunkSize, totalSize);
        size_t chunkSizeActual = chunkEnd - offset;

        TransformTexResponse response;
        response.set_posx(model->getPosition().x);
        response.set_posy(model->getPosition().y);
        response.set_posz(model->getPosition().z);

        response.set_pitch(model->getRotation().x);
        response.set_yaw(model->getRotation().y);
        response.set_roll(model->getRotation().z);

        response.set_scalex(model->getScale().x);
        response.set_scaley(model->getScale().y);
        response.set_scalez(model->getScale().z);

        response.set_texwidth(model->getTexSize().x);
        response.set_texheight(model->getTexSize().y);

        response.set_texture(reinterpret_cast<const char*>(&textureData[offset]), chunkSizeActual);

        writer->Write(response);
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
