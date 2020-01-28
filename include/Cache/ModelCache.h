#pragma once
#include "../Core/Model.h"
#include "Cache.h"


class ModelCache
{
public:
    ModelCache() {};
    Model findModel(std::string name)
    {
        auto model = model_map[name];
        if (_stricmp(name.c_str(), model.modelName.c_str()) == 0)
            return model;

        return Model();
    }

    Model addModel(std::string name, Model newModel);
    private:
    
    std::map<std::string, Model> model_map;

};
