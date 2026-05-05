#pragma once

#include "Game.hpp"
#include "Input.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include <iostream>

class App {
private:
  App(const App &other);
  App &operator=(const App &other);

  Window window;
  Renderer renderer;
  Game game;
  Input input;

public:
  App();
  ~App();

  void run();
};
