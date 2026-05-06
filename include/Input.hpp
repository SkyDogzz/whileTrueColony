#pragma once

class Input {
private:
    Input(const Input& other) = delete;
    Input& operator=(const Input& other) = delete;

public:
    Input();
    ~Input();

    void pollEvents();
};
