#pragma once
#include "../Camera.h"


struct RenderDetails
{
	RenderDetails(): _cam(nullptr), _screenHeight(0), _screenWidth(0)
	{
		
	}

	RenderDetails(Camera& cam, int screenHeight = 768, int screenWidth = 1024)
	{
		_cam = &cam;
		_screenHeight = screenHeight;
		_screenWidth = screenWidth;
	}
	Camera* _cam;
	int _screenHeight, _screenWidth;
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

