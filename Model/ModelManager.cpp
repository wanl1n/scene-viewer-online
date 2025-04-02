#include <stddef.h>
#include "ModelManager.h"
#include <iostream>

#include "../Thread/ObjectLoader.h"

ModelManager* ModelManager::sharedInstance = NULL;

ModelManager* ModelManager::getInstance() {
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new ModelManager();
	}

	return sharedInstance;
}

void ModelManager::initialize()
{
	this->threadPool = new ThreadPool("Model Manager Thread Pool", 5);
	this->threadPool->startScheduler();

	/*std::vector<Model*> vec(25, nullptr);
	this->modelList = vec;*/

	// Loading the objects
	ObjectLoader* tank = new ObjectLoader("3D/Tank/M1A1.obj", "3D/Tank/TankTex.png", "3D/Tank/TankNorm.png", "Tank",
		glm::vec3(-300.f, 0.f, 0.f),           // pos
		glm::vec3(0.25f),                   // scale
		glm::vec3(0.f, 180.f, 0.f));          // rotate
	threadPool->scheduleTask(tank);

	ObjectLoader* moon = new ObjectLoader("3D/Moon.obj", "", "", "Moon",
		glm::vec3(-200.f, 0, 0.f),	// pos
		glm::vec3(10.f),				// scale
		glm::vec3(0.f),               // rotate
		glm::vec4(238.f / 255.f, 228.f / 255.f, 170.f / 255.f, 1.f)); // color
	threadPool->scheduleTask(moon);

	ObjectLoader* banancat = new ObjectLoader("3D/Cat/banancat.obj", "3D/Cat/banancattex.png", "", "Banana Cat",
		glm::vec3(0.f, 0, 0.f),		// pos
		glm::vec3(0.5f),				// scale
		glm::vec3(0.f));		// rotate
	threadPool->scheduleTask(banancat);

	ObjectLoader* ground = new ObjectLoader("3D/Ground/Ground.obj", "3D/Ground/AddWater_basecolor.png", "3D/Ground/AddWater_normal.png", "Ground",
		glm::vec3(-100.f, 0.f, 0.f),     //pos
		glm::vec3(100.f),                     //scale
		glm::vec3(0.f, 0.f, 0.f));         //rotate
	threadPool->scheduleTask(ground);

	ObjectLoader* ant = new ObjectLoader("3D/Obstacles/Ant/ant1.obj", "3D/Obstacles/Ant/ant_(1).png", "", "Ant",
		glm::vec3(-150.f, 0.f, -200.f),     //pos
		glm::vec3(0.03f),                   //scale
		glm::vec3(0.f, 60.f, 0.f));         //rotate
	threadPool->scheduleTask(ant);

	ObjectLoader* grass = new ObjectLoader("3D/Obstacles/Grass/Grass.obj", "3D/Obstacles/Grass/GrassTex.png", "", "Grass",
		glm::vec3(0.f, 0.f, 0.f),      //pos
		glm::vec3(0.2f),                    //scale
		glm::vec3(0.f, 60.f, 0.f));         //rotate
	threadPool->scheduleTask(grass);

	ObjectLoader* mouse = new ObjectLoader("3D/Obstacles/Mouse/Mouse.obj", "3D/Obstacles/Mouse/MouseTex.png", "", "Mouse",
		glm::vec3(100.f, 0.f, 0.f),        //pos
		glm::vec3(10000.f),                 //scale
		glm::vec3(0.f, 60.f, 0.f));         //rotate
	threadPool->scheduleTask(mouse);

	ObjectLoader* flower = new ObjectLoader("3D/Obstacles/Flowers/Flower.obj", "3D/Obstacles/Flowers/FlowerTexA.png", "", "Flower",
		glm::vec3(0.f, 0.f, 0.f),        //pos
		glm::vec3(250.f),                   //scale
		glm::vec3(0.f, 60.f, 0.f));         //rotate
	threadPool->scheduleTask(flower);

	ObjectLoader* tractor = new ObjectLoader("3D/Obstacles/Car/Tractor.obj", "3D/Obstacles/Car/TractorTex.jpg", "", "Tractor",
		glm::vec3(-100.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));         //rotate
	threadPool->scheduleTask(tractor);

	// Scene 1
	//this->addObject(tank);
	//this->addObject(moon);
	//this->addObject(ground);
	//this->addObject(grass);
	//this->addObject(mouse);

	//// Scene 2
	//this->addObject(ant);
	//this->addObject(tractor);
	//this->addObject(flower);
	//this->addObject(flower);
	//this->addObject(flower);

	//// Scene 3
	//this->addObject(mouse);
	//this->addObject(mouse);
	//this->addObject(mouse);
	//this->addObject(mouse);
	//this->addObject(mouse);

	//// Scene 4
	//this->addObject(grass);
	//this->addObject(grass);
	//this->addObject(grass);
	//this->addObject(grass);
	//this->addObject(grass);

	//// Scene 5
	//this->addObject(ant);
	//this->addObject(ant);
	//this->addObject(ant);
	//this->addObject(ant);
	//this->addObject(ant);

	std::cout << "Model Manager Initialized: "<<this->modelList.size()<<" models loaded." << std::endl;
}

Model* ModelManager::findObjectByName(std::string name)
{
	if (this->modelMap[name] != NULL) {
		return this->modelMap[name];
	}
	else {
		//std::cout << "Object " << name << " not found!";
		return NULL;
	}
}

List ModelManager::getRandomModels(int sceneID)
{
	List randomModels;
	int startingIndex = 5 * (sceneID);
	if (startingIndex + 5 > this->modelList.size()) 
		return std::vector<Model*>(this->modelList.size()%5, nullptr);
	
	for (int i = startingIndex; i < startingIndex+5; i++) {
		randomModels.push_back(this->modelList[i]);
	}

	return randomModels;
}

List ModelManager::getAllObjects()
{
	return this->modelList;
}

int ModelManager::activeObjects()
{
	return this->modelList.size();
}

void ModelManager::update(float deltaTime)
{
	//std::cout << "Delta time: " << deltaTime.asSeconds() << "\n";
	for (int i = 0; i < this->modelList.size(); i++) {
		if (this->modelList[i]->isActive())
			this->modelList[i]->update(deltaTime);
	}
}

void ModelManager::draw(GLuint* shaderProgram, bool texExists)
{
	for (int i = 0; i < this->modelList.size(); i++) {
		if (this->modelList[i]->isActive())
		{
			this->modelList[i]->draw(shaderProgram, texExists);
			//std::cout << "Drawing " << this->modelList[i]->getName() << std::endl;
		}
	}
}

void ModelManager::addObject(Model* model)
{
	model->setActive(false);
	//also initialize the oject
	this->modelMap[model->getName()] = model;
	this->modelList.push_back(model);
	//this->modelMap[model->getName()]->initialize();
}

void ModelManager::deleteObject(Model* model)
{
	this->modelMap.erase(model->getName());

	int index = -1;
	for (int i = 0; i < this->modelList.size(); i++) {
		if (this->modelList[i] == model) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->modelList.erase(this->modelList.begin() + index);
	}

	delete model;
}

void ModelManager::deleteObjectByName(std::string name)
{
	Model* object = this->findObjectByName(name);

	if (object != NULL) {
		this->deleteObject(object);
	}
}
