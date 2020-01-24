#include "../../include/Cache/TextureCache.h"
#include "../../include/Loaders/TextureLoader.h"


Texture TextureCache::addTexture(std::string name, Texture tex)
{
    texture_map.insert_or_assign(name, tex);
    return findTexture(name);
}


Texture TextureCache::findTexture(std::string name)
{
    auto texture = texture_map[name];
    return texture ;
}

Texture TextureCache::findTextureByID(int id)
{
    for ( auto _texture : texture_map )
    {
        if(_texture.second.getResourceID() == id)
        {
            return _texture.second;
        }
    }

    return Texture(); //return default invalid Texture
}
