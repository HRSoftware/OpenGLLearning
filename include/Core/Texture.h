#pragma once
#include <string>


struct Texture
{
    unsigned int ID = 0;
    std::string type;
    std::string path;

    Texture() = default;
    Texture(const Texture& text) {
        ID = text.ID;
        type = text.type;
        path = text.path;
    }
};

