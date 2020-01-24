#pragma once

#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
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
    Shader();
	Shader(int id);
    Shader(int id, std::string name, std::map<std::string, int>& _uniformLocations);
    ~Shader();

    int getResourceID();

    ResourceType getResourceType();

    Shader& operator=(Shader other);

	int programID = -1;


	std::map<std::string, int> _uniformLocations;
	std::string _shaderName;
    

};

