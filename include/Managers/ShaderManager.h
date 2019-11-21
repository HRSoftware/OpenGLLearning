#pragma once
#include "../Core/Shader.h"
#include <optional>

class ShaderManager
{
public:
    void addShader(std::string refName, bool core = false, std::string fileName = "" );
    Shader getShader(std::string shaderName);
private:
    std::map<std::string, Shader> _shaderMap;
   
};
