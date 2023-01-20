#pragma once

#include "core/coordinator.hpp"
#include "core/system.hpp"

namespace ecs_opengl {
class PhysicsSystem : public System {
 public:
  void Init();
  void Update(const Coordinator& coordinator, float dt);
};
}  // namespace ecs_opengl
