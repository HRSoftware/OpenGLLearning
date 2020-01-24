#pragma once
#include <string>
#include <assimp/material.h>
#include <map>
#include "Resource.h"

class Texture : Resource<Texture>
{
    public:
    Texture(int id = -1) : Resource(id, RT_Texture){} ;
    Texture(const Texture& text, int id): Resource(id, ResourceType::RT_Texture) {
        _textureType = text._textureType;
        _path = text._path;
    }

    auto getTextureType()
    {
        return _textureType;
    }

    auto getTextureID()
    {
        return _textureID;
    }

    int getResourceID()
    {
        return resourceID;
    }

    ResourceType getResourceType()
    {
        return resourceType;
    }

    Texture& operator=(Texture newTexture)
    {
        _textureType = newTexture._textureType;
        _path = newTexture._path;
        _textureID = newTexture._textureID;
        return *this;
    }

        aiTextureType _textureType = aiTextureType_UNKNOWN;
        std::string _path;
        int _textureID = -1;
};




