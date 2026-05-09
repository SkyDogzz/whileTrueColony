#include "Input.hpp"
#include "Logger.hpp"
#include <string>

Input::Input(GLFWwindow* window)
    : window(window)
{
    glfwSetKeyCallback(window, keyCallback);
    Logger::debug("Key callback registered");
    Logger::debug("Input initialized");
}

Input::~Input() { Logger::debug("Input destroyed"); }

void Input::pollEvents() { glfwPollEvents(); }

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    Logger::debug("Key event: key=" + std::to_string(key) + ", action=" + std::to_string(action));
}
