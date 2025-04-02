#pragma once

#include <vector>
#include "../Model/Model.hpp"
#include "../Thread/IExecutionEvent.h"

using namespace models;

class Scene : public IExecutionEvent
{
public:
	Scene(int id);
	~Scene();

	void initializeDisplay();

	virtual void update(float deltaTime);
	virtual void processInput();
	virtual void loadScene();
	virtual void unloadScene();
	void onFinishedExecution() override;

	int getID() { return id; }
	float loadingProgress() { return loading; }
	
private:
	int id = 0;
	std::vector<Model*> models;
	float loading = 0;
};