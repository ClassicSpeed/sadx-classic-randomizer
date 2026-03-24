#pragma once
#include <bitset>

struct MapStatus
{
    bool isEggCarrierTransformed = false;
    static constexpr size_t EntranceCount = InvalidEntranceId;
    std::bitset<EntranceCount> entranceVisited{};

private:
    static EntranceId GetPairedEntrance(EntranceId id)
    {
        static constexpr std::pair<EntranceId, EntranceId> pairs[] = {
            {SpeedHighwayToCityHall, SpeedHighwayToSsMain},
            {LostWorldToJungle, LostWorldToJungleAlternative},
            {FinalEggToFinalEggTower, FinalEggToFinalEggTowerAlternative},
            {SkyDeckToBridge, SkyDeckToPool}
        };

        for (const auto& p : pairs)
        {
            if (id == p.first) return p.second;
            if (id == p.second) return p.first;
        }
        return InvalidEntranceId;
    }

public:
    void SetEntranceVisited(EntranceId id, bool visited)
    {
        const size_t idx = static_cast<size_t>(id);
        if (idx < EntranceCount)
        {
            entranceVisited.set(idx, visited);
        }

        const EntranceId paired = GetPairedEntrance(id);
        const size_t pidx = static_cast<size_t>(paired);
        if (paired != InvalidEntranceId && pidx < EntranceCount)
        {
            entranceVisited.set(pidx, visited);
        }
    }


    bool IsEntranceVisited(EntranceId id) const
    {
        const size_t idx = static_cast<size_t>(id);
        return (idx < EntranceCount) ? entranceVisited.test(idx) : false;
    }
};
