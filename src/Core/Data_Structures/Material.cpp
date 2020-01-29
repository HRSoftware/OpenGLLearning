#include "stdafx.h"
#pragma once

#include "../../../include/Helpers/ShaderFunctions.h"
#include "../../../include/Core/Globals.h"
#include "../../../include/Core/Data_Structures/Material.h"
#include "../../../include/Core/CurrentSceneStats.h"


void MaterialHelper::setUpShader(std::shared_ptr<Material> material)
{
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    int _textureIndex = 0;
    for (auto& _texture : material->textures) {
        glActiveTexture(GL_TEXTURE0 + _textureIndex);

        ShaderHelper::setInt(material->shader, _texture.first, _texture.second._textureID);

        /*switch (_texture.first) {
        case LOC_MAP_ALBEDO:
            ShaderHelper::setInt(material->shader, LOC_MAP_ALBEDO, _texture.second._textureID);
            break;
        case LOC_MAP_METALNESS:
            ShaderHelper::setInt(material->shader, LOC_MAP_METALNESS, _texture.second._textureID);
            break;
        case LOC_MAP_NORMAL:
            ShaderHelper::setInt(material->shader,LOC_MAP_NORMAL, _texture.second._textureID);
            break;
        case LOC_MAP_HEIGHT:
            ShaderHelper::setInt(material->shader, LOC_MAP_HEIGHT, _texture.second._textureID);
            break;
        default:
            break;
        }*/

        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, _texture.first);

        _textureIndex++;
    }
}

void MaterialHelper::useMaterial(std::shared_ptr<Material> material)
{
    Globals::RenderSystem::activeMaterial = material;
    setUpShader(material);
    ShaderHelper::useShader(material->shader);
}

Material::Material(std::string _name, std::map<ShaderLocationIndex, Texture> _textureMap, std::shared_ptr<Shader> _shader)
{
    name = _name;
    textures = _textureMap;
    shader = _shader;
}
