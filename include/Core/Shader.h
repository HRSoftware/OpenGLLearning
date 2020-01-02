#pragma once

#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
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
	Shader(int id): Resource(id, RT_Shader) {}
    Shader(int id, std::string name, std::map<std::string, int>& _uniformLocations);
    ~Shader() {}
	void reloadShaderFromFile(const char* fileName, bool isCoreShader);

	unsigned int shaderID;

	void use()
	{
		glUseProgram(shaderID);
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) const;
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const;
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const;
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value) const;

	void setVec2(const std::string& name, float x, float y) const;
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) const;

	void setVec3(const std::string& name, float x, float y, float z) const;
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value) const;

	void setVec4(const std::string& name, float x, float y, float z, float w) const;
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat) const;
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat) const;
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat) const;

	bool checkAttributeExist(const std::string& name) const;

private:
	std::map<std::string, int> _uniformLocations;

	void findUniformLocations();
	GLint getLocation(const std::string& name) const;
	std::string _shaderName;

};

struct ShaderHandle : ResourceHandle<Shader>
{
public:
    ShaderHandle(int id = -1, Resource<Shader>* ptr = nullptr, ResourceType resType = RT_Shader) : ResourceHandle(id, ptr, RT_Shader) {};
    ShaderHandle(const ResourceHandle& resHndl) : ResourceHandle(resHndl) {};
};
