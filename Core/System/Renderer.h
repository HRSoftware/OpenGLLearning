#pragma once
#include <glad/glad.h>
#include "../Camera.h"
#include "../GameObject.h"

struct RenderDetails
{
	RenderDetails(Camera& cam, int screenHeight, int screenWidth): _cam(&cam)
	{
		_height = screenHeight;
		_width = screenWidth;
	}
	Camera* _cam;
	int _height, _width;
};

class Renderer
{
	public:
	Renderer(){}

	void setCamera(Camera& cam);
	void renderScene();


	private:
	GLuint _framebuffer;
	Camera* _currentCamera;
	std::vector<GameObject*> _renderables;
	std::vector<Shader*> _shaders;


};

