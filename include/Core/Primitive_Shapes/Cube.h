#pragma once
#include "PrimitiveObject.h"
#include <glad/glad.h>


class Cube : public PrimitiveObject
{
	public:
	Cube() : PrimitiveObject(CUBE)
	{
		_vertices = {
			// positions        // texture Coords
			-0.5f, -0.5f, -0.5f, 
			0.5f, -0.5f, -0.5f, 
			0.5f,  0.5f, -0.5f, 
			0.5f,  0.5f, -0.5f, 
			-0.5f,  0.5f, -0.5f, 
			-0.5f, -0.5f, -0.5f, 

			-0.5f, -0.5f,  0.5f, 
			0.5f, -0.5f,  0.5f, 
			0.5f,  0.5f,  0.5f, 
			0.5f,  0.5f,  0.5f, 
			-0.5f,  0.5f,  0.5f, 
			-0.5f, -0.5f,  0.5f, 

			-0.5f,  0.5f,  0.5f, 
			-0.5f,  0.5f, -0.5f, 
			-0.5f, -0.5f, -0.5f, 
			-0.5f, -0.5f, -0.5f, 
			-0.5f, -0.5f,  0.5f, 
			-0.5f,  0.5f,  0.5f, 

			0.5f,  0.5f,  0.5f, 
			0.5f,  0.5f, -0.5f, 
			0.5f, -0.5f, -0.5f, 
			0.5f, -0.5f, -0.5f, 
			0.5f, -0.5f,  0.5f, 
			0.5f,  0.5f,  0.5f, 

			-0.5f, -0.5f, -0.5f, 
			0.5f, -0.5f, -0.5f, 
			0.5f, -0.5f,  0.5f, 
			0.5f, -0.5f,  0.5f, 
			-0.5f, -0.5f,  0.5f, 
			-0.5f, -0.5f, -0.5f, 

			-0.5f,  0.5f, -0.5f, 
			0.5f,  0.5f, -0.5f, 
			0.5f,  0.5f,  0.5f, 
			0.5f,  0.5f,  0.5f, 
			-0.5f,  0.5f,  0.5f, 
			-0.5f,  0.5f, -0.5f, 
		};
		setUpBuffers();
	}

	void draw() override
    {
        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }

	private:
	void setUpBuffers()
    {
        glGenVertexArrays(1, &_vao);
        glGenBuffers(1, &_vbo);
        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertices.size(), &_vertices.front(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    }

};


