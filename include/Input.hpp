#pragma once

class Input {
private:
    Input(const Input& other);
    Input& operator=(const Input& other);

public:
    Input();
    ~Input();

    void pollEvents();
};
