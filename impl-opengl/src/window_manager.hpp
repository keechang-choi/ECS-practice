#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

// std
#include <string>

namespace ecs_opengl {
class WindowManager {
 public:
  void init(std::string const& window_title, uint32_t width, uint32_t height,
            uint32_t pos_x, uint32_t pos_y);
  void update();
  void shutdown();

 private:
  GLFWwindow* window;
};
}  // namespace ecs_opengl