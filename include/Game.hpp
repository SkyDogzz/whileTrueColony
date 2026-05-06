#pragma once

class Game {
private:
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;

public:
    Game();
    ~Game();

    void update(float deltaTime);
};
