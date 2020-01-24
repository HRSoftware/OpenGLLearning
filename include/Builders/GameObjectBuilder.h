#pragma once

#include "../../include/Core/GameObject.h"
#include "../Cache/ModelCache.h"
#include "ModelBuilder.h"

//#include "ModelBuilder.h"

class GameObjectBuilder
{
    public:
        GameObjectBuilder(ResourceCache& cache) : modelFactory(cache) {};
        GameObjectBuilder& create(std::string name);
        GameObjectBuilder& addMeshes(std::vector<Mesh> _meshes);
        GameObjectBuilder& addModel(std::string, std::string name);
        GameObject build();
        
    private:
        std::string _goName;
        Model _model;
        ModelFactory modelFactory;
};


class GameObjectFactory
{
    public:
        GameObjectFactory(ResourceCache& cache) : GOBuilder(GameObjectBuilder(cache)), 
                                                  goMap(cache.gameObjectCache),
                                                  modelCache(cache.modelCache){};
        GameObject create(string gameObjectName);

        GameObject createWithModel(std::string name, string modelPath);

    protected:
        GameObjectBuilder GOBuilder;
       
        GameObjectCache& goMap;
        ModelCache& modelCache;
};
