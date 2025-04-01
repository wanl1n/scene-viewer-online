#include "SceneLoader.h"

#include "IExecutionEvent.h"
#include "../Scene/SceneManager.h"

SceneLoader::SceneLoader(int id, Scene* screen)
{
	this->screen = screen;
	this->execEvent = screen;
	this->id = id;
}

SceneLoader::~SceneLoader()
{
	//std::cout << "Destroying scene loader. " << std::endl;
}

void SceneLoader::onStartTask()
{
	//std::cout << "Running scene loader " << std::endl;
	this->screen->initializeDisplay();
	this->execEvent->onFinishedExecution();

	//delete after being done
	delete this;
}