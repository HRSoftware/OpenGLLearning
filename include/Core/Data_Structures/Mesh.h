#pragma once


#include "Vertex.h"
class Material;


struct Mesh
{
    std::string _meshName = "";
    std::vector<Vertex> _vertices{};
    std::vector<std::shared_ptr<Mesh>> _childMeshes;
    std::shared_ptr<Mesh> parentMesh = nullptr;
    std::vector<unsigned> _indices{};
    unsigned int VAO, VBO, EBO = 0;
    std::shared_ptr<Material> _material{};
    Mesh(std::string meshName, std::vector<Vertex> vertices, std::vector<unsigned> indicies, std::shared_ptr<Material> material);

    private:
        void setUpBuffers();
};




//class Mesh {
//
//public:
//    Mesh* parentMeshNode;
//    std::vector<Mesh> childrenMeshNodes;
//    std::unordered_map<int, aiTextureType> getAllTextures();
//	void deleteMesh(bool deleteChildMesh = false);
//	void updateChildNodesWithNewParent();
//
//    std::vector<Vertex> getVertices();
//    std::vector<unsigned int> getIndices();
//
//    unsigned int getVAO();
//    Material getMaterial();
//    void setMaterial(Material);
//
//    Mesh();
//    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material newMaterial, bool root = false);
//
//    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, bool root = false);
//
//    virtual ~Mesh();
//
//
//	void addChildMesh(Mesh newChildMesh);
//
//	std::vector<Vertex> _vertices;
//    std::vector<unsigned int> _indices;
//    unsigned int VAO, VBO, EBO;
//	
//	virtual void setUpBuffers();
//	Material _material;
//};

