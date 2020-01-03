#pragma once
#include "../Core/Material.h"
#include "Cache.h"

class MaterialCache : Cache<Material>{
public:

    MaterialHandle findMaterial(std::string matName);
    MaterialHandle addMaterial(const std::string& name, Material material);

private:
    std::map<std::string, Material> material_map;
};
