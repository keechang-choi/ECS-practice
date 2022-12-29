#include "render_system.hpp"

//
#include "components/camera.hpp"
#include "components/renderable.hpp"
#include "components/transform.hpp"
#include "core/coordinator.hpp"
#include "graphics/shader.hpp"

// std
#include <cmath>
#include <iostream>

namespace ecs_opengl {
void RenderSystem::Init() {
  shader_ = std::make_unique<Shader>("./shaders/simple_shader.vert",
                                     "./shaders/simple_shader.frag");

  // assert camera in coordinator?

  std::vector<glm::vec3> vertices = {
      glm::vec3{0.5f, 0.5f, -0.5f},    //
      glm::vec3{0.5f, 0.5f, -0.5f},    //
      glm::vec3{-0.5f, -0.5f, -0.5f},  //
      glm::vec3{0.5f, -0.5f, -0.5f},   //
      glm::vec3{-0.5f, 0.5f, -0.5f},   //
      glm::vec3{-0.5f, -0.5f, -0.5f},  //
      glm::vec3{-0.5f, -0.5f, 0.5},    //
      glm::vec3{0.5f, -0.5f, 0.5},     //
      glm::vec3{0.5f, 0.5f, 0.5},      //
      glm::vec3{0.5f, 0.5f, 0.5},      //
      glm::vec3{-0.5f, 0.5f, 0.5},     //
      glm::vec3{-0.5f, -0.5f, 0.5},    //
      glm::vec3{-0.5f, 0.5f, 0.5f},    //
      glm::vec3{-0.5f, 0.5f, -0.5f},   //
      glm::vec3{-0.5f, -0.5f, -0.5f},  //
      glm::vec3{-0.5f, -0.5f, -0.5f},  //
      glm::vec3{-0.5f, -0.5f, 0.5f},   //
      glm::vec3{-0.5f, 0.5f, 0.5f},    //
      glm::vec3{0.5f, 0.5f, 0.5},      //
      glm::vec3{0.5f, 0.5f, -0.5},     //
      glm::vec3{0.5f, -0.5f, -0.5},    //
      glm::vec3{0.5f, -0.5f, -0.5},    //
      glm::vec3{0.5f, -0.5f, 0.5},     //
      glm::vec3{0.5f, 0.5f, 0.5},      //
      glm::vec3{-0.5f, -0.5f, -0.5f},  //
      glm::vec3{0.5f, -0.5f, -0.5f},   //
      glm::vec3{0.5f, -0.5f, 0.5f},    //
      glm::vec3{0.5f, -0.5f, 0.5f},    //
      glm::vec3{-0.5f, -0.5f, 0.5f},   //
      glm::vec3{-0.5f, -0.5f, -0.5f},  //
      glm::vec3{-0.5f, 0.5f, -0.5},    //
      glm::vec3{0.5f, 0.5f, -0.5},     //
      glm::vec3{0.5f, 0.5f, 0.5},      //
      glm::vec3{0.5f, 0.5f, 0.5},      //
      glm::vec3{-0.5f, 0.5f, 0.5},     //
      glm::vec3{-0.5f, 0.5f, -0.5},    //
  };

  std::vector<glm::vec3> normals = {
      glm::vec3{0.0f, 0.0f, -1.0f},  //
      glm::vec3{0.0f, 0.0f, -1.0f},  //
      glm::vec3{0.0f, 0.0f, -1.0f},  //
      glm::vec3{0.0f, 0.0f, -1.0f},  //
      glm::vec3{0.0f, 0.0f, -1.0f},  //
      glm::vec3{0.0f, 0.0f, -1.0f},  //
      glm::vec3{0.0f, 0.0f, 1.0f},   //
      glm::vec3{0.0f, 0.0f, 1.0f},   //
      glm::vec3{0.0f, 0.0f, 1.0f},   //
      glm::vec3{0.0f, 0.0f, 1.0f},   //
      glm::vec3{0.0f, 0.0f, 1.0f},   //
      glm::vec3{0.0f, 0.0f, 1.0f},   //
      glm::vec3{-1.0f, 0.0f, 0.0f},  //
      glm::vec3{-1.0f, 0.0f, 0.0f},  //
      glm::vec3{-1.0f, 0.0f, 0.0f},  //
      glm::vec3{-1.0f, 0.0f, 0.0f},  //
      glm::vec3{-1.0f, 0.0f, 0.0f},  //
      glm::vec3{-1.0f, 0.0f, 0.0f},  //
      glm::vec3{1.0f, 0.0f, 0.0f},   //
      glm::vec3{1.0f, 0.0f, 0.0f},   //
      glm::vec3{1.0f, 0.0f, 0.0f},   //
      glm::vec3{1.0f, 0.0f, 0.0f},   //
      glm::vec3{1.0f, 0.0f, 0.0f},   //
      glm::vec3{1.0f, 0.0f, 0.0f},   //
      glm::vec3{0.0f, -1.0f, 0.0f},  //
      glm::vec3{0.0f, -1.0f, 0.0f},  //
      glm::vec3{0.0f, -1.0f, 0.0f},  //
      glm::vec3{0.0f, -1.0f, 0.0f},  //
      glm::vec3{0.0f, -1.0f, 0.0f},  //
      glm::vec3{0.0f, -1.0f, 0.0f},  //
      glm::vec3{0.0f, 1.0f, 0.0f},   //
      glm::vec3{0.0f, 1.0f, 0.0f},   //
      glm::vec3{0.0f, 1.0f, 0.0f},   //
      glm::vec3{0.0f, 1.0f, 0.0f},   //
      glm::vec3{0.0f, 1.0f, 0.0f},   //
      glm::vec3{0.0f, 1.0f, 0.0},    //
  };

  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);

  // vertices
  glGenBuffers(1, &vbo_vertices_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(),
               vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
                        (void*)nullptr);
  glEnableVertexAttribArray(0);

  // surface normal
  glGenBuffers(1, &vbo_normals_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_normals_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(),
               normals.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
                        (void*)nullptr);
  glEnableVertexAttribArray(1);

  // clear current vao
  glBindVertexArray(0);
}

void RenderSystem::Update(const Coordinator& coordinator, float dt) {
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shader_->Activate();
  glBindVertexArray(vao_);

  Entity camera = coordinator.GetCamera();

  auto& camera_transform = coordinator.GetComponent<Transform>(camera);
  auto& camera_camera = coordinator.GetComponent<Camera>(camera);

  for (const auto& entity : GetEntities()) {
    std::cout << "entity: " << entity << std::endl;
    const auto& transform = coordinator.GetComponent<Transform>(entity);
    const auto& renderable = coordinator.GetComponent<Renderable>(entity);

    glm::mat4 view{1.f};
    view[0][3] = -camera_transform.translation.x;
    view[1][3] = -camera_transform.translation.y;
    view[2][3] = -camera_transform.translation.z;

    // yxz
    glm::mat4 rotation{1.f};
    /*const float c3 = glm::cos(transform.rotation.z);
    const float s3 = glm::sin(transform.rotation.z);
    const float c2 = glm::cos(transform.rotation.x);
    const float s2 = glm::sin(transform.rotation.x);
    const float c1 = glm::cos(transform.rotation.y);
    const float s1 = glm::sin(transform.rotation.y);

    const glm::vec3 u{(c1 * c3 + s1 * s2 * s3), (c2 * s3),
                      (c1 * s2 * s3 - c3 * s1)};
    const glm::vec3 v{(c3 * s1 * s2 - c1 * s3), (c2 * c3),
                      (c1 * c3 * s2 + s1 * s3)};
    const glm::vec3 w{(c2 * s1), (-s2), (c1 * c2)};

    rotation[0][0] = u.x;
    rotation[1][0] = u.y;
    rotation[2][0] = u.z;
    rotation[0][1] = v.x;
    rotation[1][1] = v.y;
    rotation[2][1] = v.z;
    rotation[0][2] = w.x;
    rotation[1][2] = w.y;
    rotation[2][2] = w.z;*/

    glm::mat4 translation{1.f};
    translation[0][3] = transform.translation.x;
    translation[1][3] = transform.translation.y;
    translation[2][3] = transform.translation.z;

    glm::mat4 scale{1.f};
    scale[0][0] = transform.scale.x;
    scale[1][1] = transform.scale.y;
    scale[2][2] = transform.scale.z;

    glm::mat4 model = translation * scale * rotation;
    glm::mat4 projection = camera_camera.projection_matrix;

    shader_->SetUniform<glm::mat4>("uModel", model);
    shader_->SetUniform<glm::mat4>("uView", view);
    shader_->SetUniform<glm::mat4>("uProjection", projection);
    shader_->SetUniform<glm::vec3>("uColor", renderable.color);

    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
  // unbind
  glBindVertexArray(0);
}
}  // namespace ecs_opengl