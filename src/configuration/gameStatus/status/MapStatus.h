#pragma once
#include <bitset>

struct MapStatus
{
    bool isEggCarrierTransformed = false;
    static constexpr size_t EntranceCount = InvalidEntranceId;
    std::bitset<EntranceCount> entranceVisited{};

    const std::unordered_map<EntranceId, EntranceId> entrancePairs = {
        {SsMainToEcOutside, SsMainToBridge},
        {MrMainToEcOutside, MrMainToBridge},
        {EcOutsideToSsMain, BridgeToSsMain},
        {EcOutsideToMrMain, BridgeToMrMain},
        {EcOutsideToSkyChase2, BridgeToSkyChase2},
        {EcOutsideToChaos6ZeroBeta, BridgeToChaos6ZeroBeta},
        {EcOutsideToEcInsideMonorail, BridgeToEcInsideMonorail},
        {EcOutsideToEcInsideEggLift, DeckToEcInsideEggLift},
        {EcOutsideToCaptainRoom, DeckToCaptainRoom},
        {EcOutsideToPool, DeckToPool},
        {CaptainRoomToEcOutside, CaptainRoomToDeck},
        {PoolToEcOutside, PoolToDeck},
        {EcInsideToEcOutsideEggLift, EcInsideToDeckEggLift},
        {EcInsideToEcOutsideMonorail, EcInsideToBridgeMonorail},
        {SkyChase2ToEcOutside, SkyChase2ToBridge},
        {Chaos6ZeroBetaToEcOutside, Chaos6ZeroBetaToBridge}
    };

    void SetEntranceVisited(EntranceId id, bool visited)
    {
        const size_t idx = static_cast<size_t>(id);
        if (idx < EntranceCount)
        {
            entranceVisited.set(idx, visited);


            EntranceId pairedEntrance = InvalidEntranceId;

            auto it = entrancePairs.find(id);
            if (it != entrancePairs.end())
            {
                pairedEntrance = it->second;
            }
            else
            {
                for (const auto& pair : entrancePairs)
                {
                    if (pair.second == id)
                    {
                        pairedEntrance = pair.first;
                        break;
                    }
                }
            }

            if (pairedEntrance != InvalidEntranceId)
            {
                const size_t pairedIdx = static_cast<size_t>(pairedEntrance);
                if (pairedIdx < EntranceCount)
                {
                    entranceVisited.set(pairedIdx, visited);
                }
            }
        }
    }

    bool IsEntranceVisited(EntranceId id) const
    {
        const size_t idx = static_cast<size_t>(id);
        return (idx < EntranceCount) ? entranceVisited.test(idx) : false;
    }
};
