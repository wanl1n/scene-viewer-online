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

	this->initializeSceneModelsList();

	for (int i = 0; i < 5; i++) {
		Scene* scene = new Scene(i, this->sceneModelsList[i]);
		SceneLoader* loader = new SceneLoader(i, scene);
		this->threadPool->scheduleTask(loader);
		this->addScene(scene);
	}
	this->currentScene = scenes[0];
	this->loadScene(0);

	std::cout << "Scene Manager Initialized." << std::endl;
}

void SceneManager::initializeSceneModelsList()
{
	std::vector<std::string> scene0(5, "");
	std::vector<std::string> scene1(5, "");
	std::vector<std::string> scene2(5, "");
	std::vector<std::string> scene3(5, "");
	std::vector<std::string> scene4(5, "");

	scene0[0] = "Fish"; //15
	scene0[1] = "Toaster";
	scene0[2] = "Red Rose";
	scene0[3] = "Cabbage"; //11
	scene0[4] = "Cupcake"; //14

	scene1[0] = "Shoe"; //21
	scene1[1] = "Cup"; //13
	scene1[2] = "Burnt Croissant"; //10
	scene1[3] = "Chili";
	scene1[4] = "Orchid";

	scene2[0] = "Lychees"; //17
	scene2[1] = "Banana Cat"; //3
	scene2[2] = "Tank"; //1
	scene2[3] = "Grass"; //6
	scene2[4] = "Flower"; //8

	scene3[0] = "Ant"; //5
	scene3[1] = "Tractor"; //9
	scene3[2] = "Moon"; //2
	scene3[3] = "Mouse"; //7
	scene3[4] = "Ground"; //4

	scene4[0] = "Macaron"; //18
	scene4[1] = "Bag"; //16
	scene4[2] = "Marshmallows"; //19
	scene4[3] = "Meat"; //20
	scene4[4] = "Dried Rose"; //12

	this->sceneModelsList[0] = scene0;
	this->sceneModelsList[1] = scene1;
	this->sceneModelsList[2] = scene2;
	this->sceneModelsList[3] = scene3;
	this->sceneModelsList[4] = scene4;
}

void SceneManager::reinitializeScene(int id)
{
	this->scenes[id]->deleteModels();
	SceneLoader* loader = new SceneLoader(id, this->scenes[id]);
	this->threadPool->scheduleTask(loader);
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

std::vector<std::string> SceneManager::getModelNames(int id)
{
	return this->sceneModelsList[id];
}

SceneManager::SceneManager()
{
}
