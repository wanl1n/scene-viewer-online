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
#include "Camera/OrthoCamera.hpp"

// Lights
#include "Light/Light.hpp"
#include "Light/DirectionLight.hpp"
#include "Light/PointLight.hpp"

// Shaders
#include "Shaders/Shader.hpp"

// Player
#include "Player/Player.hpp"

// ImGUI
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Model/ModelManager.h"
#include "Networking/Client.h"
#include "Networking/Server.h"
#include "Scene/SceneManager.h"

// Namespaces of the other classes
using namespace models;
using namespace cameras;
using namespace lights;
using namespace shaders;
using namespace players;

// Global Variables
float width = 600.f;
float height = 600.f;
float speed = 1.5f;

// Player contains the states of the player tank.
Player player = Player(NULL);

// Camera global variables
float radius = 50.f;
float pitch = 0.f; // initial pitch is 0 degrees (positive x axis)
float yaw = 270.f; // initial yaw is 270 degrees (-90 degrees of positive x axis; negative z axis)
float yrot = 90.f;

// Mouse variables
double prev_xpos = width / 2;
double prev_ypos = height / 2;

// Keyboard Input Function -- Updates the Player object states.
void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
    // Movement Controls
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        // Depending on what view is being used, set true forward/up.
        if (player.isDrivingTank()) player.setMovingForward(true);
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        // Depending on what view is being used, set true backward/down.
        if (player.isDrivingTank()) player.setMovingBackward(true);
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        // Depending on what view is being used, set true left.
        if (player.isDrivingTank()) player.setTurningLeft(true);
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        // Depending on what view is being used, set true right.
        if (player.isDrivingTank()) player.setTurningRight(true);
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

    // Getting User Key Input
    glfwSetKeyCallback(window, Key_Callback);

    // Create Viewport
    glViewport(0, 0, (int)width, (int)height);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330"); 

    // Moon / Direction Light model
    Model lightModel = Model("3D/Moon.obj", "", "", "Moon",
                            glm::vec3(-100.f, 1000.f, -30.f), // pos
                            glm::vec3(10.f),                // scale
                            glm::vec3(0.f),                 // rotate
                            glm::vec4(238.f / 255.f, 228.f / 255.f, 170.f / 255.f, 1.f)); // color
	ModelManager::getInstance()->initialize();
    SceneManager::getInstance()->initialize();
    //std::vector<Model*> environment = ModelManager::getInstance()->getRandomModels();

    // Creating the shader for the objects
    Shader litShader = Shader("Shaders/sample.vert", "Shaders/sample.frag");

    // Creating the skybox
    Skybox skybox = Skybox();

    // Light Sources
    // Direction Light: From the Moon 
    DirectionLight moonlight = DirectionLight(lightModel.getPosition(), glm::vec3(0.f), lightModel.getColor(), 1.0f);
    // Spot Light: Position is at front of tank (Class name is point light but it was extended to Spot Light as a bonus)
    PointLight headlights = PointLight(glm::vec3(0), glm::vec3(1.f), 200.f);

    // Cameras
    PerspectiveCamera camera = PerspectiveCamera(60.f, height, width, 0.1f, 1000.f,
                                                                        glm::vec3(0.f, 100.f, -10.f), 
                                                                        glm::vec3(0.f, 1.f, 0.f), 
                                                                        glm::vec3(0.f, 0.f, -5.f));
    // Set the initial camera to the third person perspective camera
    MyCamera* mainCamera = &camera;

    // Enable Blending
    glEnable(GL_BLEND);
    //Choose a Blending Function
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Start Server
    Server server;
    server.start();

    // Start Client
    std::vector<Client> clients;
    clients.emplace_back(1);
    clients.emplace_back(2);

    // Run all Clients
    for (auto& client : clients)
    {
        client.runClient();
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the depth buffer as well


        // Check if clients have loaded their scenes
        for (auto& client : clients)
        {
	        if (client.isSceneLoaded())
	        {
                client.createModels();
	        }
        }

        // ----------------------- UPDATING VALUES -------------------------- //        
        // Set the current camera to the third person perspective camera to drive the tank.
        mainCamera = &camera;

        // First get the mouse position
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Calculate how much the mouse moved in x direction
        double x_mod = xpos - prev_xpos;
        // Calculate how much the mouse moved in y direction
        double y_mod = prev_ypos - ypos; 

        // Save the current mouse position as the previous for the next frame.
        prev_xpos = xpos;
        prev_ypos = ypos;

        yaw = glm::radians((xpos / (width / 2)) * -90);
        pitch = glm::radians((ypos / (height / 2)) * -90);
        // Calculate the rotation of the camera based on the mouse position.
        camera.calcMouseRotate(pitch, yaw);

        // Set the color of the lights to white since its not in night vision mode.
        headlights.setColor(glm::vec3(1, 1, 1));
        moonlight.setColor(glm::vec3(1, 1, 1));

        // If Main Camera exists, update the projection and view matrix
        if (mainCamera != NULL) mainCamera->updateShaderViewProj(litShader.getShaderProgram());

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
		SceneManager::getInstance()->processInput();

        ModelManager::getInstance()->update(1);
        SceneManager::getInstance()->update(1);
    	// ---------------------- RENDERING OBJECTS ------------------------- //
        // First draw the skybox
        skybox.draw(mainCamera->getViewMatrix(), mainCamera->getProjMatrix(), player.isUsingBinoculars());

        // Reset the shader program for the objects.
        glUseProgram(*litShader.getShaderProgram());

        // Applying the lighting to the shader program for the objects.
        moonlight.applyUniqueValuesToShader(litShader.getShaderProgram());
        headlights.applyUniqueValuesToShader(litShader.getShaderProgram());

        // Draw the environment
		ModelManager::getInstance()->draw(litShader.getShaderProgram(), true);

        for (auto& client : clients) 
        {
            for (Model model : client.getModels()) 
            {
                model.draw(litShader.getShaderProgram(), true);
            }
        }

        // Reset lighting to render lightModel unaffected by light
        headlights.turnOff();
        moonlight.turnOff();

        for (auto& client : clients) 
        {
            client.RenderUI();
        }

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