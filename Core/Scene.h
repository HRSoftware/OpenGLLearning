#pragma once

#include "Camera.h"
#include <string>
#include "../Managers/ModelManager.h"
#include "Lighting.h"
#include "floorGrid.h"
#include "Skybox.h"
#include "glfw3.h"
#include "System/InputController.h"


class Scene
{
public:
	Scene(GLFWwindow& wnd) : _currentCamera(Camera(glm::vec3(0.0f, 0.0f, 3.0f))), _window(&wnd)
	{
		_screenDimensions = { 1.f, 1.f };
	}
	bool initScene(glm::vec2 screenInfo = glm::vec2(1024, 768), Camera cam = Camera({ 1.f, 1.f, 1.f }, {0.f, 1.f, 0.f}));
	void loadResources();
	void run();
	void stop();
	void save();
	Camera* getCurrentCamera();


	private:
	Camera _currentCamera;
	ModelManager _modelManager;
	TextureManager _textureManager;
	GLFWwindow* _window;
	InputController* _inputController;

	std::map<string, Shader> _shaderVec;
	std::map<string, GameObject*> _GOVec;
	RenderDetails _renderDetails;

	glm::vec2 _screenDimensions;

	DirectionalLight _sunLight;
	FloorGrid _floorGrid;
	Skybox skybox;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	const int HEIGHT = 720;
	const int WIDTH = 1024;


	float lastX = WIDTH / 2.f;
	float lastY = HEIGHT / 2.f;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

};

static void processInput(GLFWwindow* _window, float deltaTime)
{

	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, true);

	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		InputController::_camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		InputController::_camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		InputController::_camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		InputController::_camera->ProcessKeyboard(RIGHT, deltaTime);



	if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		InputController::_camera->MovementSpeed = InputController::_camera->boostSpeed;

	if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		InputController::_camera->MovementSpeed = InputController::_camera->normalSpeed;
}

	static float lastX = 0;
	static float lastY = 0;
static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
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

	InputController::_camera->ProcessMouseMovement(xoffset, yoffset);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	InputController::_camera->ProcessMouseScroll(yoffset);
}

