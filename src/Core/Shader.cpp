
#include "../../include/Core/Shader.h"
#include <iostream>


Shader::Shader(): Resource<Shader>(-1, RT_Shader) {}

Shader::Shader(int id): Resource<Shader>(id, RT_Shader)
{
    programID = id;
}

Shader::~Shader() {}

int Shader::getResourceID()
{
    return resourceID;
}

ResourceType Shader::getResourceType()
{
    return resourceType;
}

Shader& Shader::operator=(Shader newShader)
{
    std::swap(_uniformLocations, newShader._uniformLocations);
    std::swap(_shaderName, newShader._shaderName);
    std::swap(programID, newShader.programID);
    return *this;
}

Shader::Shader(int id, std::string name, std::map<std::string, int>& uniformLocations) : Resource(id, RT_Shader)
{
    _shaderName = name;
    _uniformLocations = std::move(uniformLocations);
    programID = id;
}

