#pragma once

#include "Camera.h"
#include <string>
#include "../Managers/ModelManager.h"
#include "Lighting.h"
#include "floorGrid.h"
#include "Skybox.h"
#include "glfw3.h"
#include "System/InputController.h"


#include "System/Renderer.h"
#include "UI/UI.h"
#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"
#include "../Builders/MaterialBuilder.h"
#include "../Builders/ShaderBuilder.h"
#include "../Builders/GameObjectBuilder.h"
#include "../Builders/ModelBuilder.h"
#include "../Managers/ResourceMangager.h"

class Scene
{
public:
	Scene(GLFWwindow& wnd, Renderer* renderer) : _window(&wnd), resourceManager(resourceCache)
	{
      _renderer = renderer;
	}
	bool initScene(Camera cam = Camera({ 1.f, 1.f, 1.f }, {0.f, 1.f, 0.f}));
	void loadResources();
	void run();
	void stop();
	void save();
	Camera* getCurrentCamera();


	private:
	Camera _currentCamera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	GLFWwindow* _window;
	InputController* _inputController;
	Renderer* _renderer;

	std::map<string, Shader> _shaderVec;
	std::map<string, GameObject> _GOVec;
	RenderDetails _renderDetails;

    ResourceCache resourceCache;
    ResourceManager resourceManager;
    
	glm::vec2 _screenDimensions;

	DirectionalLight _sunLight;
	FloorGrid _floorGrid;
	Skybox skybox;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

   int _screenWidth = 0;
   int _screenHeight = 0;

	float lastX = 0;
	float lastY = 0;
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

