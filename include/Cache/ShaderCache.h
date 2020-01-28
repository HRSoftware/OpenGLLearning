#pragma once

#include "Cache.h"
#include "../Core/Shader.h"


class ShaderCache {
    friend class ShaderBuilder;
public:
    Shader findShader(std::string refName);
    Shader addShader(const std::string& refName, Shader shader);

private:
    std::map<std::string, Shader> shader_Map;
    std::map<int, std::map<std::string, int>> uniformLocationMap;
};

inline Shader ShaderCache::findShader(std::string refName)
{
    for ( auto _shader : shader_Map )
    {
        if(_shader.second._shaderName == refName)
        {
            return _shader.second;
        }
    }

    return Shader(); //return default invalid Texture
}

inline Shader ShaderCache::addShader(const std::string& refName, Shader shader)
{
    shader_Map.insert_or_assign(refName, shader);
    uniformLocationMap.insert_or_assign(shader.programID, shader._uniformLocations);
    return findShader(refName);
}
