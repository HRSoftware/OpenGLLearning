#pragma once
#include "Model.h"
#include <glm\common.hpp>
#include "Shader.h"
#include "RenderDetails.h"

#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"


class GameObject
{
public:
	GameObject(Model& model, Shader shdr, RenderDetails rd) : _model(&model), _camera(&rd._cam) {
		_height = rd._height;
		_width = rd._width;
		_modelShader = shdr;
	}
	~GameObject() {

	}

	GameObject(Model& model)
	{
		_model = &model;
	}

	void setModel(Model& model, Camera& cam, int height = 1920, int width = 1080)
	{
		_height = height;
		_width = width;
		_model = &model;
	}

	void setPosition(const glm::vec3 pos)
	{
		_position = pos;
	}

	void moveBy(const glm::vec3 pos)
	{
		_position =+ pos;
	}
	
	void setScale(const glm::vec3 scale)
	{
		_scale = scale;
	}

	void scaleBy(const glm::vec3 scale)
	{
		_scale =+ scale;
	}

	void setAngle(float angle, const glm::vec3 axis)
	{
		_orientation = glm::angleAxis(angle, glm::normalize(axis));
	}

	void rotateBy(float angle, const glm::vec3 axis)
	{
		_orientation = glm::angleAxis(angle, glm::normalize(axis)) * _orientation;
	}



	glm::vec3 getPosition()
	{
		return _position;
	}

	glm::vec3 getScale()
	{
		return _scale;
	}

	void Draw()
	{
		glm::mat4 currentModelMat = glm::mat4(1.0f);
		glm::mat4 projection = glm::perspective(_camera->Zoom, (float)_width / (float)_height, 0.01f, 1000.f);
		currentModelMat = glm::scale(currentModelMat, _scale);
		currentModelMat = glm::mat4_cast(_orientation) * currentModelMat;
		currentModelMat = glm::translate(currentModelMat, _position);
		


		_modelShader.use();
		_modelShader.setMat4("projection", projection);
		//_modelShader.setVec3("lightPos", lightPos);
		_modelShader.setMat4("view", _camera->GetViewMatrix());
		_modelShader.setMat4("model", currentModelMat);
		_model->Draw(_modelShader);
	}


private:
	Model* _model;
	glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 _scale = { 0.2f, 0.2f, 0.2f };
	glm::quat _orientation = {1.f, 0.f, 0.f, 0.f};

	Shader _modelShader;
	Camera* _camera;
	int _height, _width;
};

