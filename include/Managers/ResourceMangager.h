#pragma once
#include "../Loaders/ResourceLoader.h"
#include "../Core/Resource.h"
#include <string>
#include "../Cache/ResourceCache.h"



class ResourceManager
{
    public:
        ResourceManager(ResourceCache& cache) : resourceCache(cache), materialLoader(cache) {};
        template<class T>
        ResourceHandle<T> loadNewResource(ResourceType type, std::string pathToFile, std::string referenceName = "");


        ResourceHandle<Texture> loadNewTexture(aiTextureType type, std::string pathToFile, std::string referenceNamed = "");
        ResourceHandle<Shader> loadNewShader(ShaderType types, ::string pathToFile, std::string referenceNamed = "");
        ResourceHandle<Material> loadNewMaterial(aiMaterial* mat, std::string pathToFile, std::string referenceNamed = "");

        template<class T>
        ResourceHandle<T> getHandleForResource(Resource<T>* res, std::string name);
    
    ResourceCache& resourceCache;

    private:
    ResourceLoader<Texture> textureLoader;
    ResourceLoader<Material> materialLoader;
    ResourceLoader<Shader> shaderLoader;
    ResourceLoader<Model> modelLoader;
    
    
};

inline ResourceHandle<Texture> ResourceManager::loadNewTexture(aiTextureType type, std::string pathToFile, std::string referenceName) 
{
   return resourceCache.textureCache.add(pathToFile, textureLoader.loadNewResource(GUID_Allocator::getNewUniqueGUID(), pathToFile, type));
}

inline ResourceHandle<Shader> ResourceManager::loadNewShader(ShaderType types, ::string pathToFile, std::string referenceName)
{
    ShaderBuilder newShader;
    newShader.createShader(GUID_Allocator::getNewUniqueGUID(), referenceName, pathToFile);

    if (types || VERTEX)
        newShader.addShader(VERTEX, pathToFile);

    if(types || FRAGMENT)
        newShader.addShader(FRAGMENT, pathToFile);

    if(types || GEOMETRY)
        newShader.addShader(GEOMETRY, pathToFile);

    if(types || COMPUTE)
        newShader.addShader(COMPUTE, pathToFile);

    if(types || TESS_CONTROL)
        newShader.addShader(TESS_CONTROL, pathToFile);

    if(types || TESS_EVAL)
        newShader.addShader(TESS_EVAL, pathToFile);


    return resourceCache.shaderCache.add(pathToFile, newShader.build());
}

inline ResourceHandle<Material> ResourceManager::loadNewMaterial(aiMaterial* mat, std::string pathToFile, std::string referenceName)
{
    std::string matName = referenceName.empty() ? pathToFile : referenceName;
    MaterialBuilder newMaterial;
    newMaterial.create(GUID_Allocator::getNewUniqueGUID(), referenceName.empty() ? pathToFile : referenceName);

    
    //textures
    //shader
    return resourceCache.materialCache.add(matName, newMaterial.build());
}
