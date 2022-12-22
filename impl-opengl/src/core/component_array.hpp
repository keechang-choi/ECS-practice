#pragma once

#include "types.hpp"

// std
#include <array>
#include <cassert>
#include <unordered_map>

namespace ecs_opengl {
class IComponentArray {
 public:
  virtual ~IComponentArray() = default;
  virtual void EntityDestroyed(Entity entity) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray {
 public:
  void InsertData(Entity entity, T component) {
    assert(entity_to_index_map_.find(entity) == entity_to_index_map_.end() &&
           "Duplicated components for the same entity.");

    // put new entity at the end
    size_t new_index = size_;
    entity_to_index_map_[entity] = new_index;
    index_to_entity_map_[new_index] = entity;
    component_array_[new_index] = component;
    size_++;
  }
  void RemoveData(Entity entity) {
    assert(entity_to_index_map_.find(entity) != entity_to_index_map_.end() &&
           "Removing non existent component.");
    // move element at the end into the deleted entitiy's index
    // to maintain density.
    size_t index_of_removed_entity = entity_to_index_map_[entity];
    size_t index_of_last_element = size_ - 1;
    component_array_[index_of_removed_entity] =
        component_array_[index_of_last_element];
    // NOTE: array do not delete deprecated elements

    // update e2i map
    Entity entity_of_last_element = index_to_entity_map_[index_of_last_element];
    index_to_entity_map_[index_of_removed_entity] = entity_of_last_element;
    index_to_entity_map_.erase(index_of_last_element);

    // update i2e map
    entity_to_index_map_[entity_of_last_element] = index_of_removed_entity;
    entity_to_index_map_.erase(entity);

    size_--;
  }
  T &GetData(Entity entity) {
    assert(entity_to_index_map_.find(entity) != entity_to_index_map_.end() &&
           "Retrieving non-existent component.");
    return component_array_[entity_to_index_map_[entity]];
  }

  void EntityDestroyed(Entity entity) override {
    if (entity_to_index_map_.find(entity) != entity_to_index_map_.end()) {
      RemoveData(entity);
    }
  }

 private:
  std::array<T, kMaxEntities> component_array_{};
  std::unordered_map<Entity, size_t> entity_to_index_map_{};
  std::unordered_map<size_t, Entity> index_to_entity_map_{};
  size_t size_{};
};
}  // namespace ecs_opengl