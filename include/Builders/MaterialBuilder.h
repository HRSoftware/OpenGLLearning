#pragma once
#include <vector>
#include <utility>
#include "../Core/Material.h"
#include "../Cache/ResourceCache.h"


class MaterialBuilder
{
    public:
        MaterialBuilder(TextureCache& cache) : textureCache(cache){ };
        ~MaterialBuilder();
        MaterialBuilder& create(const int id, std::string name = "DefaultTexture");
        MaterialBuilder& addTextures(std::vector<TextureHandle>& _textures);
        MaterialBuilder& addTexture(TextureHandle texture);
        void loadTexturesFromAIMaterial(aiMaterial* mat, std::string directory);
        MaterialBuilder& addShader(ShaderHandle _shader);
        Material build();

    private:
        
        std::string materialName;
        std::vector<TextureHandle> textureHandles;
        ShaderHandle shader;

        TextureCache& textureCache;
        int resID = -1;
};


class MaterialFactory
{
public:
    MaterialFactory(TextureCache& cache) : builder(cache){};

    Material createBasicMaterial(const int id, const std::string name, ShaderHandle shdr)
    {
        Material newMaterial = builder.create(id, name)
            .addShader(shdr)
            .build();
        return newMaterial;
    }
private:
    MaterialBuilder builder;
};

