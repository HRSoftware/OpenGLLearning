#pragma once
#include "Camera.h"
#include <memory>
#include <glfw3.h>

namespace SceneStats{
    inline float deltaTime = 0.0f;
    inline std::shared_ptr<Camera> currentCamera;
    inline std::shared_ptr<GLFWwindow> window;

    inline int _screenWidth = 0;
    inline int _screenHeight = 0;

    inline float lastX = 0;
    inline float lastY = 0;
    inline bool firstMouse = true;


}
