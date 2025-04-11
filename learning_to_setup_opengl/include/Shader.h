#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <string>

class Shader {
public:
  Shader(const char *vertexSource, const char *fragmentSource);

  ~Shader();

  void use() const;

private:
  unsigned int ID;

  void checkCompileErrors(unsigned int shader, const std::string &type);
};

#endif // SHADER_H
