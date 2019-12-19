#pragma once
#include <vector>
#include <string>
#include <assimp/material.h>
#include <unordered_map>
#include "Shader.h"
#include "Texture.h"


class Material 
{
  public:
    Material(std::string name, std::vector<int> textures, Shader&);
    Material(std::string name, Texture);
    Material(std::string name = "defaultMaterial");
    std::string getName();
    void setName(std::string);
    void setTexture(std::string path, aiTextureType type);
    void setTexture(unsigned id);
    void setTexture(std::vector<int> Ids);
    int getTextureID(aiTextureType);

    std::unordered_map<int, aiTextureType> getAllTextures();
    std::vector<int> getAllTextureHandles();
    Shader& getShader();
    void setShader(Shader& newShader);
    void Use();

  private:
    std::vector<int> textureIDs;
    std::string materialName; 
    Shader* shader;
    void setUpShader(); 

    int diffTexture; 
    int specTexture;
    int heightTexture;
    int normTexture; 
};
