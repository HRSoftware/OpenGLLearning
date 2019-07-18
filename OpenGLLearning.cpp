#pragma once

#include <iostream>
#include <filesystem>

#include "glad/glad.h"
#include "KHR/khrplatform.h"
#include "glfw3.h"


#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
//#include "Bullet/btBulletDynamicsCommon.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Core/Skybox.h"
#include "Callbacks\Callbacks.h"
#include "Core\Input.h"
#include "Core\Shader.h"
#include "Core\Camera.h"
#include "Core\Model.h"
#include "Core\GameObject.h"
#include "Managers\ModelManager.h"
#include "Core/LoadTextures.h"

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(char const* path);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));


float deltaTime = 0.0f;
float lastFrame = 0.0f;

const int HEIGHT = 720;
const int WIDTH = 1024;


float lastX = WIDTH / 2.f;
float lastY = HEIGHT / 2.f;

bool firstMouse = true;
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

float specStr = 0.5f;



int main(int argc, char* argv[]) {


	camera.Position = glm::vec3(0.1f, 0.1f, 2.f);
	// Load GLFW and Create a Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);



	GLFWwindow* mWindow = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", nullptr, nullptr);

	// Check for Valid Context
	if (mWindow == nullptr) {
		fprintf(stderr, "Failed to Create OpenGL Context");
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(mWindow);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init. OpenGL Context" << std::endl;
		return -1;
	}
	// Create Context and Load OpenGL Functions


	fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

	glEnable(GL_DEPTH_TEST);
	glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback); //resize callback
	glfwSetCursorPosCallback(mWindow, mouse_callback);
	glfwSetScrollCallback(mWindow, scroll_callback);

	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	ModelManager modManager;
	modManager.loadModeltoMemory("House/house_obj.obj", "Building1");
	//modManager.loadModeltoMemory("Buildings/Building_A01.obj", "Building2");
	GameObject Building1(*modManager.getModelByName("Building1"));
	//GameObject Building2(*modManager.getModelByName("Building2"));

	Building1.setPosition({ 0.1f, 0.75f, -0.2f });
	Building1.setScale({ 0.005f, 0.005f, 0.005f });
	//Building2.setPosition({ 0.5f, 0.1f, -0.9f });

	Shader basicShader("./Shaders/basicShader.vert", "./Shaders/basicShader.frag");
	Shader lightShader("./Shaders/basicLighting.vert", "./Shaders/basicLighting.frag");
	Shader materialShader("./Shaders/materialShader.vert", "./Shaders/materialShader.frag");
	Shader modelShader("./Shaders/model_loadingShader.vert", "./Shaders/model_loadingShader.frag");
	Shader skyboxShader("./Shaders/core/skyboxShader.vert", "./Shaders/core/skyboxShader.frag");
	Shader skyboxShaderReflect("./Shaders/core/skyboxShaderReflect.vert", "./Shaders/core/skyboxShaderReflect.frag");
	
	lightShader.setVec3("lightPos", lightPos);

	//int vertexColourLocation = glGetUniformLocation(basicShader.ID, "ourColor");
	//int vertexPositionLocation = glGetUniformLocation(basicShader.ID, "ourPosition");
	//std::cout << "Uniform ID = " << vertexColourLocation << std::endl;

	materialShader.use();
	//materialShader.setVec3("material.ambient", 0.0f, 0.5f, 0.31f);
	materialShader.setInt("material.diffuse", 0.1f);
	materialShader.setInt("material.specular", 1.0f);
	materialShader.setFloat("material.shininess", 32.0f);

	materialShader.setVec3("lightPos", 1.2f, 1.0f, 2.0f);
	materialShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	materialShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	materialShader.setVec3("light.specular", 1.f, 1.f, 1.f);

	/*modelShader.use();
	modelShader.setVec3("lightPos", lightPos);*/
	
	Shader currentShader = materialShader;



	Skybox skybox;
	skybox.setShader(skyboxShader);

	std::vector<float> skyboxVertices = {
		// positions          
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	/*for_each(skyboxVertices.begin(), skyboxVertices.end(), [](float& num)
	{
		num = num / 100;
	});*/

	Skybox smallSkybox;
	smallSkybox.setVerticies(skyboxVertices);
	smallSkybox.setShader(skyboxShaderReflect);
	smallSkybox.enableNormals = true;

	float TimeCalc;
	// Rendering Loop
	while (glfwWindowShouldClose(mWindow) == false)
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(mWindow);

		glClearColor(0.25f, 0.25f, 0.5f, 1.0f);		// Background Fill Color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		currentShader.use();
		
		lightPos = glm::vec3(sin(currentFrame), lightPos.y, lightPos.z);
		glm::mat4 projection = glm::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 currentModelMat = glm::mat4(1.0f);

		

		currentShader.setMat4("projection", projection);
		currentShader.setVec3("lightPos", lightPos);
		currentShader.setMat4("view", view);

		currentModelMat = glm::translate(currentModelMat, Building1.getPosition());
		currentModelMat = glm::scale(currentModelMat, Building1.getScale());
		currentShader.setMat4("model", currentModelMat);
		Building1.Draw(currentShader);

		currentModelMat = glm::mat4(1.f);
		
		skyboxShaderReflect.use();
		skyboxShaderReflect.setMat4("model", currentModelMat);
		smallSkybox.Draw(camera.GetViewMatrix(), projection);

		//skybox.Draw(camera.GetViewMatrix(), projection);


		glfwPollEvents();
		glfwSwapBuffers(mWindow);		// Flip Buffers and Draw
	}




	glfwTerminate();
	return EXIT_SUCCESS;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.MovementSpeed = camera.boostSpeed;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		camera.MovementSpeed = camera.normalSpeed;



}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}


