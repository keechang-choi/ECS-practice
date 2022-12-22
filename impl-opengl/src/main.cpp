#include "window_manager.hpp"

int main() {
  ecs_opengl::WindowManager window_manager{"First ECS practice", 640, 480, 0,
                                           0};
  while (!window_manager.ShouldClose()) {
    glfwPollEvents();
  }
  return 0;
}