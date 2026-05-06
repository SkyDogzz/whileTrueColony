#include "Time.hpp"

Time::Time() {
  lastFrame = glfwGetTime();
  Logger::debug("Time initialized");
}

Time::~Time() { Logger::debug("Time destroyed"); }

void Time::update() {
  const double currentFrame = glfwGetTime();

  deltaTime = static_cast<float>(currentFrame - lastFrame);
  elapsedTime = static_cast<float>(currentFrame);
  lastFrame = currentFrame;
}

float Time::getDeltaTime() const { return deltaTime; }

float Time::getElapsedTime() const { return elapsedTime; }
