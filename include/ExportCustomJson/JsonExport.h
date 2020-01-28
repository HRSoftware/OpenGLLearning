#pragma once

class Model;
struct JsonFormatModel;

class JsonExporter
{

    void exportToFile(std::string filename);
    std::vector<JsonFormatModel> processModels(Model modelToProcess);


};

