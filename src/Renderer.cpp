#include "Renderer.hpp"
#include "Logger.hpp"
#include "Shader.hpp"
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <glad/gl.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <numbers>
#include <stdexcept>
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

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
};

static unsigned int parseObjIndex(const char* token)
{
    const unsigned long index = std::strtoul(token, nullptr, 10);
    if (index == 0) {
        throw std::runtime_error("ERROR::OBJ::INVALID_FACE_INDEX");
    }
    return static_cast<unsigned int>(index - 1);
}

void Renderer::initShaders()
{
    Shader shader = Shader("assets/shaders/shad.vert", "assets/shaders/shad.frag");
    shaderProgram = shader.ID;
    glUseProgram(shaderProgram);

    // initGeometry();
    initGeometry("assets/obj/teapot.obj");
}

void Renderer::initGeometry(const std::string& filename)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<glm::vec3> vertColor;
    unsigned int vertIndex = 0;

    vertColor.push_back({ 1.f, 1.f, 1.f });
    vertColor.push_back({ 1.f, 0.f, 0.f });
    vertColor.push_back({ 0.f, 1.f, 0.f });
    vertColor.push_back({ 0.f, 0.f, 1.f });
    vertColor.push_back({ 1.f, 1.f, 0.f });
    vertColor.push_back({ 0.f, 1.f, 1.f });
    vertColor.push_back({ 1.f, 0.f, 1.f });

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error(std::string("ERROR::FILE::FILE_NOT_SUCCESSFULLY_READ: ") + filename);
    }
    char line[100];
    while (file.getline(line, 100)) {
        if (line[0] == 'v' && line[1] == ' ') {
            glm::vec3 pos;
            char* token = std::strtok(line, " ");
            token = std::strtok(NULL, " ");
            pos.x = atof(token);
            token = std::strtok(NULL, " ");
            pos.y = atof(token);
            token = std::strtok(NULL, " ");
            pos.z = atof(token);
            vertices.push_back({ pos, vertColor.at(vertIndex % vertColor.size()) });
            vertIndex++;
        } else if (line[0] == 'f' && line[1] == ' ') {
            char* token = std::strtok(line, " ");
            token = std::strtok(NULL, " ");
            indices.push_back(parseObjIndex(token));
            token = std::strtok(NULL, " ");
            indices.push_back(parseObjIndex(token));
            token = std::strtok(NULL, " ");
            indices.push_back(parseObjIndex(token));
        }
    }

    indexCount = static_cast<unsigned int>(indices.size());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Logger::debug("Renderer geometry initialized");
}

void Renderer::initGeometry()
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<glm::vec3> hexagonColor;
    hexagonColor.push_back({ 1.f, 1.f, 1.f });
    hexagonColor.push_back({ 1.f, 0.f, 0.f });
    hexagonColor.push_back({ 0.f, 1.f, 0.f });
    hexagonColor.push_back({ 0.f, 0.f, 1.f });
    hexagonColor.push_back({ 1.f, 1.f, 0.f });
    hexagonColor.push_back({ 0.f, 1.f, 1.f });
    hexagonColor.push_back({ 1.f, 0.f, 1.f });

    auto addHexagon = [&vertices, &indices, &hexagonColor](const glm::vec3& center) {
        static unsigned int hexagonIndex = 0;
        const unsigned int centerIndex = static_cast<unsigned int>(vertices.size());
        const glm::vec3 color = hexagonColor.at(hexagonIndex % hexagonColor.size());

        vertices.push_back({ center, color });
        for (int i = 0; i < 6; i++) {
            const float angle = 2.0f * std::numbers::pi_v<float> * i / 6.0f;
            const float x = center.x + std::cos(angle) / 2.0f;
            const float y = center.y + std::sin(angle) / 2.0f;
            vertices.push_back({ glm::vec3(x, y, 0.0f), color });
        }

        for (int i = 1; i < 6; i++) {
            indices.push_back(centerIndex);
            indices.push_back(centerIndex + i);
            indices.push_back(centerIndex + i + 1);
        }
        indices.push_back(centerIndex);
        indices.push_back(centerIndex + 6);
        indices.push_back(centerIndex + 1);

        hexagonIndex++;
    };

    addHexagon(glm::vec3(0.0f, 0.0f, 0.0f));

    const float hexagonRadius = 0.5f;
    const float centerDistance = std::sqrt(3.0f) * hexagonRadius;

    std::vector<glm::vec3> directions;
    for (int multiplier = 1; multiplier <= 11; multiplier += 2) {
        const float angle = std::numbers::pi_v<float> / 6.0f * multiplier;
        directions.push_back(glm::vec3(std::cos(angle) * centerDistance, std::sin(angle) * centerDistance, 0.0f));
    }

    for (std::size_t i = 0; i < directions.size(); i++) {
        const glm::vec3& direction = directions.at(i);
        const glm::vec3& nextDirection = directions.at((i + 1) % directions.size());

        addHexagon(direction);
        addHexagon(direction * 2.0f);
        addHexagon(direction + nextDirection);
    }

    indexCount = static_cast<unsigned int>(indices.size());
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Logger::debug("Renderer geometry initialized");
}

void Renderer::applyConfig() const
{
    glClearColor(config.clearColorRed, config.clearColorGreen, config.clearColorBlue, config.clearColorAlpha);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    Logger::debug("Renderer clear color applied: " + std::to_string(config.clearColorRed) + ", "
        + std::to_string(config.clearColorGreen) + ", " + std::to_string(config.clearColorBlue) + ", "
        + std::to_string(config.clearColorAlpha));
}

void Renderer::beginFrame() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void Renderer::render(const Game& game, float elapsedTime) const
{
    (void)game;

    glUseProgram(shaderProgram);

    glm::mat4 transform(1.0f);
    transform = glm::rotate(transform, std::numbers::pi_v<float> / 4, glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, elapsedTime, glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.2, 0.2, 0.2));

    const int transformLocation = glGetUniformLocation(shaderProgram, "uTransform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
