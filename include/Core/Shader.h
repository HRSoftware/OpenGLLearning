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
    Shader() : Resource<Shader>(-1, RT_Shader){};
	Shader(int id): Resource<Shader>(id, RT_Shader)
	{
        programID = id;
	}
    Shader(int id, std::string name, std::map<std::string, int>& _uniformLocations);
    ~Shader() {}
	void reloadShaderFromFile(const char* fileName, bool isCoreShader);

	int getShaderID()
	{
        return programID;
	}

	int getResourceID()
	{
        return resourceID;
	}
	std::string getShaderName()
	{
        return _shaderName;
	}

	ResourceType getResourceType() 
	{
        return resourceType;
	}

	void use()
	{
		glUseProgram(programID);
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

	Shader& operator= (const Shader& shader)
	{
        _uniformLocations = shader._uniformLocations;
        _shaderName = shader._shaderName;
        programID = shader.programID;
        return *this;
	}

    std::map<std::string, int> getUniformLocations()
	{
        return _uniformLocations;
	}

	private:
	GLint getLocation(const std::string& name) const;
	
	std::map<std::string, int> _uniformLocations;
	std::string _shaderName;
    int programID = -1;

};

struct ShaderHandle : ResourceHandle<Shader>
{
public:
    ShaderHandle(int id = -1, Shader* ptr = nullptr, ResourceType resType = RT_Shader) : ResourceHandle(id, ptr, RT_Shader) {};
    ShaderHandle(const ResourceHandle& resHndl) : ResourceHandle(resHndl) {};
};
