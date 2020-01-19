
#include "../../include/Builders/GameObjectBuilder.h"



GameObjectBuilder& GameObjectBuilder::create(const std::string& name)
{
    _goName = name;
    return *this;
}

GameObjectBuilder& GameObjectBuilder::addMeshes(const std::vector<Mesh>& _meshes)
{
    _model.meshes = _meshes;
    return *this;
}

GameObjectBuilder& GameObjectBuilder::addModel(const Model& model)
{
    _model = model;
    return *this;
}

GameObjectBuilder& GameObjectBuilder::addModel(const std::string& path, const std::string& name)
{
    _model = modelFactory.create(name, path);
    return *this;
}

GameObject GameObjectBuilder::build() const
{
    return GameObject(_goName, _model);
}

GameObject GameObjectFactory::create(const string& gameObjectName)
{
    const auto newObject = GOBuilder.create(gameObjectName)
        .build();
    return goMap.addGameObject(gameObjectName, newObject);
};

GameObject GameObjectFactory::createFloorGrid(const std::string& name, FloorGrid& grid)
{
   const auto GO =  GOBuilder.create(name).addModel({-1, {grid.getMesh()}}).build();
   return goMap.addGameObject(name, GO);
}

GameObject GameObjectFactory::createWithModel(const std::string& name, const std::string& modelPath)
{
    GameObject go = GOBuilder.create(name)
        .addModel(modelPath, modelPath)
        .build();

    return goMap.addGameObject(name, go);
}
