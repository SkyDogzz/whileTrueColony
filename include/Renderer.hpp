#pragma once

#include "Game.hpp"

struct RendererConfig {
    float clearColorRed = 0.08f;
    float clearColorGreen = 0.09f;
    float clearColorBlue = 0.11f;
    float clearColorAlpha = 1.0f;
};

class Renderer {
private:
    Renderer(const Renderer& other);
    Renderer& operator=(const Renderer& other);

    RendererConfig config;

public:
    Renderer();
    explicit Renderer(const RendererConfig& config);
    ~Renderer();

    void applyConfig();
    void beginFrame();
    void render(const Game& game);
};
