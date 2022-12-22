#pragma once

// std
#include <bitset>
#include <cstdint>

namespace ecs_opengl {
using Entity = std::uint32_t;
const Entity kMaxEntities = 5000;
using ComponentType = std::uint8_t;
const ComponentType kMaxComponents = 32;
using signature = std::bitset<kMaxComponents>;
}  // namespace ecs_opengl