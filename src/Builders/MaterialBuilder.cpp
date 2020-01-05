
#include "../../include/Builders/MaterialBuilder.h"

MaterialBuilder& MaterialBuilder::create(const int id, std::string name)
{
    resID = id;
    materialName = name;
    textureHandles.clear();
    return *this;
}

MaterialBuilder& MaterialBuilder::addShader(ShaderHandle _shader)
{
    shader = _shader;
    return *this;
}

MaterialBuilder& MaterialBuilder::addTextures(std::vector<TextureHandle>& _textures)
{
    textureHandles = _textures;
    return *this;
}

MaterialBuilder& MaterialBuilder::addTexture(TextureHandle texture)
{
    textureHandles.push_back(texture);
    return *this;
}

void MaterialBuilder::loadTexturesFromAIMaterial(aiMaterial* mat, std::string directory)
{

    filesystem::path filepath = directory;
    string path = filepath.parent_path().string();
    string file = filepath.filename().string();

    std::vector<TextureHandle> textures;
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
           TextureHandle textHandle =  textureCache.findTexture("Resources\\Models\\" + path + "\\" + str.data);
           textHandle.getResourcePointer()->_textureType = _type;
            /*if (textHandle.getResourceID() == -1) {
                std::string path = directory + "/" + str.C_Str();
                path = std::regex_replace(path, std::regex("//"), "/");
                textHandle = textureCache.addTexture(path, (path, _type));
            }*/

            textureHandles.push_back(textHandle);
        }
    }
}

Material MaterialBuilder::build()
{
    return Material(resID, materialName, textureHandles, shader);
}

MaterialBuilder::~MaterialBuilder() {}
