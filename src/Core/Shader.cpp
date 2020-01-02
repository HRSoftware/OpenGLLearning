
#include "../../include/Core/Shader.h"



Shader::Shader(int id, std::string name, std::map<std::string, int>& uniformLocations) : Resource(id, RT_Shader)
{
    _shaderName = name;
    _uniformLocations = std::move(uniformLocations);
}



void Shader::reloadShaderFromFile(const char* fileName, bool isCoreShader = false)
{
	/*assert(fileName);
	GLuint reloadedProgram = .shaderID;

	if (reloadedProgram) {
		glDeleteProgram(shaderID);
		shaderID = reloadedProgram;
	}*/
}

void Shader::setBool(const std::string& name, bool value) const
{
	glProgramUniform1i(shaderID, getLocation(name), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glProgramUniform1i(shaderID, getLocation(name), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glProgramUniform1f(shaderID, getLocation(name), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
	glProgramUniform2fv(shaderID, getLocation(name), 1, glm::value_ptr(value));
}

void Shader::setVec2(const std::string& name, float x, float y) const
{
	glProgramUniform2f(shaderID, getLocation(name), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	glProgramUniform3fv(shaderID, getLocation(name), 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glProgramUniform3f(shaderID, getLocation(name), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
	glProgramUniform4fv(shaderID, getLocation(name), 1, glm::value_ptr(value));
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
	glProgramUniform4f(shaderID, getLocation(name), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
	glProgramUniformMatrix2fv(shaderID, getLocation(name), 1,GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
	glProgramUniformMatrix3fv(shaderID, getLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glProgramUniformMatrix4fv(shaderID, getLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

bool Shader::checkAttributeExist(const std::string& name) const
{
	return _uniformLocations.find(name) != _uniformLocations.end();
}

GLint Shader::getLocation(const std::string& name) const
{
	if(_uniformLocations.find(name) == _uniformLocations.end() )
	{
		std::cout << "Shader Attribute '" << name << "' not found in " << _shaderName << std::endl;
		return -1;
	}
	return  _uniformLocations.at(name);
}

