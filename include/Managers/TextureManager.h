#pragma once
#include <map>
#include <string>
#include <vector>
#include <assimp/material.h>
#include "../Core/Texture.h"

namespace TextureManager
{

    Texture* getTextureByName(std::string texName);
    Texture* getTextureByID(unsigned int ID);
    unsigned int addTexture(Texture newTexture);
    std::map<int, std::string> loadMaterialTextures(aiMaterial* mat, std::string dictionary);
    void removeTextureByID(unsigned int id);


    inline std::vector<Texture> _textureMap;

    inline unsigned int nextNewID = 1;
    inline std::vector<unsigned int> _reusableIDs;
    int checkIfTextureAlreadyLoadedByPath(std::string path);
    unsigned textureFromFile(const char* path, const std::string& directory = "", bool gamma = true);
    unsigned int getNextID();

}

