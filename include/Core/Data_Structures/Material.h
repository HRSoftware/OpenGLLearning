#pragma once

#include "Texture.h"
#include "Shader.h"

//class Texture;
enum aiTextureType;



struct Material
{
    Material() = default;
    Material(std::string, std::map<ShaderLocationIndex, Texture>, std::shared_ptr<Shader>);
    std::string name = "UNSET_MATERIAL_NAME";
    std::shared_ptr<Shader> shader = nullptr;

    std::map<ShaderLocationIndex, Texture> textures{};

};

namespace MaterialHelper
{
     void setUpShader(std::shared_ptr<Material> material);
     void useMaterial(std::shared_ptr<Material> material);
}