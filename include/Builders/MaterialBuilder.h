#pragma once
#include <vector>
#include <utility>
#include "../Core/Material.h"
#include "../Cache/ResourceCache.h"


class MaterialBuilder
{
    public:
        MaterialBuilder(ResourceCache& cache) : textureCache(cache.textureCache), shaderCache(cache.shaderCache){ };
        ~MaterialBuilder();
        MaterialBuilder& create(const int id, std::string name = "DefaultTexture");
        MaterialBuilder& addTextures(std::vector<Texture>& _textures);
        MaterialBuilder& addTexture(Texture texture);
        MaterialBuilder& loadTexturesFromAIMaterial(aiMaterial* mat, std::string directory);
        MaterialBuilder& addShader(Shader _shader);
        Material build();

    private:
        
        std::string materialName;
        std::map<aiTextureType, int> textureHandles;
        Shader shader;

        TextureCache& textureCache;
        ShaderCache& shaderCache;
        int resID = -1;
};


class MaterialFactory
{
public:
    MaterialFactory(ResourceCache& cache) : builder(cache){};

    Material createBasicMaterial(const int id, const std::string name, Shader _shader)
    {
        Material newMaterial = builder.create(id, name)
            .addShader(_shader)
            .build();
        return newMaterial;
    }
private:
    MaterialBuilder builder;
};

