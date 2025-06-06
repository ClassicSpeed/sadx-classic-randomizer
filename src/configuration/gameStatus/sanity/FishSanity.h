#pragma once
#include <unordered_map>

struct FishSanityCount
{
    int current;
    int total;
};


class FishSanity
{
public:
    FishSanity() = default;

    // Access by level ID
    FishSanityCount& operator[](const int levelId)
    {
        return _fishCounts[levelId];
    }

private:
    std::unordered_map<int, FishSanityCount> _fishCounts;
};
