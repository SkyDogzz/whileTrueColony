#include "App.hpp"
#include <GLFW/glfw3.h>

App::App() {}

App::~App() {
  window.reset();
  if (glfwInitialized)
    glfwTerminate();
}

void App::init() {
  if (!glfwInit())
    throw std::runtime_error("Failed to init GLFW");
  glfwInitialized = true;
  window = std::make_unique<Window>(1080, 780, "Here we go");
}

bool App::run() {
  try {
    init();
  } catch (std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return false;
  }

  glfwMakeContextCurrent(window->getHandle());

  while (!glfwWindowShouldClose(window->getHandle())) {
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window->getHandle());

    glfwPollEvents();
  }

  return true;
}
