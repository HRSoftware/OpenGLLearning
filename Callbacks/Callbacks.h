#pragma once
#include <glfw3.h>

inline void framebuffer_size_callback(GLFWwindow* window, int _width, int _height)
{
	glViewport(0, 0, _width, _height);
}


