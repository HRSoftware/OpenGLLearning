
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

    _model = *modelFactory.create(name, path);
    return *this;
}

GameObject GameObjectBuilder::build()
{
    return GameObject(_goName, _model);
}

GameObject* GameObjectFactory::create(string gameObjectName)
{
    GameObject newObject;
    GOBuilder.create(gameObjectName)
        .build();
    goMap.addGameObject(gameObjectName, newObject);

    return goMap.findGameObject(gameObjectName);
};

GameObject* GameObjectFactory::createFloorGrid(FloorGrid grid)
{
   GameObject go =  GOBuilder.create(grid.getName()).addMeshes({ grid.getMesh() }).build();
    goMap.addGameObject(go.getName(), go);

    return goMap.findGameObject(go.getName());
}

GameObject* GameObjectFactory::createWithModel(std::string name, std::string modelPath)
{

    GameObject go = GOBuilder.create(name)
        .addModel(modelPath, modelPath)
        .build();

    goMap.addGameObject(go.getName(), go);

    return goMap.findGameObject(go.getName());

}
