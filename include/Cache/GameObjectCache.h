#pragma once

#include "Cache.h"
#include "../Core/Data_Structures/GameObject.h"


class GameObjectCache
{
public:

    GameObject findGameObject(std::string gameObjectName);
    GameObject addGameObject(const std::string& name, GameObject material);

private:
    std::map<std::string, GameObject> gameObject_map;
};

