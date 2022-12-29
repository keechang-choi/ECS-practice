#include "window_manager.hpp"

// std
#include <iostream>

namespace ecs_opengl {
WindowManager::WindowManager(std::string name, uint32_t w, uint32_t h,
                             uint32_t x, uint32_t y)
    : window_title_{name}, width_{w}, height_{h}, pos_x_{x}, pos_y_{y} {
  Init();
}

WindowManager::~WindowManager() { Shutdown(); }
void WindowManager::Init() {
  glfwInit();

  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  window_ = glfwCreateWindow(width_, height_, window_title_.c_str(), nullptr,
                             nullptr);
  std::cout << "window: " << window_ << std::endl;
  glfwMakeContextCurrent(window_);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glfwSwapInterval(2);

  glClearColor(0.f, 0.f, 0.f, 1.f);
  glEnable(GL_DEPTH_TEST);
}
void WindowManager::Update() { glfwSwapBuffers(window_); }
void WindowManager::Shutdown() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}
}  // namespace ecs_opengl