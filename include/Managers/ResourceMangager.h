#pragma once
#include "../Loaders/ResourceLoader.h"
#include "../Core/Resource.h"
#include <string>
#include "../Cache/ResourceCache.h"
#include <regex>
#include <filesystem>



class ResourceManager
{
    public:
        ResourceManager(ResourceCache& cache) : resourceCache(cache), modelLoader(cache), materialLoader(cache.textureCache){};
        template<class T>
        ResourceHandle<T> loadNewResource(ResourceType type, std::string pathToFile, std::string referenceName = "");
        ResourceHandle<Texture> loadNewResource(aiTextureType type, std::string pathToFile, std::string referenceName);


         ResourceHandle<Texture> loadNewTexture(aiTextureType type, std::string pathToFile, std::string referenceNamed = "");
         ResourceHandle<Shader> loadNewShader(int shaderMask, ::string pathToFile, std::string referenceName = "");
         ResourceHandle<Material> loadNewMaterial(aiMaterial* mat, std::string pathToFile, std::string referenceNamed = "");
         ResourceHandle<Model> loadNewModel(std::string name, std::string path);

        template<class T>
        ResourceHandle<T> getHandleForResource(Resource<T>* res, std::string name);
        void LoadAllBasicResources(std::string rootDirectory);
    
     ResourceCache& resourceCache;

    private:
    ResourceLoader<Texture> textureLoader;
    ResourceLoader<Material> materialLoader;
    ResourceLoader<Shader> shaderLoader;
    ResourceLoader<Model> modelLoader;
    
    
};

inline ResourceHandle<Texture> ResourceManager::loadNewTexture(aiTextureType type, std::string pathToFile, std::string referenceName) 
{
   return resourceCache.textureCache.addTexture(pathToFile, textureLoader.loadNewResource(GUID_Allocator::getNewUniqueGUID(), pathToFile, type));
}

inline ResourceHandle<Shader> ResourceManager::loadNewShader(int shaderMask, ::string pathToFile, std::string referenceName)
{
    ShaderBuilder newShader;
    newShader.createShader(GUID_Allocator::getNewUniqueGUID(), referenceName, pathToFile);

    if ((shaderMask & VERTEX) == VERTEX)
        newShader.addShader(VERTEX, pathToFile);

    if((shaderMask & FRAGMENT) == FRAGMENT)
        newShader.addShader(FRAGMENT, pathToFile);

    if ((shaderMask & GEOMETRY) == GEOMETRY)
        newShader.addShader(GEOMETRY, pathToFile);

    if ((shaderMask & COMPUTE) == COMPUTE)
        newShader.addShader(COMPUTE, pathToFile);

    if ((shaderMask & TESS_CONTROL) == TESS_CONTROL)
        newShader.addShader(TESS_CONTROL, pathToFile);

    if ((shaderMask & TESS_EVAL) == TESS_EVAL)
        newShader.addShader(TESS_EVAL, pathToFile);


    return resourceCache.shaderCache.addShader(pathToFile, newShader.build());
}

inline ResourceHandle<Material> ResourceManager::loadNewMaterial(aiMaterial* mat, std::string pathToFile, std::string referenceName)
{
    std::string matName = referenceName.empty() ? pathToFile : referenceName;
    MaterialBuilder newMaterial(resourceCache.textureCache);
    newMaterial.create(GUID_Allocator::getNewUniqueGUID(), referenceName.empty() ? pathToFile : referenceName);

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
            _type = aiTextureType_NORMALS;                        //Handle each type of texture

        if (_typeString == "texture_specular")
            _type = aiTextureType_SPECULAR;

        if (_typeString == "texture_height")
            _type = aiTextureType_HEIGHT;

        for (unsigned int i = 0; i < mat->GetTextureCount(_type); i++) {
          aiString str;
        mat->GetTexture(_type, i, &str);
        // check if texture was loaded before and if so
        bool skip = false;
        TextureHandle _textureHandle = resourceCache.textureCache.findTexture(pathToFile + str.data);

            if (_textureHandle.getResourceID() == -1) {
                std::string path = path + "/" + str.C_Str();
                path = std::regex_replace(path, std::regex("//"), "/");
                _textureHandle = loadNewTexture(_type, pathToFile);
            }

            newMaterial.addTexture(_textureHandle);
        }
    }

    //shader
    return resourceCache.materialCache.addMaterial(matName, newMaterial.build());
}

inline ResourceHandle<Model> ResourceManager::loadNewModel(std::string name, std::string path)
{
    return resourceCache.modelCache.addModel(name, modelLoader.loadNewResource(GUID_Allocator::getNewUniqueGUID(), name, path));
}

inline void ResourceManager::LoadAllBasicResources(std::string rootDirectory)
{
    filesystem::path path = rootDirectory;

}
