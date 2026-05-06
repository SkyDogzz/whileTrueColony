#pragma once

#include "Game.hpp"
#include "Input.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <memory>
#include <string>#include <chrono>
#include <thread>

struct AppConfig {
  int windowWidth = 1080;
  int windowHeight = 780;
  std::string windowTitle = "While True Colony";

  int targetFps = 60;
  bool vsync = true;
};

class App {
private:
  App(const App &other);
  App &operator=(const App &other);

  AppConfig config;
  std::unique_ptr<Window> window;
  Renderer renderer;
  Game game;
  Input input;
  bool glfwInitialized = false;

  void init();

public:
  App();
  explicit App(const AppConfig &config);
  ~App();

  bool run();
};
