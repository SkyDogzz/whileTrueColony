#pragma once

#include "Game.hpp"
#include "Input.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"
#include "Time.hpp"
#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <chrono>
#include <memory>
#include <string>
#include <thread>

struct AppConfig {
    int windowWidth = 1080;
    int windowHeight = 780;
    std::string windowTitle = "While True Colony";
    int openglMajor = 4;
    int openglMinor = 6;

    int targetFps = 60;
    bool vsync = true;

    RendererConfig renderer;
    LogLevel logLevel = LogLevel::Debug;
};

class App {
private:
    App(const App& other);
    App& operator=(const App& other);

    AppConfig config;
    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Game> game;
    std::unique_ptr<Input> input;
    std::unique_ptr<Time> time;
    bool glfwInitialized = false;

    void init();

public:
    App();
    explicit App(const AppConfig& config);
    ~App();

    bool run();
};
