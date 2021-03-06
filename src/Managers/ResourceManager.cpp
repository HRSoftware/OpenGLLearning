#include "../../include/Managers/ResourceMangager.h"
template<class T>
ResourceHandle<T> ResourceManager::loadNewResource(ResourceType type, std::string pathToFile, std::string referenceName)
{
    if (referenceName.empty())
        referenceName = pathToFile;
    switch ( type )
    {
    case RT_Shader:
        return resourceCache.shaderCache.addShader(referenceName,shaderLoader.loadNewResource(GUID_Allocator::getNewUniqueGUID(), "Shaders/" + pathToFile));
    case RT_Model:
        return resourceCache.modelCache.addModel(referenceName,modelLoader.loadNewResource(GUID_Allocator::getNewUniqueGUID(), pathToFile));
    default:
        return ResourceHandle<T>();
    }
}

template<class T>
ResourceHandle<T> ResourceManager::getHandleForResource(Resource<T>* res, std::string name)
{
    switch ( res->getResourceType())
    {
    case RT_Shader:
        return resourceCache.shaderCache.findShader(name);
    case RT_Texture:
        return resourceCache.textureCache.findTexture(name);
    case RT_Model:
        return resourceCache.modelCache.findModel(name);
    case RT_Material:
        return resourceCache.materialCache.findMaterial(name);
    default:
        return;
    }
}