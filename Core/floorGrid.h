#pragma once

#include <vector>
#include "Shader.h"

class FloorGrid 
{
public:
	FloorGrid() {
		setUpBuffers();
		loadTextures();
	}
	~FloorGrid(){}

	void setShader(Shader shader);
	void Draw();

private:

	void setUpBuffers();
	void loadTextures();
	Shader _gridShader;

	const char* _gridTexture = "./Resources/Textures/Grid3.jpg";


	std::vector<float> _gridVertices = {
				//pos						texcoords
		 500.f,		0.0f,	 500.f,		250.0f,		250.0f, // top right
		 500.f,		0.0f,	-500.f,		250.0f,		  0.0f, // bottom right
		-500.f,		0.0f,	-500.f,		  0.0f,		  0.0f, // bottom left
		-500.f,		0.0f,	 500.f,		  0.0f,		250.0f  // top left 
};
	std::vector<GLuint> indices = {
	   0, 1, 3, // first triangle
	   1, 2, 3  // second triangle
	};


	GLuint gridVAO, gridVBO, gridEBO, gridTextureID = 0;

};

#pragma once
