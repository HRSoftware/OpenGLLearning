#pragma once

#include "Cache.h"
#include "../Core/Data_Structures/Material.h"

class MaterialCache{
public:

    std::shared_ptr<Material> findMaterial(std::string matName);
    std::shared_ptr<Material> addMaterial(const std::string& name, Material material);

private:
    std::map<std::string, Material> material_map;
};
