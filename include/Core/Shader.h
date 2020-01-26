#pragma once

#include "Resource.h"

enum ShaderType
{
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER,
    GEOMETRY = GL_GEOMETRY_SHADER,
    COMPUTE = GL_COMPUTE_SHADER,
    TESS_CONTROL = GL_TESS_CONTROL_SHADER,
    TESS_EVAL = GL_TESS_EVALUATION_SHADER
};

class Shader : Resource<Shader>
{
public:
    Shader() = default;
	Shader(int id);
    Shader(int id, std::string name, std::map<std::string, int>& locations);
    ~Shader() = default;

    int getResourceID();

    ResourceType getResourceType();

    Shader& operator=(const Shader&);

	int programID = -1;


	std::map<std::string, int> _uniformLocations{};
	std::string _shaderName="";

    

};

