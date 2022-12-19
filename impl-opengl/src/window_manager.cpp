#include "window_manager.hpp"

namespace ecs_opengl {
void WindowManager::init(std::string const& window_title, uint32_t width,
                         uint32_t height, uint32_t pos_x, uint32_t pos_y) {
  glfwInit();
  window =
      glfwCreateWindow(width, height, window_title.c_str(), nullptr, nullptr);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glfwSwapInterval(2);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glEnable(GL_DEPTH_TEST);
}
void WindowManager::update() { glfwSwapBuffers(window); }
void WindowManager::shutdown() {
  glfwDestroyWindow(window);
  glfwTerminate();
}
}  // namespace ecs_opengl