#pragma once
#include "glfw3.h"
#include "Camera.h"
#include "../Managers/ModelManager.h"
#include <string>
#include "GameObject.h"
#include "System/Renderer.h"
#include "Lighting.h"
#include "floorGrid.h"
#include "Skybox.h"

class Scene
{
public:
	bool initScene(GLFWwindow& wnd, glm::vec2 screenInfo = glm::vec2(1024, 768));
	void loadResources();
	void run();
	void stop();
	void save();

	private:
	Camera _currentCamera;
	ModelManager _modelManager;
	TextureManager _textureManager;
	GLFWwindow* _window;

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
	bool firstMouse = true;

	void processInput(GLFWwindow* window);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	

};

