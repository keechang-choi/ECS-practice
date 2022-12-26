#pragma once

// std
#include <string>

// libs
#include <glad/glad.h>

#include <glm/glm.hpp>

namespace ecs_opengl {

class Shader {
 public:
  Shader(const std::string& vert_path, const std::string& frag_path);
  void Activate();
  template <typename T>
  void SetUniform(const std::string& name, const T& value) {
    if constexpr (std::is_same_v<T, glm::mat4>) {
      glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE,
                         glm::value_ptr(value));
    } else if constexpr (std::is_same_v<T, glm::vec3>) {
      glUniform3fv(glGetUniformLocation(id_, name.c_str()), 1,
                   glm::value_ptr(value));
    }
  }

 private:
  GLuint id_;
};
}  // namespace ecs_opengl