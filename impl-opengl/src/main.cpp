#include <iostream>

#include "app.hpp"
#include "app2.hpp"
int main() {
  // {
  //   ecs_opengl::App app1;
  //   std::cout << "@@@@@@"
  //             << "app1 init @@@@" << std::endl;

  //   app1.run();
  // }

  {
    oop_opengl::App app2;
    std::cout << "@@@@@@"
              << "app2 init @@@@" << std::endl;
    app2.run();
  }
  return 0;
}