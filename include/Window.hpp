#pragma once

#include <iostream>

class Window {
private:
  Window(const Window &other);
  Window &operator=(const Window &other);

public:
  Window();
  ~Window();
};
