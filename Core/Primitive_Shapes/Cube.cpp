#include "Cube.h"
#include <glad/glad.h>

void Cube::setUpBuffers()
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertices.size(), &_vertices.front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void Cube::draw()
{
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

}

