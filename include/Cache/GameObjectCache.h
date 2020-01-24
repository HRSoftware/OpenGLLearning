#pragma once
#include "../Core/GameObject.h"
#include "Cache.h"


class GameObjectCache
{
public:

    GameObject findGameObject(std::string gameObjectName);
    GameObject addGameObject(const std::string& name, GameObject material);

private:
    std::map<std::string, GameObject> gameObject_map;
};

