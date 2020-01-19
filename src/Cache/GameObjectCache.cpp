

#include "../../include/Cache/GameObjectCache.h"

GameObject GameObjectCache::findGameObject(std::string gameObjectName)
{
    return  gameObject_map[gameObjectName];
}

GameObject GameObjectCache::addGameObject(const std::string& name, GameObject gameobject)
{
    gameObject_map.insert_or_assign(name, gameobject);
    return gameobject;
}

