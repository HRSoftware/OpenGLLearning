#include "../../include/Cache/TextureCache.h"


TextureHandle TextureCache::addTexture(std::string name, Texture tex)
{
    texture_map.insert_or_assign(name, tex);
    return findTexture(name);
}


TextureHandle TextureCache::findTexture(std::string name)
{
    auto textHndl = texture_map[name];
    return TextureHandle(textHndl.getResourceID(), &texture_map[name], RT_Texture) ;
}

TextureHandle TextureCache::findTextureByID(int id)
{
    for ( auto _texture : texture_map )
    {
        if(_texture.second.getResourceID() == id)
        {
            return TextureHandle(_texture.second.getResourceID(), &_texture.second, _texture.second.getResourceType());
        }
    }

    return TextureHandle(); //return default invalid textureHandle
}
