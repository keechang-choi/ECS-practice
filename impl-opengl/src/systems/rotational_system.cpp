#include "rotational_system.hpp"

#include "components/rotational.hpp"
#include "components/transform.hpp"

namespace ecs_opengl {
void RotationalSystem::Init() {}

void RotationalSystem::Update(Coordinator& coordinator, float dt) {
  if (GetEntities().size() == 0) {
    coordinator.SendEvent(Events::Window::kQuit);
  }
  // for (auto const& entity : GetEntities()) {
  //   auto& transform = coordinator.GetComponent<Transform>(entity);
  //   auto& rotational = coordinator.GetComponent<Rotational>(entity);
  //   if (transform.translation.y < -50) {
  //     coordinator.RemoveComponent<Rotational>(entity);
  //   }
  // }
  for (auto const& entity : GetEntities()) {
    auto& transform = coordinator.GetComponent<Transform>(entity);
    auto& rotational = coordinator.GetComponent<Rotational>(entity);

    transform.rotation += rotational.angular_velocity * dt;
    // anglular acceleration

    // if (transform.translation.y < -100) {
    //   coordinator.DestroyEntity(entity);
    // }
    if (transform.translation.y < -50) {
      coordinator.RemoveComponent<Rotational>(entity);
    }
  }
}
}  // namespace ecs_opengl