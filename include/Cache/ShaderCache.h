#pragma once

#include "Cache.h"
#include "../Core/Data_Structures/Shader.h"

class ShaderCache {
    friend class ShaderBuilder;
public:
    std::shared_ptr<Shader> findShader(std::string refName);
    std::shared_ptr<Shader> addShader(const std::string& refName, Shader shader);

private:
    std::map<std::string, Shader> shader_Map;
    std::map<int, std::map<string, int>> uniformLocationMap;
};

inline std::shared_ptr<Shader> ShaderCache::findShader(std::string refName)
{
    return std::make_shared<Shader>(shader_Map.at(refName));
}

inline std::shared_ptr<Shader> ShaderCache::addShader(const std::string& refName, Shader shader)
{
    shader_Map.insert_or_assign(refName, shader);
    uniformLocationMap.insert_or_assign(shader.programID, shader._uniformLocations);
    return findShader(refName);
}
