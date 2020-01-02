#pragma once
#include "../../include/Core/floorGrid.h"
#include "../../include/Managers/TextureManager.h"


FloorGrid::FloorGrid()
{
	FloorGrid::setUpBuffers();
    //gridTextureID = TextureManager::textureFromFile(_gridTexture);
}

FloorGrid::FloorGrid(Shader shdr): _gridShader(shdr)
{
	FloorGrid::setUpBuffers();
    //gridTextureID = TextureManager::textureFromFile(_gridTexture);
}

FloorGrid::~FloorGrid() {}

void FloorGrid::setUpBuffers() {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, (_vertices.size()) * sizeof(GLfloat), _vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLfloat) , _indices.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),  (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}

void FloorGrid::loadTextures()
{
   //gridTextureID = TextureManager::textureFromFile(_gridTexture);
}

std::string FloorGrid::getName()
{
    return name;
}

Mesh FloorGrid::getMesh()
{
    return floorMesh;
}

	
	


