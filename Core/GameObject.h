#pragma once
#include "Model.h"
#include <glm\common.hpp>
#include "Shader.h"

class GameObject
{
public:
	GameObject() {

	}
	~GameObject() {

	}

	GameObject(Model& model)
	{
		_model = &model;
	}

	void setModel(Model& model)
	{
		_model = &model;
	}

	void setPosition(const glm::vec3 pos)
	{
		_position = pos;
	}

	void setScale(const glm::vec3 scale)
	{
		_scale = scale;
	}


	glm::vec3 getPosition()
	{
		return _position;
	}

	glm::vec3 getScale()
	{
		return _scale;
	}

	void Draw(Shader shader)
	{
		_model->Draw(shader);
	}


private:
	Model* _model = NULL;
	glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 _scale = { 0.2f, 0.2f, 0.2f };
};

