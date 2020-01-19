#pragma once
#include "../Core/Material.h"
#include "Cache.h"

class MaterialCache : Cache<Material>{
public:

    Material findMaterial(std::string matName);
    Material addMaterial(const std::string& name, Material material);

private:
    std::map<std::string, Material> material_map;
};
