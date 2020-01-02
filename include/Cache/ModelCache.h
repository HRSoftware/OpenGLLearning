#pragma once
#include "../Core/Model.h"
#include <string>
#include <map>
#include "Cache.h"


class ModelCache : Cache<Model>
{
public:
    ModelCache() {};
private:
    std::map<std::string, Model> modelMap;
    //MaterialCache& materialCache;
};
