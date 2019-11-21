#include "../../include/Managers/ShaderManager.h"

void ShaderManager::addShader(std::string refName, bool core, std::string fileName)
{
    std::string shaderName = fileName;
    if (fileName == "")
        shaderName = refName;
    
    _shaderMap.emplace(refName, Shader(shaderName, core));
}

Shader ShaderManager::getShader(std::string shaderName)
{
     return _shaderMap[shaderName];
}
