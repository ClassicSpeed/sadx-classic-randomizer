#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

class WeightedRandomSelector
{
public:
    void addNumber(int number, int weight)
    {
        numbers.push_back({number, weight});
        totalWeight += weight;
    }

    int getRandomNumber()
    {
        std::uniform_int_distribution<int> dist(0, totalWeight - 1);
        int randomWeight = dist(rng);

        int cumulativeWeight = 0;
        for (const auto& pair : numbers)
        {
            cumulativeWeight += pair.second;
            if (randomWeight < cumulativeWeight)
            {
                return pair.first;
            }
        }
        return -1; // Should never reach here if weights are positive
    }

private:
    std::vector<std::pair<int, int>> numbers;
    int totalWeight = 0;
    std::mt19937 rng{std::random_device{}()};
};
