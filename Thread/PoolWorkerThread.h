#pragma once

#include "IETThread.h"

class IWorkerAction;

class IFinishedTask;

class PoolWorkerThread : public IETThread
{
public:
	PoolWorkerThread(int id, IFinishedTask* finishedTask);
	~PoolWorkerThread() = default;

	int getThreadID();
	void assignTask(IWorkerAction* action);

private:
	void run() override;

private:
	int id = 0;
	IWorkerAction* action;
	IFinishedTask* finishedTask;
};