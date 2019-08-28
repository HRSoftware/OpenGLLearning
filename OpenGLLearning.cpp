#pragma once

#include <iostream>
#include <filesystem>
#include "Core/Scene.h"







//#include "Bullet/btBulletDynamicsCommon.h"


#include "Core/LoadTextures.h"



//
//unsigned int loadTexture(char const* path);
//void renderQuad();




int main(int argc, char* argv[]) {

	GLFWwindow* window = glfwCreateWindow(1024, 768, "New layout", NULL, NULL);

	Scene newScene;
	newScene.initScene(*window);
	newScene.loadResources();
	newScene.run();


	
	glfwTerminate();
	return EXIT_SUCCESS;
}

