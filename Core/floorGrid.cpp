#pragma once
#include "floorGrid.h"
#include <stb\stb_image.h>


void FloorGrid::setShader(Shader shader) {
	_gridShader = shader;
}

void FloorGrid::setUpBuffers() {

	glGenVertexArrays(1, &gridVAO);
	glGenBuffers(1, &gridVBO);
	glGenBuffers(1, &gridEBO);

	glBindVertexArray(gridVAO);

	glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
	glBufferData(GL_ARRAY_BUFFER, _gridVertices.size() * sizeof(GLfloat), _gridVertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gridEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat) , indices.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),  (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}

void FloorGrid::Draw(bool bTextured)
{
	Draw(_gridShader, bTextured);
}

void FloorGrid::Draw(Shader shdr, bool bTextured)
{
	glm::mat4 projection = glm::perspective(_camera->Zoom, (float)_width / (float)_height, 0.01f, 1000.f);

	shdr.use();
	shdr.setInt("texture_diffuse1", gridTextureID);
	shdr.setMat4("projection", projection);
	if(shdr.checkAttributeExist("viewPos"))
		shdr.setVec3("viewPos", _camera->Position);
	shdr.setMat4("view", _camera->GetViewMatrix());
	shdr.setMat4("model", glm::mat4(1.f));

	if(bTextured)
		glBindTexture(GL_TEXTURE_2D, gridTextureID);

	glBindVertexArray(gridVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);

}

void FloorGrid::loadTextures()
{
	glGenTextures(1, &gridTextureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(_gridTexture, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, gridTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << _gridTexture << std::endl;
	}

	stbi_image_free(data);
}

	
	


