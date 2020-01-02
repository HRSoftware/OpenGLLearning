#pragma once
#include <string>
#include "../Core/Model.h"
#include "../Cache/ResourceCache.h"


class ModelBuilder
{
    public:
        ModelBuilder(ResourceCache& cache) : materialCache(cache.materialCache), textureCache(cache.textureCache) {};
        ModelBuilder& create(std::string);
        ModelBuilder& loadFromPath(std::string);
        Model build();

    private:

        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(std::vector<glm::vec3> pos, std::vector<unsigned> _indices);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);

        std::string modelName;
        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<int>textureHandleCollection;

        Cache<Material>& materialCache;
        Cache<Texture>& textureCache;
};

class ModelFactory
{
    public:
        ModelFactory(ResourceCache& resCache) : modelBuilder(ModelBuilder(resCache)), resourceCache(resCache)
        {
        };
        Model* create(std::string name, string path);
    private:
        ModelBuilder modelBuilder;
        string modelName;
        ResourceCache& resourceCache;
        
};

