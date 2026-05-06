#include "Renderer.hpp"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::beginFrame() { glClear(GL_COLOR_BUFFER_BIT); }
