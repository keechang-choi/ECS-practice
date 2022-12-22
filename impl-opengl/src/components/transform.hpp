#pragma once

// libs
#include <glm/glm.hpp>

namespace ecs_opengl {
struct Transform {
  glm::vec3 translation{};
  glm::vec3 rotation{};
  glm::vec3 scale{1.f, 1.f, 1.f};
};
}  // namespace ecs_opengl