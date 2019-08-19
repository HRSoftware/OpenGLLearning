#pragma once
#include "InputController.h"

void InputController::processInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, true);

	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		_camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		_camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		_camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		_camera->ProcessKeyboard(RIGHT, deltaTime);



	if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		_camera->MovementSpeed = _camera->boostSpeed;

	if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		_camera->MovementSpeed = _camera->normalSpeed;
}

void InputController::mouse_callback(GLFWwindow* window, double xpos, double ypos)
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

	_camera->ProcessMouseMovement(xoffset, yoffset);
}

void InputController::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	_camera->ProcessMouseScroll(yoffset);
}

