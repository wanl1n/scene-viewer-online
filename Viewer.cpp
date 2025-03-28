#include "Viewer.h"

#include <optional>

// ImGUI
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Model/ModelManager.h"
#include "Scene/SceneManager.h"

const float FRAME_RATE = 60.0f;
const float Viewer::TIME_PER_FRAME = 1.0f/FRAME_RATE;
Viewer* Viewer::sharedInstance = NULL;


// Keyboard Input Function -- Updates the Player object states.
void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mod) {

	// Switching Camera Controls
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {}

	// Movement Controls
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		Viewer::getInstance()->camera->setMovingForward(true);
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		Viewer::getInstance()->camera->setMovingBackward(true);
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		Viewer::getInstance()->camera->setMovingLeft(true);
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		Viewer::getInstance()->camera->setMovingRight(true);
	}
	if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		// Reset the flags.
		Viewer::getInstance()->camera->setMovingForward(false);
	}
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		// Reset the flags.
		Viewer::getInstance()->camera->setMovingBackward(false);
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		// Reset the flags.
		Viewer::getInstance()->camera->setMovingLeft(false);
	}
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		// Reset the flags.
		Viewer::getInstance()->camera->setMovingRight(false);
	}
}

Viewer::Viewer() {
	// Initialize the library
	if (glfwInit())
	{
		// Create a windowed mode window and its OpenGL context
		window = glfwCreateWindow((int)WINDOW_WIDTH, (int)WINDOW_HEIGHT, 
								"GDPARCM Scene Viewer - QUE YOUNG", 
								NULL, NULL);
		if (!window)
			glfwTerminate();
		else
		{
			// Make the window's context current
			glfwMakeContextCurrent(window);
			gladLoadGL();

			// Getting User Key Input
			glfwSetKeyCallback(window, Key_Callback);

			// Create Viewport
			glViewport(0, 0, (int)WINDOW_WIDTH, (int)WINDOW_HEIGHT);

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 330");

			this->camera = new cameras::SceneCamera(60.f, WINDOW_HEIGHT, WINDOW_WIDTH, 0.1f, 1000.f,
				glm::vec3(0.f, 0.f, -10.f),
				glm::vec3(0.f, 1.f, 0.f),
				glm::vec3(0.f, 0.f, -5.f));

			// Creating the shader for the objects
			this->shader = new shaders::Shader("Shaders/sample.vert", "Shaders/sample.frag");
			glEnable(GL_BLEND);                                             // Enable Blending
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    //Choose a Blending Function

			sharedInstance = this;

			ModelManager::getInstance()->initialize();
			SceneManager::getInstance()->initialize();
		}
	}
}

void Viewer::run() {
	/*sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;*/

	while (!glfwWindowShouldClose(window))
	{
		// User Interface
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the depth buffer as well

		/*currentTime = clock.getElapsedTime();
		float deltaTime = currentTime.asSeconds() - previousTime.asSeconds();
		this->fps = floor(1.0f / deltaTime);*/

		update(1);
		render();
		processEvents();

		//previousTime = currentTime;
	}

	/* Loop until the user closes the window */
	

}

void Viewer::processEvents()
{
	/* Poll for and process events */
	glfwPollEvents();

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		this->window.close();
	}

	if (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>())
		{
			this->window.close();
		}
		else {
			GameObjectManager::getInstance()->processInput(event.value());
		}
	}
	ScreenManager::getInstance()->processInput();*/
}

void Viewer::update(float elapsedTime) {
	ModelManager::getInstance()->update(elapsedTime);
	SceneManager::getInstance()->update(elapsedTime);

	this->camera->update(this->shader->getShaderProgram());
}

void Viewer::render() {

	// ---------------------- RENDERING OBJECTS ------------------------- //
	// Reset the shader program for the objects.
	glUseProgram(*this->shader->getShaderProgram());

	// Draw the environment
	ModelManager::getInstance()->draw(shader->getShaderProgram(), true);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	/* Swap front and back buffers */
	glfwSwapBuffers(window);
}

Viewer* Viewer::getInstance()
{
	return sharedInstance;
}

float Viewer::getFPS() const
{
	return this->fps;
}