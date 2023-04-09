#pragma once

// libs
#include <glm/glm.hpp>

namespace ecs_opengl {
struct Rotational {
  glm::vec3 angular_velocity{1.f};
  glm::vec3 angular_acceleration{0.f};
};
}  // namespace ecs_opengl