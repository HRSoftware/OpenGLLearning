#pragma once

#include "TextureCache.h"
#include "ShaderCache.h"
#include "MaterialCache.h"
#include "ModelCache.h"
#include "GameObjectCache.h"

struct ResourceCache
{
    Cache<Material> materialCache;
    Cache<Texture> textureCache;
    Cache<Model> modelCache;
    Cache<Shader> shaderCache;
    Cache<GameObject> gameObjectCache;
};


