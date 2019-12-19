#pragma once
#include <string>
#include <assimp/material.h>
#include <map>

struct Texture
{
    int ID = 0;
    aiTextureType type = aiTextureType_UNKNOWN;
    std::string path;

    Texture() = default;
    Texture(const Texture& text) {
        ID = text.ID;
        type = text.type;
        path = text.path;
    }
};




