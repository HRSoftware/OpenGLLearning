#pragma once
#include "../Core/Texture.h"
#include <regex>
#include <iostream>
#include <filesystem>
#include <glad/glad.h>
#include <stb/stb_image.h>
#include "Cache.h"
#include "../Loaders/TextureLoader.h"


class TextureCache : Cache<Texture>
{
public:
    TextureHandle findTexture(std::string name);
    Texture findTextureByID(int id);
};



