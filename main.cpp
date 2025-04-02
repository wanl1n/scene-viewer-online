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

    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		SceneManager::getInstance()->loadScene(0);
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        SceneManager::getInstance()->loadScene(1);
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        SceneManager::getInstance()->loadScene(2);
    }
    if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
        SceneManager::getInstance()->loadScene(3);
    }
    if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
        SceneManager::getInstance()->loadScene(4);
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

    // Creating the shader for the objects
    Shader litShader = Shader("Shaders/sample.vert", "Shaders/sample.frag");

    // Creating the skybox
    Skybox skybox = Skybox();

    // Light Sources
    DirectionLight moonlight = DirectionLight(lightModel.getPosition(), glm::vec3(0.f), lightModel.getColor(), 1.0f);

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

    // Scene and model managers
    ModelManager::getInstance()->initialize();
    SceneManager::getInstance()->initialize();

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
        client.runClient();
    }

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

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
        // First get the mouse position
        glfwGetCursorPos(window, &xpos, &ypos);

        // Calculate how much the mouse moved in x direction
        double x_mod = xpos - prev_xpos;
        // Calculate how much the mouse moved in y direction
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

        // Set the color of the lights to white since its not in night vision mode.
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