#pragma once
#include <assimp\material.h>


struct Texture
{
    std::string name = "UNSET_TEXTURE_NAME";
    uint _textureID = 0;
    aiTextureType _textureType = aiTextureType_UNKNOWN;
};





