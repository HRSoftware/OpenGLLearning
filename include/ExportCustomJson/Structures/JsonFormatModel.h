#pragma once
#include "../../Core/Mesh.h"
#include <vector>

struct JsonModel
{
    std::string ModelName;
    Vertex _vertex;
    std::vector<int> _indices;
    std::vector<std::string> _textures;
    std::vector<Material> _material;
};
