#pragma once
#include <map>
#include <string>
#include <vector>
#include <assimp/material.h>
#include "../Core/Texture.h"

class TextureManager
{
public:
    TextureManager()
    {
        _textureMap.clear();
    }
    Texture* getTextureByName(std::string texName);
    Texture* getTextureByID(unsigned int ID);
    unsigned int addTexture(Texture newTexture);
    std::map<int, std::string> loadMaterialTextures(aiMaterial* mat, std::string dictionary);
    void removeTextureByID(unsigned int id);

private:
    std::vector<Texture> _textureMap;

    unsigned int nextNewID = 1;
    std::vector<unsigned int> _reusableIDs;
    int checkTextureExistsByPath(std::string path);
    unsigned textureFromFile(const char* path, const std::string& directory, bool gamma = true) const;
    unsigned int getNextID();

};

