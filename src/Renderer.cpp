#include "Renderer.hpp"
#include "Logger.hpp"
#include <cmath>
#include <glad/gl.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <vector>

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
                                 "uniform mat4 uTransform;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = uTransform * vec4(aPos, 1.0);\n"
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
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    auto addHexagon = [&vertices, &indices](const glm::vec3& center) {
        const unsigned int centerIndex = static_cast<unsigned int>(vertices.size());

        vertices.push_back(center);
        for (int i = 0; i < 6; i++) {
            const float angle = 2.0f * M_PI * i / 6.0f;
            const float x = center.x + std::cos(angle) / 2.0f;
            const float y = center.y + std::sin(angle) / 2.0f;
            vertices.push_back(glm::vec3(x, y, 0.0f));
        }

        for (int i = 1; i < 6; i++) {
            indices.push_back(centerIndex);
            indices.push_back(centerIndex + i);
            indices.push_back(centerIndex + i + 1);
        }
        indices.push_back(centerIndex);
        indices.push_back(centerIndex + 6);
        indices.push_back(centerIndex + 1);
    };

    addHexagon(glm::vec3(0.0f, 0.0f, 0.0f));

    for (int multiplier = 1; multiplier <= 11; multiplier += 2) {
        const float angle = M_PI / 6.0f * multiplier;
        addHexagon(glm::vec3(std::cos(angle), std::sin(angle), 0.0f));
    }

    indexCount = static_cast<unsigned int>(indices.size());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

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

void Renderer::render(const Game& game, float elapsedTime) const
{
    (void)game;

    glUseProgram(shaderProgram);

    glm::mat4 transform(1.0f);
    transform = glm::rotate(transform, elapsedTime, glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));

    const int transformLocation = glGetUniformLocation(shaderProgram, "uTransform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
