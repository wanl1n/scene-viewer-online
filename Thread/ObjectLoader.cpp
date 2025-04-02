#include "ObjectLoader.h"

#include "IExecutionEvent.h"
#include "../Model/Model.hpp"
#include "../Model/ModelManager.h"

using namespace models;

ObjectLoader::ObjectLoader(std::string strObjPath, const char* pathTex, const char* pathNorm, std::string name,
	glm::vec3 pos, glm::vec3 scale, glm::vec3 rotate, glm::vec4 color)
{
	this->strObjPath = strObjPath;
	this->pathTex = pathTex;
	this->pathNorm = pathNorm;
	this->name = name;
	this->pos = pos;
	this->scale = scale;
	this->rotate = rotate;
	this->color = color;
}

ObjectLoader::ObjectLoader(std::string&& objData, const std::vector<uint8_t>& texData, int texWidth, int texHeight)
{
}

ObjectLoader::~ObjectLoader()
{
	//std::cout << "Destroying scene loader. " << std::endl;
}

void ObjectLoader::onStartTask()
{
	IETThread::sleep(5000);
	std::cout << "Model " << name << " loading." << std::endl;

	Model* model = new Model(strObjPath, pathTex, pathNorm, name, pos, scale, rotate, color);
	std::cout << "Model " << model->getName() << " loaded." << std::endl;
	ModelManager::getInstance()->addObject(model);

	//this->execEvent->onFinishedExecution();

	//delete after being done
	delete this;
}