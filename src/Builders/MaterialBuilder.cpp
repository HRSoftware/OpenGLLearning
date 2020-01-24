#include "stdafx.h"
#include "../../include/Builders/MaterialBuilder.h"
#include "../../include/Loaders/TextureLoader.h"

MaterialBuilder& MaterialBuilder::create(const int id, std::string name)
{
    resID = id;
    materialName = name;
    textures.clear();
    return *this;
}

MaterialBuilder& MaterialBuilder::addShader(Shader _shader)
{
    shader = _shader;
    return *this;
}

MaterialBuilder& MaterialBuilder::addTextures(std::vector<Texture>& _textures)
{
    textures = _textures;
    return *this;
}

MaterialBuilder& MaterialBuilder::addTexture(Texture texture)
{
    textures.push_back(texture);
    return *this;
}

void MaterialBuilder::loadTexturesFromAIMaterial(aiMaterial* mat, std::string directory)
{

    filesystem::path filepath = directory;
    string path = filepath.parent_path().string();
    string file = filepath.filename().string();

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
           Texture texture =  textureCache.findTexture(directory + "/" + str.data);
           
            if (texture._textureID == -1) {
                std::string path = directory + "/" + str.C_Str();
                path = std::regex_replace(path, std::regex("//"), "/");

                texture = TextureLoader::createTexture(directory + "/" + str.data, _type);
                textureCache.addTexture(path, texture);
            }
            else
                texture._textureType = _type;

           textures.push_back(texture);
        }
    }
}

Material MaterialBuilder::build()
{
    return Material(resID, materialName, textures, shader);
}

MaterialBuilder::~MaterialBuilder() {}
