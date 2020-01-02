#pragma once
#include "../Builders/ShaderBuilder.h"
#include "../Builders/MaterialBuilder.h"
#include "../Helpers/GUIDAllocator.h"
#include "../Cache/ResourceCache.h"

template<class T>
class ResourceLoader
{
public:

    template<class T>
    T loadNewResource(int id, std::string pathToFile)
    {
        throw;
    }

};

template<>
class ResourceLoader<Texture>
{
    public:
    static Texture loadNewResource(int id, std::string pathToFile, aiTextureType type)
    {
        return createTexture(id, pathToFile, type);
    }

    private:
    static Texture createTexture(int id, std::string pathToFile, aiTextureType type)
    {
        Texture newTexture(id);
        newTexture._path = pathToFile;
        newTexture._textureID = createTextureIDFromFile(pathToFile.c_str(),"", true);
        newTexture._textureType = type;

        return newTexture;

    }
    static int createTextureIDFromFile(const char* path, const std::string& directory, bool gamma)
        {
            std::filesystem::path filePath = path;
            std::string fullFilePath;
            std::string fullbackFilePath = std::string(filePath.parent_path().string() + "/textures/" + filePath.filename().string());


            fullFilePath = directory == "" ? filePath.string() : directory + "/" + filePath.string();
            fullFilePath = std::regex_replace(fullFilePath, std::regex("//"), "/");
            fullbackFilePath = std::regex_replace(fullbackFilePath, std::regex("//"), "/");

            if (!std::filesystem::exists(fullFilePath))
            {
                fullFilePath = fullbackFilePath;
                if(!std::filesystem::exists(fullFilePath))
                {
                    std::cout << "\tTexture not found for " << filePath.parent_path() << "\t" <<filePath.filename() << std::endl;
                    return -1;
                }

                std::cout << "texture file found!" << std::endl;
            }

            int textureID;
            glGenTextures(1, reinterpret_cast<GLuint*>(&textureID));

            int width, height, nrComponents;
            unsigned char* data = stbi_load(fullFilePath.c_str(), &width, &height, &nrComponents, 0);
            if (data)
            {
                GLenum format;
                switch ( nrComponents )
                {
                case 1:
                    format = GL_RED;
                    break;
                case 3:
                    format = GL_RGB;
                    break;
                case 4: 
                    format = GL_RGBA;
                    break;
                default:
                    break;

                }

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
};

template<>
class ResourceLoader<Material>
{
    public:
        ResourceLoader(ResourceCache& _cache) : textureCache(_cache.textureCache){};
        Material loadNewResource(int id, std::string matName, aiMaterial* mat)
        {

            MaterialBuilder new Material;
            newMaterial.create(id, matName)
                .addTextures(loadTexturesFromMaterial(mat, matName));
            return createTexture(id, matName, type);
        }

    private:
    std::vector<TextureHandle> loadTexturesFromMaterial(aiMaterial* mat, std::string directory)
    {
        std::vector<std::string> types = {
            "texture_diffuse",
            "texture_normal",
            "texture_specular",
            "texture_height"
        };

        std::vector<TextureHandle> textures;

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

                TextureHandle textureHandle = textureCache.find(str.C_Str());
                if (textureHandle.getResourceID() == -1)
                    textures.push_back(loadTextureFromMaterial(str, _type, directory));
                else
                    textures.push_back(textureHandle);
            }
        }
        return textures;
    }
    auto loadTextureFromMaterial(aiString str, aiTextureType type, std::string directory) -> TextureHandle
    {
        std::string path = directory + "/" + str.C_Str();
        path = std::regex_replace(path, std::regex("//"), "/");

        return textureCache.add(path, ResourceLoader<Texture>::loadNewResource(GUID_Allocator::getNewUniqueGUID(), path, type));

    }
    
    Cache<Texture>& textureCache;
};

