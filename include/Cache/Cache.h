#pragma once
#include <string>
#include <map>
#include "../Core/Resource.h"
#include "../Core/GameObject.h"

template <class T>
class Cache
{
    public:
    ResourceHandle<T> add(std::string name, T object)
    {
        cacheMap.insert_or_assign(name, object);

        return find(name);
    }

    ResourceHandle<T> find(std::string name)
    {
        Resource<T>* _object = &cacheMap.find(name)->second;

        int id = _object->getResourceID();
        ResourceType type = _object->getResourceType();
        if (_object == nullptr)
        {
            id = -1;
            type = RT_INVALID;
        }

        return ResourceHandle(id, _object, type);
    }

    protected:
    std::map<std::string, T> cacheMap;

};


class MaterialCache : Cache<Material>
{
    ResourceHandle<Texture> addFromAssimpMatieral(aiMaterial* mat, std::string directory)
    {
        std::vector<ResourceHandle<Texture>> textures;
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
                _textureID =  checkIfTextureExists(directory + "/" + str.data);

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

        return ResourceHandle<Texture>();
    }
};