#pragma once

#include <iostream>

class Renderer {
private:
  Renderer(const Renderer &other);
  Renderer &operator=(const Renderer &other);

public:
  Renderer();
  ~Renderer();
};
