#pragma once
class Model;


class ModelCache
{
public:
    ModelCache();
    std::shared_ptr<Model> findModel(std::string name);

    std::shared_ptr<Model> addModel(std::string name, Model newModel);

    private:
    
    std::map<std::string, Model> model_map;

};
