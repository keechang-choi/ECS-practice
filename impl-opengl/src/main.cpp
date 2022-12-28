#include <iostream>

#include "app.hpp"
int main() {
  ecs_opengl::App app;
  std::cout << "@@@@@@"
            << "app init @@@@" << std::endl;

  app.run();
  return 0;
}