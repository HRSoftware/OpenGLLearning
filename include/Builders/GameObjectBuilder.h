#pragma once
#include <string>
#include "../../include/Core/GameObject.h"
#include "../Cache/ModelCache.h"
#include "ModelBuilder.h"

//#include "ModelBuilder.h"

class GameObjectBuilder
{
    public:
        GameObjectBuilder(ResourceCache& cache) : modelFactory(cache) {};
        GameObjectBuilder& create(const std::string& name);
        GameObjectBuilder& addMeshes(const std::vector<Mesh>& _meshes);
        GameObjectBuilder& addModel(const Model& model);
        GameObjectBuilder& addModel(const std::string&, const std::string& name);
        GameObject build() const;
        
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
        GameObject create(const string& gameObjectName);

        GameObject createFloorGrid(const std::string& name, FloorGrid& grid);
        GameObject createWithModel(const std::string& name, const std::string& modelPath);

    protected:
        GameObjectBuilder GOBuilder;
       
        GameObjectCache& goMap;
        ModelCache& modelCache;
};
