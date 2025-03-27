#pragma once

#include <queue>
#include <unordered_map>

#include "IETThread.h"
#include "IFinishedTask.h"

class PoolWorkerThread;
class IWorkerAction;

class ThreadPool : public IETThread, public IFinishedTask
{
public:
	ThreadPool(std::string name, int numWorkers);
	~ThreadPool();

	void startScheduler();
	void stopScheduler();
	void scheduleTask(IWorkerAction* action);

private:
	void run() override;
	void onFinished(int threadID) override;

private:
	std::string name;
	bool running = false;
	int numWorkers = 0;

	std::unordered_map<int, PoolWorkerThread*> activeThreads;
	std::queue<PoolWorkerThread*> inactiveThreads;
	std::queue<IWorkerAction*> pendingActions;
};