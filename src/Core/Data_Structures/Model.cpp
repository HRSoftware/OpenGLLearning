#include "stdafx.h"

#include "../../../include/Core/Data_Structures/Mesh.h"

#include "../../../include/Builders/MaterialBuilder.h"

#include "../../../include/Core/Data_Structures/Model.h"
#include "../../../include/Core/Data_Structures/Material.h"


Model& Model::operator=(Model newModel)
{
    meshes = newModel.meshes;
    directory = newModel.directory;
    //textures = newModel.textures;
    modelName = newModel.modelName;
    return *this;
}

