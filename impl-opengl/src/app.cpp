#include "app.hpp"

#include "components/camera.hpp"
#include "components/renderable.hpp"
#include "components/transform.hpp"
#include "core/coordinator.hpp"
#include "core/types.hpp"
#include "systems/render_system.hpp"
#include "window_manager.hpp"

// std
#include <chrono>
#include <iostream>
#include <random>

namespace ecs_opengl {
void App::run() {
  WindowManager window_manager{
      "First ECS practice", 640, 480, 0, 0,
  };
  std::cout << "@@@@@@"
            << "window init @@@@" << std::endl;
  Coordinator coordinator;
  coordinator.Init();

  coordinator.RegisterComponent<Camera>();
  coordinator.RegisterComponent<Renderable>();
  coordinator.RegisterComponent<Transform>();

  std::cout << "@@@@@@"
            << "component register @@@@" << std::endl;

  const auto render_system = coordinator.RegisterSystem<RenderSystem>();
  {
    Signature signature;
    signature.set(coordinator.GetComponentType<Renderable>());
    signature.set(coordinator.GetComponentType<Transform>());
    coordinator.SetSystemSignature<RenderSystem>(signature);
  }
  render_system->Init();

  std::cout << "@@@@@@"
            << "render system init @@@@" << std::endl;
  // camera
  {
    Entity camera = coordinator.CreateEntity();
    coordinator.AddComponent(
        camera, Transform{.translation = glm::vec3{200.f, 200.f, 300.f}});
    coordinator.AddComponent(
        camera, Camera{.projection_matrix =
                           MakePerspectiveProjection(45.f, 1.f, 0.1f, 1000.f)});

    coordinator.SetCamera(camera);
  }
  std::vector<Entity> entities(kMaxEntities - 1);

  std::default_random_engine generator;
  std::uniform_real_distribution<float> random_position(-100.f, 100.f);
  std::uniform_real_distribution<float> random_rotation(0.f, 3.f);
  std::uniform_real_distribution<float> random_scale(3.f, 5.f);
  std::uniform_real_distribution<float> random_color(0.f, 1.f);
  std::uniform_real_distribution<float> random_gravity(-10.f, -1.f);

  float scale = random_scale(generator);

  for (auto& i : entities) {
    Entity entity = coordinator.CreateEntity();
    coordinator.AddComponent(entity, Transform{
                                         .translation =
                                             glm::vec3{
                                                 random_position(generator),
                                                 random_position(generator),
                                                 random_position(generator),
                                             },
                                         .rotation =
                                             glm::vec3{
                                                 random_rotation(generator),
                                                 random_rotation(generator),
                                                 random_rotation(generator),
                                             },
                                         .scale =
                                             glm::vec3{
                                                 scale,
                                                 scale,
                                                 scale,
                                             },
                                     });
    coordinator.AddComponent(entity, Renderable{.color = glm::vec3{
                                                    random_color(generator),
                                                    random_color(generator),
                                                    random_color(generator),
                                                }});
  }
  float dt = 0.0f;

  while (!window_manager.ShouldClose()) {
    auto start_time = std::chrono::high_resolution_clock::now();

    render_system->Update(coordinator, dt);

    // swap
    window_manager.Update();
    glfwPollEvents();

    auto stop_time = std::chrono::high_resolution_clock::now();
    dt = std::chrono::duration<float, std::chrono::seconds::period>(stop_time -
                                                                    start_time)
             .count();
  }
}
}  // namespace ecs_opengl