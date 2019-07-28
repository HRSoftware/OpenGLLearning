#pragma once
#include "Camera.h"


struct  RenderDetails
{
	 RenderDetails(Camera& cam, int screenHeight, int screenWidth): _cam(cam)
	 {
		 _height = screenHeight;
		 _width = screenWidth;
	 }
	 Camera& _cam;
	int _height, _width;
};
