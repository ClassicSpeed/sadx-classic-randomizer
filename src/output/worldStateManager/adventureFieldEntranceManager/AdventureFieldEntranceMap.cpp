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
        {AngelIslandToMrMain, LevelAndActIDs_MysticRuins2, 0, MrMainToAngelIsland, 90, {0, 15, 0}},
        {AngelIslandToIceCap, LevelAndActIDs_MysticRuins2, 1, IceCapToAngelIsland, 100, {-1425, 53, 353}},
        {AngelIslandToRedMountain, LevelAndActIDs_MysticRuins2, 2, RedMountainToAngelIsland, 268, {-1955, -335, 1652}},
        {AngelIslandToPastAltar, LevelAndActIDs_MysticRuins2, 3, PastAltarToAngelIsland, 0.0f, {-2.5f, -225, 2397.5f}},

        //Past Altar
        {PastAltarToAngelIsland, LevelAndActIDs_Past2, 1, AngelIslandToPastAltar, 0.0f, {0, 24, 247.5f}},
        {PastAltarToPastMain, LevelAndActIDs_Past2, 0, PastMainToPastAltar, 0.0f, {223.44f, -9.5, 1815.62f}},

        //Past Main
        {PastMainToPastAltar, LevelAndActIDs_Past1, 0, PastAltarToPastMain, 0.0f, {1.907f, 28, 1512.719f}},

        // Jungle
        {JungleToMrMain, LevelAndActIDs_MysticRuins3, 0, MrMainToJungle, 137.36f, {-1143, 369, 418}},
        {JungleToLostWorld, LevelAndActIDs_MysticRuins3, 2, LostWorldToJungle, 180, {-516, 100, -994}},
        {
            JungleToLostWorldAlternative, LevelAndActIDs_MysticRuins3, 1, LostWorldToJungleAlternative, 180,
            {-516, 103, -1327}
        },
        {JungleToFinalEggTower, LevelAndActIDs_MysticRuins3, 4, FinalEggTowerToJungle, 0, {71, 17, -1687.5}},
        {JungleToSandHill, LevelAndActIDs_MysticRuins3, 3, SandHillToJungle, 90, {-1555.5, 55, -69.5}},

        // Final Egg Tower
        {FinalEggTowerToJungle, LevelAndActIDs_MysticRuins4, 0, JungleToFinalEggTower, 0.0f, {0, 124, 166.5}},
        {
            FinalEggTowerToFinalEggAlternative, LevelAndActIDs_MysticRuins4, 1, FinalEggToFinalEggTowerAlternative,
            0.0f,
            {0, 124, -155}
        },
        {FinalEggTowerToFinalEgg, LevelAndActIDs_MysticRuins4, 2, FinalEggToFinalEggTower, 115, {175, 135, -25.75}},
        {FinalEggTowerToBetaEggViper, LevelAndActIDs_MysticRuins4, 3, BetaEggViperToFinalEggTower, 45, {0, 16, 0}},


        // Egg Carrier Outside (Untransformed)
        {EcOutsideToSsMain, LevelAndActIDs_EggCarrierOutside1, 0, SsMainToEcOutside, 0.0f, {0, 0, 0}},
        {EcOutsideToMrMain, LevelAndActIDs_EggCarrierOutside1, 0, MrMainToEcOutside, 0.0f, {0, 0, 0}},

        {EcOutsideToPool, LevelAndActIDs_EggCarrierOutside1, 1, PoolToEcOutside, 0.0f, {0, 759.5f, 1074.2f}},

        // Bridge (Transformed)


        // Deck (Transformed)
        {DeckToPool, LevelAndActIDs_EggCarrierOutside3, 1, PoolToDeck, 0.0f, {0, 1551.5897f, 3566.501f}},


        // Privated Pool
        {PoolToEcOutside, LevelAndActIDs_EggCarrierOutside6, 0, EcOutsideToPool, 90, {4.5, 25, 25}},
        {PoolToDeck, LevelAndActIDs_EggCarrierOutside6, 0, DeckToPool, 90, {4.5, 25, 25}},


        // Arsenal
        {ArsenalToEcInside, LevelAndActIDs_EggCarrierInside1, 0, EcInsideToArsenal, 90, {-106, 123, 0}},


        // Egg Carrier Inside
        {EcInsideToHotShelter, LevelAndActIDs_EggCarrierInside2, 1, HotShelterToEcInside, 0.0f, {0, 15, 245}},
        {
            EcInsideToHedgehogHammer, LevelAndActIDs_EggCarrierInside2, 3, HedgehogHammerToEcInside, 135,
            {-62, 15, 192.5}
        },
        {EcInsideToWaterTank, LevelAndActIDs_EggCarrierInside2, 4, WaterTankToEcInside, 90, {-183, 95, -280}},
        {EcInsideToArsenal, LevelAndActIDs_EggCarrierInside2, 5, ArsenalToEcInside, 90, {183.5, 95, 0}},


        // Hedgehog Hammer
        {HedgehogHammerToEcInside, LevelAndActIDs_EggCarrierInside3, 1, EcInsideToHedgehogHammer, 90, {90, 15, 0}},
        {HedgehogHammerToPrisonHall, LevelAndActIDs_EggCarrierInside3, 0, PrisonHallToHedgehogHammer, 90, {-90, 15, 0}},

        // Prison Hall
        {
            PrisonHallToHedgehogHammer, LevelAndActIDs_EggCarrierInside4, 0, HedgehogHammerToPrisonHall, 90,
            {144, 15, 60}
        },
        // Water Tank
        {WaterTankToEcInside, LevelAndActIDs_EggCarrierInside5, 0, EcInsideToWaterTank, 90, {95.5, 71, 0}},

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

        // Ice Cap
        {IceCapToAngelIsland, LevelAndActIDs_IceCap1, 0, AngelIslandToIceCap, 0, {0, 0, 0}},

        // Red Mountain
        {RedMountainToAngelIsland, LevelAndActIDs_RedMountain1, 0, AngelIslandToRedMountain, 0, {0, 0, 0}},

        // Lost World
        {LostWorldToJungle, LevelAndActIDs_LostWorld1, 0, JungleToLostWorld, 0, {0, 0, 0}},
        {LostWorldToJungleAlternative, LevelAndActIDs_LostWorld2, 0, JungleToLostWorldAlternative, 0, {0, 0, 0}},

        // Final Egg
        {
            FinalEggToFinalEggTowerAlternative, LevelAndActIDs_FinalEgg3, 0, FinalEggTowerToFinalEggAlternative, 0,
            {0, 0, 0}
        },
        {FinalEggToFinalEggTower, LevelAndActIDs_FinalEgg1, 0, FinalEggTowerToFinalEgg, 0, {0, 0, 0}},

        // Hot Shelter
        {HotShelterToEcInside, LevelAndActIDs_HotShelter1, 0, EcInsideToHotShelter, 0.0f, {0, 0, 0}},

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
        // Egg Viper
        {BetaEggViperToFinalEggTower, LevelAndActIDs_EggViper, 0, FinalEggTowerToBetaEggViper, 0, {0, 0, 0}},

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


        // Sand Hill
        {SandHillToJungle, LevelAndActIDs_SandHill, 0, JungleToSandHill, 0, {0, 0, 0}},

    };
}

const std::vector<AdventureFieldEntrance>& AdventureFieldEntranceMap::GetEntrances() const
{
    return _entranceList;
}

AdventureFieldEntrance* AdventureFieldEntranceMap::GetNewConnection(
    const LevelAndActIDs sourceLocation, const LevelAndActIDs destinationLocation, const bool isEggCarrierTransformed)

{
    const EntranceId sourceEntranceId = FindEntranceByLocation(sourceLocation, destinationLocation);
    if (sourceEntranceId == static_cast<EntranceId>(-1))
        return nullptr;
    PrintDebug("------AdventureFieldEntranceMap: Found entrance %d for source location %d, %d\n",
               sourceEntranceId, GET_LEVEL(sourceLocation), GET_ACT(sourceLocation));

    const EntranceId destinationEntranceId = GetReplacementConnection(sourceEntranceId);

    PrintDebug("------AdventureFieldEntranceMap: Found replacement connection %d for entrance %d\n",
               destinationEntranceId, sourceEntranceId);


    AdventureFieldEntrance* newEntrance = FindEntranceById(destinationEntranceId, isEggCarrierTransformed);
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


AdventureFieldEntrance* AdventureFieldEntranceMap::FindEntranceById(const EntranceId entranceId,
                                                                    const bool isEggCarrierTransformed)
{
    EntranceId actualEntranceId = entranceId;
    if (isEggCarrierTransformed)
    {
        switch (entranceId)
        {
        case EcOutsideToPool:
            actualEntranceId = DeckToPool;
            break;
        case PoolToEcOutside:
            actualEntranceId = PoolToDeck;
            break;
        default:
            break;
        }
    }
    else
    {
        switch (entranceId)
        {
        case DeckToPool:
            actualEntranceId = EcOutsideToPool;
            break;
        case PoolToDeck:
            actualEntranceId = PoolToEcOutside;
            break;
        default:
            break;
        }
    }
    PrintDebug("------AdventureFieldEntranceMap: Looking for entrance ID %d (actual ID %d)\n",
               entranceId, actualEntranceId);

    for (auto& entrance : _entranceList)
    {
        if (entrance.entranceId == actualEntranceId)
            return &entrance;
    }

    return nullptr;
}
