#pragma once
#include "../Core/Material.h"

class MaterialCache {
public:

    Material* findMaterial(std::string matName);
    Material* addMaterial(const std::string& name, Material material);

private:
    std::map<std::string, Material> material_map;
};
