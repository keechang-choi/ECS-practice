#pragma once

#include "core/coordinator.hpp"
#include "core/system.hpp"

namespace ecs_opengl {
class RotationalSystem : public System {
 public:
  void Init();
  void Update(Coordinator& coordinator, float dt);
};
}  // namespace ecs_opengl
