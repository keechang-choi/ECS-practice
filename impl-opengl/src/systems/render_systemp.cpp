#include "components/camera.hpp"
#include "components/renderable.hpp"
#include "components/transform.hpp"
#include "core/coordinator.hpp"
#include "graphics/shader.hpp"
#include "render_system.hpp"

// std
#include "cmath"

namespace ecs_opengl {
void RenderSystem::Init() {
  shader_ = std::make_unique<Shader>("../shaders/simple_shader.vert",
                                     "../shaders/simple_shader.frag");

  // assert camera in coordinator?

  std::vector<glm::vec3> vertices = {
      glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec3{0.5f, -0.5f, -0.5f},
      glm::vec3{0.5f, 0.5f, -0.5f},   glm::vec3{0.5f, 0.5f, -0.5f},
      glm::vec3{-0.5f, 0.5f, -0.5f},  glm::vec3{-0.5f, -0.5f, -0.5f},
      glm::vec3{-0.5f, -0.5f, 0.5},   glm::vec3{0.5f, -0.5f, 0.5},
      glm::vec3{0.5f, 0.5f, 0.5},     glm::vec3{0.5f, 0.5f, 0.5},
      glm::vec3{-0.5f, 0.5f, 0.5},    glm::vec3{-0.5f, -0.5f, 0.5},
      glm::vec3{-0.5f, 0.5f, 0.5f},   glm::vec3{-0.5f, 0.5f, -0.5f},
      glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec3{-0.5f, -0.5f, -0.5f},
      glm::vec3{-0.5f, -0.5f, 0.5f},  glm::vec3{-0.5f, 0.5f, 0.5f},
      glm::vec3{0.5f, 0.5f, 0.5},     glm::vec3{0.5f, 0.5f, -0.5},
      glm::vec3{0.5f, -0.5f, -0.5},   glm::vec3{0.5f, -0.5f, -0.5},
      glm::vec3{0.5f, -0.5f, 0.5},    glm::vec3{0.5f, 0.5f, 0.5},
      glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec3{0.5f, -0.5f, -0.5f},
      glm::vec3{0.5f, -0.5f, 0.5f},   glm::vec3{0.5f, -0.5f, 0.5f},
      glm::vec3{-0.5f, -0.5f, 0.5f},  glm::vec3{-0.5f, -0.5f, -0.5f},
      glm::vec3{-0.5f, 0.5f, -0.5},   glm::vec3{0.5f, 0.5f, -0.5},
      glm::vec3{0.5f, 0.5f, 0.5},     glm::vec3{0.5f, 0.5f, 0.5},
      glm::vec3{-0.5f, 0.5f, 0.5},    glm::vec3{-0.5f, 0.5f, -0.5}};
}
}  // namespace ecs_opengl