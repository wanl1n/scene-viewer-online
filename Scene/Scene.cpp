#include "Scene.h"

#include "../Model/ModelManager.h"

Scene::Scene(int id, std::vector<std::string> names)
{
	this->id = id;
	this->modelNames = names;
}

Scene::~Scene()
{
}

void Scene::initializeDisplay()
{
	while (models.size() < 5 || models[0] == nullptr || models[1] == nullptr || models[2] == nullptr || models[3] == nullptr || models[4] == nullptr)
	{
		this->models = ModelManager::getInstance()->getModelsByName(modelNames);

		int loadedModels = 0;
		if (models[0]) loadedModels++;
		if (models[1]) loadedModels++;
		if (models[2]) loadedModels++;
		if (models[3]) loadedModels++;
		if (models[4]) loadedModels++;
		loading = loadedModels / 5;
	}
	this->initialized = true;
	std::cout << "Scene " << this->id << " initialized with "<< models.size()<<" models." << std::endl;
}

void Scene::update(float deltaTime)
{
	if (this->initialized)
	{
		for (Model* model : models)
		{
			if (model)
				model->setActive(true);
		}
	}
}

void Scene::processInput()
{
}

void Scene::loadScene()
{
    for (Model* model : models)
    {
		if (model != nullptr)
			model->setActive(true);
    }
}

void Scene::unloadScene()
{
    for (Model* model : models)
    {
		if (model != nullptr)
			model->setActive(false);
    }
}

void Scene::onFinishedExecution()
{
}

std::vector<Model*> Scene::getModels()
{
	return this->models;
}

bool Scene::isInitialized()
{
	return this->initialized;
}
