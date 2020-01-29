#include "stdafx.h"


#include "../../include/Cache/ModelCache.h"
#include "../../include/Core/Data_Structures/Model.h"

ModelCache::ModelCache() {}

std::shared_ptr<Model> ModelCache::findModel(std::string name)
{
    return std::make_shared<Model>(model_map.at(name));
}

std::shared_ptr<Model> ModelCache::addModel(std::string name, Model newModel)
{
    model_map[name] = newModel;
    //        
    //        return modelMap[modelName].textureHandlesCollection;
    return findModel(name);
}
