#include <oop.hpp>

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
};  // namespace oop_opengl
