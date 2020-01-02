#include "../../include/Loaders/TextureLoader.h"
#include "../../include/Managers/ResourceMangager.h"


auto TextureLoader::loadTexturesFromMaterial(aiMaterial* mat, std::string directory) -> std::vector<ResourceHandle<Texture>>
{
    std::vector<std::string> types = {
        "texture_diffuse",
        "texture_normal",
        "texture_specular",
        "texture_height"
    };
    
    std::vector<ResourceHandle<Texture>> textures;

    for (std::string _typeString : types) {
        aiTextureType _type;
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
            textures.push_back(loadTextureFromMaterial(str, _type, directory));
        }
    }
    return textures;
}

auto TextureLoader::loadTextureFromMaterial(aiString str, aiTextureType type, std::string directory) -> ResourceHandle<Texture>
{
            std::string path = directory + "/" + str.C_Str();
            path = std::regex_replace(path, std::regex("//"), "/");
            return createTexture(path, type);
}



//int TextureLoader::createTextureIDFromFile(const char* path, const std::string& directory, bool gamma)
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
