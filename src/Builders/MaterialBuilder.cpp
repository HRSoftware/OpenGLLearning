#include <utility>
#include "../../include/Builders/MaterialBuilder.h"

MaterialBuilder& MaterialBuilder::create(std::string name)
{
    materialName = name;
    shader = nullptr;
    textures.clear();
    return *this;
}

MaterialBuilder& MaterialBuilder::addShader(Shader& _shader)
{
    shader = shader;
    return *this;
}

MaterialBuilder& MaterialBuilder::addTextures(std::vector<int>& _textures)
{
    textures = _textures;
    return *this;
}

MaterialBuilder& MaterialBuilder::addTexture(int texture)
{
    textures.push_back(texture);
    return *this;
}

Material MaterialBuilder::build()
{
    Material newMaterial;
    newMaterial.setShader(*shader);
    newMaterial.setTexture(textures);
    
    return Material(materialName, textures, *shader);
}

void MaterialBuilder::loadTextures(aiMaterial* mat, std::string directory)
{
        std::vector<int> textureIds;
        aiTextureType _type;
        int _textureID = 0;
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
                _textureID = checkIfTextureExists(directory + "/" + str.data);

                if (_textureID == -1) {
                    std::string path = directory + "/" + str.C_Str();
                    path = std::regex_replace(path, std::regex("//"), "/");
                    Texture texture = createTexture(path, _type);

                    addTexture(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.

                    _textureID = texture.ID;
                }

                textureIds.push_back(_textureID);
            }
        }
        return textureIds;
    };


inline Material* MaterialCache::findMaterial(const std::string matName)
{
    auto it = material_map.begin();
    for(it; it != material_map.end(); it++)
    {
        if (it->first == matName)
            return &it->second;
    }
    return nullptr;
}

MaterialBuilder::~MaterialBuilder() {}
