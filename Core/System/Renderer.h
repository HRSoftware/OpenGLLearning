#pragma once
#include "../Camera.h"


struct RenderDetails
{
	RenderDetails()
	{
		throw "Default RenderDetails Constrcutor used";
	}
	RenderDetails(Camera* cam = nullptr, int screenHeight = 768, int screenWidth = 1024): _cam(cam)
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
	int _framebuffer;
	Camera* _currentCamera;
	


};

