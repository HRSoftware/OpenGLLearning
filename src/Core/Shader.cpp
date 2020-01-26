#include "stdafx.h"
#include "../../include/Core/Shader.h"


Shader::Shader(int id): Resource<Shader>(id, RT_Shader)
{
    programID = id;
}

Shader::Shader(int id, std::string name, std::map<std::string, int>& locations)
{
    _shaderName = name;
    _uniformLocations = std::move(locations);
    programID = id;
}


int Shader::getResourceID()
{
    return resourceID;
}

ResourceType Shader::getResourceType()
{
    return resourceType;
}

Shader& Shader::operator=(const Shader& newShader)
{
    _uniformLocations = newShader._uniformLocations;
    _shaderName = newShader._shaderName;
    programID = newShader.programID;
    return *this;
}

