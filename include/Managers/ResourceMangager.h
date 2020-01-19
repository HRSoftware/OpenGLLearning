#pragma once

#include <rapidjson/rapidjson.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/document.h>
#include "rapidjson/error/en.h"
#include "../Loaders/ResourceLoader.h"
#include "../Core/Resource.h"
#include <string>
#include "../Cache/ResourceCache.h"
#include <regex>
#include <filesystem>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/document.h>
#include <rapidjson/document.h>


class ResourceManager
{
    public:
        ResourceManager(ResourceCache& cache) : resourceCache(cache), modelLoader(cache), materialLoader(cache.textureCache){};
        template<class T>
        void loadNewResource(ResourceType type, std::string pathToFile, std::string referenceName = "");
        ResourceHandle<Texture> loadNewResource(aiTextureType type, std::string pathToFile, std::string referenceName);


        int loadNewTexture(aiTextureType type, std::string pathToFile, std::string referenceNamed = "");
         int loadNewShader(int shaderMask, ::string pathToFile, std::string referenceName = "");
         Material loadNewMaterial(aiMaterial* mat, std::string pathToFile, std::string referenceNamed = "");
        Model loadNewModel(std::string name, std::string path, std::string);

        template<class T>
        ResourceHandle<T> getHandleForResource(Resource<T>* res, std::string name);

        void LoadShaders(const rapidjson::Value& shaders);
        void LoadModels(const rapidjson::Value& models);
        void LoadTextures(const rapidjson::Value& textures);
        void LoadGameObjects(const rapidjson::Value& gameObjects);
        void LoadAllBasicResources();


        void handleJSONFile(const rapidjson::Value&);
        void handleJSONItem(const rapidjson::GenericValue<rapidjson::UTF8<>>&);
        void handleJSONObject(const rapidjson::GenericValue<rapidjson::UTF8<>>::ConstObject&);
        void handleJSONArray(const rapidjson::Value::ConstArray&);

        ResourceCache& resourceCache;

    private:
    ResourceLoader<Texture> textureLoader;
    ResourceLoader<Material> materialLoader;
    ResourceLoader<Shader> shaderLoader;
    ResourceLoader<Model> modelLoader;

    void handleFile(filesystem::directory_entry file);
    void handleFolder(filesystem::directory_iterator dir);
};

