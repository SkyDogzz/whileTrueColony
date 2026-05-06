#include "Input.hpp"

Input::Input() {}

Input::~Input() {}

void Input::pollEvents() { glfwPollEvents(); }
