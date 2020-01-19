#pragma once
#include "../Core/Shader.h"
#include "Cache.h"

struct ShaderCache
{
    int addShader(string, Shader);
    void addUniform(int shaderID, std::pair<string, int> uniform);
    std::map<std::string, Shader> shaderMap;
    //std::map<int, std::map<string, int>> uniformMap;

    Shader findShader(string shaderName);

    bool checkAttributeExist(Shader shader, const std::string& name) ;
};

inline int ShaderCache::addShader(string shaderName, Shader shader)
{
    shaderMap.insert_or_assign(shaderName, shader);
    return shader.programID;
}




inline Shader ShaderCache::findShader(string shaderName)
{
    return shaderMap[shaderName];
}


//class ShaderCache : Cache<Shader> {
//    friend class ShaderBuilder;
//public:
//    ShaderHandle findShader(std::string refName);
//    ShaderHandle addShader(const std::string& refName, Shader shader);
//
//private:
//    std::map<std::string, Shader> shader_Map;
//    std::map<int, std::map<string, int>> uniformLocationMap;
//};
//
//inline ShaderHandle ShaderCache::findShader(std::string refName)
//{
//    for ( auto _shader : shader_Map )
//    {
//        if(_shader.second.getShaderName() == refName)
//        {
//            return ShaderHandle(_shader.second.getResourceID(), &_shader.second, _shader.second.getResourceType());
//        }
//    }
//
//    return ShaderHandle(); //return default invalid textureHandle
//}
//
//inline ShaderHandle ShaderCache::addShader(const std::string& refName, Shader shader)
//{
//    shader_Map.insert_or_assign(refName, shader);
//    uniformLocationMap.insert_or_assign(shader.getShaderID(), shader.getUniformLocations());
//    return findShader(refName);
//}
