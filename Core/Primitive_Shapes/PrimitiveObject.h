#pragma once
#include <glad/glad.h>
#include <vector>

enum SHAPE_TYPE
{
	NONE = 0,
	CUBE,
	SPHERE,
	PLANE
};

class PrimitiveObject
{
public:
	PrimitiveObject(SHAPE_TYPE type = NONE)
	{
		_shapeType = type;
	}

	GLuint getVBO() const { return _vbo; };
	GLuint getVAO() const { return _vao; };
	GLuint getEBO() const { return _ebo; };
	std::vector<float>& getVertices() { return _vertices; };
	virtual void draw() = 0;

protected:
	std::vector<float> _vertices;
	GLuint _vao, _vbo, _ebo = 0;
	SHAPE_TYPE _shapeType;

};