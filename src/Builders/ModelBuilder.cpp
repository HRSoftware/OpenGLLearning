

#include "../../include/Builders/ModelBuilder.h"

ModelBuilder& ModelBuilder::create(std::string name)
{
    modelName = name;
    meshes.clear();
    textureHandleCollection.clear();
    return *this;
}

ModelBuilder& ModelBuilder::loadFromPath(std::string path)
{
    std::string fullPath = "Resources/Models/" + path;
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        fullPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if ( !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode ) // if is Not Zero
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return *this;
    }

    directory = path.substr(0, fullPath.find_last_of('/'));

    processNode(scene->mRootNode, scene);
    return *this;
}

void ModelBuilder::processNode(aiNode* node, const aiScene* scene)
{
    // process each mesh located at the current node
    for ( unsigned int i = 0; i < node->mNumMeshes; i++ )
    {
        // the node object only contains _indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
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
        // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's
        vector.x = pos[i].x;
        vector.y = pos[i].y;
        vector.z = pos[i].z;
        vertex.Position = vector;


        vertices.push_back(vertex);
    }

    indices = _indices;

    return Mesh(vertices, indices, true);
}

Mesh ModelBuilder::processMesh(aiMesh* mesh, const aiScene* scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    std::vector<Texture> _texturesHandles;

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
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

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

    MaterialHandle mat = materialCache.find(MaterialName.C_Str());

    if(mat.getResourcePointer() == nullptr)
    {
        _texturesHandles = ResourceC;
        ResourceLoader<Material>::loadNewResource()
        materialCache.addNew(MaterialName.C_Str(), Material(MaterialName.C_Str(), _texturesHandles));
        mat = materialCache.find(MaterialName.C_Str());
    }
    return Mesh(vertices, indices, mat);
}

Model ModelBuilder::build()
{
    Model newModel;
        newModel.meshes = meshes;
        newModel.directory = directory;
        newModel.gammaCorrection = true;
        newModel.textureHandlesCollection = textureHandleCollection;
    return newModel;
}

Model* ModelFactory::create(std::string name, string path)
{
    Model* model = resourceCache.modelCache.findModel(name);
    if(model == nullptr)
    {
        Model newModel = modelBuilder.create(name)
            .loadFromPath(path)
            .build();

        resourceCache.modelCache.addModel(name, newModel);
        model = resourceCache.modelCache.findModel(name);
    }
    return model;
}


