#pragma once
#include <bitset>

struct MapStatus
{
    bool isEggCarrierTransformed = false;
    static constexpr size_t EntranceCount = InvalidEntranceId;
    std::bitset<EntranceCount> entranceVisited{};

    void SetEntranceVisited(EntranceId id, bool visited)
    {
        const size_t idx = static_cast<size_t>(id);
        if (idx < EntranceCount) entranceVisited.set(idx, visited);
    }

    bool IsEntranceVisited(EntranceId id) const
    {
        const size_t idx = static_cast<size_t>(id);
        return (idx < EntranceCount) ? entranceVisited.test(idx) : false;
    }
};
