#include "camera.hpp"

namespace ecs_opengl {
glm::mat4 MakePerspectiveProjection(float fovy, float aspect, float near,
                                    float far) {
  assert(glm::abs(aspect - std::numeric_limits<float>::epsilon()) > 0.0f);
  const float tan_half_fovy = tan(fovy / 2.f);
  glm::mat4 projection_matrix = glm::mat4{0.0f};
  projection_matrix[0][0] = 1.f / (aspect * tan_half_fovy);
  projection_matrix[1][1] = 1.f / (tan_half_fovy);
  projection_matrix[2][2] = -(far + near) / (far - near);
  projection_matrix[2][3] = -1.f;
  projection_matrix[3][2] = -(2 * far * near) / (far - near);
  return projection_matrix;
}

glm::mat4 MakeViewMatrix(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
  // forward (z)
  const glm::vec3 w{glm::normalize(position - target)};
  // left (x)
  const glm::vec3 u{glm::normalize(glm::cross(up, w))};
  // up (y)
  const glm::vec3 v{glm::cross(w, u)};

  // R^-1 T^-1
  glm::mat4 view_matrix{1.f};
  view_matrix[0][0] = u.x;
  view_matrix[1][0] = u.y;
  view_matrix[2][0] = u.z;
  view_matrix[0][1] = v.x;
  view_matrix[1][1] = v.y;
  view_matrix[2][1] = v.z;
  view_matrix[0][2] = w.x;
  view_matrix[1][2] = w.y;
  view_matrix[2][2] = w.z;

  view_matrix[3][0] = -glm::dot(u, position);
  view_matrix[3][1] = -glm::dot(v, position);
  view_matrix[3][2] = -glm::dot(w, position);

  return view_matrix;
}
}  // namespace ecs_opengl