
#include "../../include/Core/Material.h"
//
//Material::Material() : Resource(-1, RT_Material){}
//
//Material::Material(int id, std::string name, std::vector<TextureHandle> _textures, ShaderHandle shdr) : Resource(id, RT_Material)
//{
//    materialName = name;
//    setTextures(_textures);
//    shader = shdr;
//}
//
//Material::Material(int id, std::string name, std::vector<TextureHandle> texture) : Resource(id, RT_Material)
//{
//    materialName = name;
//    setTextures(texture);
//}
//
//Material::Material(int id, std::string name, TextureHandle texture) : Resource(id, RT_Material)
//{
//    materialName = name;
//    setTexture(texture);
//}
//
//
//std::string Material::getName()
//{
//    return materialName;
//}
//void Material::setName(std::string newMaterialName)
//{
//    materialName = newMaterialName;
//}
//void Material::setTexture(TextureHandle texture)
//{
//    Texture tempTexture = *texture.getResourcePointer();
//    switch (tempTexture.getTextureType() )
//    {
//    case aiTextureType_DIFFUSE:
//        diffTexture = tempTexture.getTextureID();
//        break;
//
//    case aiTextureType_SPECULAR:
//        specTexture = tempTexture._textureID;
//        break;
//
//    case aiTextureType_NORMALS:
//        normTexture = tempTexture._textureID;
//        break;
//    case aiTextureType_HEIGHT:
//        heightTexture = tempTexture._textureID;
//        break;
//    default:
//        break;
//    }
//
//    textureHandles.push_back(texture);
//}
//void Material::setTextures(std::vector<TextureHandle> textures)
//{
//    for (auto texture : textures) {
//        setTexture(texture);
//    }
//}
//
//int Material::getTextureIDForType(aiTextureType type)
//{
//    unsigned textID = 0;
//    switch ( type )
//    {
//    case aiTextureType_DIFFUSE:
//        textID = diffTexture;
//        break;
//    case aiTextureType_SPECULAR:
//        textID = specTexture;
//        break;
//    case aiTextureType_NORMALS:
//        textID = normTexture;
//        break;
//    case aiTextureType_HEIGHT:
//        textID = heightTexture;
//        break;
//    default:
//        textID = 0;
//        break;
//    }
//
//    return textID;
//}
//
//
//std::unordered_map<int, aiTextureType> Material::getAllTextures()
//{
//    std::unordered_map<int, aiTextureType> textureMap;
//    textureMap.insert_or_assign(diffTexture, aiTextureType_DIFFUSE);
//    textureMap.insert_or_assign(specTexture, aiTextureType_SPECULAR);
//    textureMap.insert_or_assign(normTexture, aiTextureType_NORMALS);
//    textureMap.insert_or_assign(heightTexture, aiTextureType_HEIGHT);
//
//    return textureMap;
//}
//
//std::vector<TextureHandle> Material::getAllTextureHandles()
//{
//    return textureHandles;
//}
//
//ShaderHandle Material::getShader()
//{
//    return shader;
//}
//void Material::setShader(ShaderHandle& newShader)
//{
//    shader = newShader;
//    setUpShader();
//}
//
//void Material::Use()
//{
//    shader.getResourcePointer()->use();
//}
//
//void Material::setTextureToType(int id, aiTextureType textType)
//{
//    switch (textType)
//    {
//    case aiTextureType_DIFFUSE:
//        diffTexture = id;
//        break;
//    case aiTextureType_SPECULAR:
//        specTexture = id;
//        break;
//    case aiTextureType_HEIGHT:
//        heightTexture = id;
//        break;
//    case aiTextureType_NORMALS:
//        normTexture = id;
//        break;
//    default:
//        break;
//    }
//}
//
//void Material::setUpShader()
//{
//        // bind appropriate textures
//        unsigned int diffuseNr = 1;
//        unsigned int specularNr = 1;
//        unsigned int normalNr = 1;
//        unsigned int heightNr = 1;
//
//        int _textureIndex = 0;
//        for ( auto _texture : getAllTextures() )
//        {
//            glActiveTexture(GL_TEXTURE0 + _textureIndex);
//            aiTextureType type = _texture.second;
//
//
//            switch ( type )
//            {
//            case aiTextureType_DIFFUSE:
//                shader.getResourcePointer()->setInt(("texture_diffuse" + std::to_string(diffuseNr++)), _textureIndex);
//                break;
//            case aiTextureType_SPECULAR:
//                shader.getResourcePointer()->setInt(("texture_specular" + std::to_string(specularNr++)), _textureIndex);
//                break;
//            case aiTextureType_NORMALS:
//                shader.getResourcePointer()->setInt(("texture_normal" + std::to_string(normalNr++)), _textureIndex);
//                break;
//            case aiTextureType_HEIGHT:
//                shader.getResourcePointer()->setInt(("texture_height" + std::to_string(heightNr++)), _textureIndex);
//                break;
//            default:
//                break;
//            }
//
//            // and finally bind the texture
//            glBindTexture(GL_TEXTURE_2D, _texture.first);
//
//            _textureIndex++;
//        }
//}
//
