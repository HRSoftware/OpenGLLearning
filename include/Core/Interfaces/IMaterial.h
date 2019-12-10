#pragma once
#include <vector>
#include <string>
#include <assimp/material.h>

class Material
{
  public:

    std::string getName();
    void setName(std::string);
    void addTexture(unsigned, aiTextureType);
    void addTextures(std::vector<unsigned>);


  private:
    std::vector<unsigned> textureIDs;
    std::string materialName;

    int diffTexture;
    int specTexture;
    int heightTexture;
    int normTexture;
        
};
