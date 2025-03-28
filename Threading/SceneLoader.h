#pragma once
//#include "IETThread.h"
#include "IWorkerAction.h"
#include "../Scene/Scene.h"

class IExecutionEvent;

// Converted to IWorkerAction, now it's a Job.
class SceneLoader : public IWorkerAction
{
public:
	SceneLoader(int id, Scene* screen);
	~SceneLoader();

private:
	void onStartTask() override;

	int id;
	IExecutionEvent* execEvent;
	Scene* screen;
};