#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Input {
private:
    Input(const Input& other) = delete;
    Input& operator=(const Input& other) = delete;

    GLFWwindow* window = nullptr;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
    explicit Input(GLFWwindow* window);
    ~Input();

    void pollEvents();
};
