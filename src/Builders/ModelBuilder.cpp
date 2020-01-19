

#include "../../include/Builders/ModelBuilder.h"
#include "../../include/Helpers/GUIDAllocator.h"

ModelBuilder& ModelBuilder::create(int id, std::string name, std::string _shader)
{
    modelName = name;
    meshes.clear();
    _textureHandles.clear();
    ShaderToUse = _shader;
    
    return *this;
}

ModelBuilder& ModelBuilder::loadFromPath(std::string _path)
{
    std::string fullPath = _path;
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        fullPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if ( !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode ) // if is Not Zero
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return *this;
    }

    directory = _path.substr(0, fullPath.find_last_of('/'));

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
    Material _materialHandle;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's
        vertex.Position = {
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        };

        // normals
        if (mesh->mNormals != NULL)
            vertex.Normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};

        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            vertex.TexCoords = { mesh->mTextureCoords[0][i].x,mesh->mTextureCoords[0][i].y};
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        if (mesh->mTangents != NULL)
            vertex.Tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };

        if (mesh->mBitangents != NULL) 
            vertex.Bitangent = {  mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z};
        
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

    aiString materialName;
    material->Get(AI_MATKEY_NAME, materialName);

    _materialHandle = materialCache.findMaterial(materialName.C_Str());

    if( !materialCache.findMaterial(materialName.C_Str())._isValid)
    {
        string newMaterialName = modelName + "_" + materialName.C_Str();
        materialBuilder.create(GUID_Allocator::getNewUniqueGUID(), newMaterialName)
                       .loadTexturesFromAIMaterial(material, directory)
                       .addShader(shaderCache.findShader(ShaderToUse));
        
       _materialHandle = materialCache.addMaterial(newMaterialName, materialBuilder.build());
    }
    return Mesh(vertices, indices, _materialHandle);
}

Model ModelBuilder::build()
{
    Model newModel(GUID_Allocator::getNewUniqueGUID());
        newModel.meshes = meshes;
        newModel.directory = directory;
        newModel.gammaCorrection = true;
        newModel.textureHandles = _textureHandles;
        
    return newModel;
}

Model ModelFactory::create(std::string name, string path)
{
    Model model = resourceCache.modelCache.findModel(name);
    if(model.getResourceID() == -1)
    {
        Model newModel = modelBuilder.create(GUID_Allocator::getNewUniqueGUID(), name, "modelLoadingShader")
            .loadFromPath(path)
            .build();

        resourceCache.modelCache.addModel(name, newModel);
        return newModel;
    }
    return model;
}


