
#include "../../include/Core/Material.h"
#include "../../include/Managers/TextureManager.h"

Material::Material(std::string name, std::vector<int> textures)
{
    materialName = name;
    setTexture(textures);
}

Material::Material(std::string name, Texture texture)
{
    materialName = name;
    setTexture(texture.ID);
}

Material::Material(std::string name)
{
    materialName = name;
}

std::string Material::getName()
{
    return materialName;
}
void Material::setName(std::string newMaterialName)
{
    materialName = newMaterialName;
}
void Material::setTexture(std::string path, aiTextureType type = aiTextureType_UNKNOWN)
{
    int id = TextureManager::checkIfTextureExists(path);
    if (id == -1)
        id = TextureManager::createTexture(path, type).ID;

    switch (TextureManager::getTextureType(id)) {
    case aiTextureType_DIFFUSE:
        diffTexture = id;
        break;

    case aiTextureType_SPECULAR:
        specTexture = id;
        break;

    case aiTextureType_NORMALS:
        normTexture = id;
        break;
    case aiTextureType_HEIGHT:
        heightTexture = id;
        break;
    default:
        break;
    }
    
    textureIDs.push_back(id);

}
void Material::setTexture(unsigned id)
{
    switch ( TextureManager::getTextureType(id) )
    {
    case aiTextureType_DIFFUSE:
        diffTexture = id;
        break;

    case aiTextureType_SPECULAR:
        specTexture = id;
        break;

    case aiTextureType_NORMALS:
        normTexture = id;
        break;
    case aiTextureType_HEIGHT:
        heightTexture = id;
        break;
    default:
        break;
    }

    textureIDs.push_back(id);
}
void Material::setTexture(std::vector<int> Ids)
{
    for (auto id : Ids) {
        setTexture(id);
    }
}

int Material::getTextureID(aiTextureType type)
{
    unsigned textID = 0;
    switch ( type )
    {
    case aiTextureType_DIFFUSE:
        textID = diffTexture;
        break;
    case aiTextureType_SPECULAR:
        textID = specTexture;
        break;
    case aiTextureType_NORMALS:
        textID = normTexture;
        break;
    case aiTextureType_HEIGHT:
        textID = heightTexture;
        break;
    default:
        textID = 0;
        break;
    }

    return textID;
}


std::unordered_map<int, aiTextureType> Material::getAllTextures()
{
    std::unordered_map<int, aiTextureType> textureMap;
    textureMap.insert_or_assign(diffTexture, aiTextureType_DIFFUSE);
    textureMap.insert_or_assign(specTexture, aiTextureType_SPECULAR);
    textureMap.insert_or_assign(normTexture, aiTextureType_NORMALS);
    textureMap.insert_or_assign(heightTexture, aiTextureType_HEIGHT);

    return textureMap;
}

Shader& Material::getShader()
{
    return shader;
}
void Material::setShader(Shader newShader)
{
    shader = newShader;
    setUpShader();
}

void Material::Use()
{
    shader.use();
}

void Material::setUpShader()
{
        // bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;

        int _textureIndex = 0;
        for ( auto _texture : getAllTextures() )
        {
            glActiveTexture(GL_TEXTURE0 + _textureIndex);
            aiTextureType type = _texture.second;


            switch ( type )
            {
            case aiTextureType_DIFFUSE:
                shader.setInt(("texture_diffuse" + std::to_string(diffuseNr++)), _textureIndex);
                break;
            case aiTextureType_SPECULAR:
                shader.setInt(("texture_specular" + std::to_string(specularNr++)), _textureIndex);
                break;
            case aiTextureType_NORMALS:
                shader.setInt(("texture_normal" + std::to_string(normalNr++)), _textureIndex);
                break;
            case aiTextureType_HEIGHT:
                shader.setInt(("texture_height" + std::to_string(heightNr++)), _textureIndex);
                break;
            default:
                break;
            }

            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, _texture.first);

            _textureIndex++;
        }
}

