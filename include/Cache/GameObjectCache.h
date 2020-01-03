#pragma once
#include "../Core/GameObject.h"
#include "Cache.h"


class GameObjectCache : Cache<GameObject>
{
public:

    GameObjectHandle findGameObject(std::string gameObjectName);
    GameObjectHandle addGameObject(const std::string& name, GameObject material);

private:
    std::map<std::string, GameObject> gameObject_map;
};

