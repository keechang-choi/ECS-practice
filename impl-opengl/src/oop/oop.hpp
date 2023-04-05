#include <memory>
#include <vector>

#include "components/camera.hpp"
#include "components/gravity.hpp"
#include "components/renderable.hpp"
#include "components/rigid_body.hpp"
#include "components/transform.hpp"
#include "core/event_manager.hpp"
#include "graphics/shader.hpp"

namespace oop_opengl {
class EntityTransform {
 public:
  ecs_opengl::Transform transform;
  EntityTransform(ecs_opengl::Transform t);
};

class EntityPhysics : public EntityTransform {
 public:
  ecs_opengl::Gravity gravity;
  ecs_opengl::RigidBody rigid_body;
  EntityPhysics(ecs_opengl::Transform t, ecs_opengl::Gravity g,
                ecs_opengl::RigidBody rb);
};

class EntityRenderable : public EntityPhysics {
 public:
  ecs_opengl::Renderable renderable;
  EntityRenderable(ecs_opengl::Transform t, ecs_opengl::Gravity g,
                   ecs_opengl::RigidBody rb, ecs_opengl::Renderable r);
};

class EntityCamera : public EntityTransform {
 public:
  ecs_opengl::Camera camera;
  EntityCamera(ecs_opengl::Transform t, ecs_opengl::Camera c);
};

class PhysicsSystem {
 public:
  void Init();
  void Update(ecs_opengl::EventManager& event_manager,
              std::vector<EntityRenderable>& entities, float dt);
};

class RenderSystem {
 public:
  void Init();
  void Update(const EntityCamera& entity_camera,
              std::vector<EntityRenderable>& entities, float dt);

 private:
  std::unique_ptr<ecs_opengl::Shader> shader_;

  GLuint vao_{};
  GLuint vbo_vertices_{};
  GLuint vbo_normals_{};
};

}  // namespace oop_opengl
