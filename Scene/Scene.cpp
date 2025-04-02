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
	std::cout << "Scene " << this->id << " initialized with "<< models.size()<<" models." << std::endl;
}

void Scene::update(float deltaTime)
{
	for (Model* model : models)
	{
		if (model)
			model->setActive(true);
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
