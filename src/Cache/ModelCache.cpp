#include "../../include/Cache/ModelCache.h"

ModelHandle ModelCache::addModel(std::string name, Model newModel)
{
    model_map[name] = newModel;
    //        
    //        return modelMap[modelName].textureHandlesCollection;
    return findModel(name);
}
