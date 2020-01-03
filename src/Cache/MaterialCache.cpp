#include "../../include/Cache/MaterialCache.h"

MaterialHandle MaterialCache::findMaterial(std::string matName)
{
    auto materialHndl = material_map[matName];
    if(materialHndl.getResourceID() != -1)
        return MaterialHandle(materialHndl.getResourceID(), &material_map[matName], RT_Material);

    return MaterialHandle();
}

MaterialHandle MaterialCache::addMaterial(const std::string& name, Material material)
{
    material_map.insert_or_assign(name, material);
    return findMaterial(name);
}
