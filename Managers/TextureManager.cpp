#include "TextureManager.h"
#include <assimp/material.h>
#include <filesystem>
#include <stb/stb_image.h>
#include <iostream>
#include <glad/glad.h>


Texture* TextureManager::getTextureByID(unsigned int ID)
{

    for ( Texture& _texture : _textureMap )
    {
        if (_texture.ID == ID)
            return &_texture;
    }

}

unsigned int TextureManager::addTexture(Texture newTexture)
{
    if (checkTextureExistsByPath(newTexture.path) == -1) {
        _textureMap.push_back(newTexture);
        return newTexture.ID;
    }
    return 0;
}

int TextureManager::checkTextureExistsByPath(std::string path)
{
 
    for ( Texture _texture : _textureMap )
    {
        if (_texture.path == path)
            return _texture.ID;
    }
	
    return -1;
}

void TextureManager::removeTextureByID(unsigned int id)
{
    _textureMap.erase(_textureMap.begin() + (id - 1));
    _reusableIDs.push_back(id);
}

unsigned int TextureManager::getNextID()
{
	unsigned int tempIDHolder = nextNewID;

	if (!_reusableIDs.empty())
        tempIDHolder = _reusableIDs.front();
	
	nextNewID++;
	return tempIDHolder;
}

std::map<int, std::string> TextureManager::loadMaterialTextures(aiMaterial* mat, std::string directory)
{
    
    std::map<int, std::string> textureHandles;
    aiTextureType _type;

    std::vector<std::string> types = {
        "texture_diffuse",
        "texture_normal",
        "texture_specular",
        "texture_height"
    };
    
    for (std::string _typeString : types) {

        if (_typeString == "texture_diffuse")
            _type = aiTextureType_DIFFUSE;

        if (_typeString == "texture_normal")
            _type = aiTextureType_NORMALS;

        if (_typeString == "texture_specular")
            _type = aiTextureType_SPECULAR;

        if (_typeString == "texture_height")
            _type = aiTextureType_HEIGHT;

        for (unsigned int i = 0; i < mat->GetTextureCount(_type); i++) {
            aiString str;
            mat->GetTexture(_type, i, &str);
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            int _textureID = checkTextureExistsByPath(directory + "/" + str.data);

            if (_textureID == -1) {
                Texture texture;
                texture.ID = TextureFromFile(str.C_Str(), directory);
                texture.type = _typeString;
                texture.path = directory + "/" + str.C_Str();
                addTexture(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.

                _textureID = texture.ID;
            }

            textureHandles.emplace(_textureID, _typeString); //return ID of already loaded texture
        }
    }
    return textureHandles;
};


unsigned int TextureManager::TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
    std::string filename = std::string(path);
    namespace fs = std::filesystem;
    if ( fs::exists(directory + "/textures/"))
        filename = "textures/" + filename;

    filename = directory + "/" + filename;


    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
