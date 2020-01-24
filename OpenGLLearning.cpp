#include "stdafx.h"
#pragma once

#include "include/Core/Scene.h"
//#include "Bullet/btBulletDynamicsCommon.h"
#include "include/Core/LoadTextures.h"





int main(int argc, char* argv[]) {

    int width = 1920;
    int height = 1080;
	glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	GLFWwindow* _window = glfwCreateWindow(width, height, "New layout", NULL, NULL);
   Renderer _renderer;

	// Check for Valid Context
	if (_window == nullptr) {
		fprintf(stderr, "Failed to Create OpenGL Context");
		return false;
	} 

	glfwMakeContextCurrent(_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init. OpenGL Context" << std::endl;
		return false;
	}

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
	fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	
	Scene newScene(*_window, &_renderer);
	newScene.initScene();
	newScene.loadResources();



	newScene.run();

	glfwTerminate();
	return EXIT_SUCCESS;
}

