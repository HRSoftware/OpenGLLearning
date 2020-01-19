#pragma once
#include "../Core/Texture.h"
#include <regex>
#include <iostream>
#include <filesystem>

#include <stb/stb_image.h>
#include "Cache.h"

class TextureCache
{
    std::map<string, int> textureMap;
    std::map<int, aiTextureType> textureTypeMap;

    public:
        int addTexture(string name, int id);
        aiTextureType getTypeForTextureID(int id);
    Texture findTexture(string textureName);
        void setTextureType(int id, aiTextureType);
};

//class TextureCache : Cache<Texture>
//{
//public:
//    TextureHandle addTexture(std::string name, Texture tex);
//    TextureHandle findTexture(std::string name);
//    TextureHandle findTextureByID(int id);
//
//private:
//    std::map<std::string, Texture> texture_map;
//};



