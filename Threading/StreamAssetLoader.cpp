#include "StreamAssetLoader.h"

#include <filesystem>
#include <iostream>
#include <random>

#include "IETThread.h"
//#include "../TextureManager.h"
#include "../Utils/StringUtils.h"
#include "IExecutionEvent.h"

StreamAssetLoader::StreamAssetLoader(String path, IExecutionEvent* executionEvent)
{
	this->path = path;
	this->execEvent = executionEvent;
}

StreamAssetLoader::~StreamAssetLoader()
{
	//std::cout << "Destroying stream asset loader. " << std::endl;
}

void StreamAssetLoader::onStartTask()
{
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		IETThread::sleep(18); // Add a bit of loading delay.

		String path = entry.path().generic_string();
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		//TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);
	}

	this->execEvent->onFinishedExecution();

	//delete after being done
	delete this;
}