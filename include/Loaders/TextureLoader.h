#pragma once
#include "../Core/Texture.h"
#include "ResourceLoader.h"
#include "../Managers/ResourceMangager.h"


static class TextureLoader : private ResourceLoader<Texture>
{
    public:
    static TextureHandle loadNewResource(std::string path, aiTextureType type);
    static auto loadTexturesFromMaterial(aiMaterial* mat, std::string directory) -> std::vector<ResourceHandle<Texture>
    >;
   
    private:
    static TextureHandle createTexture(std::string path, aiTextureType type);
    static auto loadTextureFromMaterial(aiString str, aiTextureType type, std::string directory) -> ResourceHandle<
    Texture>;
    static int createTextureIDFromFile(const char* path, const std::string& directory, bool gamma);
    
};


inline TextureHandle TextureLoader::loadNewResource(std::string path,  aiTextureType type = aiTextureType_UNKNOWN)
{
    return createTexture(path, type);
}

inline TextureHandle TextureLoader::createTexture(std::string path, aiTextureType type = aiTextureType_UNKNOWN)
{
    Texture newTexture(GUID_Allocator::getNewUniqueGUID());
    newTexture._path = path;
    newTexture._textureID = createTextureIDFromFile(path.c_str(),"", true);
    newTexture._textureType = type;
    return ResourceManager::resourceCache.textureCache.addNew(path, newTexture);

}
