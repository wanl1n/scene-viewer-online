#include <stddef.h>
#include "ModelManager.h"
#include <iostream>

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
	// Loading the objects
	Model* tank = new Model("3D/Tank/M1A1.obj", "3D/Tank/TankTex.png", "3D/Tank/TankNorm.png", "Tank",
		glm::vec3(-300.f, 0.f, 0.f),           // pos
		glm::vec3(0.25f),                   // scale
		glm::vec3(0.f, 180.f, 0.f));          // rotate

	Model* moon = new Model("3D/Moon.obj", "", "", "Moon",
		glm::vec3(-200.f, 0, 0.f), // pos
		glm::vec3(10.f),                // scale
		glm::vec3(0.f),                 // rotate
		glm::vec4(238.f / 255.f, 228.f / 255.f, 170.f / 255.f, 1.f)); // color

	Model* ground = new Model("3D/Ground/Ground.obj", "3D/Ground/AddWater_basecolor.png", "3D/Ground/AddWater_normal.png", "Ground",
		glm::vec3(-100.f, 0.f, 0.f),           //pos
		glm::vec3(100.f),                     //scale
		glm::vec3(0.f, 0.f, 0.f));         //rotate

	Model* ant = new Model("3D/Obstacles/Ant/ant1.obj", "3D/Obstacles/Ant/ant_(1).png", "", "Ant",
		glm::vec3(-150.f, 0.f, -200.f),     //pos
		glm::vec3(0.03f),                   //scale
		glm::vec3(0.f, 60.f, 0.f));         //rotate

	Model* grass = new Model("3D/Obstacles/Grass/Grass.obj", "3D/Obstacles/Grass/GrassTex.png", "", "Grass",
		glm::vec3(0.f, 0.f, 0.f),      //pos
		glm::vec3(0.2f),                    //scale
		glm::vec3(0.f, 60.f, 0.f));         //rotate

	Model* mouse = new Model("3D/Obstacles/Mouse/Mouse.obj", "3D/Obstacles/Mouse/MouseTex.png", "", "Mouse",
		glm::vec3(100.f, 0.f, 0.f),        //pos
		glm::vec3(10000.f),                 //scale
		glm::vec3(0.f, 60.f, 0.f));         //rotate

	Model* flower = new Model("3D/Obstacles/Flowers/Flower.obj", "3D/Obstacles/Flowers/FlowerTexA.png", "", "Flower",
		glm::vec3(0.f, 0.f, 0.f),        //pos
		glm::vec3(250.f),                   //scale
		glm::vec3(0.f, 60.f, 0.f));         //rotate

	Model* tractor = new Model("3D/Obstacles/Car/Tractor.obj", "3D/Obstacles/Car/TractorTex.jpg", "", "Tractor",
		glm::vec3(-100.f, 0.f, 0.f),        //pos
		glm::vec3(3.f),                     //scale
		glm::vec3(0.f, 60.f, 0.f));         //rotate

	// Scene 1
	this->addObject(tank);
	this->addObject(moon);
	this->addObject(ground);
	this->addObject(grass);
	this->addObject(mouse);

	// Scene 2
	this->addObject(ant);
	this->addObject(tractor);
	this->addObject(flower);
	this->addObject(flower);
	this->addObject(flower);

	// Scene 3
	this->addObject(mouse);
	this->addObject(mouse);
	this->addObject(mouse);
	this->addObject(mouse);
	this->addObject(mouse);

	// Scene 4
	this->addObject(grass);
	this->addObject(grass);
	this->addObject(grass);
	this->addObject(grass);
	this->addObject(grass);

	// Scene 5
	this->addObject(moon);
	this->addObject(moon);
	this->addObject(moon);
	this->addObject(moon);
	this->addObject(moon);

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

List ModelManager::getRandomModels()
{
	List randomModels;
	for (int i = startingIndex; i < startingIndex+5; i++) {
		randomModels.push_back(this->modelList[i]);
	}

	startingIndex += 5;
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
