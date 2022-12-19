#include "window_manager.hpp"

int main() {
  ecs_opengl::WindowManager window_manager;
  window_manager.init("First ECS practice", 1920, 1080, 0, 0);
  while (1) {
    ;
  }
  return 0;
}