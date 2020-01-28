

#ifndef MESH_H
#define MESH_H

#include "Material.h"
#include "Texture.h"
using namespace std;

struct Vertex {
	glm::vec3 Position{0};
	glm::vec3 Normal{0};
	glm::vec2 TexCoords{0};
	glm::vec3 Tangent{0};
	glm::vec3 Bitangent{0};
};

class Mesh {

public:
    Mesh* parentMeshNode;
    std::vector<Mesh> childrenMeshNodes;
    vector<Vertex> getVertices();
    vector<unsigned int> getIndices();
    std::unordered_map<int, aiTextureType> getAllTextures();
    unsigned int getVAO();
    Material getMaterial();
    void setMaterial(Material);

    Mesh() : _material(-1, nullptr, RT_Material){}
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, Material newMaterial, bool root = false) :  _material(newMaterial)
	{
		_vertices = std::move(vertices);
		_indices = std::move(indices);
		Mesh::setUpBuffers();
	}

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, bool root = false) : _material(-1, nullptr, RT_Material)
	{
        _vertices = std::move(vertices);
        _indices = std::move(indices);
        Mesh::setUpBuffers();
	}

	virtual ~Mesh() = default;

	void deleteMesh(bool deleteChildMesh = false);

	void addChildMesh(Mesh newChildMesh);

protected:
	vector<Vertex> _vertices;
    vector<unsigned int> _indices;
    unsigned int VAO, VBO, EBO;
	void updateChildNodesWithNewParent();
	virtual void setUpBuffers();
	Material _material;
};
#endif

