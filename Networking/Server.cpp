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

    std::unordered_map<int, std::vector<ModelData>> sceneModelsData = ModelManager::getInstance()->getSceneModelsData();

    if (sceneModelsData.find(sceneID) != sceneModelsData.end())
    {
        for (auto model : sceneModelsData[sceneID])  
        {
            response->add_modelnames(model.name);
        }
    }

	return grpc::Status::OK;
}


grpc::Status Server::GetModel(grpc::ServerContext* context, const ModelRequest* request,
    grpc::ServerWriter<ModelResponse>* writer)
{
    std::string modelName = request->modelname();

    std::string modelPath = "";
    for (const auto& entry : ModelManager::getInstance()->getSceneModelsData()) 
    {
        for (const auto& model : entry.second) {
            if (model.name == modelName) {
                modelPath = model.modelPath;  
                break;
            }
        }
        if (!modelPath.empty()) {
            break;
        }
    }

    if (modelPath.empty()) 
    {
        std::cerr << "Model not found: " << modelName << std::endl;
        return grpc::Status(grpc::StatusCode::NOT_FOUND, "Model not found");
    }

    std::string modelData = ModelManager::getModelBuffer(modelPath);

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

    ModelData modelData;

    std::string texPath = "";  
    for (const auto& entry : ModelManager::getInstance()->getSceneModelsData()) 
    {
        for (const auto& model : entry.second) 
        {
            if (model.name == modelName) 
            {
                modelData = model;
                texPath = model.texturePath;
                break;
            }
        }
        if (!texPath.empty()) {
            break;
        }
    }

    if (texPath.empty()) {
        return grpc::Status(grpc::StatusCode::NOT_FOUND, "Texture path not found");
    }

    auto [textureData, texWidth, texHeight] = ModelManager::getInstance()->getTextureDataAndSize(texPath);

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
        response.set_posx(modelData.position.x);
        response.set_posy(modelData.position.y);
        response.set_posz(modelData.position.z);

        response.set_pitch(modelData.rotation.x);
        response.set_yaw(modelData.rotation.y);
        response.set_roll(modelData.rotation.z);

        response.set_scalex(modelData.scale.x);
        response.set_scaley(modelData.scale.y);
        response.set_scalez(modelData.scale.z);

        response.set_texwidth(texWidth);
        response.set_texheight(texHeight);

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

    // Model Manager
    ModelManager::getInstance()->initialize();

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
