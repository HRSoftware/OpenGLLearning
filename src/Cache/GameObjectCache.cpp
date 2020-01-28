#include "stdafx.h"

#include "../../include/Cache/GameObjectCache.h"

GameObject GameObjectCache::findGameObject(std::string gameObjectName)
{
    auto gameObject = gameObject_map[gameObjectName];
    if(gameObject.getName() != "")
        return gameObject;

    return GameObject();
}

GameObject GameObjectCache::addGameObject(const std::string& name, GameObject material)
{
    gameObject_map.insert_or_assign(name, material);
    return findGameObject(name);
}

