#include "Input.hpp"
#include "Logger.hpp"

Input::Input() { Logger::debug("Input initialized"); }

Input::~Input() { Logger::debug("Input destroyed"); }

void Input::pollEvents() { glfwPollEvents(); }
