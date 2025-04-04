#pragma once
//singleton class
/* Game object manager contains all of the declared game object classes and calls the update function
 */
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>
#include "Model.hpp"

struct ModelData
{
	std::string name;

	std::string modelPath;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	std::string texturePath;

	std::string modelBuffer;
	std::vector<uint8_t> textureData;
	glm::vec2 texSize;


	ModelData(std::string name, const std::string& path, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, const std::string& texPath)
		: name(name), modelPath(path), position(pos), rotation(rot), scale(scl), texturePath(texPath) {}
	ModelData() {}
};


using namespace models;
typedef std::unordered_map<std::string, Model*> ModelTable;
typedef std::vector<Model*> List;

class ModelManager
{
public:
	static ModelManager* getInstance();
	void initialize(); 
	void update(float deltaTime);
	void draw(GLuint* shaderProgram, bool texExists);

	// Setters
	void addObject(Model* model);
	void deleteObject(Model* model);
	void deleteObjectByName(std::string name);

	// Getters
	Model* findObjectByName(std::string name);
	List getRandomModels(int sceneID);
	List getModelsByName(std::vector<std::string> names);
	List getAllObjects();
	int activeObjects();

	std::unordered_map<int, std::vector<ModelData>> getSceneModelsData();
	static std::string getModelBuffer(std::string modelPath);
	static std::tuple<std::vector<uint8_t>, int, int> getTextureDataAndSize(std::string texPath);

private:
	ModelManager() {};
	ModelManager(ModelManager const&) {};             // copy constructor is private
	ModelManager& operator=(ModelManager const&) {};  // assignment operator is private
	static ModelManager* sharedInstance;

	std::unordered_map<int, std::vector<ModelData>> sceneModelsData;

	ModelTable modelMap;
	List modelList;

	std::mutex* mutex;

	static glm::vec3 randomPos();
	static float randomFloat(float min, float max);
};