#pragma once
#include "../Core/Model.h"
#include <string>
#include <map>
#include "Cache.h"


class ModelCache : Cache<Model>
{
public:
    ModelCache() {};
    Model& findModel(std::string name)
    {
        return model_map[name];
    }
    Model addModel(std::string name, Model newModel);
    private:
    
    std::map<std::string, Model> model_map;

};
