#include "Renderer.hpp"
#include "Logger.hpp"

Renderer::Renderer() { Logger::debug("Renderer initialized"); }

Renderer::~Renderer() { Logger::debug("Renderer destroyed"); }

void Renderer::beginFrame() { glClear(GL_COLOR_BUFFER_BIT); }
