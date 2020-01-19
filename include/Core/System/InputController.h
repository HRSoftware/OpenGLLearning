#pragma once

#include "../CurrentSceneStats.h"

inline bool firstMouse = true;
class InputController
{
	public:
	InputController(){}
	InputController(GLFWwindow& window, Camera* cam = nullptr)
	{
        firstMouse = true;
	}

	static float lastX, lastY;
	private:
		 //bool firstMouse; 
		 
		 

};
//static void processInput(GLFWwindow* _window, float deltaTime)
//{
//	
//	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(_window, true);
//
//	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
//		InputController::_camera->ProcessKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
//		InputController::_camera->ProcessKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
//		InputController::_camera->ProcessKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
//		InputController::_camera->ProcessKeyboard(RIGHT, deltaTime);
//
//
//
//	if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//		InputController::_camera->MovementSpeed = InputController::_camera->boostSpeed;
//
//	if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
//		InputController::_camera->MovementSpeed = InputController::_camera->normalSpeed;
//}
//
//static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	float lastX = InputController::lastX;
//	float lastY = InputController::lastY;
//	static bool firstMouse;
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	InputController::lastX = xpos;
//	InputController::lastY = ypos;
//
//	InputController::_camera->ProcessMouseMovement(xoffset, yoffset);
//}
//
//static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	InputController::_camera->ProcessMouseScroll(yoffset);
//}
