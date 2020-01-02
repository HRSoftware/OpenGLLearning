#pragma once
#include <vector>
#include <string>
#include <assimp/material.h>
#include <unordered_map>
#include "Shader.h"
#include "Resource.h"
#include "Texture.h"



class Material : public Resource<Material>
{
  public:
    Material(int id, std::string name, std::vector<TextureHandle>, ShaderHandle);
    Material(int id, std::string name, std::vector<TextureHandle> texture);
    Material(int id, std::string name, TextureHandle );
    std::string getName();
    void setName(std::string);
    void setTexture(TextureHandle texture);
    void setTextures(std::vector<TextureHandle> textures);
    int getTextureIDForType(aiTextureType);

    std::unordered_map<int, aiTextureType> getAllTextures();
    std::vector<TextureHandle> getAllTextureHandles();
    ShaderHandle getShader();
    void setShader(ShaderHandle& newShader);
    void Use();


  private:
    std::vector<TextureHandle> textureHandles;
    std::string materialName; 
    ShaderHandle shader;
    void setUpShader(); 

    int diffTexture; 
    int specTexture;
    int heightTexture;
    int normTexture; 
};

struct MaterialHandle : ResourceHandle<Material>
{
public:
    MaterialHandle(int id, Resource<Material>* ptr, ResourceType resType) : ResourceHandle(id, ptr, RT_Material) {};
    MaterialHandle(const ResourceHandle& resHndl) : ResourceHandle(resHndl) {};
};
