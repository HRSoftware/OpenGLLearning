
#include "../../include/Builders/GameObjectBuilder.h"



GameObjectBuilder& GameObjectBuilder::create(std::string name)
{
    _goName = name;
    return *this;
}

GameObjectBuilder& GameObjectBuilder::addMeshes(std::vector<Mesh> _meshes)
{
    
    _model.getResourcePointer()->meshes = _meshes;
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

GameObjectHandle GameObjectFactory::create(string gameObjectName)
{
    GameObject newObject = GOBuilder.create(gameObjectName)
        .build();
    return goMap.addGameObject(gameObjectName, newObject);
};

GameObjectHandle GameObjectFactory::createFloorGrid(std::string name, FloorGrid grid)
{
   GameObject go =  GOBuilder.create(name).addMeshes({ grid.getMesh() }).build();
   return goMap.addGameObject(name, go);
}

GameObjectHandle GameObjectFactory::createWithModel(std::string name, std::string modelPath)
{
    GameObject go = GOBuilder.create(name)
        .addModel(modelPath, modelPath)
        .build();

    return goMap.addGameObject(name, go);
}
