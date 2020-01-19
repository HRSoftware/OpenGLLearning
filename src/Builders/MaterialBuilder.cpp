
#include "../../include/Builders/MaterialBuilder.h"

MaterialBuilder& MaterialBuilder::create(const int id, std::string name)
{
    resID = id;
    materialName = name;
    textureHandles.clear();
    
    return *this;
}

MaterialBuilder& MaterialBuilder::addShader(Shader _shader)
{
    shader = _shader;
    return *this;
}

MaterialBuilder& MaterialBuilder::addTextures(std::vector<Texture>& _textures)
{
    for (auto t : _textures)
        textureHandles.insert_or_assign(t.type, t.id);

    return *this;
}

MaterialBuilder& MaterialBuilder::addTexture(Texture texture)
{
    textureHandles.insert_or_assign(texture.type, texture.id);
    return *this;
}

MaterialBuilder& MaterialBuilder::loadTexturesFromAIMaterial(aiMaterial* mat, std::string directory)
{
    aiString name;
    mat->Get(AI_MATKEY_NAME, name);
    string matName = name.C_Str();
    filesystem::path filepath = directory;
    string path = filepath.parent_path().string();
    string file = filepath.filename().string();

    std::vector<Texture> textures;
    aiTextureType _type = aiTextureType_UNKNOWN;
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

            string path = filepath.string() + "/" + str.data;
           int textureID = textureCache.findTexture(path).id;

           textureCache.setTextureType(textureID, _type);

            textureHandles.insert_or_assign(_type, textureID);
        }
    }
    return *this;
}

Material MaterialBuilder::build()
{
    return Material{ true, materialName, textureHandles, shader };
}

MaterialBuilder::~MaterialBuilder() {}
