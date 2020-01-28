#pragma once

class Model;
class ModelCache
{
public:
    ModelCache();
    Model findModel(std::string name);

    Model addModel(std::string name, Model newModel);

    private:
    
    std::map<std::string, Model> model_map{};

};
