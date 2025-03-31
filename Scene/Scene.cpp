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
    this->models = ModelManager::getInstance()->getRandomModels();
	std::cout << "Scene " << this->id << " initialized with "<< models.size()<<" models." << std::endl;
}

void Scene::update(float deltaTime)
{
}

void Scene::processInput()
{
}

void Scene::loadScene()
{
    for (Model* model : models)
    {
        model->setActive(true);
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
