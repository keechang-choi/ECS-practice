#pragma once

#include "system.hpp"
#include "types.hpp"

// std
#include <cassert>
#include <memory>
#include <unordered_map>

namespace ecs_opengl {
class SystemManager {
 public:
  template <typename T>
  std::unique_ptr<T>& RegisterSystem() {
    const char* type_name = typeid(T).name();
    assert(systems_.find(type_name) == systems_.end() &&
           "Registering already existing system.");
    systems_.insert({type_name, std::make_unique<T>()});
    return system;
  }

  template <typename T>
  void SetSignature(Signature signature) {
    const char* type_name = typeid(T).name();
    assert(systems_.find(type_name) != systems_.end() &&
           "System not registered!");
    signatures_.insert({type_name, signature});
  }

  void EntityDestroyed(Entity entity) {
    for (auto const& pair : systems_) {
      auto const& system = pair.second;
      system->RemoveEntity(entity);
    }
  }

  void EntitySignatureChanged(Entity entity, Signature entity_signature) {
    for (auto const& pair : systems_) {
      auto const& type = pair.first;
      auto const& system = pair.second;
      auto const& system_signature = signatures_[type];
      if ((entity_signature & system_signature) == system_signature) {
        // entity contains all target components of the system.
        system->AddEntity(entity);
      } else {
        system->RemoveEntity(entity);
      }
    }
  }

 private:
  std::unordered_map<const char*, Signature> signatures_;
  std::unordered_map<const char*, std::unique_ptr<System>> systems_{};
};
}  // namespace ecs_opengl
