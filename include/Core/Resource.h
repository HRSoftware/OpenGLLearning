#pragma once
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
      RT_Model,
      RT_GameObject
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

    ResourceType getResourceType()
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
    ResourceHandle();
    ResourceHandle(int id = -1, T* ptr = nullptr, ResourceType resType = RT_INVALID);
    ResourceHandle(const ResourceHandle<T>& resHndl) : resourceID(resHndl.resourceID), ptr_Resource(resHndl.ptr_Resource), resourceType(resHndl.resourceType) {};

    int getResourceID();

    
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
ResourceHandle<T>::ResourceHandle() : resourceID(-1), ptr_Resource(nullptr), resourceType(RT_INVALID){}

template <class T>
ResourceHandle<T>::ResourceHandle(int id, T* ptr, ResourceType resType) : resourceID(id), ptr_Resource(ptr), resourceType(resType) {}

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


