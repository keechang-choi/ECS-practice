#pragma once

// std
#include <cassert>
#include <limits>

// libs
// #define GLM_FORCE_RADIANS
// #define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace ecs_opengl {
glm::mat4 MakePerspectiveProjection(float fovy, float aspect, float near,
                                    float far);
glm::mat4 MakeViewMatrix(glm::vec3 position, glm::vec3 target, glm::vec3 up);
struct Camera {
  glm::mat4 projection_matrix{1.f};
  glm::mat4 view_matrix{1.f};
};
}  // namespace ecs_opengl