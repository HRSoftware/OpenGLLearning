#pragma once
#include "../Core/GameObject.h"
#include "Cache.h"


class GameObjectCache : Cache<GameObject>
{
public:

    GameObject* findGameObject(std::string gameObjectName);
    void addGameObject(const std::string& name, GameObject gameObject);

private:
    std::map<std::string, GameObject> gameObject_map;
};

