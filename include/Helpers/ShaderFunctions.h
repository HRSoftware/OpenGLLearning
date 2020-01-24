
#pragma once

#include <iostream>
#include <glad/glad.h>
#include "../Core/Shader.h"


namespace HR {
    inline std::string currentShaderName = "";
    inline void useProgram(int id)
    {
        glUseProgram(id);
    }

    inline GLint getLocation(Shader shader, const std::string& name)
    {
        if (shader._uniformLocations.count(name) == 0) {
            std::cout << "Shader Attribute '" << name << "' not found in "<< currentShaderName << std::endl;
            return -1;
        }
        return  shader._uniformLocations.at(name);
    }

    inline void setBool(Shader shader, const std::string& name, bool value)
    {

        glProgramUniform1i(shader.programID, getLocation(shader, name), (int)value);
    }

    inline void setInt(Shader shader, const std::string& name, int value)
    {

        glProgramUniform1i(shader.programID, getLocation(shader, name), value);
    }

    inline void setFloat(Shader shader, const std::string& name, float value)
    {

        glProgramUniform1f(shader.programID, getLocation(shader, name), value);
    }

    inline void setVec2(Shader shader, const std::string& name,
        const glm::vec2& value)
    {

        glProgramUniform2fv(shader.programID, getLocation(shader, name), 1, glm::value_ptr(value));
    }

    inline void setVec2(Shader shader, const std::string& name, float x, float y)
    {

        glProgramUniform2f(shader.programID, getLocation(shader, name), x, y);
    }

    inline void setVec3(Shader shader, const std::string& name,
        const glm::vec3& value)
    {

        glProgramUniform3fv(shader.programID, getLocation(shader, name), 1, glm::value_ptr(value));
    }

    inline void setVec3(Shader shader, const std::string& name, float x, float y,
        float z) 
    {

        glProgramUniform3f(shader.programID, getLocation(shader, name), x, y, z);
    }

    inline void setVec4(Shader shader, const std::string& name,
        const glm::vec4& value)
    {

        glProgramUniform4fv(shader.programID, getLocation(shader, name), 1, glm::value_ptr(value));
    }

    inline void setVec4(Shader shader, const std::string& name, float x, float y, float z,
        float w)
    {

        glProgramUniform4f(shader.programID, getLocation(shader, name), x, y, z, w);
    }

    inline void setMat2(Shader shader, const std::string& name, const glm::mat2& mat)
    {

        glProgramUniformMatrix2fv(shader.programID, getLocation(shader, name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    inline void setMat3(Shader shader, const std::string& name, const glm::mat3& mat)
    {

        glProgramUniformMatrix3fv(shader.programID, getLocation(shader, name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    inline void setMat4(Shader shader, const std::string& name, const glm::mat4& mat)
    {

        glProgramUniformMatrix4fv(shader.programID, getLocation(shader, name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    inline bool checkAttributeExist(Shader shader, const std::string& name)
    {
        return shader._uniformLocations.find(name) != shader._uniformLocations.end();
    }
}
