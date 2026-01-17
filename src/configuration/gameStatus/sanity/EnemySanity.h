#pragma once

struct EnemySanityCount
{
    int current;
    int total;
};

#include <unordered_map>

class EnemySanity
{
public:
    EnemySanity() = default;

    std::unordered_map<int, EnemySanityCount>& operator[](const int levelId)
    {
        return _enemyCount[levelId];
    }

private:
    std::unordered_map<int, std::unordered_map<int, EnemySanityCount>> _enemyCount;
};
