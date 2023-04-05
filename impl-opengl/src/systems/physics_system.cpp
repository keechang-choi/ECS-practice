#include "physics_system.hpp"

#include "components/gravity.hpp"
#include "components/rigid_body.hpp"
#include "components/transform.hpp"

namespace ecs_opengl {
void PhysicsSystem::Init() {}

void PhysicsSystem::Update(Coordinator& coordinator, float dt) {
  if (GetEntities().size() == 0) {
    coordinator.SendEvent(Events::Window::kQuit);
  }
  for (auto const& entity : GetEntities()) {
    auto& rigid_body = coordinator.GetComponent<RigidBody>(entity);
    auto& transform = coordinator.GetComponent<Transform>(entity);
    auto const& gravity = coordinator.GetComponent<Gravity>(entity);

    transform.translation += rigid_body.velocity * dt;

    transform.rotation += rigid_body.angular_velocity * dt;
    // mass?
    rigid_body.velocity += gravity.force * dt;
    // anglular acceleration

    if (transform.translation.y < -100) {
      coordinator.DestroyEntity(entity);
    }
  }
}
}  // namespace ecs_opengl