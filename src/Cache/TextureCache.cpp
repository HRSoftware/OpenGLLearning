#include "../../include/Cache/TextureCache.h"


TextureHandle TextureCache::addTexture(std::string name, Texture tex)
{
  
    cacheMap.insert_or_assign(name, tex);
    return findTexture(name);
}


TextureHandle TextureCache::findTexture(std::string name)
{
    Texture textHndl = cacheMap[name];
    return TextureHandle(textHndl.getResourceID(), &cacheMap[name], RT_Texture) ;
}

Texture TextureCache::findTextureByID(int id)
{
    for ( auto T : cacheMap )
    {
        if(T.second.getTextureID() == id)
        {
            return T.second;
        }
    }
}
