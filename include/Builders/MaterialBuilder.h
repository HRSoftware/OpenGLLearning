#pragma once

#include "../Core/Data_Structures/Material.h"
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
        MaterialBuilder& addTexture(std::shared_ptr<Texture> texture);
        void loadTexturesFromAIMaterial(std::shared_ptr<aiMaterial> mat, std::string directory);
        MaterialBuilder& setShader(std::shared_ptr<Shader> _shader);
        Material build();

    private:
        
        std::string materialName;
        Material newMaterial;
        std::map<ShaderLocationIndex, Texture> textures{};
        std::shared_ptr<Shader> shader = nullptr;

        TextureCache& textureCache;
        ShaderCache& shaderCache;
        int resID = -1;
};


class MaterialFactory
{
public:
    MaterialFactory(ResourceCache& cache) : builder(cache){};

    Material createBasicMaterial(const int id, const std::string name, std::shared_ptr<Shader> shdr)
    {
        Material newMaterial = builder.create(id, name)
            .setShader(shdr)
            .build();
        return newMaterial;
    }
private:
    MaterialBuilder builder;
};

