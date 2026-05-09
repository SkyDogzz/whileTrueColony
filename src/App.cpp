#include "App.hpp"
#include <chrono>
#include <glad/gl.h>
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <thread>

namespace {
std::string formatFps(double fps)
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << fps;
    return stream.str();
}

void glfwErrorCallback(int error, const char* description)
{
    Logger::error("GLFW error " + std::to_string(error) + ": " + (description ? description : "unknown error"));
}
}

App::App() { Logger::debug("App created with default config"); }

App::App(const AppConfig& config)
    : config(config)
{
    Logger::debug("App created with custom config");
}

App::~App()
{
    Logger::debug("Destroying app");
    input.reset();
    game.reset();
    renderer.reset();
    window.reset();
    if (glfwInitialized) {
        Logger::info("Terminating GLFW");
        glfwTerminate();
    }
}

void App::init()
{
    Logger::setLevel(config.logLevel);
    Logger::info("Initializing app");
    Logger::debug("Window config: " + std::to_string(config.windowWidth) + "x" + std::to_string(config.windowHeight)
        + " \"" + config.windowTitle + "\"");
    Logger::debug(
        "Requested OpenGL version: " + std::to_string(config.openglMajor) + "." + std::to_string(config.openglMinor));
    Logger::debug("Frame timing: vsync=" + std::string(config.vsync ? "enabled" : "disabled")
        + ", targetFps=" + std::to_string(config.targetFps));

    Logger::info("Initializing GLFW");
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit())
        throw std::runtime_error("Failed to init GLFW");
    glfwInitialized = true;

    time = std::make_unique<Time>();
    renderer = std::make_unique<Renderer>(config.renderer);
    game = std::make_unique<Game>();
    window = std::make_unique<Window>(
        config.windowWidth, config.windowHeight, config.windowTitle.c_str(), config.openglMajor, config.openglMinor);
    input = std::make_unique<Input>(window->getHandle());
    Logger::info("App initialized");
}

bool App::run()
{
    Logger::info("Starting application");

    try {
        init();
    } catch (const std::exception& e) {
        Logger::error(e.what());
        return false;
    }

    window->makeContextCurrent();
    Logger::debug("OpenGL context is current");

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        Logger::error("Failed to initialize GLAD");
        return false;
    }

    Logger::info("GLAD initialized");
    const GLubyte* glVersion = glGetString(GL_VERSION);
    if (glVersion)
        Logger::info("OpenGL version: " + std::string(reinterpret_cast<const char*>(glVersion)));
    window->initializeViewport();
    renderer->applyConfig();
    renderer->initShaders();

    glfwSwapInterval(config.vsync ? 1 : 0);
    Logger::info(config.vsync ? "VSync enabled" : "VSync disabled");
    if (!config.vsync && config.targetFps > 0)
        Logger::info("Target FPS set to " + std::to_string(config.targetFps));

    int fpsFrameCount = 0;
    double fpsElapsedTime = 0.0;

    while (!window->shouldClose()) {
        const double frameStart = glfwGetTime();

        time->update();
        fpsFrameCount++;
        fpsElapsedTime += time->getDeltaTime();

        if (fpsElapsedTime >= 1.0) {
            Logger::debug("FPS: " + formatFps(fpsFrameCount / fpsElapsedTime));
            fpsFrameCount = 0;
            fpsElapsedTime = 0.0;
        }

        input->pollEvents();

        game->update(time->getDeltaTime());

        renderer->beginFrame();
        renderer->render(*game, time->getElapsedTime());
        window->swapBuffers();

        if (!config.vsync && config.targetFps > 0) {
            const double frameTime = glfwGetTime() - frameStart;
            const double targetFrameTime = 1.0 / config.targetFps;

            if (frameTime < targetFrameTime) {
                std::this_thread::sleep_for(std::chrono::duration<double>(targetFrameTime - frameTime));
            }
        }
    }

    Logger::info("Application stopped");
    return true;
}
