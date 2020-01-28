#include "stdafx.h"

#include "Structures/JsonFormatModel.h""
#include "JsonExporter.h"
#include "../Core/Model.h"

std::vector<JsonFormatModel> JsonExporter::processModels(Model modelToProcess)
{
    JsonFormatModel JFM;
    std::vector<Vertex> _vertex;
    std::vector<string> _textures;
    std::vector<Material> _materials;
    for(auto mesh : modelToProcess.meshes)
    {
        for(auto vertices : mesh.getVertices())
        {
            _vertex.push_back(vertices);
        }

        fpr(auto textures : mesh.getAllTextures());
        
    }
}
