#include "Window.hpp"
#include "Logger.hpp"
#include <string>

Window::Window(int width, int height, const char *title) {
  Logger::info("Creating window: " + std::to_string(width) + "x" +
               std::to_string(height) + " \"" + title + "\"");

  window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!window)
    throw std::runtime_error("Failed to create GLFW window");

  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  Logger::debug("Framebuffer resize callback registered");
  Logger::info("Window created");
}

Window::~Window() {
  if (window) {
    Logger::debug("Destroying window");
    glfwDestroyWindow(window);
  }
}

GLFWwindow *Window::getHandle() const { return window; }

void Window::makeContextCurrent() {
  glfwMakeContextCurrent(window);
  Logger::debug("Window context made current");
}

void Window::initializeViewport() {
  int width = 0;
  int height = 0;

  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  Logger::debug("Viewport initialized: " + std::to_string(width) + "x" +
                std::to_string(height));
}

bool Window::shouldClose() { return glfwWindowShouldClose(window); }

void Window::swapBuffers() { glfwSwapBuffers(window); }

void Window::framebufferSizeCallback(GLFWwindow *window, int width,
                                     int height) {
  (void)window;
  glViewport(0, 0, width, height);
  Logger::debug("Framebuffer resized: " + std::to_string(width) + "x" +
                std::to_string(height));
}
