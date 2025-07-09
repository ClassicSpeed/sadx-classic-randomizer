#include "AdventureFieldEntranceMap.h"

//TODO: enable controls after entering the EC

//TODO: Improve performance by using a map or unordered_map for faster lookups
AdventureFieldEntranceMap::AdventureFieldEntranceMap()
{
    _entranceList = {


        //City Hall
        {CityHallToSsMain, LevelAndActIDs_StationSquare1, 1, SsMainToCityHall, 50.0f, {550.79f, 14.5, 856.22f}},
        {CityHallToChaos0, LevelAndActIDs_StationSquare1, 1, Chaos0ToCityHall, 0, {270, 16, 450}},
        {CityHallToSewers, LevelAndActIDs_StationSquare1, 2, SewersToCityHall, 0, {0, 0, 0}},


        //Station
        {StationToSsMain, LevelAndActIDs_StationSquare2, 0, SsMainToStation, 26, {59, 79, 1452}},
        {StationToCasinopolis, LevelAndActIDs_StationSquare2, 1, CasinopolisToStation, 45, {-620, 12.5, 905}},
        {StationToHotel, LevelAndActIDs_StationSquare2, 2, HotelToStation, 0.0f, {-445, 13, 1515}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToSsMain, 26, {-236.8f, 153, 1237}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToSsMain, 26, {-164, 153, 1204}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToSsMain, 26, {-115, 153, 1179}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToSsMain, 26, {-43, 153, 1142}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToSsMain, 26, {4.6f, 153, 1116.4f}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToSsMain, 26, {76.5f, 153, 1080.7f}},
        {StationToEggWalker, LevelAndActIDs_StationSquare2, 1, EggWalkerToStation, 0, {-400, 13, 955}},

        // Sewers
        {SewersToSsMain, LevelAndActIDs_StationSquare3, 1, SsMainToSewers, 0, {174.09f, 6, 1897.51f}},
        {SewersToCityHall, LevelAndActIDs_StationSquare3, 0, CityHallToSewers, 90, {433.5, 13, 635}},

        // SSMain
        {SsMainToCityHall, LevelAndActIDs_StationSquare4, 1, CityHallToSsMain, 110.8F, {443, 13, 1077}},
        {SsMainToStation, LevelAndActIDs_StationSquare4, 0, StationToSsMain, 18.81f, {28, 41, 1388}},
        {SsMainToHotel, LevelAndActIDs_StationSquare4, 3, HotelToSsMain, 90, {-168, 15, 1685}},
        {SsMainToTwinkleParkLobby, LevelAndActIDs_StationSquare4, 4, TwinkleParkLobbyToSsMain, 90, {580, 65, 1772}},
        {SsMainToEcOutside, LevelAndActIDs_StationSquare4, 6, EcOutsideToSsMain, 30, {174.09f, 6, 1897.51f}},
        {SsMainToSewers, LevelAndActIDs_StationSquare4, 2, SewersToSsMain, 0, {400, 58, 1450}},
        {SsMainToSpeedHighway, LevelAndActIDs_StationSquare4, 5, SpeedHighwayToSsMain, 45, {380, 20, 1370}},

        // Hotel
        {HotelToSsMain, LevelAndActIDs_StationSquare5, 1, SsMainToHotel, 90, {-245.5, 13, 1685.25}},
        {HotelToStation, LevelAndActIDs_StationSquare5, 3, StationToHotel, 0.0f, {-370, 13, 1605}},
        {HotelToEmeraldCoast, LevelAndActIDs_StationSquare5, 2, EmeraldCoastToHotel, 135, {-520, 10, 2093}},
        {HotelToSsChaoGarden, LevelAndActIDs_StationSquare5, 4, SsChaoGardenToHotel, 90, {-395, 13, 1700}},
        {HotelToChaos2, LevelAndActIDs_StationSquare5, 5, Chaos2ToHotel, 90, {-395, 13, 1665}},


        // Twinkle Park Lobby
        {TwinkleParkLobbyToSsMain, LevelAndActIDs_StationSquare6, 0, SsMainToTwinkleParkLobby, 90, {580, 65, 1772}},


        // MRMain
        {MrMainToSsMain, LevelAndActIDs_MysticRuins1, 0, StationToMrMain, 0.0f, {0, 0, 0}},


        // Egg Carrier Outside (Untransformed)
        {EcOutsideToSsMain, LevelAndActIDs_EggCarrierOutside1, 0, SsMainToEcOutside, 0.0f, {0, 0, 0}},

        // SS Chao Garden
        {SsChaoGardenToHotel, LevelAndActIDs_SSGarden, 0, HotelToSsChaoGarden, 90, {-395, 13, 1700}},


        // Speed Highway
        {SpeedHighwayToSsMain, LevelAndActIDs_SpeedHighway1, 0, SsMainToSpeedHighway, 0, {0, 0, 0}},

        // Emerald Coast
        {EmeraldCoastToHotel, LevelAndActIDs_EmeraldCoast1, 0, HotelToEmeraldCoast, 0, {0, 0, 0}},

        // Casinopolis
        {CasinopolisToStation, LevelAndActIDs_Casinopolis1, 0, StationToCasinopolis, 0, {0, 0, 0}},

        // Chaos 0
        {Chaos0ToCityHall, LevelAndActIDs_Chaos0, 1, CityHallToChaos0, 0, {0, 0, 0}},
        // Chaos 2
        {Chaos2ToHotel, LevelAndActIDs_Chaos2, 0, HotelToChaos2, 0, {0, 0, 0}},
        // Egg Walker
        {EggWalkerToStation, LevelAndActIDs_EggWalker, 0, StationToEggWalker, 0, {0, 0, 0}},
    };
}

const std::vector<AdventureFieldEntrance>& AdventureFieldEntranceMap::GetEntrances() const
{
    return _entranceList;
}

AdventureFieldEntrance* AdventureFieldEntranceMap::GetNewConnection(
    const LevelAndActIDs sourceLocation, const LevelAndActIDs destinationLocation)

{
    const EntranceId sourceEntranceId = FindEntranceByLocation(sourceLocation, destinationLocation);
    if (sourceEntranceId == static_cast<EntranceId>(-1))
        return nullptr;
    PrintDebug("------AdventureFieldEntranceMap: Found entrance %d for source location %d, %d\n",
               sourceEntranceId, GET_LEVEL(sourceLocation), GET_ACT(sourceLocation));

    const EntranceId destinationEntranceId = GetReplacementConnection(sourceEntranceId);

    PrintDebug("------AdventureFieldEntranceMap: Found replacement connection %d for entrance %d\n",
               destinationEntranceId, sourceEntranceId);


    AdventureFieldEntrance* newEntrance = FindEntranceById(destinationEntranceId);
    PrintDebug("------AdventureFieldEntranceMap: Found entrance by ID %d, %d\n",
               GET_LEVEL(newEntrance->levelAndActId), GET_ACT(newEntrance->levelAndActId));
    return newEntrance;
}


EntranceId AdventureFieldEntranceMap::FindEntranceByLocation(
    const LevelAndActIDs sourceLocation, const LevelAndActIDs destinationLocation)
{
    for (auto& entrance : _entranceList)
    {
        if (entrance.levelAndActId == sourceLocation)
        {
            for (const auto& destEntrance : _entranceList)
            {
                if (destEntrance.levelAndActId == destinationLocation &&
                    destEntrance.connectsTo == entrance.entranceId)
                {
                    return entrance.entranceId;
                }
            }
        }
    }

    return static_cast<EntranceId>(-1); // Return invalid ID if not found
}

EntranceId AdventureFieldEntranceMap::GetReplacementConnection(const EntranceId entranceId)
{
    for (const auto& [entranceA, entranceB] : _entranceNewConnections)
    {
        if (entranceA == entranceId)
            return entranceB;
        if (entranceB == entranceId)
            return entranceA;
    }
    return entranceId;
}


AdventureFieldEntrance* AdventureFieldEntranceMap::FindEntranceById(const EntranceId entranceId)
{
    for (auto& entrance : _entranceList)
    {
        if (entrance.entranceId == entranceId)
            return &entrance;
    }

    return nullptr;
}
