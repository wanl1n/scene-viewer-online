#pragma once

#include <vector>
#include "../Model/Model.hpp"
#include "../Thread/IExecutionEvent.h"

using namespace models;

class Scene : public IExecutionEvent
{
public:
	Scene(int id, std::vector<std::string> names);
	~Scene();

	void initializeDisplay();

	virtual void update(float deltaTime);
	virtual void processInput();

	virtual void loadScene();
	virtual void unloadScene();
	void deleteModels();

	void onFinishedExecution() override;

	std::vector<Model*> getModels();
	bool isInitialized();

	int getID() { return id; }
	float loadingProgress() { return loading; }
	
private:
	int id = 0;
	std::vector<Model*> models;
	bool initialized = false;
	float loading = 0;

	std::vector<std::string> modelNames;
};