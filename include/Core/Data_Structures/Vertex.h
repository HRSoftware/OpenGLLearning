#pragma once
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
struct Vertex {
    glm::vec3 Position{0};
    glm::vec3 Normal{0};
    glm::vec2 TexCoords{0};
    glm::vec3 Tangent{0};
    glm::vec3 Bitangent{0};
};