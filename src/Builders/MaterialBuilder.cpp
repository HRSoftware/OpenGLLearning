#include "stdafx.h"
#include "../../include/Builders/MaterialBuilder.h"
#include "../../include/Loaders/TextureLoader.h"

MaterialBuilder& MaterialBuilder::create(const int id = 2, std::string name)
{
    resID = id;
    materialName = name;
    textures.clear();
    return *this;
}

MaterialBuilder& MaterialBuilder::setShader(std::shared_ptr<Shader> _shader)
{
    shader = _shader;
    return *this;
}

MaterialBuilder& MaterialBuilder::addTextures(std::vector<Texture>& _textures)
{
    for (auto texture : _textures)
        textures.push_back(std::make_shared<Texture>(texture));
    return *this;
}

MaterialBuilder& MaterialBuilder::addTexture(std::shared_ptr<Texture> texture)
{
    textures.push_back(texture);
    return *this;
}

void MaterialBuilder::loadTexturesFromAIMaterial(std::shared_ptr<aiMaterial>, std::string directory)
{

    std::filesystem::path filepath = directory;
    string path = filepath.parent_path().string();
    string file = filepath.filename().string();

    aiTextureType _type;
    ShaderLocationIndex _locationIndex;
    std::vector<std::string> types = {
        "texture_diffuse",
        "texture_normal",
        "texture_specular",
        "texture_height"
    };

    for (std::string _typeString : types) {

        if (_typeString == "texture_diffuse")
        {
            _type = aiTextureType_DIFFUSE;
            _locationIndex = LOC_MAP_ALBEDO;
        }

        if (_typeString == "texture_normal")
        {
            _type = aiTextureType_NORMALS;
            _locationIndex = LOC_MAP_NORMAL;
        }


        if (_typeString == "texture_specular")
        {
            _type = aiTextureType_SPECULAR;
            _locationIndex = LOC_MAP_METALNESS;
        }

        if (_typeString == "texture_height")
        {
            _type = aiTextureType_HEIGHT;
            _locationIndex = LOC_MAP_HEIGHT;
        }

        for (unsigned int i = 0; i < mat->GetTextureCount(_type); i++) {
            aiString str;
            mat->GetTexture(_type, i, &str);
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
           auto texture =  textureCache.findTexture(directory + "/" + str.data);
           
            if (texture->_textureID == 0) {
                std::string path = directory + "/" + str.C_Str();
                path = std::regex_replace(path, std::regex("//"), "/");

                Texture newTexture = TextureLoader::createTexture(directory + "/" + str.data, _type);
                texture = textureCache.addTexture(path, newTexture);
            }
            else
                texture->_textureType = _type;

           textures.insert_or_assign(_locationIndex, make_pair(texture, ));
        }
    }
}

Material MaterialBuilder::build()
{
    newMaterial.name = materialName;
    newMaterial.textures = textures;

    return newMaterial;
}

MaterialBuilder::~MaterialBuilder() {}
