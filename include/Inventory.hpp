#pragma once

#include <array>

enum class ResourceType { Wood, Stone, Iron, Count };

class Inventory {
private:
    std::array<int, static_cast<std::size_t>(ResourceType::Count)> amounts { };
    int capacity = 0;
};
