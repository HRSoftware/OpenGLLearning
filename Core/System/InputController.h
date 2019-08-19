#pragma once

#include "../Camera.h"
#include <glfw3.h>
class InputController
{

	public:

	InputController(GLFWwindow& window, Camera& camera)
	{
		_window = &window;
		_camera = &camera;
		firstMouse = true;
	}
	void processInput(GLFWwindow* window, float deltaTime);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	void changeCamera(Camera& newCamera)
	{
		_camera = &newCamera;
	}

	private:
		 GLFWwindow* _window;
		 Camera* _camera;
		 bool firstMouse; 
		 float lastX, lastY;

};
