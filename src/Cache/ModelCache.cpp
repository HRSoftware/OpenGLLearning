#include "stdafx.h"


#include "../../include/Core/Model.h"
#include "../../include/Cache/ModelCache.h"

ModelCache::ModelCache() {}

Model ModelCache::findModel(std::string name)
{
    auto model = model_map[name];
    if ( _stricmp(name.c_str(), model.modelName.c_str()) == 0 )
        return model;

    return Model();
}

Model ModelCache::addModel(std::string name, Model newModel)
{
    model_map[name] = newModel;
    //        
    //        return modelMap[modelName].textureHandlesCollection;
    return findModel(name);
}
