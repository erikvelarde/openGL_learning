#pragma once

#include "./Circle.h"
#include "./Shader.h"
#include <GLFW/glfw3.h>
#include <memory>
#include <stdexcept>
#ifndef APPLICATION_H
#define APPLICATION_H

class Application {
public:
  Application(int width, int height, const char *title);

  ~Application();

  void run();

private:
  GLFWwindow *window;
  int windowWidth;
  int windowHeight;
  float aspectRatio;
  std::unique_ptr<Shader> shader;
  std::unique_ptr<Circle> circle;
  const float moveSpeed = 0.02f;

  void initGLFW();

  void createWindow(const char *title);

  void initGLAD();

  void setupCallbacks();

  void setupShaders();

  void setupCircle();

  void onFramebufferSize(int width, int height);

  void processInput();

  void render();
};

#endif // !APPLICATION_H
