#pragma once
#include <assimp/material.h>
#include "Shader.h"
#include "Texture.h"


struct Material
{
    bool _isValid = false;
    std::string materialName = "";
    std::map<aiTextureType, int> textures;
    Shader shader;
};


//class Material : public Resource<Material>
//{
//  public:
//      Material();
//    Material(int id, std::string name, std::vector<TextureHandle>, ShaderHandle);
//    Material(int id, std::string name, std::vector<TextureHandle> texture);
//    Material(int id, std::string name, TextureHandle );
//    std::string getName();
//    void setName(std::string);
//    void setTexture(TextureHandle texture);
//    void setTextures(std::vector<TextureHandle> textures);
//    int getTextureIDForType(aiTextureType);
//
//    std::unordered_map<int, aiTextureType> getAllTextures();
//    std::vector<TextureHandle> getAllTextureHandles();
//    ShaderHandle getShader();
//
//    void setShader(ShaderHandle& newShader);
//    void Use();
//    void setTextureToType(int id, aiTextureType textType);
//
//
//    Material& operator = (const Material& mat)
//    {
//        textureHandles = mat.textureHandles;
//        materialName = mat.materialName;
//        shader = mat.shader;
//
//        diffTexture = mat.diffTexture;
//        specTexture = mat.specTexture;
//        heightTexture = mat.heightTexture;
//        normTexture = mat.normTexture;
//        return *this;
//    }
//
//
//  private:
//    std::vector<TextureHandle> textureHandles;
//    std::string materialName; 
//    ShaderHandle shader;
//    void setUpShader(); 
//
//    int diffTexture; 
//    int specTexture;
//    int heightTexture;
//    int normTexture; 
//};
//
//struct MaterialHandle : ResourceHandle<Material>
//{
//public:
//    MaterialHandle(int id = -1, Material* ptr = nullptr, ResourceType resType = RT_Material) : ResourceHandle(id, ptr, resType) {};
//    MaterialHandle(const ResourceHandle& resHndl) : ResourceHandle(resHndl) {};
//};
