#pragma once

#include "types.hpp"

// std
#include <array>
#include <cassert>
#include <queue>

namespace ecs_opengl {
class EntityManager {
 public:
  EntityManager() {
    // restrict existing entity id candidates
    for (Entity entity = 0; entity < kMaxEntities; entity++) {
      available_entities_.push(entity);
    }
  }

  Entity CreateEntity() {
    assert(living_entity_count_ < kMaxEntities && "Too many entities!");

    Entity id = available_entities_.front();
    available_entities_.pop();
    living_entity_count_++;

    return id;
  }

  void DestroyEntity(Entity entity) {
    assert(entity < kMaxEntities && "Entity out of range!");
    signatures_[entity].reset();
    available_entities_.push(entity);
    living_entity_count_--;
  }

  void SetSignature(Entity entity, Signature signature) {
    assert(entity < kMaxEntities && "Entity out of range!");
    signatures_[entity] = signature;
  }

  Signature GetSignature(Entity entity) {
    assert(entity < kMaxEntities && "Entity out of range!");
    return signatures_[entity];
  }

 private:
  std::queue<Entity> available_entities_{};
  std::array<Signature, kMaxEntities> signatures_{};
  uint32_t living_entity_count_{};
};
}  // namespace ecs_opengl