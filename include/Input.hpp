#pragma once

#include <iostream>

class Input {
private:
  Input(const Input &other);
  Input &operator=(const Input &other);

public:
  Input();
  ~Input();
};
