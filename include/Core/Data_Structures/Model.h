
#pragma once
#ifndef MODEL_H
#define MODEL_H

class Mesh;
#include "../Interfaces/IRenderCallbacks.h"
using namespace std;


class Model
{
public:
    std::string modelName = "";
    std::vector<std::shared_ptr<Mesh>> meshes;
    string directory;

    Model() = default;
    Model& operator=(Model newModel);
};


#endif


