#include "oop.hpp"

#include "components/camera.hpp"
#include "graphics/shader.hpp"

// std
#include <cmath>
#include <iostream>

namespace oop_opengl {
EntityTransform::EntityTransform(ecs_opengl::Transform t) : transform{t} {};

EntityPhysics::EntityPhysics(ecs_opengl::Transform t, ecs_opengl::Gravity g,
                             ecs_opengl::RigidBody rb)
    : EntityTransform(t), gravity{g}, rigid_body{rb} {};

EntityRenderable::EntityRenderable(ecs_opengl::Transform t,
                                   ecs_opengl::Gravity g,
                                   ecs_opengl::RigidBody rb,
                                   ecs_opengl::Renderable r)
    : EntityPhysics(t, g, rb), renderable{r} {};

EntityCamera::EntityCamera(ecs_opengl::Transform t, ecs_opengl::Camera c)
    : EntityTransform(t), camera{c} {};

void RenderSystem::Init() {
  shader_ = std::make_unique<ecs_opengl::Shader>(
      "./shaders/simple_shader.vert", "./shaders/simple_shader.frag");

  // assert camera in coordinator?

  std::vector<glm::vec3> vertices = {
      // glm::vec3{-1.0f, -1.0f, 0.0f},  //
      // glm::vec3{1.0f, -1.0f, 0.0f},   //
      // glm::vec3{0.0f, 1.0f, 0.0f},    //
      glm::vec3{-1.0f, -1.0f, -1.0f},  //
      glm::vec3{-1.0f, -1.0f, 1.0f},   //
      glm::vec3{-1.0f, 1.0f, 1.0f},    //

      glm::vec3{1.0f, 1.0f, -1.0f},    //
      glm::vec3{-1.0f, -1.0f, -1.0f},  //
      glm::vec3{-1.0f, 1.0f, -1.0f},   //

      glm::vec3{1.0f, -1.0f, 1.0f},    //
      glm::vec3{-1.0f, -1.0f, -1.0f},  //
      glm::vec3{1.0f, -1.0f, -1.0f},   //

      glm::vec3{1.0f, 1.0f, -1.0f},    //
      glm::vec3{1.0f, -1.0f, -1.0f},   //
      glm::vec3{-1.0f, -1.0f, -1.0f},  //

      glm::vec3{-1.0f, -1.0f, -1.0f},  //
      glm::vec3{-1.0f, 1.0f, 1.0f},    //
      glm::vec3{-1.0f, 1.0f, -1.0f},   //

      glm::vec3{1.0f, -1.0f, 1.0f},    //
      glm::vec3{-1.0f, -1.0f, 1.0f},   //
      glm::vec3{-1.0f, -1.0f, -1.0f},  //

      glm::vec3{-1.0f, 1.0f, 1.0f},   //
      glm::vec3{-1.0f, -1.0f, 1.0f},  //
      glm::vec3{1.0f, -1.0f, 1.0f},   //

      glm::vec3{1.0f, 1.0f, 1.0f},    //
      glm::vec3{1.0f, -1.0f, -1.0f},  //
      glm::vec3{1.0f, 1.0f, -1.0f},   //

      glm::vec3{1.0f, -1.0f, -1.0f},  //
      glm::vec3{1.0f, 1.0f, 1.0f},    //
      glm::vec3{1.0f, -1.0f, 1.0f},   //

      glm::vec3{1.0f, 1.0f, 1.0f},    //
      glm::vec3{1.0f, 1.0f, -1.0f},   //
      glm::vec3{-1.0f, 1.0f, -1.0f},  //

      glm::vec3{1.0f, 1.0f, 1.0f},    //
      glm::vec3{-1.0f, 1.0f, -1.0f},  //
      glm::vec3{-1.0f, 1.0f, 1.0f},   //

      glm::vec3{1.0f, 1.0f, 1.0f},   //
      glm::vec3{-1.0f, 1.0f, 1.0f},  //
      glm::vec3{1.0f, -1.0f, 1.0f},  //
  };

  std::vector<glm::vec3> normals = {
      glm::vec3{-1.0f, 0.0f, 0.0f},  //
      glm::vec3{-1.0f, 0.0f, 0.0f},  //
      glm::vec3{-1.0f, 0.0f, 0.0f},  //

      glm::vec3{0.0f, 0.0f, -1.0f},  //
      glm::vec3{0.0f, 0.0f, -1.0f},  //
      glm::vec3{0.0f, 0.0f, -1.0f},  //

      glm::vec3{0.0f, -1.0f, 0.0f},  //
      glm::vec3{0.0f, -1.0f, 0.0f},  //
      glm::vec3{0.0f, -1.0f, 0.0f},  //

      glm::vec3{0.0f, 0.0f, -1.0f},  //
      glm::vec3{0.0f, 0.0f, -1.0f},  //
      glm::vec3{0.0f, 0.0f, -1.0f},  //

      glm::vec3{-1.0f, 0.0f, 0.0f},  //
      glm::vec3{-1.0f, 0.0f, 0.0f},  //
      glm::vec3{-1.0f, 0.0f, 0.0f},  //

      glm::vec3{0.0f, -1.0f, 0.0f},  //
      glm::vec3{0.0f, -1.0f, 0.0f},  //
      glm::vec3{0.0f, -1.0f, 0.0f},  //

      glm::vec3{0.0f, 0.0f, 1.0f},  //
      glm::vec3{0.0f, 0.0f, 1.0f},  //
      glm::vec3{0.0f, 0.0f, 1.0f},  //

      glm::vec3{1.0f, 0.0f, 0.0f},  //
      glm::vec3{1.0f, 0.0f, 0.0f},  //
      glm::vec3{1.0f, 0.0f, 0.0f},  //

      glm::vec3{1.0f, 0.0f, 0.0f},  //
      glm::vec3{1.0f, 0.0f, 0.0f},  //
      glm::vec3{1.0f, 0.0f, 0.0f},  //

      glm::vec3{0.0f, 1.0f, 0.0f},  //
      glm::vec3{0.0f, 1.0f, 0.0f},  //
      glm::vec3{0.0f, 1.0f, 0.0f},  //

      glm::vec3{0.0f, 1.0f, 0.0f},  //
      glm::vec3{0.0f, 1.0f, 0.0f},  //
      glm::vec3{0.0f, 1.0f, 0.0},   //

      glm::vec3{0.0f, 0.0f, 1.0f},  //
      glm::vec3{0.0f, 0.0f, 1.0f},  //
      glm::vec3{0.0f, 0.0f, 1.0f},  //

  };

  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);

  // vertices
  glGenBuffers(1, &vbo_vertices_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(),
               vertices.data(), GL_STATIC_DRAW);
  // std::cout << "size: " << sizeof(glm::vec3) << std::endl;
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
                        (void*)nullptr);
  glEnableVertexAttribArray(0);

  // // surface normal
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

void RenderSystem::Update(const EntityCamera& entity_camera,
                          std::vector<EntityRenderable>& entities, float dt) {
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shader_->Activate();
  glBindVertexArray(vao_);

  auto& camera_transform = entity_camera.transform;
  auto& camera_camera = entity_camera.camera;

  for (const auto& entity : entities) {
    const auto& transform = entity.transform;
    const auto& renderable = entity.renderable;

    glm::mat4 view{1.f};
    view = ecs_opengl::MakeViewMatrix(camera_transform.translation,
                                      glm::vec3{0.f, 0.f, 0.f},
                                      glm::vec3{0.f, 1.f, 0.f});
    // view[3][0] = -camera_transform.translation.x;
    // view[3][1] = -camera_transform.translation.y;
    // view[3][2] = -camera_transform.translation.z;

    // yxz
    glm::mat4 rotation{1.f};
    const float c3 = glm::cos(transform.rotation.z);
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
    rotation[0][1] = u.y;
    rotation[0][2] = u.z;
    rotation[1][0] = v.x;
    rotation[1][1] = v.y;
    rotation[1][2] = v.z;
    rotation[2][0] = w.x;
    rotation[2][1] = w.y;
    rotation[2][2] = w.z;

    glm::mat4 translation{1.f};
    translation[3][0] = transform.translation.x;
    translation[3][1] = transform.translation.y;
    translation[3][2] = transform.translation.z;

    glm::mat4 scale{1.f};
    scale[0][0] = transform.scale.x;
    scale[1][1] = transform.scale.y;
    scale[2][2] = transform.scale.z;

    glm::mat4 model = translation * rotation * scale;

    glm::mat4 projection = camera_camera.projection_matrix;

    glm::vec3 inv_scale = 1.f / transform.scale;
    // RS^{-1}
    glm::mat3 normal3 = {
        inv_scale.x * u,
        inv_scale.y * v,
        inv_scale.z * w,
    };
    glm::mat4 normal4{normal3};

    // std::cout << "mat normal: " << std::endl;
    // for (int i = 0; i < 3; i++) {
    //   for (int j = 0; j < 3; j++) {
    //     std::cout << normal[j][i] << " ";
    //   }
    //   std::cout << std::endl;
    // }

    // temp check
    // TODO: add test
    float width = 640.f;
    float height = 480.f;
    // projection = glm::perspective(glm::radians(45.0f),
    //                               (float)width / (float)height, 0.1f,
    //                               1000.0f);

    // glm::mat4 glm_view = glm::lookAt(
    //     glm::vec3(200, 200, 300),  // Camera is at (4,3,3), in World Space
    //     glm::vec3(0, 0, 0),        // and looks at the origin
    //     glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    // );

    // std::cout << "view: " << std::endl;
    // for (int i = 0; i < 4; i++) {
    //   for (int j = 0; j < 4; j++) {
    //     std::cout << view[j][i] << " ";
    //   }
    //   std::cout << std::endl;
    // }

    // std::cout << "glm_view: " << std::endl;
    // for (int i = 0; i < 4; i++) {
    //   for (int j = 0; j < 4; j++) {
    //     std::cout << glm_view[j][i] << " ";
    //   }
    //   std::cout << std::endl;
    // }

    shader_->SetUniform<glm::mat4>("uModel", model);
    shader_->SetUniform<glm::mat4>("uView", view);
    shader_->SetUniform<glm::mat4>("uProjection", projection);
    shader_->SetUniform<glm::mat4>("uNormal", normal4);
    shader_->SetUniform<glm::vec3>("uColor", renderable.color);
    // glEnableVertexAttribArray(0);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices_);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, /*sizeof(glm::vec3)*/ 0,
    //                       (void*)nullptr);

    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
  // unbind
  glBindVertexArray(0);
}

void PhysicsSystem::Init() {}

void PhysicsSystem::Update(ecs_opengl::EventManager& event_manager,
                           std::vector<EntityRenderable>& entities, float dt) {
  // if (entities.size() == 0) {
  //   event_manager.SendEvent(Events::Window::kQuit);
  // }
  bool sw_quit = true;
  for (auto it = entities.begin(); it != entities.end(); /*it++*/) {
    auto& entity = *it;
    auto& rigid_body = entity.rigid_body;
    auto& transform = entity.transform;
    auto const& gravity = entity.gravity;

    if (transform.translation.y < -50) {
      it++;
      continue;
    }
    sw_quit = false;
    transform.translation += rigid_body.velocity * dt;

    transform.rotation += rigid_body.angular_velocity * dt;
    // mass?
    rigid_body.velocity += gravity.force * dt;
    // anglular acceleration

    it++;
    // if (transform.translation.y < -100) {
    //   it = entities.erase(it);
    // } else {
    //   it++;
    // }
  }
  if (sw_quit) {
    event_manager.SendEvent(Events::Window::kQuit);
  }
}
};  // namespace oop_opengl
