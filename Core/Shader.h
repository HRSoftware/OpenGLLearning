#pragma once

#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

class Shader
{
public:
	Shader() {}
	~Shader() {}
	Shader(std::string filename, bool bCore = false);
	void reloadShaderFromFile(const char* fileName, bool isCoreShader);

	unsigned int ID;

	void use()
	{
		glUseProgram(ID);
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) const
	{
		glProgramUniform1i(ID, getLocation(name), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		glProgramUniform1i(ID, getLocation(name), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		glProgramUniform1f(ID, getLocation(name), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glProgramUniform2fv(ID, getLocation(name), 1,  glm::value_ptr(value));
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		glProgramUniform2f(ID, getLocation(name), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glProgramUniform3fv(ID, getLocation(name), 1,  glm::value_ptr(value));
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glProgramUniform3f(ID, getLocation(name), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glProgramUniform4fv(ID, getLocation(name), 1,  glm::value_ptr(value));
	}
	void setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glProgramUniform4f(ID, getLocation(name), x, y, z, w);

	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glProgramUniformMatrix2fv(ID, getLocation(name), 1,GL_FALSE,  glm::value_ptr(mat));
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glProgramUniformMatrix3fv(ID, getLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glProgramUniformMatrix4fv(ID, getLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
	}

	bool checkAttributeExist(const std::string& name) const {  return _uniformLocations.find(name) != _uniformLocations.end(); }

private:
	std::map<std::string, int> _uniformLocations;

	void findUniformLocations();
	GLint getLocation(const std::string& name) const;
	std::string _shaderName;

};

