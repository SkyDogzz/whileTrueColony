#include "Game.hpp"
#include "Logger.hpp"

Game::Game() { Logger::debug("Game initialized"); }

Game::~Game() { Logger::debug("Game destroyed"); }

void Game::update(float deltaTime) { (void)deltaTime; }
