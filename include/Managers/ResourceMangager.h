#pragma once
#include "../Loaders/ResourceLoader.h"
#include "../Core/Resource.h"
#include <string>
#include "../Cache/ResourceCache.h"





class ResourceManager
{
public:
    ResourceManager(ResourceCache& cache) : resourceCache(cache), modelLoader(cache),
                                            materialLoader(cache.textureCache), shaderLoader(cache) {};
    template<class T>
    ResourceHandle<Texture> loadNewResource(aiTextureType type, std::string pathToFile, std::string referenceName);

    void loadNewResource(ResourceType type, std::string pathToFile, std::string referenceName = "");

    Texture loadNewTexture(aiTextureType type, std::string pathToFile, std::string referenceNamed = "");
    Shader loadNewShader(int shaderMask, ::string pathToFile, std::string referenceName = "");
    Material loadNewMaterial(aiMaterial* mat, std::string pathToFile, std::string referenceNamed = "");
    Model addNewModel(std::string name, std::string path, std::string shader);


    template<class T>
    ResourceHandle<T> getHandleForResource(Resource<T>* res, std::string name);
    void LoadAllBasicResources(std::string rootDirectory);

    void LoadShadersFromJson(const rapidjson::Value& shaders);
    void LoadModelsFromJson(const rapidjson::Value& models);
    void LoadTextures(const rapidjson::Value& textures);
    void LoadGameObjectsFromJson(const rapidjson::Value& gameObjects);
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
