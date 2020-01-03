#pragma once

#include "TextureCache.h"
#include "ShaderCache.h"
#include "MaterialCache.h"
#include "ModelCache.h"
#include "GameObjectCache.h"

struct ResourceCache
{
    MaterialCache materialCache;
    TextureCache textureCache;
    ModelCache modelCache;
    ShaderCache shaderCache;
    GameObjectCache gameObjectCache;
};


