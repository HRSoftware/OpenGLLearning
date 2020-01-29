#pragma once

#include "Data_Structures/Material.h"
#include "Camera.h"

namespace SceneStats {
    inline std::shared_ptr<Camera> currentCamera = nullptr;
    inline int _screenWidth = 1920;
    inline int _screenHeight = 1080;


}


namespace RenderSystem {
   inline std::shared_ptr<Material> activeMaterial;
   inline std::shared_ptr<Camera> currentCamera;
}
