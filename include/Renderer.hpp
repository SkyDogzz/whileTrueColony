#pragma once

#include "Game.hpp"
#include <fstream>
#include <iostream>
#include <string>

struct RendererConfig {
    float clearColorRed = 0.08f;
    float clearColorGreen = 0.09f;
    float clearColorBlue = 0.11f;
    float clearColorAlpha = 1.0f;
};

class Renderer {
private:
    Renderer(const Renderer& other) = delete;
    Renderer& operator=(const Renderer& other) = delete;

    RendererConfig config;
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;
    unsigned int shaderProgram = 0;
    unsigned int indexCount = 0;

    void initGeometry();
    void initGeometry(const std::string& filename);

public:
    Renderer();
    explicit Renderer(const RendererConfig& config);
    ~Renderer();

    void initShaders();
    void applyConfig() const;
    void beginFrame() const;
    void render(const Game& game, float elapsedTime) const;
};
