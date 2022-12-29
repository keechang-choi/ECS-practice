#pragma once

#include "component_manager.hpp"
#include "entity_manager.hpp"
#include "system_manager.hpp"
#include "types.hpp"

// std
#include <memory>

namespace ecs_opengl {

class Coordinator {
 public:
  void Init() {
    component_manager_ = std::make_unique<ComponentManager>();
    entity_manager_ = std::make_unique<EntityManager>();
    system_manager_ = std::make_unique<SystemManager>();
  }

  // Entity methods
  Entity CreateEntity() { return entity_manager_->CreateEntity(); }

  void DestroyEntity(Entity entity) {
    entity_manager_->DestroyEntity(entity);
    component_manager_->EntityDestroyed(entity);
    system_manager_->EntityDestroyed(entity);
  }

  // Component methods
  template <typename T>
  void RegisterComponent() {
    component_manager_->RegisterComponent<T>();
  }

  template <typename T>
  void AddComponent(Entity entity, T component) {
    component_manager_->AddComponent(entity, component);

    auto signature = entity_manager_->GetSignature(entity);
    signature.set(component_manager_->GetComponentType<T>(), true);
    entity_manager_->SetSignature(entity, signature);
    system_manager_->EntitySignatureChanged(entity, signature);
  }

  template <typename T>
  void RemoveComponent(Entity entity, T component) {
    component_manager_->RemoveComponent<T>(entity);

    auto signature = entity_manager_->GetSignature(entity);
    signature.set(component_manager_->GetComponentType<T>(), false);
    entity_manager_->SetSignature(entity, signature);
    system_manager_->EntitySignatureChanged(entity, signature);
  }

  template <typename T>
  T& GetComponent(Entity entity) const {
    return component_manager_->GetComponent<T>(entity);
  }

  template <typename T>
  ComponentType GetComponentType() const {
    return component_manager_->GetComponentType<T>();
  }

  // system methods
  template <typename T>
  T* RegisterSystem() {
    return system_manager_->RegisterSystem<T>();
  }

  template <typename T>
  void SetSystemSignature(Signature signature) {
    system_manager_->SetSignature<T>(signature);
  }

  void SetCamera(Entity camera) { camera_ = camera; }
  Entity GetCamera() const { return camera_; }

 private:
  std::unique_ptr<ComponentManager> component_manager_;
  std::unique_ptr<EntityManager> entity_manager_;
  std::unique_ptr<SystemManager> system_manager_;
  Entity camera_;
};
}  // namespace ecs_opengl