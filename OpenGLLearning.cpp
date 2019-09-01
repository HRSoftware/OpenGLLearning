#pragma once

#include <iostream>
#include <filesystem>
#include "Core/Scene.h"
//#include "Bullet/btBulletDynamicsCommon.h"
#include "Core/LoadTextures.h"
//unsigned int loadTexture(char const* path);
//void renderQuad();

int main(int argc, char* argv[]) {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* _window = glfwCreateWindow(1024, 768, "New layout", NULL, NULL);

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

	fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	Scene newScene(*_window);
	newScene.initScene({ 1024, 768 });
	newScene.loadResources();


	newScene.run();

	glfwTerminate();
	return EXIT_SUCCESS;
}

