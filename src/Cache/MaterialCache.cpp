#include "../../include/Cache/MaterialCache.h"

Material MaterialCache::findMaterial(std::string matName)
{

    if(material_map[matName].getResourceID() != -1)
        return material_map[matName];

    return Material();
}

Material MaterialCache::addMaterial(const std::string& name, Material material)
{
    material_map.insert_or_assign(name, material);
    return findMaterial(name);
}
