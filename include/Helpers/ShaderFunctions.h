
#pragma once

#include "../Core/Data_Structures/Shader.h"
#include "../Core/Globals.h"


namespace ShaderHelper {
    inline void useShader(std::shared_ptr<Shader> shader)
    {
        glUseProgram(shader->programID);
    }

    inline GLint getLocation(std::shared_ptr<Shader> shader, const std::string& indexName)
    {
        if (shader->_customUniformLocations.at(indexName) == 0) {
            std::cout << "Shader Attribute '" << indexName << "' not found in "<< shader->_shaderName << std::endl;
            return -1;
        }
        return  shader->_customUniformLocations.at(indexName);
    }

    inline void setBool(std::shared_ptr<Shader> shader, ShaderLocationIndex indexName, bool value)
    {
        glProgramUniform1i(shader->programID, indexName, (int)value);
    }

    inline void setInt(std::shared_ptr<Shader> shader, ShaderLocationIndex indexName, int value)
    {
        glProgramUniform1i(shader->programID, indexName, value);
    }

    inline void setFloat(std::shared_ptr<Shader> shader, ShaderLocationIndex indexName, float value)
    {
        glProgramUniform1f(shader->programID, indexName, value);
    }

    inline void setVec2(std::shared_ptr<Shader> shader, ShaderLocationIndex indexName, const glm::vec2& value)
    {
        glProgramUniform2fv(shader->programID, indexName, 1, glm::value_ptr(value));
    }

    inline void setVec2(std::shared_ptr<Shader> shader, ShaderLocationIndex indexName, float x, float y)
    {
        glProgramUniform2f(shader->programID, indexName, x, y);
    }

    inline void setVec3(std::shared_ptr<Shader> shader, ShaderLocationIndex indexName,const glm::vec3& value)
    {
        glProgramUniform3fv(shader->programID, indexName, 1, glm::value_ptr(value));
    }

    inline void setVec3(std::shared_ptr<Shader> shader, ShaderLocationIndex indexName, float x, float y,float z) 
    {
        glProgramUniform3f(shader->programID, indexName, x, y, z);
    }

    inline void setVec4(std::shared_ptr<Shader> shader, ShaderLocationIndex indexName,const glm::vec4& value)
    {
        glProgramUniform4fv(shader->programID, indexName, 1, glm::value_ptr(value));
    }

    inline void setVec4(std::shared_ptr<Shader> shader, ShaderLocationIndex indexName, float x, float y, float z,float w)
    {
        glProgramUniform4f(shader->programID, indexName, x, y, z, w);
    }

    inline void setMat2(std::shared_ptr<Shader> shader, ShaderLocationIndex indexName, const glm::mat2& mat)
    {
        glProgramUniformMatrix2fv(shader->programID, indexName, 1, GL_FALSE, glm::value_ptr(mat));
    }

    inline void setMat3(std::shared_ptr<Shader> shader, ShaderLocationIndex indexName, const glm::mat3& mat)
    {
        glProgramUniformMatrix3fv(shader->programID, indexName, 1, GL_FALSE, glm::value_ptr(mat));
    }

    inline void setMat4(std::shared_ptr<Shader> shader, ShaderLocationIndex indexName, const glm::mat4& mat)
    {
        glProgramUniformMatrix4fv(shader->programID, indexName, 1, GL_FALSE, glm::value_ptr(mat));
    }

    inline bool checkAttributeExist(std::shared_ptr<Material> material, ShaderLocationIndex index)
    {
        return material->shader->_uniformLocations.at(index) != -1;
    }
}
