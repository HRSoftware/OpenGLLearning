#pragma once
#include "../Core/Texture.h"

#include "Cache.h"


class TextureCache
{
public:
    Texture addTexture(std::string name, Texture tex);
    Texture findTexture(std::string name);
    Texture findTextureByID(int id);

private:
    std::map<std::string, Texture> texture_map;
};



