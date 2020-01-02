#include "../../include/Managers/ResourceMangager.h"
template<class T>
ResourceHandle<T> ResourceManager::loadNewResource(ResourceType type, std::string pathToFile, std::string referenceName)
{
    if (referenceName.empty())
        referenceName = pathToFile;
    switch ( type )
    {
    case RT_Shader:
        return resourceCache.shaderCache.addNew(referenceName,shaderLoader.loadNewResource<Shader>(GUID_Allocator::getNewUniqueGUID(), "Shaders/" + pathToFile));
    case RT_Model:
        return resourceCache.modelCache.addNew(referenceName,modelLoader.loadNewResource<Model>(GUID_Allocator::getNewUniqueGUID(), pathToFile));
    default:
        return ResourceHandle(-1, nullptr , RT_INVALID);
    }
}

template<class T>
ResourceHandle<T> ResourceManager::getHandleForResource(Resource<T>* res, std::string name)
{
    switch ( res->getResourceType())
    {
    case RT_Shader:
        return resourceCache.shaderCache.find(name);
    case RT_Texture:
        return resourceCache.textureCache.find(name);
    case RT_Model:
        return resourceCache.modelCache.find(name);
    case RT_Material:
        return resourceCache.materialCache.find(name);
    default:
        return;
    }
}