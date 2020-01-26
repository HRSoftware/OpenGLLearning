#pragma once

#include "../Core/Material.h"
#include "../Cache/ResourceCache.h"


class MaterialBuilder
{
    public:
        MaterialBuilder(ResourceCache& cache) : textureCache(cache.textureCache), shaderCache(cache.shaderCache)
        {
            shader = shaderCache.findShader("modelLoadingShader"); //default shader
        };
        ~MaterialBuilder();
        MaterialBuilder& create(const int id, std::string name = "DefaultTexture");
        MaterialBuilder& addTextures(std::vector<Texture>& _textures);
        MaterialBuilder& addTexture(Texture texture);
        void loadTexturesFromAIMaterial(aiMaterial* mat, std::string directory);
        MaterialBuilder& setShader(Shader _shader);
        Material build();

    private:
        
        std::string materialName;
        std::vector<Texture> textures{};
        Shader shader;

        TextureCache& textureCache;
        ShaderCache& shaderCache;
        int resID = -1;
};


class MaterialFactory
{
public:
    MaterialFactory(ResourceCache& cache) : builder(cache){};

    Material createBasicMaterial(const int id, const std::string name, Shader shdr)
    {
        Material newMaterial = builder.create(id, name)
            .setShader(shdr)
            .build();
        return newMaterial;
    }
private:
    MaterialBuilder builder;
};

