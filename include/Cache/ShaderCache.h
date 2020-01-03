#pragma once
#include "../Core/Shader.h"
#include "Cache.h"

class ShaderCache : Cache<Shader> {
    friend class ShaderBuilder;
public:
    ShaderHandle findShader(std::string refName);
    ShaderHandle addShader(const std::string& refName, Shader shader);

private:
    std::map<std::string, Shader> shader_Map;
};

inline ShaderHandle ShaderCache::findShader(std::string refName)
{
    for ( auto _shader : shader_Map )
    {
        if(_shader.second.getResourceID() == -1)
        {
            return ShaderHandle(_shader.second.getResourceID(), &_shader.second, _shader.second.getResourceType());
        }
    }

    return ShaderHandle(); //return default invalid textureHandle
}

inline ShaderHandle ShaderCache::addShader(const std::string& refName, Shader shader)
{
    shader_Map.insert_or_assign(refName, shader);
    return findShader(refName);
}
