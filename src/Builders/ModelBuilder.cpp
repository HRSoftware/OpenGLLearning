
#include "stdafx.h"

#include "../../include/Helpers/GUIDAllocator.h"
#include "../../include/Core/Data_Structures/Mesh.h"
#include "../../include/Builders/ModelBuilder.h"
#include "../../include/Helpers/GUIDAllocator.h"

ModelBuilder& ModelBuilder::create(int id, std::string name)
{
    modelName = name;
    meshes.clear();
    _Textures.clear();
    
    return *this;
}

ModelBuilder& ModelBuilder::loadFromPath(std::string path)
{
    std::string fullPath = path;
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        fullPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if ( !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode ) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return *this;
    }

    directory = path.substr(0, fullPath.find_last_of('/'));

    processNode(scene->mRootNode, scene);
    return *this;
}

ModelBuilder& ModelBuilder::setMaterial(const string& matName)
{
    modelMaterial = materialCache.findMaterial(matName);
    return *this;
}

void ModelBuilder::processNode(aiNode* node, const aiScene* scene)
{
    for ( unsigned int i = 0; i < node->mNumMeshes; i++ )
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for ( unsigned int i = 0; i < node->mNumChildren; i++ )
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh ModelBuilder::processMesh(std::vector<glm::vec3> pos, std::vector<unsigned> _indices)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    for ( unsigned int i = 0; i < pos.size(); i++ )
    {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = pos[i].x;
        vector.y = pos[i].y;
        vector.z = pos[i].z;
        vertex.Position = vector;

        vertices.push_back(vertex);
    }
    indices = _indices;
    std::string name = modelName + "_Mesh_" + std::to_string(meshes.size());
    return Mesh(name, vertices, indices, nullptr);
}

Mesh ModelBuilder::processMesh(aiMesh* mesh, const aiScene* scene)
{
    
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    std::shared_ptr<Material> _material;

    for ( unsigned int i = 0; i < mesh->mNumVertices; i++ )
    {
        Vertex vertex;
        glm::vec3 vector;
        // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        // normals
        if ( mesh->mNormals != NULL )
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        // texture coordinates
        if ( mesh->mTextureCoords[0] ) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }

        if ( mesh->mTangents != NULL )
        {
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
        }

        if ( mesh->mBitangents != NULL )
        {
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }

        vertices.push_back(vertex);
    }

    for ( unsigned int i = 0; i < mesh->mNumFaces; i++ )
    {
        aiFace face = mesh->mFaces[i];
        for ( unsigned int j = 0; j < face.mNumIndices; j++ )
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    aiString MaterialName;
    material->Get(AI_MATKEY_NAME, MaterialName);

    _material = materialCache.findMaterial(MaterialName.C_Str());

    if(_material->name == "")
    {
        materialBuilder.create(GUID_Allocator::getNewUniqueGUID(), MaterialName.C_Str())
        .loadTexturesFromAIMaterial(material, directory);
       _material = materialCache.addMaterial(MaterialName.C_Str(), materialBuilder.build());
    }
    std::string name = modelName + "_Mesh_" + std::to_string(meshes.size());
    return Mesh(name, vertices, indices, _material);
}


Model ModelBuilder::build()
{
    Model newModel;

        for(auto mesh : meshes)
            newModel.meshes.push_back(std::make_shared<Mesh>(mesh));
        
        newModel.directory = directory;
        //newModel.textures = _textures;
        newModel.modelName = modelName;
    return newModel;
}

std::shared_ptr<Model> ModelFactory::create(std::string name, string path)
{
    auto model = resourceCache.modelCache.findModel(name);
    if(model->modelName == "")
    {
        Model newModel = modelBuilder.create(GUID_Allocator::getNewUniqueGUID(), name)
            .loadFromPath(path)
            .build();

        resourceCache.modelCache.addModel(name, newModel);
        model = resourceCache.modelCache.findModel(name);
    }
    return model;
}


