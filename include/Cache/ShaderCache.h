#pragma once
#include "../Core/Shader.h"
#include "Cache.h"

class ShaderCache : Cache<Shader> {
    friend class ShaderBuilder;
public:
    Shader* findShader(std::string refName);
    void addShader(const std::string& refName, Shader shader);

private:
    std::map<std::string, Shader> _shaderMap;
};
