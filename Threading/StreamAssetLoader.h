#pragma once
//#include "IETThread.h"
#include <string>

#include "IWorkerAction.h"

class IExecutionEvent;

// Converted to IWorkerAction, now it's a Job.
class StreamAssetLoader : public IWorkerAction
{
private:
	typedef std::string String;
public:
	StreamAssetLoader(String path, IExecutionEvent* executionEvent);
	~StreamAssetLoader();

private:
	void onStartTask() override;

	String path;
	IExecutionEvent* execEvent;
};

