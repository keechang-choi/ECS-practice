#pragma once

#include "component_array.hpp"
#include "types.hpp"

// std
#include <any>
#include <memory>
#include <unordered_map>

namespace ecs_opengl {
class ComponentManager {
 public:
  template <typename T>
  void RegisterComponent() {
    const char* type_name = typeid(T).name();
    assert(component_types.find(type_name) == component_types.end() &&
           "Component already registered!");
    component_types.insert({type_name, next_component_type});
    component_arrays.insert({type_name, std::make_unique<ComponentArray<T>>()});

    next_component_type++;
  }

  template <typename T>
  ComponentType GetComponentType() {
    const char* type_name = typeid(T).name();
    assert(component_types.find(type_name) != component_types.end() &&
           "Component not registered!");
    return component_types[type_name];
  }

  template <typename T>
  void AddComponent(Entity entity, T component) {
    GetComponentArray<T>()->InsertData(entity, component);
  }

  template <typename T>
  void RemoveComponent(Entity entity) {
    GetComponentArray<T>()->RemoveData(entity);
  }

  template <typename T>
  T& GetComponent(Entity entity) {
    return GetComponentArray<T>()->GetData(entity);
  }

  void EntityDestroyed(Entity entity) {
    for (auto const& pair : component_arrays) {
      auto const& component = pair.second;
      component->EntityDestroyed(entity);
    }
  }

 private:
  std::unordered_map<const char*, ComponentType> component_types{};
  std::unordered_map<const char*, std::unique_ptr<IComponentArray>>
      component_arrays{};
  ComponentType next_component_type{};
  template <typename T>
  ComponentArray<T>* GetComponentArray() {
    const char* type_name = typeid(T).name();
    assert(component_types.find(type_name) != component_types.end() &&
           "Component not registered!");
    return static_cast<ComponentArray<T>*>(component_arrays[type_name].get());
  }
};
}  // namespace ecs_opengl