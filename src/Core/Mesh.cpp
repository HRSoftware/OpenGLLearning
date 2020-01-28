#include "stdafx.h" 

#include "../../include/Core/Data_Structures/Vertex.h"
#include "../../include/Core/Mesh.h"

std::vector<Vertex> Mesh::getVertices()
 {
     return _vertices;
 }

 std::vector<unsigned> Mesh::getIndices()
 {
     return _indices;
 }

 std::unordered_map<int, aiTextureType> Mesh::getAllTextures()
 {
     return _material.getAllTextures();
 }

 unsigned Mesh::getVAO()
 {
     return VAO;
 }

 Material Mesh::getMaterial()
 {
     return _material;
 }

 void Mesh::setMaterial(Material material)
 {
     _material = material;
 }

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, Material newMaterial, bool root): _material(newMaterial)
{
    _vertices = std::move(vertices);
    _indices = std::move(indices);
    Mesh::setUpBuffers();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, bool root)
{
    _vertices = std::move(vertices);
    _indices = std::move(indices);
    Mesh::setUpBuffers();
}

Mesh::~Mesh() = default;

 void Mesh::deleteMesh(bool deleteChildMesh)
{
    if ( !deleteChildMesh && parentMeshNode != nullptr )
    {
        updateChildNodesWithNewParent(); //all children have new parent
        parentMeshNode->childrenMeshNodes = childrenMeshNodes; //parent new has new children
    }
    this->~Mesh(); //delete this mesh
}

 void Mesh::addChildMesh(Mesh newChildMesh)
{
    newChildMesh.parentMeshNode = this;
    childrenMeshNodes.push_back(newChildMesh);
}

 void Mesh::updateChildNodesWithNewParent()
{
    for ( auto childMesh : childrenMeshNodes )
    {
        childMesh.parentMeshNode = std::move(this->parentMeshNode);
    }
}

 void Mesh::setUpBuffers()
{
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
}