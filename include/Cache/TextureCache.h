#pragma once
#include "../Core/Texture.h"

class TextureCache
{
public:
    void addTexture(std::string name, Texture tex)
    {
        textureCache[name] = tex;
    }

    Texture* findTexture(std::string name)
    {
        return &textureCache[name];
    }

    Texture* findTextureByID(unsigned id);

private:
    std::map<std::string, Texture>  textureCache;
};
