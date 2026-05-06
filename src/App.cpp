#include "App.hpp"
#include <GLFW/glfw3.h>

App::App() { Logger::debug("App created with default config"); }

App::App(const AppConfig &config) : config(config) {
  Logger::debug("App created with custom config");
}

App::~App() {
  Logger::debug("Destroying app");
  input.reset();
  game.reset();
  renderer.reset();
  window.reset();
  if (glfwInitialized) {
    Logger::info("Terminating GLFW");
    glfwTerminate();
  }
}

void App::init() {
  Logger::setLevel(config.logLevel);
  Logger::info("Initializing app");
  Logger::debug("Window config: " + std::to_string(config.windowWidth) + "x" +
                std::to_string(config.windowHeight) + " \"" +
                config.windowTitle + "\"");
  Logger::debug("Frame timing: vsync=" +
                std::string(config.vsync ? "enabled" : "disabled") +
                ", targetFps=" + std::to_string(config.targetFps));

  Logger::info("Initializing GLFW");
  if (!glfwInit())
    throw std::runtime_error("Failed to init GLFW");
  glfwInitialized = true;

  time = std::make_unique<Time>();
  renderer = std::make_unique<Renderer>();
  game = std::make_unique<Game>();
  input = std::make_unique<Input>();
  window = std::make_unique<Window>(config.windowWidth, config.windowHeight,
                                    config.windowTitle.c_str());
}

bool App::run() {
  Logger::info("Starting application");

  try {
    init();
  } catch (std::exception &e) {
    Logger::error(e.what());
    return false;
  }

  window->makeContextCurrent();
  Logger::debug("OpenGL context is current");

  glfwSwapInterval(config.vsync ? 1 : 0);
  Logger::info(config.vsync ? "VSync enabled" : "VSync disabled");
  if (!config.vsync && config.targetFps > 0)
    Logger::info("Target FPS set to " + std::to_string(config.targetFps));

  while (!window->shouldClose()) {
    const double frameStart = glfwGetTime();

    time->update();
    renderer->beginFrame();
    window->swapBuffers();
    input->pollEvents();

    if (!config.vsync && config.targetFps > 0) {
      const double frameTime = glfwGetTime() - frameStart;
      const double targetFrameTime = 1.0 / config.targetFps;

      if (frameTime < targetFrameTime) {
        std::this_thread::sleep_for(
            std::chrono::duration<double>(targetFrameTime - frameTime));
      }
    }
  }

  Logger::info("Application stopped");
  return true;
}
