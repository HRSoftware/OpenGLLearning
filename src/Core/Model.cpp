#include "../../include/Core/Model.h"
#include "../../include/Builders/MaterialBuilder.h"

//void Model::loadModel(string const& path)
//{
//    Assimp::Importer importer;
//    const aiScene* scene = importer.ReadFile(
//        path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
//
//    if ( !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode ) // if is Not Zero
//    {
//        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
//        return;
//    }
//
//    directory = path.substr(0, path.find_last_of('/'));
//
//
//    processNode(scene->mRootNode, scene);
//}
//
//void Model::processNode(aiNode* node, const aiScene* scene)
//{
//    // process each mesh located at the current node
//    for ( unsigned int i = 0; i < node->mNumMeshes; i++ )
//    {
//        // the node object only contains _indices to index the actual objects in the scene. 
//        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
//        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//        Mesh newMesh = processMesh(mesh, scene);
//        for ( auto textureHandleID : newMesh.getAllTextures())
//        {
//            if (std::find(textureHandlesCollection.begin(), textureHandlesCollection.end(), textureHandleID.second) == textureHandlesCollection.end())
//                textureHandlesCollection.push_back(textureHandleID.first); 
//        }
//        meshes.push_back(newMesh);
//    }
//    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
//    for ( unsigned int i = 0; i < node->mNumChildren; i++ )
//    {
//        processNode(node->mChildren[i], scene);
//    }
//}
//
//Mesh Model::processMesh(std::vector<glm::vec3> pos, std::vector<unsigned> _indices)
//{
//    vector<Vertex> vertices;
//    vector<unsigned int> indices;
//
//    for ( unsigned int i = 0; i < pos.size(); i++ )
//    {
//        Vertex vertex;
//        glm::vec3 vector;
//        // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's
//        vector.x = pos[i].x;
//        vector.y = pos[i].y;
//        vector.z = pos[i].z;
//        vertex.Position = vector;
//
//
//        vertices.push_back(vertex);
//    }
//
//    indices = _indices;
//
//    return Mesh(vertices, indices, true);
//}
//
//Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
//{
//    vector<Vertex> vertices;
//    vector<unsigned int> indices;
//    std::vector<int> _texturesHandles;
//
//    for ( unsigned int i = 0; i < mesh->mNumVertices; i++ )
//    {
//        Vertex vertex;
//        glm::vec3 vector;
//        // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's
//        vector.x = mesh->mVertices[i].x;
//        vector.y = mesh->mVertices[i].y;
//        vector.z = mesh->mVertices[i].z;
//        vertex.Position = vector;
//
//        // normals
//        if ( mesh->mNormals != NULL )
//        {
//            vector.x = mesh->mNormals[i].x;
//            vector.y = mesh->mNormals[i].y;
//            vector.z = mesh->mNormals[i].z;
//            vertex.Normal = vector;
//        }
//
//        // texture coordinates
//        if ( mesh->mTextureCoords[0] ) // does the mesh contain texture coordinates?
//        {
//            glm::vec2 vec;
//            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
//            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
//            vec.x = mesh->mTextureCoords[0][i].x;
//            vec.y = mesh->mTextureCoords[0][i].y;
//            vertex.TexCoords = vec;
//        }
//        else
//            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
//
//        if ( mesh->mTangents != NULL )
//        {
//            vector.x = mesh->mTangents[i].x;
//            vector.y = mesh->mTangents[i].y;
//            vector.z = mesh->mTangents[i].z;
//            vertex.Tangent = vector;
//        }
//
//        if ( mesh->mBitangents != NULL )
//        {
//            vector.x = mesh->mBitangents[i].x;
//            vector.y = mesh->mBitangents[i].y;
//            vector.z = mesh->mBitangents[i].z;
//            vertex.Bitangent = vector;
//        }
//
//        vertices.push_back(vertex);
//    }
//
//    for ( unsigned int i = 0; i < mesh->mNumFaces; i++ )
//    {
//        aiFace face = mesh->mFaces[i];
//        for ( unsigned int j = 0; j < face.mNumIndices; j++ )
//            indices.push_back(face.mIndices[j]);
//    }
//    // process materials
//    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
//    
//    aiString MaterialName;
//    material->Get(AI_MATKEY_NAME, MaterialName);
//
//    Material* mat = MaterialCache::findMaterial(MaterialName.C_Str());
//
//    if(mat == nullptr)
//    {
//        _texturesHandles = TextureManager::loadTexturesFromMaterial(material, directory);
//        Material newMaterial(MaterialName.C_Str(), _texturesHandles);
//        
//        mat = &newMaterial;
//    }
//
//    return Mesh(vertices, indices, mat);
//}

void Model::setMaterial(MaterialHandle material)
{
    for (Mesh mesh : meshes) {
        mesh.setMaterial(material);
    }
};
