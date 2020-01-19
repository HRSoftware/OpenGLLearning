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
    GameObject();

    GameObject(FloorGrid floor) ;
	GameObject(const std::string& name, const Model& model);
	GameObject(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices);
	~GameObject();


    void setModel(const Model& model);
    void setName(const std::string& name);
	void setPosition(const glm::vec3 pos);
	void moveBy(glm::vec3 pos);
	void moveXBy(float pos);
	void moveYBy(float pos);
	void moveZBy(float pos);
	void setScale(const glm::vec3 scale);
	void scaleBy(const glm::vec3 scale);
	void setAngle(float angle, const glm::vec3 axis);
	void rotateBy(float angle, const glm::vec3 axis);
	void updateModelMatrix();

    [[nodiscard]] std::string getName() const;
    [[nodiscard]]glm::vec3 getPosition() const;
    [[nodiscard]]glm::vec3 getScale() const;
	glm::mat4 getModelMatrix();
    std::vector<Mesh> getMeshes() const;


    GameObject& operator= (const GameObject& gameObject)= default;

    protected:

    std::shared_ptr<Model> _model;

	private:
        std::string GOName;
	glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 _scale = { 1.f, 1.f, 1.f };
	glm::quat _orientation = {1.f, 0.f, 0.f, 0.f};
	bool _isModelNULL = false;

    glm::mat4 _modelMatrix = {};
	bool _isModelMatrixOutdated = false;
};


//struct GameObjectHandle : ResourceHandle<GameObject>
//{
//    GameObjectHandle(int id = -1, GameObject* ptr = nullptr, ResourceType resType = RT_GameObject) : ResourceHandle(id, ptr, RT_GameObject) {};
//    GameObjectHandle(const ResourceHandle& resHndl) : ResourceHandle(resHndl) {};
//};