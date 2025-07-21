#include "AdventureFieldEntranceMap.h"

//TODO: enable controls after entering the EC

//TODO: Improve performance by using a map or unordered_map for faster lookups
AdventureFieldEntranceMap::AdventureFieldEntranceMap()
{
    _entranceList = {


        //City Hall
        {CityHallToSsMain, LevelAndActIDs_StationSquare1, 1, SsMainToCityHall, 50.0f, {550.79f, 14.5, 856.22f}},
        {CityHallToChaos0, LevelAndActIDs_StationSquare1, 0, Chaos0ToCityHall, 0, {270, 16, 450}},
        {CityHallToSewers, LevelAndActIDs_StationSquare1, 2, SewersToCityHall, 0, {361, 10, 941.5}},
        {CityHallToSpeedHighway, LevelAndActIDs_StationSquare1, 0, SpeedHighwayToCityHall, 0, {270, 20, 255}},

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
        {SewersToSsMain, LevelAndActIDs_StationSquare3, 1, SsMainToSewers, 0, {395, -87, 1323}},
        {SewersToCityHall, LevelAndActIDs_StationSquare3, 0, CityHallToSewers, 90, {433.5, 13, 635}},

        // SSMain
        {SsMainToCityHall, LevelAndActIDs_StationSquare4, 1, CityHallToSsMain, 110.8F, {443, 13, 1077}},
        {SsMainToStation, LevelAndActIDs_StationSquare4, 0, StationToSsMain, 18.81f, {28, 41, 1388}},
        {SsMainToHotel, LevelAndActIDs_StationSquare4, 3, HotelToSsMain, 90, {-168, 15, 1685}},
        {SsMainToTwinkleParkLobby, LevelAndActIDs_StationSquare4, 4, TwinkleParkLobbyToSsMain, 90, {580, 65, 1772}},
        {SsMainToEcOutside, LevelAndActIDs_StationSquare4, 6, EcOutsideToSsMain, 30, {174.09f, 6, 1897.51f}},
        //TODO: Add a connection to the EC bridge
        {SsMainToSewers, LevelAndActIDs_StationSquare4, 2, SewersToSsMain, 0, {400, 58, 1450}},
        {SsMainToSpeedHighway, LevelAndActIDs_StationSquare4, 5, SpeedHighwayToSsMain, 90, {380, 20, 1370}},

        // Hotel
        {HotelToSsMain, LevelAndActIDs_StationSquare5, 1, SsMainToHotel, 90, {-245.5, 13, 1685.25}},
        {HotelToStation, LevelAndActIDs_StationSquare5, 3, StationToHotel, 0.0f, {-370, 13, 1605}},
        {HotelToEmeraldCoast, LevelAndActIDs_StationSquare5, 2, EmeraldCoastToHotel, 135, {-520, 10, 2093}},
        {HotelToSsChaoGarden, LevelAndActIDs_StationSquare5, 4, SsChaoGardenToHotel, 90, {-395, 13, 1700}},
        {HotelToChaos2, LevelAndActIDs_StationSquare5, 5, Chaos2ToHotel, 90, {-395, 13, 1665}},


        // Twinkle Park Lobby
        {TwinkleParkLobbyToSsMain, LevelAndActIDs_StationSquare6, 0, SsMainToTwinkleParkLobby, 90, {675, 65, 1771.5f}},
        {
            TwinkleParkLobbyToTwinkleCircuit, LevelAndActIDs_StationSquare6, 2, TwinkleCircuitToTwinkleParkLobby, 0,
            {757, 65, 1735}
        },
        {
            TwinkleParkLobbyToTwinklePark, LevelAndActIDs_StationSquare6, 1, TwinkleParkToTwinkleParkLobby, 90,
            {804, 65, 1771.5f}
        },


        // MRMain
        {MrMainToSsMain, LevelAndActIDs_MysticRuins1, 0, StationToMrMain, 56.25f, {0, 228, 1207}},
        {MrMainToChaos4, LevelAndActIDs_MysticRuins1, 0, Chaos4ToMrMain, 0, {80, 87, 180}},
        {MrMainToEggHornet, LevelAndActIDs_MysticRuins1, 0, EggHornetToMrMain, 0, {950, 142, 950}},
        {MrMainToSkyChase1, LevelAndActIDs_MysticRuins1, 0, SkyChase1ToMrMain, 90, {1561, 206, 900}},
        {MrMainToEcOutside, LevelAndActIDs_MysticRuins1, 0, EcOutsideToMrMain, 147.5f, {-70, -385, 1264}},
        {MrMainToJungle, LevelAndActIDs_MysticRuins1, 2, JungleToMrMain, 211, {-200.86f, 81.5, -69.51f}},
        {MrMainToMrChaoGarden, LevelAndActIDs_MysticRuins1, 4, MrChaoGardenToMrMain, 111, {1696, 17.5, -86}},
        {MrMainToAngelIsland, LevelAndActIDs_MysticRuins1, 1, AngelIslandToMrMain, 112.5f, {-347, 120, 869}},
        {MrMainToWindyValley, LevelAndActIDs_MysticRuins1, 3, WindyValleyToMrMain, 145, {640, 80, -143}},

        // Angel Island
        {AngelIslandToMrMain, LevelAndActIDs_MysticRuins2, 0, MrMainToAngelIsland, 0.0f, {0, 0, 0}},
        {AngelIslandToPastAltar, LevelAndActIDs_MysticRuins2, 3, PastAltarToAngelIsland, 0.0f, {-2.5f, -225, 2397.5f}},

        //Past Altar
        {PastAltarToAngelIsland, LevelAndActIDs_Past2, 0, AngelIslandToPastAltar, 0.0f, {0, 24, 247.5f}},


        // Jungle
        {JungleToMrMain, LevelAndActIDs_MysticRuins3, 0, MrMainToJungle, 137.36f, {-1143, 369, 418}},


        // Egg Carrier Outside (Untransformed)
        {EcOutsideToSsMain, LevelAndActIDs_EggCarrierOutside1, 0, SsMainToEcOutside, 0.0f, {0, 0, 0}},
        {EcOutsideToMrMain, LevelAndActIDs_EggCarrierOutside1, 0, MrMainToEcOutside, 0.0f, {0, 0, 0}},

        // SS Chao Garden
        {SsChaoGardenToHotel, LevelAndActIDs_SSGarden, 0, HotelToSsChaoGarden, 90, {-395, 13, 1700}},

        // Mr Chao Garden
        {MrChaoGardenToMrMain, LevelAndActIDs_MRGarden, 0, MrMainToMrChaoGarden, 0.0f, {0, 0, 0}},


        // Speed Highway
        {SpeedHighwayToSsMain, LevelAndActIDs_SpeedHighway1, 0, SsMainToSpeedHighway, 0, {0, 0, 0}},
        {SpeedHighwayToCityHall, LevelAndActIDs_SpeedHighway3, 0, CityHallToSpeedHighway, 0, {0, 0, 0}},

        // Emerald Coast
        {EmeraldCoastToHotel, LevelAndActIDs_EmeraldCoast1, 0, HotelToEmeraldCoast, 0, {0, 0, 0}},

        // Casinopolis
        {CasinopolisToStation, LevelAndActIDs_Casinopolis1, 0, StationToCasinopolis, 0, {0, 0, 0}},

        // Twinkle Park
        {TwinkleParkToTwinkleParkLobby, LevelAndActIDs_TwinklePark1, 0, TwinkleParkLobbyToTwinklePark, 0, {0, 0, 0}},

        // Windy Valley
        {WindyValleyToMrMain, LevelAndActIDs_WindyValley1, 0, MrMainToWindyValley, 0, {0, 0, 0}},

        // Chaos 0
        {Chaos0ToCityHall, LevelAndActIDs_Chaos0, 1, CityHallToChaos0, 0, {0, 0, 0}},
        // Chaos 2
        {Chaos2ToHotel, LevelAndActIDs_Chaos2, 0, HotelToChaos2, 0, {0, 0, 0}},
        // Egg Walker
        {EggWalkerToStation, LevelAndActIDs_EggWalker, 0, StationToEggWalker, 0, {0, 0, 0}},
        // Chaos 4
        {Chaos4ToMrMain, LevelAndActIDs_Chaos4, 0, MrMainToChaos4, 0, {0, 0, 0}},
        // Egg Hornet
        {EggHornetToMrMain, LevelAndActIDs_EggHornet, 0, MrMainToEggHornet, 0, {0, 0, 0}},

        // Twinkle Circuit
        {
            TwinkleCircuitToTwinkleParkLobby, LevelAndActIDs_TwinkleCircuit1, 0, TwinkleParkLobbyToTwinkleCircuit, 0,
            {0, 0, 0}
        },
        {
            TwinkleCircuitToTwinkleParkLobby, LevelAndActIDs_TwinkleCircuit2, 0, TwinkleParkLobbyToTwinkleCircuit, 0,
            {0, 0, 0}
        },
        {
            TwinkleCircuitToTwinkleParkLobby, LevelAndActIDs_TwinkleCircuit3, 0, TwinkleParkLobbyToTwinkleCircuit, 0,
            {0, 0, 0}
        },
        {
            TwinkleCircuitToTwinkleParkLobby, LevelAndActIDs_TwinkleCircuit4, 0, TwinkleParkLobbyToTwinkleCircuit, 0,
            {0, 0, 0}
        },
        {
            TwinkleCircuitToTwinkleParkLobby, LevelAndActIDs_TwinkleCircuit5, 0, TwinkleParkLobbyToTwinkleCircuit, 0,
            {0, 0, 0}
        },
        {
            TwinkleCircuitToTwinkleParkLobby, LevelAndActIDs_TwinkleCircuit6, 0, TwinkleParkLobbyToTwinkleCircuit, 0,
            {0, 0, 0}
        },
        // Sky Chase 1
        {SkyChase1ToMrMain, LevelAndActIDs_SkyChase1, 0, MrMainToSkyChase1, 0, {0, 0, 0}},

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
