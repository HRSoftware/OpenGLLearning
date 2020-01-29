#pragma once

#include "Data_Structures/Material.h"
#include "Camera.h"
namespace Globals{
    namespace Display {
        inline int _screenWidth = 1920;
        inline int _screenHeight = 1080;
        inline glm::vec2 _screenDimensions;
    }

    namespace Window {
        inline std::shared_ptr<GLFWwindow> activeWindow = nullptr;
        inline float lastX;
        inline float lastY;
        inline bool firstMouse = true;
    }

    namespace RenderSystem {
       inline std::shared_ptr<Material> activeMaterial;
       inline std::shared_ptr<Camera> currentCamera;
    }

}