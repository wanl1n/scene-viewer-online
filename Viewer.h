#pragma once
#include "MainInclude.hpp"
#include "Camera/SceneCamera.hpp"
#include "Shaders/Shader.hpp"

class Viewer
{
public:
	static const float TIME_PER_FRAME;
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;
	cameras::SceneCamera* camera;
	shaders::Shader* shader;

	static Viewer* getInstance();
	static Viewer* sharedInstance;
	float getFPS() const;

	Viewer(const Viewer&) = delete;
	Viewer(Viewer&&) = delete;
	Viewer& operator=(const Viewer&) = delete;
	Viewer& operator=(Viewer&&) = delete;

	Viewer();
	void run();

private:
	GLFWwindow* window;
	float fps = 0.0f;

	void render();
	void processEvents();
	void update(float elapsedTime);
};

