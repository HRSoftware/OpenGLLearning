#include "../../include/Cache/ModelCache.h"

Model ModelCache::addModel(std::string name, Model newModel)
{
    model_map[name] = newModel;
    //        
    //        return modelMap[modelName].textureHandlesCollection;
    return newModel;
}
