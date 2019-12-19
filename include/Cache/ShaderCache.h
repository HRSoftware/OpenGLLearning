#pragma once
#include "../Core/Shader.h"

class ShaderCache {
    friend class ShaderBuilder;
public:
    Shader* findShader(std::string refName);
    void addShader(const std::string& refName, Shader shader);

private:
    std::map<std::string, Shader> _shaderMap;
};
