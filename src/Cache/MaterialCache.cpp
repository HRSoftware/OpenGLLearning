#include "stdafx.h"
#include "../../include/Cache/MaterialCache.h"

std::shared_ptr<Material> MaterialCache::findMaterial(std::string matName)
{
    if(material_map[matName].name != "UNSET_MATERIAL_NAME")
        return std::make_shared<Material>(material_map[matName]);

    return nullptr;
}

std::shared_ptr<Material> MaterialCache::addMaterial(const std::string& name, Material material)
{
    material_map.insert_or_assign(name, material);
    return std::make_shared<Material>(material);
}
