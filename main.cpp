// Include files
#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#include "MainInclude.hpp"

// Models
#include "Model/Model.hpp"
#include "Model/Skybox.hpp"

// Cameras
#include "Camera/MyCamera.hpp"
#include "Camera/PerspectiveCamera.hpp"

// Lights
#include "Light/DirectionLight.hpp"

// Shaders
#include "Shaders/Shader.hpp"

// Player
#include "Player/Player.hpp"

// ImGUI
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "FPSCounter/FPSCounter.h"
#include "Networking/Client.h"
#include "Networking/Server.h"

// Namespaces of the other classes
using namespace models;
using namespace cameras;
using namespace lights;
using namespace shaders;
using namespace players;

// Global Variables
float width = 1280.f;
float height = 720.f;

// Player contains the states of the player tank.
Player player = Player(NULL);

// Camera global variables
float pitch = 0.f; // initial pitch is 0 degrees (positive x axis)
float yaw = 270.f; // initial yaw is 270 degrees (-90 degrees of positive x axis; negative z axis)

// Mouse variables
double prev_xpos = width / 2;
double prev_ypos = height / 2;

// Keyboard Input Function -- Updates the Player object states.
void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
    // Movement Controls
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        // Depending on what view is being used, set true forward/up.
        player.setMovingForward(true);
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        // Depending on what view is being used, set true backward/down.
        player.setMovingBackward(true);
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        // Depending on what view is being used, set true left.
        player.setTurningLeft(true);
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        // Depending on what view is being used, set true right.
        player.setTurningRight(true);
    }
    if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
        // Reset the flags.
        player.setMovingForward(false);
    }
    if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
        // Reset the flags.
        player.setMovingBackward(false);
    }
    if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
        // Reset the flags.
        player.setTurningLeft(false);
    }
    if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
        // Reset the flags.
        player.setTurningRight(false);
    }
}

int main()
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit()) return -1;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow((int)width, (int)height, "GDPARCM Scene Viewer - QUE YOUNG", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    gladLoadGL();

    // Get the initial framebuffer size (this is the actual size of the window in pixels)
    int width_, height_;
    glfwGetFramebufferSize(window, &width_, &height_);

    // Getting User Key Input
    glfwSetKeyCallback(window, Key_Callback);

    // Create Viewport
    glViewport(0, 0, (int)width_, (int)height_);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330"); 

    // Creating the shader for the objects
    Shader litShader = Shader("Shaders/sample.vert", "Shaders/sample.frag");

    // Creating the skybox
    Skybox skybox = Skybox();

    // Light Sources
    DirectionLight moonlight = DirectionLight(glm::vec3(0, 1000, 0), glm::vec3(0.f), glm::vec3(1.0f), 1.0f);

    // Cameras
    PerspectiveCamera camera = PerspectiveCamera(60.f, height, width, 0.1f, 500.f,
                                                glm::vec3(0.f, 100.f, -10.f), 
                                                glm::vec3(0.f, 1.f, 0.f), 
                                                glm::vec3(0.f, 0.f, -5.f));
	// Set the initial camera to the third person perspective camera
    MyCamera* mainCamera = &camera;

    // Enable Blending
    glEnable(GL_BLEND);
    //Choose a Blending Function
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //// Scene and model managers
    //ModelManager::getInstance()->initialize();
    //SceneManager::getInstance()->initialize();

    // Start Server
    Server server;
    server.start();

    // Start Client
    std::vector<Client> clients;
    clients.emplace_back(0);
    clients.emplace_back(1);
    clients.emplace_back(2);
    clients.emplace_back(3);
    clients.emplace_back(4);

    // Run all Clients
    for (auto& client : clients)
    {
        client.start();
    }

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    FPSCounter fpsCounter;

    double prevTime = 0.0f;
    double currentTime = 0.0f;
    double deltaTime;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapInterval(1);

        currentTime = glfwGetTime();
    	deltaTime = currentTime - prevTime;
        prevTime = currentTime;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //double targetFrameTime = 1.0 / 60.0;

        //if (deltaTime < targetFrameTime)
        //{
        //    glfwWaitEventsTimeout(targetFrameTime - deltaTime);
        //}

        // Change background color (Deep Purple)
        glClearColor(0.2f, 0.0f, 0.5f, 1.0f);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the depth buffer as well

        // Check if clients have loaded their scenes
        /*for (auto& client : clients)
        {
	        if (client.isSceneLoaded())
	        {
                client.createModels();
	        }
        }*/

        // ----------------------- UPDATING VALUES -------------------------- //        
        // First get the mouse position
        glfwGetCursorPos(window, &xpos, &ypos);

        // Calculate how much the mouse moved in x and y direction
        double x_mod = xpos - prev_xpos;
        double y_mod = prev_ypos - ypos; 

        // Save the current mouse position as the previous for the next frame.
        prev_xpos = xpos;
        prev_ypos = ypos;

        // Sensitivity factor (adjustable)
        float sensitivity = 0.2f;

        // Accumulate yaw & pitch based on movement
        yaw += glm::radians(x_mod * sensitivity);
        pitch += glm::radians(y_mod * sensitivity);

        // Calculate the rotation of the camera based on the mouse position.
        camera.calcMouseRotate(pitch, -yaw);
        camera.updateShaderViewProj(litShader.getShaderProgram());

        // Update the Tank Movements
        if (player.isMovingForward()) { 
            camera.moveForward();
        }
        if (player.isMovingBackward()) { 
			camera.moveBackward();
        }
        if (player.isTurningRight()) { 
            camera.moveRight();
        }
        if (player.isTurningLeft()) { 
			camera.moveLeft();
        }
        ModelManager::getInstance()->update(1);
    	// ---------------------- RENDERING OBJECTS ------------------------- //
        // First draw the skybox
        skybox.draw(mainCamera->getViewMatrix(), mainCamera->getProjMatrix(), player.isUsingBinoculars());

        // Reset the shader program for the objects.
        glUseProgram(*litShader.getShaderProgram());

        // Applying the lighting to the shader program for the objects.
        moonlight.applyUniqueValuesToShader(litShader.getShaderProgram());

        // Draw the environment
        for (auto& client : clients) 
        {
            for (Model* model : client.getModels()) 
            {
                if (model->isActive())
					model->draw(litShader.getShaderProgram(), true);
            }
        }

        // Reset lighting to render lightModel unaffected by light
        moonlight.turnOff();

        for (auto& client : clients) 
        {
            client.RenderUI();
        }

        fpsCounter.update(deltaTime);

        // Render FPS counter
    	fpsCounter.draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}