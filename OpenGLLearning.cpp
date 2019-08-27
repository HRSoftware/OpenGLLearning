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
#include "Core/Lighting.h"
#include "Core/Skybox.h"
#include "Callbacks\Callbacks.h"
#include "Core\Input.h"
#include "Core\Shader.h"
#include "Core\Camera.h"
#include "Core\Model.h"
#include "Core\GameObject.h"
#include "Managers\ModelManager.h"
#include "Core/LoadTextures.h"
#include "Core/floorGrid.h"
#include "Core/RenderDetails.h"
#include "Core/Lighting.h"
#include "Core/ShadowRender.h"
#include "Core/Primitive_Shapes/Cube.h"
#include "Core/s"


void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(char const* path);
void renderQuad();

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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	RenderDetails renderDetails(camera, HEIGHT, WIDTH);

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
	modManager.loadModeltoMemory("Old_House/Old House.obj", "Building3");


	Shader basicShader("basicShader");
	Shader shadowGenShader("shadowMapShader", true);
	Shader materialShader("materialShader");
	Shader skyboxShader("skyboxShader", true);
	Shader gridShader("gridShader", true);
	Shader debugDepthShader("debugDepth");
	Shader frameBufferShader("framebufferShader");
	Shader lightingShader("basicLighting");
	Shader newShadowRenderShader("modelLoadingShader", true);

	
	GameObject Building1(modManager.getModelByName("Building1"), newShadowRenderShader, renderDetails);
	GameObject Building2(modManager.getModelByName("Building1"), newShadowRenderShader, renderDetails);
	GameObject Building3(modManager.getModelByName("Building3"), newShadowRenderShader, renderDetails);

	Building1.setPosition({ 0.1f, 0.f, -0.2f });
	Building1.setScale({ 0.005f, 0.005f, 0.005f }); 
	
	Building2.setPosition({ 10.f, 0.f, 10.f });
	Building2.setScale({ 0.005f, 0.005f, 0.005f });
	Building2.setAngle(90, { 0.0, 1.f, 0.0f });


	Building3.setPosition({ 25.f, 0.f, 5.f });
	Building3.setScale({ 0.05f, 0.05f, 0.05f});

	DirectionalLight sunLight(glm::vec3(.2f, 0.2f, 0.2f ), 4.f, { 10.f, 15.f, 4.f });
	sunLight.setAmbient({ 0.2f, 0.2f, 0.2f });
	sunLight.setDiffuse({ 0.5f, 0.5f, 0.5f}); 
	sunLight.setSpecular({ 0.1f,0.1f, 0.1f });
	sunLight.setDirection({ -0.2f, -1.0f, -0.3f });



	newShadowRenderShader.setFloat("shininess", 10.0f);
	newShadowRenderShader.setVec3("light.position", sunLight.getPosition());
	newShadowRenderShader.setVec3("light.ambient", sunLight.getAmbient());
	newShadowRenderShader.setVec3("light.diffuse", sunLight.getDiffuse());
	newShadowRenderShader.setFloat("light.intensity", sunLight.getStrength());
	newShadowRenderShader.setVec3("light.specular", sunLight.getSpecular());

	lightingShader.setFloat("shininess", 10.f);
	lightingShader.setVec3("light.position", sunLight.getPosition());
	lightingShader.setVec3("light.ambient", sunLight.getAmbient());
	lightingShader.setVec3("light.diffuse", sunLight.getDiffuse());
	//lightingShader.setFloat("light.intensity", sunLight.getStrength());
	lightingShader.setVec3("light.specular", sunLight.getSpecular());
	
	Shader currentShader;

	FloorGrid grid(gridShader, renderDetails);

	Skybox skybox;
	skybox.setShader(skyboxShader);


	ShadowRender shadowRender(shadowGenShader);
	shadowRender.addLight(sunLight);

	std::vector<GameObject*> buildings = { };
	buildings.push_back(&grid);
	buildings.push_back(&Building1);
	buildings.push_back(&Building2);
	buildings.push_back(&Building2);

	Cube cube;

	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, WIDTH, HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	newShadowRenderShader.setInt("shadowMap", depthMap);
	// Rendering Loop
	while (glfwWindowShouldClose(mWindow) == false)
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(mWindow);

		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		float near_plane = 0.01f, far_plane = 1000.f;
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;
		// render scene from light's point of view
		newShadowRenderShader.use();
		newShadowRenderShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);

		
		//Building1.Draw(newShadowRenderShader);
		//Building2.Draw(newShadowRenderShader);
		//Building3.Draw(newShadowRenderShader);
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		
		//shadowRender.castShadows(buildings);



		

		glViewport(0, 0, WIDTH, HEIGHT);

		glClearColor(0.25f, 0.25f, 0.5f, 1.0f);		// Background Fill Color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glm::mat4 projection = glm::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.f);
		glm::mat4 view = camera.GetViewMatrix();

		if (glfwGetKey(mWindow, GLFW_KEY_T) == GLFW_PRESS)
			//sunLight.setPosition(camera.Position);
			camera.Position = sunLight.getPosition();

		if (glfwGetKey(mWindow, GLFW_KEY_R) == GLFW_PRESS)
			Building1.rotateBy(0.1f, { 0, 1, 0 });

		if (glfwGetKey(mWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
			Building2.moveXBy(0.1f);
		
		if (glfwGetKey(mWindow, GLFW_KEY_UP) == GLFW_PRESS)
			Building2.moveXBy(-0.1f);
		
		if (glfwGetKey(mWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
			Building2.moveZBy(0.1f);

		if (glfwGetKey(mWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
			Building2.moveZBy(-0.1f);
		
		Building1.Draw(newShadowRenderShader );
		Building2.Draw(lightingShader);
		Building3.Draw(newShadowRenderShader);
		grid.Draw();

		skybox.Draw(view, projection);

		glfwPollEvents();

		
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glViewport(0, 0, WIDTH / 2, HEIGHT/ 2);
		Building1.Draw(newShadowRenderShader, false);
		Building2.Draw();
		Building3.Draw(false);

		
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


