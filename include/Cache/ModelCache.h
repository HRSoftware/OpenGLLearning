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
        if (model.getResourceID() != -1)
            return model;

        return Model();
    }

    Model addModel(std::string name, Model newModel);
    private:
    
    std::map<std::string, Model> model_map;

};
