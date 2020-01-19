#pragma once

#include "CurrentSceneStats.h"
#include <string>
#include "../Managers/ModelManager.h"
#include "Lighting.h"
#include "floorGrid.h"
#include "Skybox.h"
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
	Scene(const shared_ptr<struct GLFWwindow*>& wnd, Renderer* renderer) : resourceManager(resourceCache)
	{
        SceneStats::window = wnd;
        SceneStats::currentCamera = std::make_shared<Camera>(Camera({ 1.f, 1.f, 1.f }, { 0.f, 1.f, 0.f }));
      _renderer = renderer;
	}
	bool initScene(Camera cam = Camera({ 1.f, 1.f, 1.f }, {0.f, 1.f, 0.f}));
	void moreHouses();
	void loadResources();
	void run();
	void stop();
	void save();



	private:
	GLFWwindow* _window;
	InputController* _inputController;
	Renderer* _renderer;

	std::map<string, Shader> _shaderVec;
	std::map<string, GameObject> _GOVec;
	RenderDetails _renderDetails;

    ResourceCache resourceCache;
    ResourceManager resourceManager;
 
	DirectionalLight _sunLight;
	FloorGrid _floorGrid;
	Skybox skybox;

	float lastFrame = 0.0f;

	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

};

static void processInput(GLFWwindow* _window, float deltaTime)
{
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, true);

	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		SceneStats::currentCamera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
        SceneStats::currentCamera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
        SceneStats::currentCamera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
        SceneStats::currentCamera->ProcessKeyboard(RIGHT, deltaTime);



	if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        SceneStats::currentCamera->MovementSpeed = SceneStats::currentCamera->boostSpeed;

	if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        SceneStats::currentCamera->MovementSpeed = SceneStats::currentCamera->normalSpeed;
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	
	
	if (firstMouse)
	{
        SceneStats::lastX = xpos;
        SceneStats::lastY = ypos;
		SceneStats::firstMouse = false;
	}

	float xoffset = xpos - SceneStats::lastX;
	float yoffset = SceneStats::lastY - ypos; // reversed since y-coordinates go from bottom to top

    SceneStats::lastX = xpos;
    SceneStats::lastY = ypos;

    SceneStats::currentCamera->ProcessMouseMovement(xoffset, yoffset);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    SceneStats::currentCamera->ProcessMouseScroll(yoffset);
}

