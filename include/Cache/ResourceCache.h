#pragma once

#include "../Loaders/ResourceLoader.h"
#include "TextureCache.h"
#include "ModelCache.h"
#include "ShaderCache.h"
#include "MaterialCache.h"

class ResourceCache
{
    public:
    MaterialCache materialCache;
    TextureCache textureCache;
    ModelCache modelCache;
    ShaderCache shaderCache;

    ResourceLoader resourceLoader;
};


