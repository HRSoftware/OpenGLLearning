#include "stdafx.h"
//#include "../../include/Managers/TextureManager.h"
//
//
//auto TextureManager::getTextureByID(unsigned ID) -> Texture*
//{
//    auto result = _textureMap.find(ID);
//    if(result != _textureMap.end())
//        return &result->second;
//
//   return nullptr;
//}
//
//aiTextureType TextureManager::getTextureType(unsigned ID)
//{
//    auto type = TextureManager::getTextureByID(ID);
//    if (type == nullptr)
//        return aiTextureType_UNKNOWN;
//
//   return type->type;
//}
//
//auto TextureManager::addTextures(aiMaterial* mat, std::string directory) -> std::vector<int>
//{
//    std::vector<int> textureIDCollection;
//    for ( auto texture : _textureMap )
//    {
//        if (texture.second.path == directory)
//            textureIDCollection.push_back(texture.first);
//    }
//
//    if(textureIDCollection.size() == 0)
//        textureIDCollection = loadTexturesFromMaterial(mat, directory);
//
//    return textureIDCollection;
//}
//
//void TextureManager::addTexture(Texture texture) //make private later(should not be called directly)
//{
//    _textureMap[texture.ID] = texture;
//}
//
//Texture TextureManager::createTexture(std::string path, aiTextureType _type)
//{
//   Texture newTexture;
//   int _textureID = checkIfTextureExists(path);
//
//    if (_textureID == -1) {
//        newTexture.ID = textureFromFile(path.c_str(),"");
//        newTexture.type = _type;
//        newTexture.path = path;
//        addTexture(newTexture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
//    }
//    else
//    {
//        newTexture = *getTextureByID(_textureID);
//    }
//
//    return newTexture;
//}
//
//auto TextureManager::checkIfTextureExists(std::string path) -> int
//{
//    int id = -1;
//    for ( auto _texture : _textureMap )
//    {
//        if (_texture.second.path == path)
//            id = _texture.first;
//    }
//
//    return id;
//}
//
//void TextureManager::removeTextureByID(unsigned int id)
//{
//    _textureMap.erase(id);
//}
//
//auto TextureManager::loadTexturesFromMaterial(aiMaterial* mat, std::string directory) -> std::vector<int>
//{
//    std::vector<int> textureIds;
//    aiTextureType _type;
//    int _textureID = 0;
//    std::vector<std::string> types = {
//        "texture_diffuse",
//        "texture_normal",
//        "texture_specular",
//        "texture_height"
//    };
//    
//    for (std::string _typeString : types) {
//
//        if (_typeString == "texture_diffuse")
//            _type = aiTextureType_DIFFUSE;
//
//        if (_typeString == "texture_normal")
//            _type = aiTextureType_NORMALS;
//
//        if (_typeString == "texture_specular")
//            _type = aiTextureType_SPECULAR;
//
//        if (_typeString == "texture_height")
//            _type = aiTextureType_HEIGHT;
//        
//        for (unsigned int i = 0; i < mat->GetTextureCount(_type); i++) {
//            aiString str;
//            mat->GetTexture(_type, i, &str);
//            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
//            bool skip = false;
//            _textureID = checkIfTextureExists(directory + "/" + str.data);
//
//            if (_textureID == -1) {
//                std::string path = directory + "/" + str.C_Str();
//                path = std::regex_replace(path, std::regex("//"), "/");
//                Texture texture = createTexture(path, _type);
//                
//                addTexture(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
//
//                _textureID = texture.ID;
//            }
//
//            textureIds.push_back(_textureID);
//        }
//    }
//    return textureIds;
//};
//
//auto TextureManager::textureFromFile(const char* path, const std::string& directory, bool gamma) -> int
//{
//    std::filesystem::path filePath = path;
//    std::string fullFilePath;
//    std::string fullbackFilePath = std::string(filePath.parent_path().string() + "/textures/" + filePath.filename().string());
//   
//    
//    fullFilePath = directory == "" ? filePath.string() : directory + "/" + filePath.string();
//    fullFilePath = std::regex_replace(fullFilePath, std::regex("//"), "/");
//    fullbackFilePath = std::regex_replace(fullbackFilePath, std::regex("//"), "/");
//
//    if (!std::filesystem::exists(fullFilePath))
//    {
//        fullFilePath = fullbackFilePath;
//        if(!std::filesystem::exists(fullFilePath))
//        {
//            std::cout << "\tTexture not found for " << filePath.parent_path() << "\t" <<filePath.filename() << std::endl;
//            return -1;
//        }
//
//        std::cout << "texture file found!" << std::endl;
//    }
//
//    int textureID;
//    glGenTextures(1, reinterpret_cast<GLuint*>(&textureID));
//
//    int width, height, nrComponents;
//    unsigned char* data = stbi_load(fullFilePath.c_str(), &width, &height, &nrComponents, 0);
//    if (data)
//    {
//        GLenum format;
//        switch ( nrComponents )
//        {
//        case 1:
//            format = GL_RED;
//            break;
//        case 3:
//            format = GL_RGB;
//            break;
//        case 4: 
//            format = GL_RGBA;
//            break;
//        default:
//            break;
//
//        }
//
//        glBindTexture(GL_TEXTURE_2D, textureID);
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        stbi_image_free(data);
//    }
//    else
//    {
//        std::cout << "Texture failed to load at path: " << path << std::endl;
//        stbi_image_free(data);
//    }
//
//    return textureID;
//}
