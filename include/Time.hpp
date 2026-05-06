#pragma once

#include "Logger.hpp"
#include <GLFW/glfw3.h>

class Time {
public:
    Time();
    ~Time();

    void update();

    float getDeltaTime() const;
    float getElapsedTime() const;

private:
    double lastFrame = 0.0;
    float deltaTime = 0.0f;
    float elapsedTime = 0.0f;
};
