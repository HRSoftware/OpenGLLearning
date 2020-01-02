
#include "../../include/Builders/MaterialBuilder.h"

MaterialBuilder& MaterialBuilder::create(const int id, std::string name)
{
    resID = id;
    materialName = name;
    textures.clear();
    return *this;
}

MaterialBuilder& MaterialBuilder::addShader(ShaderHandle _shader)
{
    shader = _shader;
    return *this;
}

MaterialBuilder& MaterialBuilder::addTextures(std::vector<TextureHandle>& _textures)
{
    textures = _textures;
    return *this;
}

MaterialBuilder& MaterialBuilder::addTexture(TextureHandle texture)
{
    textures.push_back(texture);
    return *this;
}

Material MaterialBuilder::build()
{
    return Material(resID, materialName, textures, shader);
}

MaterialBuilder::~MaterialBuilder() {}
