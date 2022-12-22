#pragma once

// std
#include <cassert>
#include <limits>

// libs
#define GLM_FORCE_RADIANS
// #define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace ecs_opengl {

glm::mat4 MakePerspectiveProjection(float fovy, float aspect, float near,
                                    float far) {
  assert(glm::abs(aspect - std::numeric_limits<float>::epsilon()) > 0.0f);
  const float tan_half_fovy = tan(fovy / 2.f);
  glm::mat4 projection_matrix = glm::mat4{0.0f};
  projection_matrix[0][0] = 1.f / (aspect * tan_half_fovy);
  projection_matrix[1][1] = 1.f / (tan_half_fovy);
  projection_matrix[2][2] = far / (far - near);
  projection_matrix[2][3] = 1.f;
  projection_matrix[3][2] = -(far * near) / (far - near);
  return projection_matrix;
}

struct Camera {
  glm::mat4 projection_matrix{1.f};
  glm::mat4 view_matrix{1.f};
};
}  // namespace ecs_opengl