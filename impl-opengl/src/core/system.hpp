#pragma once

#include "types.hpp"

// std
#include <set>

namespace ecs_opengl {
class System {
 public:
  const std::set<Entity>& GetEntities() { return entities_; }

  void AddEntity(Entity entity) { entities_.insert(entity); }

  void RemoveEntity(Entity entity) { entities_.erase(entity); }

 private:
  std::set<Entity> entities_;
};
}  // namespace ecs_opengl