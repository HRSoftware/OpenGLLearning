#pragma once
#include <vector>
#include <utility>
#include "../Core/Material.h"


class MaterialBuilder
{
    public:
        MaterialBuilder() { };
    ~MaterialBuilder();
    MaterialBuilder& create(const int id, std::string name = "DefaultTexture");
    MaterialBuilder& addTextures(std::vector<TextureHandle>& _textures);
    MaterialBuilder& addTexture(TextureHandle texture);
    MaterialBuilder& addShader(ShaderHandle _shader);
    Material build();

    private:

    std::vector<Texture> loadTextures(aiMaterial*, std::string);
        std::string materialName;
        std::vector<TextureHandle> textures;
        ShaderHandle shader;
        int resID;
};


class MaterialFactory
{
public:
    MaterialFactory() {};

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

