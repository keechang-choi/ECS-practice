#pragma once

// libs
#include <glm/glm.hpp>

namespace ecs_opengl {
struct RigidBody {
  glm::vec3 velocity{};
  glm::vec3 acceleration{};
};
}  // namespace ecs_opengl