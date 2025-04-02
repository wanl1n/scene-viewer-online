#include "Scene.h"

#include "../Model/ModelManager.h"

Scene::Scene(int id)
{
	this->id = id;
}

Scene::~Scene()
{
}

void Scene::initializeDisplay()
{
	while (models.size() < 5)
	{
		this->models = ModelManager::getInstance()->getRandomModels(id);

		loading = this->models.size() / 5;
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
		if (model)
			model->setActive(true);
    }
}

void Scene::unloadScene()
{
    for (Model* model : models)
    {
		if (model)
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
