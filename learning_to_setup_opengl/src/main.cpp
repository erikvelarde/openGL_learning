#include "Application.h"
int main() {
  try {
    Application app(800, 600, "Moving Circle");
    app.run();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
