#pragma once
#include <vector>
#include "../Core/Material.h"
#include "ShaderBuilder.h"
#include "../Cache/ResourceCache.h"


class MaterialBuilder
{
    public:
    ~MaterialBuilder();
    MaterialBuilder& create(std::string name = "DefaultTexture");
    MaterialBuilder& addTextures(std::vector<int>& textures);
    MaterialBuilder& addTexture(int texture);
    MaterialBuilder& addShader(Shader& shader);
    Material build();

    private:


        void loadTextures(aiMaterial*, std::string);
        std::string materialName;
        std::vector<int> textures;
        Shader* shader;
};


class MaterialFactory
{
public:
    MaterialFactory(ResourceCache& cache) : matCache(cache.materialCache){};

    void createBasicMaterial(const std::string name, Shader& shdr)
    {
        Material newMaterial = builder.create(name)
            .addShader(shdr)
            .build();
        matCache.addMaterial(name, newMaterial);
    }
private:
    MaterialCache& matCache; 
    MaterialBuilder builder;

};

