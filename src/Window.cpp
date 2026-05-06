#include "Window.hpp"
#include "Logger.hpp"
#include <glad/gl.h>
#include <stdexcept>
#include <string>

Window::Window(int width, int height, const char* title, int openglMajor, int openglMinor)
{
    Logger::info("Creating window: " + std::to_string(width) + "x" + std::to_string(height) + " \"" + title + "\"");
    Logger::debug("Applying OpenGL version hints: " + std::to_string(openglMajor) + "." + std::to_string(openglMinor));

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openglMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openglMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        const char* description = nullptr;
        const int error = glfwGetError(&description);
        std::string message = "Failed to create GLFW window";
        if (error != GLFW_NO_ERROR) {
            message += " (GLFW error " + std::to_string(error) + ": "
                + (description ? description : "unknown error") + ")";
        }
        throw std::runtime_error(message);
    }

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    Logger::debug("Framebuffer resize callback registered");
    Logger::info("Window created");
}

Window::~Window()
{
    if (window) {
        Logger::debug("Destroying window");
        glfwDestroyWindow(window);
    }
}

GLFWwindow* Window::getHandle() const { return window; }

void Window::makeContextCurrent() const
{
    glfwMakeContextCurrent(window);
    Logger::debug("Window context made current");
}

void Window::initializeViewport() const
{
    int width = 0;
    int height = 0;

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    Logger::debug("Viewport initialized: " + std::to_string(width) + "x" + std::to_string(height));
}

bool Window::shouldClose() const { return glfwWindowShouldClose(window); }

void Window::swapBuffers() const { glfwSwapBuffers(window); }

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
    Logger::debug("Framebuffer resized: " + std::to_string(width) + "x" + std::to_string(height));
}
