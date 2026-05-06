#pragma once

#include <GL/gl.h>

class Renderer {
private:
  Renderer(const Renderer &other);
  Renderer &operator=(const Renderer &other);

public:
  Renderer();
  ~Renderer();

  void beginFrame();
};
