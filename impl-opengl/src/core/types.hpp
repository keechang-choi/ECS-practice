#pragma once

// std
#include <bitset>
#include <cstdint>

namespace ecs_opengl {
using Entity = std::uint32_t;
const Entity kMaxEntities = 300;
using ComponentType = std::uint8_t;
const ComponentType kMaxComponents = 32;
using Signature = std::bitset<kMaxComponents>;

using EventId = std::uint32_t;
}  // namespace ecs_opengl

// Source: https://gist.github.com/Lee-R/3839813
constexpr std::uint32_t fnv1a_32(char const* s, std::size_t count) {
  return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) *
         16777619u;  // NOLINT (hicpp-signed-bitwise)
}

constexpr std::uint32_t operator"" _hash(char const* s, std::size_t count) {
  return fnv1a_32(s, count);
}
namespace Events::Window {
const ecs_opengl::EventId kQuit = "Events::Window::kQuit"_hash;
}