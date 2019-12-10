
#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "Interfaces/IRenderCallbacks.h"
#include <filesystem>
#include "../Managers/TextureManager.h"

using namespace std;


class Model
{
public:
    vector<int> textureHandlesCollection;
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

    Model()
    {

    }

    Model(string const& path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);
    }

    Model(std::vector<glm::vec3> pos, std::vector<unsigned int> _indices)
    {
        meshes.push_back(processMesh(pos, _indices));
    }

    Mesh processMesh(std::vector<glm::vec3> pos, std::vector<unsigned int> _indices);

private:
    
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string const& path);

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};

#endif

#pragma once
