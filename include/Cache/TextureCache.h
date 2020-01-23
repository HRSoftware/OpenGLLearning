#pragma once
#include "../Core/Texture.h"
#include <regex>
#include <iostream>
#include <filesystem>
#include <glad/glad.h>
#include <stb/stb_image.h>
#include "Cache.h"


class TextureCache : Cache<Texture>
{
public:
    TextureHandle addTexture(std::string name, Texture tex);
    TextureHandle findTexture(std::string name);
    TextureHandle findTextureByID(int id);

private:
    std::map<std::string, Texture> texture_map;
};



