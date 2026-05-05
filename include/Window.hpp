#pragma once

#include <GLFW/glfw3.h>
#include <stdexcept>

class Window {
private:
  Window(const Window &other);
  Window &operator=(const Window &other);

  GLFWwindow *window = nullptr;

public:
  Window(int width, int height, const char *title);
  ~Window();

  GLFWwindow *getHandle() const;
};
