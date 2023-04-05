#pragma once

#include <any>
#include <unordered_map>

#include "types.hpp"

namespace ecs_opengl {
class Event {
 public:
  Event() = delete;
  explicit Event(EventId type) : type_(type) {}

  template <typename T>
  void SetParam(EventId id, T value) {
    data_[id] = value;
  }

  template <typename T>
  void GetParam(EventId id) {
    return std::any_cast<T>(data_[id]);
  }

  EventId GetType() const { return type_; }

 private:
  EventId type_{};
  std::unordered_map<EventId, std::any> data_{};
};
}  // namespace ecs_opengl