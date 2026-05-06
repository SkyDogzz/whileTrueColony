#include "Input.hpp"
#include "Logger.hpp"
#include <GLFW/glfw3.h>

Input::Input() { Logger::debug("Input initialized"); }

Input::~Input() { Logger::debug("Input destroyed"); }

void Input::pollEvents() { glfwPollEvents(); }
