#pragma once
#include <string>
#include "../../include/Core/Material.h"
#include "../../include/Core/Mesh.h"
#include "../../include/Core/GameObject.h"
#include "MaterialBuilder.h"
#include "ModelBuilder.h"

class GameObjectBuilder
{
    public:
        GameObjectBuilder& create(std::string name);
        GameObjectBuilder& addMaterial(Material& mat);
        GameObjectBuilder& addMeshes(std::vector<Mesh> _meshes);
        GameObject build();
        
    private:
        std::string goName;
        Material material;
        std::vector<Mesh> meshes;
};


class GameObjectFactory
{
    public:
        GameObjectFactory(std::map<string, GameObject>& goMapRef, MaterialCache& matCacheRef, ModelCache& modelMapRef) : goMap(goMapRef),
                                                                                                                                      matCache(matCacheRef), 
            modelCache(modelMapRef){};
        GameObject* create(string gameObjectName, string materialName, string modelName)
        {
            GameObject newObject;
            GOBuilder.create(gameObjectName)
                .addMaterial(*matCache.findMaterial(materialName))
                .addMeshes(modelCache.findModel(modelName)->meshes)
                .build();
            goMap.insert_or_assign(gameObjectName, newObject);

            return &goMap.find(gameObjectName)->second;
        };
    private:
        GameObjectBuilder GOBuilder;
        std::map<string, GameObject>& goMap;
        MaterialCache& matCache;
        ModelCache& modelCache;
};
