#pragma once


#include "Cache.h"
#include "../../include/Core/Data_Structures/Texture.h"

class TextureCache
{
public:
    std::shared_ptr<Texture> addTexture(std::string name, Texture tex);
    std::shared_ptr<Texture> findTexture(std::string name);

private:
    std::map<std::string, Texture> texture_map;
};



