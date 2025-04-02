#include "SceneManager.h"

#include <imgui.h>
#include <iostream>

#include "../Thread/SceneLoader.h"
#include "../Imgui/ImGuiUtils.h"

//a singleton class
SceneManager* SceneManager::sharedInstance = nullptr;

SceneManager* SceneManager::getInstance() {
	if (sharedInstance == nullptr) {
		//initialize
		sharedInstance = new SceneManager();
	}

	return sharedInstance;
}

void SceneManager::initialize()
{
	this->threadPool = new ThreadPool("Scene Manager Thread Pool", std::thread::hardware_concurrency());
	this->threadPool->startScheduler();

	for (int i = 0; i < 5; i++) {
		Scene* scene = new Scene(i);
		SceneLoader* loader = new SceneLoader(i, scene);
		this->threadPool->scheduleTask(loader);
		this->addScene(scene);
	}
	this->currentScene = scenes[0];
	this->loadScene(0);

	std::cout << "Scene Manager Initialized." << std::endl;
}

void SceneManager::addScene(Scene* scene)
{
	this->scenes.push_back(scene);
}

void SceneManager::loadScene(int sceneID)
{
	if (this->currentScene != scenes[sceneID])
	{
		this->currentScene->unloadScene();
		this->currentScene = this->scenes[sceneID];
		this->currentScene->loadScene();
	}
}

void SceneManager::processInput()
{
	this->currentScene->processInput();
}

void SceneManager::update(float deltaTime)
{
	this->currentScene->update(deltaTime);

	ImGui::Begin("Scene Manager");
	ImGui::Text("Loading Progress:");
	for (Scene* scene : scenes)
	{
		std::string label = "Loading Scene " + std::to_string(scene->getID());
		ImGuiUtils::LoadingBar(label.c_str(), SceneManager::getInstance()->loadingProgress(scene->getID()));
	}
	ImGui::End();
}

bool SceneManager::loadingProgress(int sceneID)
{
	//std::cout << "Scene Manager loading progress " << this->SceneMap[Scene::game]->loadingProgress() << std::endl;
	return this->scenes[sceneID]->loadingProgress();
	//return 0;
}

std::vector<Scene*> SceneManager::getScenes()
{
	return this->scenes;
}

SceneManager::SceneManager()
{
}
