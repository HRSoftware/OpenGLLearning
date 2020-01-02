#pragma once

#include <vector>
#include "Shader.h"
#include "Mesh.h"

class FloorGrid
{
public:
	std::vector<Vertex> _vertices = {
        {{500.f,		0.0f,	 500.f}, {}, {250.f, 250.f}, {}, {}},
		{{500.f,		0.0f,	 -500.f}, {}, {250.f, 0.f}, {}, {}},
		{{-500.f,		0.0f,	 -500.f}, {}, {0.f, 0.f}, {}, {}},
		{{-500.f,		0.0f,	 500.f}, {}, {0.f, 250.f}, {}, {}} };
	
	
	GLuint VAO,VBO,EBO;
    int gridTextureID = 0;
	std::vector<unsigned int> _indices = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

	FloorGrid();
	FloorGrid(Shader shdr);
	~FloorGrid();
	
	std::string getName();
    Mesh getMesh();

	private:
        std::string name = "FloorGrid";
	void setUpBuffers();
	void loadTextures();
	Shader _gridShader;
	int _height, _width = 250;
    Mesh floorMesh;
    

	const char* _gridTexture = "Resources/Textures/Grid3.jpg";

};


#pragma once
