#pragma once
#include <assimp\material.h>


class Texture
{
    public:
        Texture();
    Texture(const Texture& text, int id) {
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

inline Texture::Texture() {}




