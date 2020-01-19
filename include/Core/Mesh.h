

#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <vector>
#include "Texture.h"
#include <map>
#include "Material.h"

using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

class Mesh {

public:
    Mesh* parentMeshNode;
    std::vector<Mesh> childrenMeshNodes;
    vector<Vertex> getVertices();
    vector<unsigned int> getIndices();
    std::map<aiTextureType, int> getAllTextures();
    unsigned int getVAO();
    Material getMaterial();
    void setMaterial(Material);

    Mesh() {};
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, Material newMaterial, bool root = false) :  _material(newMaterial)
	{
		_vertices = std::move(vertices);
		_indices = std::move(indices);
		Mesh::setUpBuffers();
	}

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, bool root = false)
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

