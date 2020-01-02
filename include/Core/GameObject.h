#pragma once

#include "floorGrid.h"
#include "Model.h"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include <glm/gtc/bitfield.hpp>
#include <utility>


class GameObject
{
public:
	GameObject()
	= default;

    GameObject(FloorGrid floor);
	GameObject(std::string name, Model model);
	GameObject(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices);
	~GameObject();


    void setModel(Model _model);
    void setName(std::string name);
	void setPosition(glm::vec3 pos);
	void moveBy(glm::vec3 pos);
	void moveXBy(float pos);
	void moveYBy(float pos);
	void moveZBy(float pos);
	void setScale(const glm::vec3 scale);
	void scaleBy(const glm::vec3 scale);
	void setAngle(float angle, const glm::vec3 axis);
	void rotateBy(float angle, const glm::vec3 axis);
	void updateModelMatrix();

	std::string getName();
	glm::vec3 getPosition() const;
	glm::vec3 getScale() const;
	glm::mat4 getModelMatrix();
	std::vector<Mesh>& getMeshes();

protected:

    Model _model;
	private:
        std::string GOName;
	glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 _scale = { 1.f, 1.f, 1.f };
	glm::quat _orientation = {1.f, 0.f, 0.f, 0.f};
	bool _isModelNULL = false;

    glm::mat4 _modelMatrix = {};
	bool _isModelMatrixOutdated = false;
};

