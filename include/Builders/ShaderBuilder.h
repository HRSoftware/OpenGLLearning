#pragma once
#include "../Core/Shader.h"


class ShaderBuilder {
    public:

        ShaderBuilder& createShader(int id, std::string refName, std::string fileName = "", bool core = false);
        ShaderBuilder& addShader(ShaderType shaderType, std::string fileName = "");
        Shader build();
    std::map<std::string, int> findUniformLocations();

    private:
        std::string shaderProgramName;
        std::string shaderFileName;
        std::vector<int> shadersIDs;
        
        std::map<std::string, int> _uniformLocations;
        int programID = -1;
        int resID = -1;
};

class ShaderFactory
{
    public:
        ShaderFactory() {};
   
   static Shader createBasicShader(int id,const std::string refName, std::string filename = "")
    {
        Shader newShader = builder.createShader(id, refName, filename)
            .addShader(VERTEX, filename)
            .addShader(FRAGMENT, filename)
            .build();
        return newShader;
    }
    private:
        static ShaderBuilder builder;
};
