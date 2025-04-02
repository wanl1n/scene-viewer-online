#pragma once
#include "Scene.h"
#include "../Thread/ThreadPool.h"

class SceneManager
{
public:
	static SceneManager* getInstance();
	void initialize();

	void addScene(Scene* scene);
	void loadScene(int sceneID);
	void processInput();
	void update(float deltaTime);

	bool loadingProgress(int sceneID);

private:
	SceneManager();
	SceneManager(SceneManager const&) {};             // copy constructor is private
	SceneManager& operator=(SceneManager const&) {};  // assignment operator is private
	static SceneManager* sharedInstance;

	Scene* currentScene;
	std::vector<Scene*> scenes;
	ThreadPool* threadPool;
};
