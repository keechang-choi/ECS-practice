#pragma once

// libs
#include <glm/glm.hpp>

namespace ecs_opengl {
struct Gravity {
  glm::vec3 force{};
};
}  // namespace ecs_opengl