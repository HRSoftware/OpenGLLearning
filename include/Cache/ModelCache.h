#pragma once
#include "../Core/Model.h"


class ModelCache
{
public:
    ModelCache() {};
    void addModel(string, Model);
    Model* findModel(string);

private:
    std::map<string, Model> modelMap;
    //MaterialCache& materialCache;
};
