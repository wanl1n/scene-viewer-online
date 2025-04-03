#pragma once
#include "Scene.h"
#include "../Thread/ThreadPool.h"

class SceneManager
{
public:
	static SceneManager* getInstance();
	void initialize();
	void initializeSceneModelsList();

	void addScene(Scene* scene);
	void loadScene(int sceneID);
	void processInput();
	void update(float deltaTime);

	bool loadingProgress(int sceneID);

	std::vector<Scene*> getScenes();
	std::vector<std::string> getModelNames(int id);

private:
	SceneManager();
	SceneManager(SceneManager const&) {};             // copy constructor is private
	SceneManager& operator=(SceneManager const&) {};  // assignment operator is private
	static SceneManager* sharedInstance;

	Scene* currentScene;
	std::vector<Scene*> scenes;
	ThreadPool* threadPool;

	std::unordered_map<int, std::vector<std::string>> sceneModelsList;
};
