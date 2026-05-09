#include "Renderer.hpp"
#include "Logger.hpp"
#include <cmath>
#include <glad/gl.h>

Renderer::Renderer() { Logger::debug("Renderer initialized"); }

Renderer::Renderer(const RendererConfig& config)
    : config(config)
{
    Logger::debug("Renderer initialized");
}

Renderer::~Renderer()
{
    if (EBO != 0)
        glDeleteBuffers(1, &EBO);
    if (VBO != 0)
        glDeleteBuffers(1, &VBO);
    if (VAO != 0)
        glDeleteVertexArrays(1, &VAO);
    if (shaderProgram != 0)
        glDeleteProgram(shaderProgram);

    Logger::debug("Renderer destroyed");
}

const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

void Renderer::initShaders()
{
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        Logger::error("Vertex shader compilation failed: " + std::string(infoLog));
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        Logger::error("Fragment shader compilation failed: " + std::string(infoLog));
    }
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        Logger::error("Shader program linking failed: " + std::string(infoLog));
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    initGeometry();
}

void Renderer::initGeometry()
{
    float vertices[21];
    vertices[0] = 0.f;
    vertices[1] = 0.f;
    vertices[2] = 0.f;
    for (int i = 0; i < 6; i++) {
        const float angle = 2.0f * M_PI * i / 6.0f;
        float x = cos(angle);
        float y = sin(angle);
        vertices[3 * (i + 1)] = x;
        vertices[3 * (i + 1) + 1] = y;
        vertices[3 * (i + 1) + 2] = 0;
    }
    const unsigned int indices[] = {
        0,
        1,
        2,
        0,
        2,
        3,
        0,
        3,
        4,
        0,
        4,
        5,
        0,
        5,
        6,
        0,
        6,
        7,
        0,
        6,
        1,
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Logger::debug("Renderer geometry initialized");
}

void Renderer::applyConfig() const
{
    glClearColor(config.clearColorRed, config.clearColorGreen, config.clearColorBlue, config.clearColorAlpha);
    Logger::debug("Renderer clear color applied: " + std::to_string(config.clearColorRed) + ", "
        + std::to_string(config.clearColorGreen) + ", " + std::to_string(config.clearColorBlue) + ", "
        + std::to_string(config.clearColorAlpha));
}

void Renderer::beginFrame() const { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::render(const Game& game) const
{
    (void)game;

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 21, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
