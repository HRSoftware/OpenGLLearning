
#include "../../include/Builders/GameObjectBuilder.h"



GameObjectBuilder& GameObjectBuilder::create(std::string name)
{
    goName = name;
    return *this;
}
GameObjectBuilder& GameObjectBuilder::addMaterial(Material& mat)
{
    material = mat;
    return *this;
}
GameObjectBuilder& GameObjectBuilder::addMeshes(std::vector<Mesh> _meshes)
{
    meshes = _meshes;
    return *this;
}

GameObject GameObjectBuilder::build()
{
    return GameObject(goName, meshes, material);
}
