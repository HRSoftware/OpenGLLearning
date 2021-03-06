

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
#include <glad/glad.h>
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
    std::unordered_map<int, aiTextureType> getAllTextures();
    unsigned int getVAO();
    MaterialHandle getMaterial();
    void setMaterial(MaterialHandle);

    Mesh() : _material(-1, nullptr, RT_Material){}
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, MaterialHandle newMaterial, bool root = false) :  _material(newMaterial)
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
	MaterialHandle _material;
};
#endif

