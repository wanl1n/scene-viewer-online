#pragma once
//singleton class
/* Game object manager contains all of the declared game object classes and calls the update function
 */
#include <unordered_map>
#include <vector>
#include <string>
#include "Model.hpp"
#include "../Thread/ThreadPool.h"

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

private:
	ModelManager() {};
	ModelManager(ModelManager const&) {};             // copy constructor is private
	ModelManager& operator=(ModelManager const&) {};  // assignment operator is private
	static ModelManager* sharedInstance;

	//ModelManager::getInstance()->addObject(fpsCounter);
	ModelTable modelMap;
	List modelList;
	ThreadPool* threadPool;
};