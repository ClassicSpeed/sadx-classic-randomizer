#pragma once

struct CapsuleSanityCount
{
    int current;
    int total;
};

#include <unordered_map>

class CapsuleSanity
{
public:
    CapsuleSanity() = default;

    std::unordered_map<int, CapsuleSanityCount>& operator[](const int levelId)
    {
        return _capsuleCount[levelId];
    }

private:
    std::unordered_map<int, std::unordered_map<int, CapsuleSanityCount>> _capsuleCount;
};
