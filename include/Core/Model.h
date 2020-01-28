
#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
class Texture;
class Material;

#include "Interfaces/IRenderCallbacks.h"



using namespace std;


class Model
{
public:
    //std::vector<Texture> textures; //redundant??
    std::string modelName = "";
    std::vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

    Model(int id = -1);
    Model& operator=(Model newModel);
    Model(int id, string const& path, bool gamma = false);
    Model(int id, std::vector<glm::vec3> pos, std::vector<unsigned int> _indices);

    void setMaterial(Material material);
    //Mesh processMesh(std::vector<glm::vec3> pos, std::vector<unsigned int> _indices);

private:
    
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    //void loadModel(string const& path);

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    //void processNode(aiNode* node, const aiScene* scene);
    //Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};


#endif


