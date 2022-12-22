#include "window_manager.hpp"

namespace ecs_opengl {
WindowManager::WindowManager(std::string name, uint32_t w, uint32_t h,
                             uint32_t x, uint32_t y)
    : window_title{name}, width{w}, height{h}, pos_x{x}, pos_y{y} {
  Init();
}

WindowManager::~WindowManager() { Shutdown(); }
void WindowManager::Init() {
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
void WindowManager::Update() { glfwSwapBuffers(window); }
void WindowManager::Shutdown() {
  glfwDestroyWindow(window);
  glfwTerminate();
}
}  // namespace ecs_opengl