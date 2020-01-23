

#include "../../include/Cache/GameObjectCache.h"

GameObjectHandle GameObjectCache::findGameObject(std::string gameObjectName)
{
    auto gameObject = gameObject_map[gameObjectName];
    if(gameObject.getResourceID() != -1)
        return GameObjectHandle(gameObject.getResourceID(), &gameObject_map[gameObjectName], RT_Material);

    return GameObjectHandle();
}

GameObjectHandle GameObjectCache::addGameObject(const std::string& name, GameObject material)
{
    gameObject_map.insert_or_assign(name, material);
    return findGameObject(name);
}

