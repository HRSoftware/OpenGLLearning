#pragma once
#include "Shader.h"


enum ResourceType
  {
      RT_None = 0,
      RT_INVALID,
      RT_Srite,
      RT_Texture,
      RT_Mesh,
      RT_Material,
      RT_Audio,
      RT_Shader,
      RT_Model
  };

template<class T>
class Resource
{
    public:
    Resource(int id = -1, ResourceType type = RT_INVALID) : resourceID(id), resourceType(type) {};
    
    int getResourceID()
    {
        return resourceID;
    }

    const ResourceType getResourceType()
    {
        return resourceType;
    }

    const int resourceID;


    protected:
    
    const ResourceType resourceType = ResourceType::RT_None;
};

template<class T>
class ResourceHandle
{
public:
    ResourceHandle(int id = -1, Resource<T> * ptr = nullptr, ResourceType resType = RT_INVALID) : resourceID(id), ptr_Resource(ptr), resourceType(resType) {};
    ResourceHandle(const ResourceHandle& resHndl) : resourceID(resHndl.resourceID), ptr_Resource(resHndl.ptr_Resource), resourceType(resHndl.resourceType) {};

    int getResourceID();

    template<class T>
    T* getResourcePointer()
    {
        return ptr_Resource;
    }

    ResourceType getResourceType();

    protected:
    int resourceID;
    T* ptr_Resource;
    ResourceType resourceType;
};

template <class T>
int ResourceHandle<T>::getResourceID()
{
    return resourceID;
}


template <class T>
ResourceType ResourceHandle<T>::getResourceType()
{
    return resourceType;
}



