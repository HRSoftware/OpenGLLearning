#pragma once
#include "../Core/Model.h"
#include <map>
#include <glm\common.hpp>

class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	bool loadModeltoMemory(const std::string fileName, std::string modelName) //will only search in /Resources/Models/ for the file
	{
		modelMap[modelName] = Model("Resources/Models/" + fileName, true);
		return true;
	}

	Model* getModelByName(std::string name)
	{
		return &modelMap[name];
	}


private:
	std::map<std::string, Model> modelMap;
};

ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{
}