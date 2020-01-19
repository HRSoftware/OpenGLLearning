
#include <utility>
#include "../../include/Core/GameObject.h"
#include "../../include/Helpers/GUIDAllocator.h"

GameObject::GameObject()
{
    _isModelNULL = true;
}

GameObject::GameObject(FloorGrid floor)
{
    _isModelNULL = false;
    GOName = floor.getName();
    _isModelMatrixOutdated = true;
}


GameObject::GameObject(const std::string& name, const Model& model)
{
    _isModelNULL = false;
    GOName = name;
    _model = std::make_shared<Model>(model);
    _isModelMatrixOutdated = true;
}

GameObject::GameObject(std::vector<Vertex> _vertices, std::vector<unsigned> _indices)
{
    _isModelMatrixOutdated = true;
    _model->meshes.push_back(Mesh(std::move(_vertices), std::move(_indices), true));
}

GameObject::~GameObject()
{
}

void GameObject::setModel(const Model& model)
{
    _model = std::make_shared<Model>(model);
    _isModelMatrixOutdated = true;
    _isModelNULL = false;
}

void GameObject::setName(const std::string& name)
{
    GOName = name;
}
std::string GameObject::getName() const
{
    return GOName;
}

void GameObject::setPosition(glm::vec3 pos)
{
    _position = pos;
    _isModelMatrixOutdated = true;
}

void GameObject::moveBy(glm::vec3 pos)
{
    _position = + pos;
    _isModelMatrixOutdated = true;
}

void GameObject::moveXBy(float pos)
{
    _position.x = _position.x + pos;
    _isModelMatrixOutdated = true;
}

void GameObject::moveYBy(float pos)
{
    _position.y = _position.y + pos;
    _isModelMatrixOutdated = true;
}

void GameObject::moveZBy(float pos)
{
    _position.z = _position.z + pos;
    _isModelMatrixOutdated = true;
}

void GameObject::setScale(const glm::vec3 scale)
{
    _scale = scale;
    _isModelMatrixOutdated = true;
}

void GameObject::scaleBy(const glm::vec3 scale)
{
    _scale = + scale;
    _isModelMatrixOutdated = true;
}

void GameObject::setAngle(float angle, const glm::vec3 axis)
{
    _orientation = glm::angleAxis(angle, glm::normalize(axis));
    _isModelMatrixOutdated = true;
}

void GameObject::rotateBy(float angle, const glm::vec3 axis)
{
    _orientation = glm::angleAxis(angle, glm::normalize(axis)) * _orientation;
    _isModelMatrixOutdated = true;
}

glm::mat4 GameObject::getModelMatrix()
{
    if ( _isModelMatrixOutdated )
        updateModelMatrix();

    return _modelMatrix;
}

void GameObject::updateModelMatrix()
{
    _modelMatrix = glm::mat4(1.f);
    _modelMatrix = glm::scale(_modelMatrix, _scale); //scale
    _modelMatrix = glm::toMat4(_orientation) * _modelMatrix; //rotation

    _modelMatrix[3][0] = _position.x; //translation
    _modelMatrix[3][1] = _position.y;
    _modelMatrix[3][2] = _position.z;

    _isModelMatrixOutdated = false;
}

glm::vec3 GameObject::getPosition() const
{
    return _position;
}

glm::vec3 GameObject::getScale() const
{
    return _scale;
}

std::vector<Mesh> GameObject::getMeshes() const
{
    return _model->meshes;
}
