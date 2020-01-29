#include "stdafx.h"

#include "../Core/Data_Structures/Model.h"
#include "JsonExporter.h"

std::vector<JsonModel> JsonExporter::processModels(Model modelToProcess)
{
    std::vector<JsonModel> modelVec;
    JsonModel JFM;
    std::vector<Vertex> _vertex;
    std::vector<string> _textures;
    std::vector<Material> _materials;
    for(auto mesh : modelToProcess.meshes)
    {
        for(auto vertices : mesh->_vertices)
        {
            _vertex.push_back(vertices);
        }

        
        
    }

    return modelVec;
}
