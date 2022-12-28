#pragma once

#include "components/camera.hpp"
#include "components/renderable.hpp"
#include "components/transform.hpp"
#include "core/coordinator.hpp"
#include "core/system.hpp"
#include "graphics/shader.hpp"

// std
#include <memory>

namespace ecs_opengl {
class RenderSystem : public System {
 public:
  void Init();
  void Update(const Coordinator& coordinator, float dt);

 private:
  std::unique_ptr<Shader> shader_;

  GLuint vao_{};
  GLuint vbo_vertices_{};
  GLuint vbo_normals_{};
};
}  // namespace ecs_opengl