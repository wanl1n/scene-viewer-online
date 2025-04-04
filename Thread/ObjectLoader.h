#pragma once
#include "../Networking/Client.h"
#include "IETThread.h"

class ObjectLoader : public IETThread
{
public:
	Client* client;

	ObjectLoader(Client* client) {
		this->client = client;
	}
	~ObjectLoader() {
		this->client = nullptr;
	}

	void run() override
	{
		this->client->createModels();
		delete this;
	}
};

