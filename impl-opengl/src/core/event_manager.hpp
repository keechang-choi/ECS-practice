#pragma once

#include <functional>
#include <list>
#include <unordered_map>

#include "event.hpp"
#include "types.hpp"

namespace ecs_opengl {
class EventManager {
 public:
  void AddListener(EventId eventId,
                   std::function<void(Event&)> const& listener) {
    listeners_[eventId].push_back(listener);
  }

  void SendEvent(Event& event) {
    uint32_t type = event.GetType();

    for (auto const& listener : listeners_[type]) {
      listener(event);
    }
  }

  void SendEvent(EventId eventId) {
    Event event(eventId);

    for (auto const& listener : listeners_[eventId]) {
      listener(event);
    }
  }

 private:
  std::unordered_map<EventId, std::list<std::function<void(Event&)>>>
      listeners_;
};
}  // namespace ecs_opengl