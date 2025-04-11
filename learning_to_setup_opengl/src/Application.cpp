#include "./Application.h"

Application::Application(int width, int height, const char *title)
    : windowWidth(width), windowHeight(height),
      aspectRatio((float)width / (float)height) {
  initGLFW();
  createWindow(title);
  initGLAD();
  setupCallbacks();
  setupShaders();
  setupCircle();
}

Application::~Application() { glfwTerminate(); }

void Application::run() {
  while (!glfwWindowShouldClose(window)) {
    processInput();
    render();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void Application::initGLFW() {
  if (!glfwInit()) {
    throw std::runtime_error("Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Application::createWindow(const char *title) {
  window = glfwCreateWindow(windowWidth, windowHeight, title, nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }
  glfwMakeContextCurrent(window);
}

void Application::initGLAD() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
  }
  glViewport(0, 0, windowWidth, windowHeight);
}

void Application::setupCallbacks() {
  glfwSetFramebufferSizeCallback(
      window, [](GLFWwindow *window, int width, int height) {
        auto app = static_cast<Application *>(glfwGetWindowUserPointer(window));
        app->onFramebufferSize(width, height);
      });
  glfwSetWindowUserPointer(window, this);
}

void Application::setupShaders() {
  const char *vertexShaderSource = R"(
            #version 330 core
            layout (location = 0) in vec2 aPos;
            void main() {
                gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
            }
        )";

  const char *fragmentShaderSource = R"(
            #version 330 core
            out vec4 FragColor;
            void main() {
                FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Red color
            }
        )";

  shader = std::make_unique<Shader>(vertexShaderSource, fragmentShaderSource);
}

void Application::setupCircle() {
  circle = std::make_unique<Circle>(0.5f, 0.5f, 0.1f, 100);
  circle->updateVertices(aspectRatio);
}

void Application::onFramebufferSize(int width, int height) {
  windowWidth = width;
  windowHeight = height;
  aspectRatio = (float)width / (float)height;
  glViewport(0, 0, width, height);
  circle->updateVertices(aspectRatio);
}

void Application::processInput() {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  float dx = 0.0f, dy = 0.0f;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    dy += moveSpeed;
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    dy -= moveSpeed;
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    dx -= moveSpeed;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    dx += moveSpeed;

  if (dx != 0.0f || dy != 0.0f) {
    circle->move(dx, dy, -1.0f, 1.0f);
    circle->updateVertices(aspectRatio);
  }
}

void Application::render() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  shader->use();
  circle->draw();
}
