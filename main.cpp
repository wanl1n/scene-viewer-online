// Include files
#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#include "MainInclude.hpp"
#include "Viewer.h"

int main()
{
	Viewer viewer;
	viewer.run();

	// Terminate GLFW
    glfwTerminate();
    return 0;
}