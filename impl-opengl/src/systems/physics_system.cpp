#include "physics_system.hpp"

#include "components/gravity.hpp"
#include "components/rigid_body.hpp"
#include "components/transform.hpp"

namespace ecs_opengl {
void PhysicsSystem::Init() {}

void PhysicsSystem::Update(const Coordinator& coordinator, float dt) {
  for (auto const& entity : GetEntities()) {
    auto& rigid_body = coordinator.GetComponent<RigidBody>(entity);
    auto& transform = coordinator.GetComponent<Transform>(entity);
    auto const& gravity = coordinator.GetComponent<Gravity>(entity);

    transform.translation += rigid_body.velocity * dt;
    // mass?
    rigid_body.velocity += gravity.force * dt;
  }
}
}  // namespace ecs_opengl