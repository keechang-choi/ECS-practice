#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

// std
#include <string>

namespace ecs_opengl {
class WindowManager {
 public:
  WindowManager(std::string name, uint32_t w, uint32_t h, uint32_t x,
                uint32_t y);
  ~WindowManager();

  WindowManager(const WindowManager&) = delete;
  WindowManager& operator=(const WindowManager&) = delete;

  void Update();
  bool ShouldClose() { return glfwWindowShouldClose(window); }

 private:
  void Init();
  void Shutdown();

  std::string window_title;
  uint32_t width;
  uint32_t height;
  uint32_t pos_x;
  uint32_t pos_y;
  GLFWwindow* window;
};
}  // namespace ecs_opengl