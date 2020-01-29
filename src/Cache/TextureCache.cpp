#include "stdafx.h"

#include "../../include/Loaders/TextureLoader.h"

#include "../../include/Cache/TextureCache.h"
#include "../../include/Loaders/TextureLoader.h"

std::shared_ptr<Texture> TextureCache::addTexture(std::string name, Texture tex)
{
    texture_map.insert_or_assign(name, tex);
    return findTexture(name);
}


std::shared_ptr<Texture> TextureCache::findTexture(std::string name)
{
    return std::make_shared<Texture>(texture_map.at(name));
}


