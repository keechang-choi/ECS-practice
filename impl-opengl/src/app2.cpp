#include "app2.hpp"

#include "components/camera.hpp"
#include "core/event_manager.hpp"
#include "core/types.hpp"
#include "oop/oop.hpp"
#include "window_manager.hpp"

// std
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

namespace oop_opengl {
void App::run() {
  ecs_opengl::WindowManager window_manager{
      "First ECS practice", 640, 480, 0, 0,
  };
  //   std::cout << "@@@@@@"
  //             << "window init @@@@" << std::endl;

  ecs_opengl::EventManager event_manager{};

  event_manager.AddListener(Events::Window::kQuit,
                            std::bind(&ecs_opengl::WindowManager::QuitHandler,
                                      &window_manager, std::placeholders::_1));

  //   std::cout << "@@@@@@"
  //             << "component register @@@@" << std::endl;

  PhysicsSystem physics_system{};
  physics_system.Init();

  RotationSystem rotation_system{};
  rotation_system.Init();

  RenderSystem render_system{};
  render_system.Init();

  //   std::cout << "@@@@@@"
  //             << "render system init @@@@" << std::endl;
  // camera

  EntityCamera camera{
      ecs_opengl::Transform{
          .translation = glm::vec3{0.f, 0.f, 200.f /*200.f, 200.f, 300.f*/}},
      ecs_opengl::Camera{.projection_matrix =
                             ecs_opengl::MakePerspectiveProjection(
                                 45.f, 640.f / 480.f, 0.1f, 1000.f)}};

  int num_entities = ecs_opengl::kMaxEntities - 1;
  std::vector<std::unique_ptr<EntityRenderable>> entities;
  entities.reserve(num_entities);

  std::default_random_engine generator;
  generator.seed(1111);
  std::uniform_real_distribution<float> random_position(-100.f, 100.f);
  std::uniform_real_distribution<float> random_rotation(0.f, 3.f);
  std::uniform_real_distribution<float> random_scale(1.f, 5.f);
  std::uniform_real_distribution<float> random_color(0.f, 1.f);
  std::uniform_real_distribution<float> random_gravity(-10.f, -1.f);
  std::uniform_real_distribution<float> random_angular_velocity(0.f, 3.f);

  float scale = random_scale(generator);

  for (int i = 0; i < num_entities; i++) {
    auto g =
        ecs_opengl::Gravity{glm::vec3{0.f, random_gravity(generator), 0.f}};
    auto rb = ecs_opengl::RigidBody{
        .velocity = glm::vec3{0.f, 0.f, 0.f},
        .acceleration = glm::vec3{0.f, 0.f, 0.f},
    };
    auto ro = ecs_opengl::Rotational{.angular_velocity = glm::vec3{
                                         0.f,
                                         0.f,
                                         random_angular_velocity(generator),
                                     }};
    auto t = ecs_opengl::Transform{
        .translation =
            glm::vec3{
                random_position(generator),
                300.f + random_position(generator),
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
                random_scale(generator),
                random_scale(generator),
                random_scale(generator),
            },
    };
    auto r = ecs_opengl::Renderable{.color = glm::vec3{
                                        random_color(generator),
                                        random_color(generator),
                                        random_color(generator),
                                    }};
    entities.push_back(std::make_unique<EntityRenderable>(t, g, rb, ro, r));
  }
  double lastTime = glfwGetTime();
  int nbFrames = 0;

  float dt = 0.0f;
  while (!window_manager.ShouldClose()) {
    auto start_time = std::chrono::high_resolution_clock::now();

    // Measure speed
    double currentTime = glfwGetTime();
    nbFrames++;
    if (currentTime - lastTime >=
        1.0) {  // If last prinf() was more than 1 sec ago
      // printf and reset timer
      std::cout << std::fixed << std::setprecision(4)
                << 1000.0 / double(nbFrames) << " ms/frame\n";
      nbFrames = 0;
      lastTime += 1.0;
    }

    render_system.Update(camera, entities, dt);
    physics_system.Update(event_manager, entities, dt);
    rotation_system.Update(event_manager, entities, dt);

    // swap
    window_manager.Update();
    glfwPollEvents();

    auto stop_time = std::chrono::high_resolution_clock::now();
    dt = std::chrono::duration<float, std::chrono::seconds::period>(stop_time -
                                                                    start_time)
             .count();
  }
}
}  // namespace oop_opengl