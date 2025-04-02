#pragma once
//#include "IETThread.h"
#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "IWorkerAction.h"

class IExecutionEvent;

// Converted to IWorkerAction, now it's a Job.
class ObjectLoader : public IWorkerAction
{
public:
	ObjectLoader(std::string strObjPath, const char* pathTex, 
				const char* pathNorm, std::string name,
				glm::vec3 pos = glm::vec3(0.f),
				glm::vec3 scale = glm::vec3(1.f),
				glm::vec3 rotate = glm::vec3(0.f),
				glm::vec4 color = glm::vec4(0.f));
	ObjectLoader(std::string&& objData, 
				const std::vector<uint8_t>& texData, 
				int texWidth, int texHeight);
	~ObjectLoader();

private:
	void onStartTask() override;

	//IExecutionEvent* execEvent;
	std::string strObjPath;
	const char* pathTex;
	const char* pathNorm;
	std::string name;
	glm::vec3 pos = glm::vec3(0.f);
	glm::vec3 scale = glm::vec3(1.f);
	glm::vec3 rotate = glm::vec3(0.f);
	glm::vec4 color = glm::vec4(0.f);
};