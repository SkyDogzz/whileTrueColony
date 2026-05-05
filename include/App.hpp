#pragma once

#include "Game.hpp"
#include "Input.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <exception>
#include <iostream>
#include <memory>

class App {
private:
  App(const App &other);
  App &operator=(const App &other);

  std::unique_ptr<Window> window;
  Renderer renderer;
  Game game;
  Input input;
  bool glfwInitialized = false;

  void init();

public:
  App();
  ~App();

  bool run();
};
