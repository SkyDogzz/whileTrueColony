#include "Window.hpp"

Window::Window(int width, int height, const char *title) {
  window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!window)
    throw std::runtime_error("Failed to create GLFW window");
}

Window::~Window() {
  if (window)
    glfwDestroyWindow(window);
}

GLFWwindow *Window::getHandle() const { return window; }

void Window::makeContextCurrent() { glfwMakeContextCurrent(window); }

bool Window::shouldClose() { return glfwWindowShouldClose(window); }

void Window::swapBuffers() { glfwSwapBuffers(window); }
