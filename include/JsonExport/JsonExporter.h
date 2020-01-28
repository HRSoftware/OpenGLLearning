#pragma once
#include "Structures/JsonFormatModel.h"
class Model;


class JsonExporter
{

    void exportToFile(std::string filename);
    std::vector<JsonModel> processModels(Model modelToProcess);


};

