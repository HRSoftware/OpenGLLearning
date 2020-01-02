
#include "../../include/Core/GameObject.h"



GameObject::GameObject(std::string name, Model model)
{
    GOName = name;
    _model = model;
    _isModelMatrixOutdated = true;
}

GameObject::GameObject(std::vector<Vertex> _vertices, std::vector<unsigned> _indices)
{
    _isModelMatrixOutdated = true;
    _model.meshes.push_back(Mesh(std::move(_vertices), std::move(_indices), true));
}

GameObject::~GameObject()
{
    _isModelNULL = true;
}

void GameObject::setModel(Model model)
{
    _model = model;
    _isModelMatrixOutdated = true;
}

void GameObject::setName(std::string name)
{
    GOName = name;
}
std::string GameObject::getName()
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

std::vector<Mesh>& GameObject::getMeshes()
{
    return _model.meshes;
}
