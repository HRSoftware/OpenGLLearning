#pragma once
#include "../Core/Texture.h"
#include "../Core/Model.h"

class ResourceLoader
{
    public:
        Texture loadTexture(std::string path);
        Model loadModel(std::string path);
    private:
};
