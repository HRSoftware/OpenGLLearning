
#include "../../include/Core/Material.h"


Material::Material() {}

Material::Material(int id, std::string name, std::vector<Texture> _textures, Shader shdr) : Resource(id, RT_Material)
{
    materialName = name;
    setTextures(_textures);
    shader = shdr;
}

Material::Material(int id, std::string name, std::vector<Texture> texture) : Resource(id, RT_Material)
{
    materialName = name;
    setTextures(texture);
}

Material::Material(int id, std::string name, Texture texture) : Resource(id, RT_Material)
{
    materialName = name;
    setTexture(texture);
}


std::string Material::getName()
{
    return materialName;
}
void Material::setName(std::string newMaterialName)
{
    materialName = newMaterialName;
}
void Material::setTexture(Texture texture)
{
    switch (texture.getTextureType() )
    {
    case aiTextureType_DIFFUSE:
        diffTexture = texture.getTextureID();
        break;

    case aiTextureType_SPECULAR:
        specTexture = texture._textureID;
        break;

    case aiTextureType_NORMALS:
        normTexture = texture._textureID;
        break;
    case aiTextureType_HEIGHT:
        heightTexture = texture._textureID;
        break;
    default:
        break;
    }

    textures.push_back(texture);
}
void Material::setTextures(std::vector<Texture> textures)
{
    for (auto texture : textures) {
        setTexture(texture);
    }
}

int Material::getTextureIDForType(aiTextureType type)
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

Shader Material::getShader()
{
    return shader;
}
void Material::setShader(Shader& newShader)
{
    shader = newShader;
    setUpShader();
}

void Material::Use()
{
    HR::useProgram(shader.programID);
}

void Material::setTextureToType(int id, aiTextureType textType)
{
    switch (textType)
    {
    case aiTextureType_DIFFUSE:
        diffTexture = id;
        break;
    case aiTextureType_SPECULAR:
        specTexture = id;
        break;
    case aiTextureType_HEIGHT:
        heightTexture = id;
        break;
    case aiTextureType_NORMALS:
        normTexture = id;
        break;
    default:
        break;
    }
}

Material& Material::operator=(const Material& mat)
{
    textures = mat.textures;
    materialName = mat.materialName;
    shader = mat.shader;

    diffTexture = mat.diffTexture;
    specTexture = mat.specTexture;
    heightTexture = mat.heightTexture;
    normTexture = mat.normTexture;
    return *this;
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
                HR::setInt(shader,("texture_diffuse" + std::to_string(diffuseNr++)), _textureIndex);
                break;
            case aiTextureType_SPECULAR:
                HR::setInt(shader,("texture_specular" + std::to_string(specularNr++)), _textureIndex);
                break;
            case aiTextureType_NORMALS:
                HR::setInt(shader,("texture_normal" + std::to_string(normalNr++)), _textureIndex);
                break;
            case aiTextureType_HEIGHT:
                HR::setInt(shader,("texture_height" + std::to_string(heightNr++)), _textureIndex);
                break;
            default:
                break;
            }

            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, _texture.first);

            _textureIndex++;
        }
}

void Material::setUpShader(bool textured)
{
    if ( textured )
    {
        // bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;

        int _textureIndex = 0;
        for ( auto _texture : textures )
        {
            glActiveTexture(GL_TEXTURE0 + _textureIndex);

            switch ( _texture.getTextureType() )
            {
                case aiTextureType_DIFFUSE:
                    HR::setInt(shader, ("texture_diffuse" + std::to_string(diffuseNr++)), _textureIndex);
                    break;
                case aiTextureType_SPECULAR:
                    HR::setInt(shader, ("texture_specular" + std::to_string(specularNr++)), _textureIndex);
                    break;
                case aiTextureType_NORMALS:
                    HR::setInt(shader, ("texture_normal" + std::to_string(normalNr++)), _textureIndex);
                    break;
                case aiTextureType_HEIGHT:
                    HR::setInt(shader, ("texture_height" + std::to_string(heightNr++)), _textureIndex);
                    break;
                default:
                    break;
            }

            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, _texture._textureID);

            _textureIndex++;
        }
    }
}

