#include "App.hpp"
#include <GLFW/glfw3.h>

App::App() {}

App::App(const AppConfig &config) : config(config) {}

App::~App() {
  window.reset();
  if (glfwInitialized)
    glfwTerminate();
}

void App::init() {
  if (!glfwInit())
    throw std::runtime_error("Failed to init GLFW");
  glfwInitialized = true;
  window = std::make_unique<Window>(config.windowWidth, config.windowHeight,
                                    config.windowTitle.c_str());
}

bool App::run() {
  try {
    init();
  } catch (std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return false;
  }

  window->makeContextCurrent();
  glfwSwapInterval(config.vsync ? 1 : 0);

  while (!window->shouldClose()) {
    const double frameStart = glfwGetTime();

    renderer.beginFrame();
    window->swapBuffers();
    input.pollEvents();

    if (!config.vsync && config.targetFps > 0) {
      const double frameTime = glfwGetTime() - frameStart;
      const double targetFrameTime = 1.0 / config.targetFps;

      if (frameTime < targetFrameTime) {
        std::this_thread::sleep_for(
            std::chrono::duration<double>(targetFrameTime - frameTime));
      }
    }
  }

  return true;
}
