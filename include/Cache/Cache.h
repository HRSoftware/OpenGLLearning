#pragma once

#include "../Core/Resource.h"
#include "../Core/Data_Structures/GameObject.h"

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
