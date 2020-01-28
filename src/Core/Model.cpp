#include "stdafx.h"

#include "../../include/Core/Mesh.h"

#include "../../include/Builders/MaterialBuilder.h"
#include "../../include/Core/Model.h"

Model::Model(int id){ }

Model& Model::operator=(Model newModel)
{
    meshes = newModel.meshes;
    directory = newModel.directory;
    //textures = newModel.textures;
    gammaCorrection = newModel.gammaCorrection;
    modelName = newModel.modelName;
    return *this;
}

Model::Model(int id, string const& path, bool gamma): gammaCorrection(gamma)
{
    //loadModel(path);
}

Model::Model(int id, std::vector<glm::vec3> pos, std::vector<unsigned> _indices)
{
    //meshes.push_back(processMesh(pos, _indices));
}


void Model::setMaterial(Material material)
{
    for (Mesh mesh : meshes) {
        mesh.setMaterial(material);
    }
};
