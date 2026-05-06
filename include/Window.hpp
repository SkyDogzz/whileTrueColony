#pragma once

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

class Window {
private:
    Window(const Window& other);
    Window& operator=(const Window& other);

    GLFWwindow* window = nullptr;

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

public:
    Window(int width, int height, const char* title);
    ~Window();

    GLFWwindow* getHandle() const;
    void makeContextCurrent();
    void initializeViewport();
    bool shouldClose();
    void swapBuffers();
};
