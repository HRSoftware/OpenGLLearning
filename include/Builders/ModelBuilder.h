#pragma once
#include <string>
#include "../Core/Model.h"
#include "../Cache/ResourceCache.h"
#include "MaterialBuilder.h"


class ModelBuilder
{
    public:
        ModelBuilder(ResourceCache& cache) : materialCache(cache.materialCache), textureCache(cache.textureCache), materialBuilder(cache.textureCache) {};
        ModelBuilder& create(int id, std::string);
        ModelBuilder& loadFromPath(std::string);
        Model build();

    private:

        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(std::vector<glm::vec3> pos, std::vector<unsigned> _indices);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);

        std::string modelName;
        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<TextureHandle> _textureHandles;

        MaterialCache& materialCache;
        TextureCache& textureCache;
        MaterialBuilder materialBuilder;
};

class ModelFactory
{
    public:
        ModelFactory(ResourceCache& resCache) : modelBuilder(ModelBuilder(resCache)), resourceCache(resCache)
        {
        };
        ModelHandle create(std::string name, string path);

    private:
        ModelBuilder modelBuilder;
        string modelName;
        ResourceCache& resourceCache;       
};

