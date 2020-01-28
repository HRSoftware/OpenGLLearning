#pragma once

#include "../Core/Texture.h"
#include "../Core/Shader.h"

//class Texture;
enum aiTextureType;


class Material
{
  public:
      Material() = default;
    Material(int id, std::string name, std::vector<Texture>, Shader);
    Material(int id, std::string name, std::vector<Texture> texture);
    Material(int id, std::string name, Texture );
    std::string getName();
    void setName(std::string);
    void setTexture(Texture texture);
    void setTextures(std::vector<Texture> textures);
    int getTextureIDForType(aiTextureType);

    std::unordered_map<int, aiTextureType> getAllTextures();

    Shader getShader();

    void setShader(Shader& newShader);
    void Use();
    void setTextureToType(int id, aiTextureType textType);


    Material& operator =(const Material& mat);
    void setUpShader(bool textured);

  private:
    std::vector<Texture> textures{};
    std::string materialName = ""; 
    Shader shader;
    void setUpShader(); 

    int diffTexture = -1; 
    int specTexture = -1;
    int heightTexture = -1;
    int normTexture = -1;


      
};