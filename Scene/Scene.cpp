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
		this->models = ModelManager::getInstance()->getRandomModels();
	}
	std::cout << "Scene " << this->id << " initialized with "<< models.size()<<" models." << std::endl;
}

void Scene::update(float deltaTime)
{
	for (Model* model : models)
	{
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
        model->setActive(true);
		std::cout << "Model " << model->getName() << " loaded." << std::endl;
    }
}

void Scene::unloadScene()
{
    for (Model* model : models)
    {
        model->setActive(false);
    }
}

void Scene::onFinishedExecution()
{
}
