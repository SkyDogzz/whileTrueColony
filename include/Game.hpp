#pragma once

#include <iostream>

class Game {
private:
    Game(const Game& other);
    Game& operator=(const Game& other);

public:
    Game();
    ~Game();

    void update(float deltaTime);
};
