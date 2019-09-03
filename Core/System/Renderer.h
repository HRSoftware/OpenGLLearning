#pragma once
#include "../Camera.h"
#include "../Mesh.h"
#include "../GameObject.h"


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
	Renderer(): _framebuffer(0), _currentCamera(nullptr) {}

	void setCamera(Camera& cam);

   void renderGameObject(GameObject* gameobj, Shader shader);
   void renderMesh(int VAO , int indiceSize, int framebuffer = 0);
   void setUpShader(vector<Texture>& textures, Shader shader, bool textured = true);
   void renderBatch(std::map<string, GameObject*>& renderBatch, Shader shader);


	private:
	int _framebuffer;
	Camera* _currentCamera;
	


};

