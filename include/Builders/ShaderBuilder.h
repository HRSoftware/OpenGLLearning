#pragma once


class Shader;
enum ShaderType;

class ShaderBuilder {
    public:
        ShaderBuilder() = default;
        ShaderBuilder& createShader(int id, std::string refName, std::string fileName = "", bool core = false);
        ShaderBuilder& addShader(ShaderType shaderType, std::string fileName = "");
        Shader build();
    std::map<std::string, int> findUniformLocations();

    private:
        std::string shaderProgramName = "";
        std::string shaderFileName = "";
        std::vector<int> shadersIDs{};
        
        std::map<std::string, int> _uniformLocations = {};
        int programID = -1;
        int resID = -1;
};

class ShaderFactory
{
    public:
    ShaderFactory();

    static Shader createBasicShader(int id, const std::string refName, std::string filename = "");
    private:
    inline static ShaderBuilder builder;
};
