#include "stdafx.h"
#include "../../include/Builders/GameObjectBuilder.h"



GameObjectBuilder& GameObjectBuilder::create(std::string name)
{
    _goName = name;
    return *this;
}

GameObjectBuilder& GameObjectBuilder::addMeshes(std::vector<Mesh> _meshes)
{
    _model.meshes = _meshes;
    return *this;
}

GameObjectBuilder& GameObjectBuilder::addModel(std::string path, std::string name)
{
    _model = modelFactory.create(name, path);
    return *this;
}

GameObject GameObjectBuilder::build()
{
    return GameObject(_goName, _model);
}

GameObject GameObjectFactory::create(string gameObjectName)
{
    GameObject newObject = GOBuilder.create(gameObjectName)
        .build();
    return goMap.addGameObject(gameObjectName, newObject);
};

GameObject GameObjectFactory::createWithModel(std::string name, std::string modelPath)
{
    GameObject go = GOBuilder.create(name)
        .addModel(modelPath, modelPath)
        .build();

    return goMap.addGameObject(name, go);
}
