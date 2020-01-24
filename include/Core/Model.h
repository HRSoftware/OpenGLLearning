
#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

#include "Interfaces/IRenderCallbacks.h"



using namespace std;


class Model : Resource<Model>
{
public:
    vector<Texture> textures; //redundant??
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

    Model(int id = -1) : Resource<Model>(id, RT_Model)
    {

    }

    Model& operator=(Model newModel)
    {
        meshes = newModel.meshes;
        directory = newModel.directory;
        textures = newModel.textures;
        gammaCorrection = newModel.gammaCorrection;
        return *this;
    }

    Model(int id, string const& path, bool gamma = false) : gammaCorrection(gamma), Resource<Model>(id, RT_Model)
    {
        //loadModel(path);
    }

    Model(int id, std::vector<glm::vec3> pos, std::vector<unsigned int> _indices) : Resource<Model>(id, RT_Model)
    {
        //meshes.push_back(processMesh(pos, _indices));
    }

    int getResourceID()
    {
        return resourceID;
    }

    ResourceType getResourceType()
    {
        return resourceType;
    }
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


