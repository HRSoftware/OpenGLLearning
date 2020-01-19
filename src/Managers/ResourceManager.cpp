#include "../../include/Managers/ResourceMangager.h"
template<class T>
void ResourceManager::loadNewResource(ResourceType type, std::string pathToFile, std::string referenceName)
{
    if (referenceName.empty())
        referenceName = pathToFile;
    switch ( type )
    {
    case RT_Shader:
         resourceCache.shaderCache.addShader(referenceName,shaderLoader.loadNewResource(GUID_Allocator::getNewUniqueGUID(), "Shaders/" + pathToFile));
    case RT_Model:
         resourceCache.modelCache.addModel(referenceName,modelLoader.loadNewResource(GUID_Allocator::getNewUniqueGUID(),referenceName, pathToFile));
    case RT_Texture:
        resourceCache.textureCache.addTexture(referenceName, textureLoader.loadNewResource(GUID_Allocator::getNewUniqueGUID(), pathToFile, aiTextureType_UNKNOWN).id);
    }
}

template<class T>
ResourceHandle<T> ResourceManager::getHandleForResource(Resource<T>* res, std::string name)
{
    switch ( res->getResourceType())
    {
    case RT_Shader:
        return resourceCache.shaderCache.findShader(name);
    case RT_Texture:
        return resourceCache.textureCache.findTexture(name);
    case RT_Model:
        return resourceCache.modelCache.findModel(name);
    case RT_Material:
        return resourceCache.materialCache.findMaterial(name);
    default:
        return;
    }
}

inline int ResourceManager::loadNewTexture(aiTextureType type, std::string pathToFile, std::string referenceName) 
{
    return resourceCache.textureCache.addTexture(pathToFile, textureLoader.loadNewResource(GUID_Allocator::getNewUniqueGUID(), pathToFile, type).id);
}

inline int ResourceManager::loadNewShader(int shaderMask, ::string pathToFile, std::string referenceName)
{
    ShaderBuilder newShader;
    newShader.createShader(GUID_Allocator::getNewUniqueGUID(), referenceName.empty() ? pathToFile : referenceName, pathToFile);

    if ((shaderMask & VERTEX) == VERTEX)
        newShader.addShader(VERTEX, pathToFile);

    if((shaderMask & FRAGMENT) == FRAGMENT)
        newShader.addShader(FRAGMENT, pathToFile);

    if ((shaderMask & GEOMETRY) == GEOMETRY)
        newShader.addShader(GEOMETRY, pathToFile);

    if ((shaderMask & COMPUTE) == COMPUTE)
        newShader.addShader(COMPUTE, pathToFile);

    if ((shaderMask & TESS_CONTROL) == TESS_CONTROL)
        newShader.addShader(TESS_CONTROL, pathToFile);

    if ((shaderMask & TESS_EVAL) == TESS_EVAL)
        newShader.addShader(TESS_EVAL, pathToFile);

    return resourceCache.shaderCache.addShader(referenceName, newShader.build());
}

inline Material ResourceManager::loadNewMaterial(aiMaterial* mat, std::string pathToFile, std::string referenceName)
{
    std::string matName = referenceName.empty() ? pathToFile : referenceName;
    MaterialBuilder newMaterial(resourceCache);
    newMaterial.create(GUID_Allocator::getNewUniqueGUID(), referenceName.empty() ? pathToFile : referenceName);

    aiTextureType _type = aiTextureType_UNKNOWN;
    std::vector<std::string> types = {
        "texture_diffuse",
        "texture_normal",
        "texture_specular",
        "texture_height"
    };

    for (std::string _typeString : types) {

        if (_typeString == "texture_diffuse")
            _type = aiTextureType_DIFFUSE;

        if (_typeString == "texture_normal")
            _type = aiTextureType_NORMALS;                        //Handle each type of texture

        if (_typeString == "texture_specular")
            _type = aiTextureType_SPECULAR;

        if (_typeString == "texture_height")
            _type = aiTextureType_HEIGHT;

        for (unsigned int i = 0; i < mat->GetTextureCount(_type); i++) {
            aiString str;
            mat->GetTexture(_type, i, &str);
            // check if texture was loaded before and if so
            bool skip = false;
            Texture _textureHandle = resourceCache.textureCache.findTexture(pathToFile + str.data);

            if (_textureHandle.id == -1) {
                std::string path = path + "/" + str.C_Str();
                path = std::regex_replace(path, std::regex("//"), "/");
                _textureHandle.id = loadNewTexture(_type, pathToFile);
                _textureHandle.type = _type;
            }

            newMaterial.addTexture(_textureHandle);
        }
    }

    //shader
    return resourceCache.materialCache.addMaterial(matName, newMaterial.build());
}

inline Model ResourceManager::loadNewModel(std::string name, std::string path, std::string shader)
{
    return resourceCache.modelCache.addModel(name, modelLoader.loadNewResource(name, path, shader));
}

inline void ResourceManager::LoadShaders(const rapidjson::Value& shaders)
{
    printf("\n=========|\tLoading Shaders\t|=========\n");
    for(auto& arrayObject : shaders.GetArray())
    {
        assert(arrayObject.IsObject());
        int shaderTypes = 0;
        for(auto& arrayShaderType : arrayObject.FindMember("type")->value.GetArray())
        {
            if (std::strcmp(arrayShaderType.GetString(), "VERTEX") == 0)
                shaderTypes |= ShaderType::VERTEX;
            if (std::strcmp(arrayShaderType.GetString(), "FRAGMENT") == 0)
                shaderTypes |= ShaderType::FRAGMENT;
            if (std::strcmp(arrayShaderType.GetString(), "COMPUTE") == 0)
                shaderTypes |= ShaderType::COMPUTE;
            if (std::strcmp(arrayShaderType.GetString(), "GEOMETRY") == 0)
                shaderTypes |= ShaderType::GEOMETRY;
            if (std::strcmp(arrayShaderType.GetString(), "TESS_CONTROL") == 0)
                shaderTypes |= ShaderType::TESS_CONTROL;
            if (std::strcmp(arrayShaderType.GetString(), "TELL_EVAL") == 0)
                shaderTypes |= ShaderType::TESS_EVAL;
        }


        loadNewShader(shaderTypes,
            arrayObject.FindMember("path")->value.GetString(),
            arrayObject.FindMember("name")->value.GetString());
    }
}

inline void ResourceManager::LoadModels(const rapidjson::Value& models)
{
    printf("\n=========|\tLoading Models\t|=========\n");
    for(auto& modelObject : models.GetArray())
    {
        for(auto& textureObject : modelObject.FindMember("textures")->value.GetObject())
        {
            loadNewTexture(aiTextureType_UNKNOWN, textureObject.value.GetString(), textureObject.name.GetString());

            printf("Path: %s,\t Name: %s\n", textureObject.value.GetString(), textureObject.name.GetString());
        }
        loadNewModel(modelObject.FindMember("name")->value.GetString(),
            modelObject.FindMember("model")->value.GetString(),
            modelObject.FindMember("shader")->value.GetString());
    }
}

inline void ResourceManager::LoadGameObjects(const rapidjson::Value& gameObjects)
{
    glm::vec3 scale;
    printf("\n=========|\tConfiguring GameObjects\t|=========\n");
    for(auto& gameObject : gameObjects.GetArray())
    {
        auto positionObject = gameObject.FindMember("position")->value.GetObject();

        glm::vec3 position = {
            positionObject.FindMember("x")->value.GetFloat(),
            positionObject.FindMember("y")->value.GetFloat(),
            positionObject.FindMember("z")->value.GetFloat()
        };

        auto scaleObject = gameObject.FindMember("scale")->value.GetObject();

        glm::vec3 scale = {
            scaleObject.FindMember("x")->value.GetFloat(),
            scaleObject.FindMember("y")->value.GetFloat(),
            scaleObject.FindMember("z")->value.GetFloat()
        };

        auto gameObjectName = gameObject.FindMember("name")->value.GetString();
        GameObject newGameObject;
        newGameObject.setName(gameObjectName);
        newGameObject.setPosition(position);
        newGameObject.setScale(scale);
        newGameObject.setModel(resourceCache.modelCache.findModel(gameObject.FindMember("model")->value.GetString()));
        newGameObject.updateModelMatrix();

        resourceCache.gameObjectCache.addGameObject(gameObjectName, newGameObject);

    }
}

void ResourceManager::LoadAllBasicResources()
{
    std::ifstream resourceFile("resources.json");

    rapidjson::IStreamWrapper isw(resourceFile);

    rapidjson::Document doc;
    doc.ParseStream(isw);

    rapidjson::GetParseErrorFunc GetParseError = rapidjson::GetParseError_En; // or whatever
    const RAPIDJSON_ERROR_CHARTYPE* errorMessage = GetParseError(doc.GetParseError());

    if(doc.HasParseError())
        std::cout << "Error reading resource file. Error Code:" << doc.GetParseError() << "\n\t -- " << GetParseError(doc.GetParseError()) << "\n\t -- " << doc.GetErrorOffset() << std::endl;

    LoadShaders(doc["Shaders"]);
    LoadModels(doc["Models"]);
    LoadGameObjects(doc["GameObjects"]);
}



inline void ResourceManager::handleJSONFile(const rapidjson::Value& item)
{
    if (item.IsArray())
        handleJSONArray(item.GetArray());
    if (item.IsObject())
        handleJSONObject(item.GetObject());
}

inline void ResourceManager::handleJSONItem(const rapidjson::GenericValue<rapidjson::UTF8<>>& item)
{
    if (item.IsString())
        printf("\n\t %s", item.GetString());

    if (item.IsArray())
        handleJSONArray(item.GetArray());

    if (item.IsObject())
        handleJSONObject(item.GetObject());
}

inline void ResourceManager::handleJSONArray(const rapidjson::Value::ConstArray& array)
{
    for ( const auto& itr : array )
    {
        if ( itr.IsString())
            printf("%s", itr.GetString());

        if ( itr.IsObject())
            handleJSONObject(itr.GetObject());

        if ( itr.IsArray())
            handleJSONArray(itr.GetArray());
    }
}

inline void ResourceManager::handleJSONObject(const rapidjson::GenericValue<rapidjson::UTF8<>>::ConstObject& object)
{
    for (auto& member : object)
    {
        printf("\t");
        handleJSONItem(member.value);
    }

}

inline void ResourceManager::handleFile(filesystem::directory_entry file)
{
    std::vector<string> textureExtensions = {".png", ".jpeg", ".tga", ".svg"};

    auto ext = file.path().extension().string();
    std::vector<string>::iterator it = std::find(textureExtensions.begin(), textureExtensions.end(), ext);
    if (it != textureExtensions.end())
    {   
        std::string path = std::regex_replace(file.path().string(), std::regex("\\\\"), "\\"); // 
        loadNewTexture(aiTextureType_UNKNOWN, path, path);
    }
}

inline void ResourceManager::handleFolder(filesystem::directory_iterator dir)
{
    for (auto const& entry : filesystem::directory_iterator(dir))
        if (entry.is_directory())
            handleFolder(filesystem::directory_iterator(entry.path().string()));
        else
            handleFile(entry);
}
