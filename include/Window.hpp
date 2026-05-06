#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Window {
private:
    Window(const Window& other) = delete;
    Window& operator=(const Window& other) = delete;

    GLFWwindow* window = nullptr;

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

public:
    Window(int width, int height, const char* title, int openglMajor, int openglMinor);
    ~Window();

    GLFWwindow* getHandle() const;
    void makeContextCurrent() const;
    void initializeViewport() const;
    bool shouldClose() const;
    void swapBuffers() const;
};
