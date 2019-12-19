#pragma once
#include "../Core/Shader.h"
#include <utility>
#include <vector>
#include "../Cache/ResourceCache.h"


class ShaderBuilder{
    public:
    
    enum ShaderType
    {
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
        GEOMETRY = GL_GEOMETRY_SHADER,
        COMPUTE = GL_COMPUTE_SHADER,
        TESS_CONTROL = GL_TESS_CONTROL_SHADER,
        TESS_EVAL = GL_TESS_EVALUATION_SHADER
    };

        ShaderBuilder& createShader(std::string refName, std::string fileName = "", bool core = false);
        ShaderBuilder& addShader(ShaderType shaderType, std::string fileName = "");
        Shader build();
    std::map<std::string, int> findUniformLocations();

    private:
        std::string shaderProgramName;
        std::string shaderFileName;
        std::vector<int> shadersIDs;
        int programID;
        std::map<std::string, int> _uniformLocations;
    };

class ShaderFactory
{
    public:
        ShaderFactory(ResourceCache& cache) : shaderCache(cache.shaderCache){};
   
    void createBasicShader(const std::string refName, std::string filename = "")
    {
        Shader newShader = builder.createShader(refName, filename)
            .addShader(ShaderBuilder::VERTEX, filename)
            .addShader(ShaderBuilder::FRAGMENT, filename)
            .build();
        shaderCache.addShader(refName, newShader);
    }
    private:
        ShaderCache& shaderCache; 
        ShaderBuilder builder;
};
