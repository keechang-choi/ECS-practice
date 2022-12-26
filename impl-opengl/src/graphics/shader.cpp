#include "shader.hpp"

// std
#include <fstream>
#include <iostream>
#include <sstream>

namespace ecs_opengl {
Shader::Shader(const std::string& vert_path, const std::string& frag_path) {
  std::string vert_file_contents;

  std::string frag_file_contents;

  // read
  std::ifstream vert_file;
  vert_file.open(vert_path);
  std::stringstream vert_file_stream;
  vert_file_stream << vert_file.rdbuf();
  vert_file.close();
  vert_file_contents = vert_file_stream.str();

  std::ifstream frag_file;
  frag_file.open(vert_path);
  std::stringstream frag_file_stream;
  frag_file_stream << frag_file.rdbuf();
  frag_file.close();
  frag_file_contents = frag_file_stream.str();

  // compile
  int success;
  char info_log[512];

  GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
  const GLchar* vert_shader_source = vert_file_contents.c_str();
  glShaderSource(vert_shader, 1, &vert_shader_source, nullptr);
  glCompileShader(vert_shader);
  glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vert_shader, 512, nullptr, info_log);
    std::cerr << "Error compiling vertex shader: " << info_log << std::endl;
  }

  GLuint frag_shader = glCreateShader(GL_VERTEX_SHADER);
  const GLchar* frag_shader_source = vert_file_contents.c_str();
  glShaderSource(frag_shader, 1, &frag_shader_source, nullptr);
  glCompileShader(frag_shader);
  glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(frag_shader, 512, nullptr, info_log);
    std::cerr << "Error compiling fragment shader: " << info_log << std::endl;
  }

  // link
  id_ = glCreateProgram();
  glAttachShader(id_, vert_shader);
  glAttachShader(id_, frag_shader);
  glLinkProgram(id_);
  glGetProgramiv(id_, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(id_, 512, nullptr, info_log);
    std::cerr << "Error linking shaders: " << info_log << std::endl;
  }

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);
}

void Shader::Activate() { glUseProgram(id_); }
}  // namespace ecs_opengl