#pragma once
#include "../Core/Model.h"
#include <string>
#include <map>
#include "Cache.h"


class ModelCache : Cache<Model>
{
public:
    ModelCache() {};
    ModelHandle findModel(std::string name)
    {
        auto modelHandle = model_map[name];
        if(modelHandle.getResourceID() != -1)
            return ModelHandle(modelHandle.getResourceID(), &model_map[name], RT_Texture) ;

        return ModelHandle();
    }
    ModelHandle addModel(std::string name, Model newModel);
    private:
    
    std::map<std::string, Model> model_map;

};
