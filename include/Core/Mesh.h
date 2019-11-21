

#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include "Texture.h"
#include <map>

using namespace std;

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

class Mesh {

public:
	/*  Mesh Data */
	
    Mesh* parentMeshNode;
    std::vector<Mesh> childrenMeshNodes;
    vector<Vertex> getVertices();
    vector<unsigned int> getIndices();
    map<int, string> textureHandles;
    unsigned int getVAO();

	/*  Functions  */
	// constructor
	Mesh(){}
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, map<int, string> textures, bool root = false)
	{
		this->_vertices = vertices;
		this->_indices = indices;
		this->textureHandles = textures;
		Mesh::setUpBuffers();
	}

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, bool root = false)
	{
        this->_vertices = vertices;
        this->_indices = indices;
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
};
#endif

