#include "Renderer.hpp"
#include <string>

Renderer::Renderer() { Logger::debug("Renderer initialized"); }

Renderer::Renderer(const RendererConfig &config) : config(config) {
  Logger::debug("Renderer initialized");
}

Renderer::~Renderer() { Logger::debug("Renderer destroyed"); }

void Renderer::applyConfig() {
  glClearColor(config.clearColorRed, config.clearColorGreen,
               config.clearColorBlue, config.clearColorAlpha);
  Logger::debug("Renderer clear color applied: " +
                std::to_string(config.clearColorRed) + ", " +
                std::to_string(config.clearColorGreen) + ", " +
                std::to_string(config.clearColorBlue) + ", " +
                std::to_string(config.clearColorAlpha));
}

void Renderer::beginFrame() { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::render(const Game &game) { (void)game; }
