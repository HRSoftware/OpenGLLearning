#pragma once

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

	unsigned int getVBO() const { return _vbo; };
	unsigned int getVAO() const { return _vao; };
	unsigned int getEBO() const { return _ebo; };
	std::vector<float>& getVertices() { return _vertices; };
	virtual void draw() = 0;

protected:
	std::vector<float> _vertices;
	unsigned int _vao, _vbo, _ebo = 0;
	SHAPE_TYPE _shapeType;

};