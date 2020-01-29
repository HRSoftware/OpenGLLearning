#pragma once
#include "../Core/Data_Structures/Texture.h"
#include "ResourceLoader.h"
#include "../Managers/ResourceMangager.h"


class TextureLoader : private ResourceLoader<Texture>
{
    public:
    static auto loadMultipleTexturesFromMaterial(aiMaterial* mat, std::string directory) -> std::vector<Texture>;
    static Texture createTexture(std::string path, aiTextureType type);
   
    private:
    
    static auto loadSingleTextureFromMaterial(aiString str, aiTextureType type, std::string directory) -> Texture;
    static int createTextureIDFromFile(const char* path, const std::string& directory, bool gamma);
};



inline Texture TextureLoader::createTexture(std::string path, aiTextureType type = aiTextureType_UNKNOWN)
{
    Texture newTexture;
    newTexture.name = path;
    newTexture._textureID = createTextureIDFromFile(path.c_str(),"", true);
    newTexture._textureType = type;
    return newTexture;
}
