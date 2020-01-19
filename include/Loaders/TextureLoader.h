#pragma once
#include "../Core/Texture.h"
#include "ResourceLoader.h"
#include "../Managers/ResourceMangager.h"


class TextureLoader : private ResourceLoader<Texture>
{
    public:
    static Texture loadNewResource(std::string path, aiTextureType type);
    static auto loadMultipleTexturesFromMaterial(aiMaterial* mat, std::string directory) -> std::vector<Texture>;
   
    private:
    static Texture createTexture(std::string path, aiTextureType type);
    static auto loadSingleTextureFromMaterial(aiString str, aiTextureType type, std::string directory) -> Texture;
    static int createTextureIDFromFile(const char* path, const std::string& directory, bool gamma);
};


inline Texture TextureLoader::loadNewResource(std::string path,  aiTextureType type = aiTextureType_UNKNOWN)
{
    return createTexture(path, type);
}

inline Texture TextureLoader::createTexture(std::string path, aiTextureType type = aiTextureType_UNKNOWN)
{
    Texture newTexture;
    newTexture.id = createTextureIDFromFile(path.c_str(),"", true);
    newTexture.type = type;
    return newTexture;
}
