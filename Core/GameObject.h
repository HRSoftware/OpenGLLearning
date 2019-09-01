#pragma once
#include "Model.h"

#include "System/Renderer.h"

#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include <glm/gtc/bitfield.hpp>


class GameObject
{
public:
	GameObject(): _model(nullptr), _camera(nullptr), _height(0), _width(0), _ModelMatrix() {} ;
	GameObject(RenderDetails rd) : _model(nullptr), _camera(rd._cam), _height(0), _width(0), _ModelMatrix() { }

	GameObject(Model* model, const Shader& shdr, RenderDetails rd) : _model(model), _camera(rd._cam), _ModelMatrix()
	{
		_height = rd._screenHeight;
		_width = rd._screenWidth;
		_modelShader = shdr;
		_isModelMatrixOutdated = true;
	}

	~GameObject() {
		_isModelNULL = true;
	}

	GameObject(Model& model): _camera(nullptr), _height(0), _width(0), _ModelMatrix()
	{
		_model = &model;
		_isModelMatrixOutdated = true;
	}

	void setModel(Model& model, Camera& cam, int height = 1920, int width = 1080)
	{
		_height = height;
		_width = width;
		_model = &model;
		_isModelMatrixOutdated = true;
	}

	void setPosition( glm::vec3 pos)
	{
		_position = pos;
		_isModelMatrixOutdated = true;
	}

	void moveBy( glm::vec3 pos)
	{
		_position =+ pos;
		_isModelMatrixOutdated = true;
	}

	void moveXBy( float pos)
	{
		_position.x = _position.x + pos;
		_isModelMatrixOutdated = true;
	}

	void moveYBy( float pos)
	{
		_position.y = _position.y + pos;
		_isModelMatrixOutdated = true;
	}

	void moveZBy( float pos)
	{
		_position.z = _position.z + pos;
		_isModelMatrixOutdated = true;
	}
	
	void setScale(const glm::vec3 scale)
	{
		_scale = scale;
		_isModelMatrixOutdated = true;
	}

	void scaleBy(const glm::vec3 scale)
	{
		_scale =+ scale;
		_isModelMatrixOutdated = true;
	}

	void setAngle(float angle, const glm::vec3 axis)
	{
		_orientation = glm::angleAxis(angle, glm::normalize(axis));
		_isModelMatrixOutdated = true;
	}

	void rotateBy(float angle, const glm::vec3 axis)
	{
		_orientation = glm::angleAxis(angle, glm::normalize(axis)) * _orientation;
		_isModelMatrixOutdated = true;
	}

	glm::mat4 getModelMatrix()
	{
		if (_isModelMatrixOutdated)
			updateModelMatrix();

		return _ModelMatrix;
	}

	void updateModelMatrix()
	{
		glm::mat4 projection = glm::perspective(_camera->Zoom, (float)_width / (float)_height, 0.01f, 1000.f);

		_ModelMatrix = glm::mat4(1.f);
		_ModelMatrix = glm::scale(_ModelMatrix, _scale); //scale
		_ModelMatrix = glm::toMat4(_orientation) * _ModelMatrix; //rotation

		_ModelMatrix[3][0] = _position.x;   //translation
		_ModelMatrix[3][1] = _position.y;
		_ModelMatrix[3][2] = _position.z;

		_isModelMatrixOutdated = false;
	}

	glm::vec3 getPosition() const
	{
		return _position;
	}

	glm::vec3 getScale() const
	{
		return _scale;
	}

	virtual void Draw(Shader shdr, bool textured = true)
	{
		if (_isModelMatrixOutdated)
			updateModelMatrix();

		shdr.setMat4("projection", _camera->getProjectionMatrix());

		shdr.setMat4("view", _camera->GetViewMatrix());
		shdr.setVec3("viewPos", _camera->Position);

		shdr.setMat4("model", _ModelMatrix);
		_model->Draw(shdr, textured);
	}

	virtual void Draw(bool bTextured = true)
	{
		Draw(_modelShader, bTextured);
	}


	bool isModelNULL() { return _model == NULL; };

private:
	Model* _model;
	glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 _scale = { 1.f, 1.f, 1.f };
	glm::quat _orientation = {1.f, 0.f, 0.f, 0.f};
	bool _isModelNULL = false;
	Shader _modelShader;

	Camera* _camera;
	int _height, _width;
	glm::mat4 _ModelMatrix;
	bool _isModelMatrixOutdated = false;
};

