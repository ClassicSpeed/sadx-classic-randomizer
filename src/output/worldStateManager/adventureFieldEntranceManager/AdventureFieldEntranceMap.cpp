#include "AdventureFieldEntranceMap.h"

//TODO: enable controls after entering the EC

//TODO: Improve performance by using a map or unordered_map for faster lookups
AdventureFieldEntranceMap::AdventureFieldEntranceMap()
{
    _entranceList = {
        //TODO: MR garden - MRMain
        //Fix control disable when transitioning into the  same stage with vehicles
        //Fix icecap door?


        //City Hall
        {CityHallToSsMain, LevelAndActIDs_StationSquare1, 1, SsMainToCityHall, 50.0f, {550.79f, 14.5, 856.22f}},
        {CityHallToChaos0, LevelAndActIDs_StationSquare1, 0, Chaos0ToCityHall, 180, {270, 16, 450}},
        {CityHallToSewers, LevelAndActIDs_StationSquare1, 2, SewersToCityHall, 0, {361, 10, 941.5}},
        {CityHallToSpeedHighway, LevelAndActIDs_StationSquare1, 0, SpeedHighwayToCityHall, 180, {270, 20, 255}},

        //Station
        {StationToSsMain, LevelAndActIDs_StationSquare2, 0, SsMainToStation, 26, {59, 79, 1452}},
        {StationToCasinopolis, LevelAndActIDs_StationSquare2, 1, CasinopolisToStation, 225, {-620, 12.5, 905}},
        {StationToHotel, LevelAndActIDs_StationSquare2, 2, HotelToStation, 0.0f, {-445, 13, 1515}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToSsMain, 206, {-236.8f, 153, 1237}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToSsMain, 206, {-164, 153, 1204}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToSsMain, 206, {-115, 153, 1179}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToSsMain, 206, {-43, 153, 1142}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToSsMain, 206, {4.6f, 153, 1116.4f}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToSsMain, 206, {76.5f, 153, 1080.7f}},
        {StationToEggWalker, LevelAndActIDs_StationSquare2, 1, EggWalkerToStation, 0, {-400, 13, 955}},

        // Sewers
        {SewersToSsMain, LevelAndActIDs_StationSquare3, 1, SsMainToSewers, 0, {395, -87, 1323}},
        {SewersToCityHall, LevelAndActIDs_StationSquare3, 0, CityHallToSewers, 270, {433.5, 13, 635}},

        // SSMain
        {SsMainToCityHall, LevelAndActIDs_StationSquare4, 1, CityHallToSsMain, 110.8F, {443, 13, 1077}},
        {SsMainToStation, LevelAndActIDs_StationSquare4, 0, StationToSsMain, 198.81f, {28, 41, 1388}},
        {SsMainToHotel, LevelAndActIDs_StationSquare4, 3, HotelToSsMain, 270, {-168, 15, 1685}},
        {SsMainToTwinkleParkLobby, LevelAndActIDs_StationSquare4, 4, TwinkleParkLobbyToSsMain, 90, {580, 65, 1772}},
        {SsMainToEcOutside, LevelAndActIDs_StationSquare4, 6, EcOutsideToSsMain, 30, {174.09f, 6, 1897.51f}},
        {SsMainToBridge, LevelAndActIDs_StationSquare4, 6, BridgeToSsMain, 30, {174.09f, 6, 1897.51f}},
        {SsMainToSewers, LevelAndActIDs_StationSquare4, 2, SewersToSsMain, 180, {400, 58, 1450}},
        {SsMainToSpeedHighway, LevelAndActIDs_StationSquare4, 5, SpeedHighwayToSsMain, 90, {380, 20, 1370}},

        // Hotel
        {HotelToSsMain, LevelAndActIDs_StationSquare5, 1, SsMainToHotel, 90, {-245.5, 13, 1685.25}},
        {HotelToStation, LevelAndActIDs_StationSquare5, 3, StationToHotel, 180, {-370, 13, 1605}},
        {HotelToEmeraldCoast, LevelAndActIDs_StationSquare5, 2, EmeraldCoastToHotel, 315, {-520, 10, 2093}},
        {HotelToSsChaoGarden, LevelAndActIDs_StationSquare5, 4, SsChaoGardenToHotel, 270, {-395, 13, 1700}},
        {HotelToChaos2, LevelAndActIDs_StationSquare5, 5, Chaos2ToHotel, 270, {-395, 13, 1665}},


        // Twinkle Park Lobby
        {TwinkleParkLobbyToSsMain, LevelAndActIDs_StationSquare6, 0, SsMainToTwinkleParkLobby, 270, {675, 65, 1771.5f}},
        {
            TwinkleParkLobbyToTwinkleCircuit, LevelAndActIDs_StationSquare6, 2, TwinkleCircuitToTwinkleParkLobby, 180,
            {757, 65, 1735}
        },
        {
            TwinkleParkLobbyToTwinklePark, LevelAndActIDs_StationSquare6, 1, TwinkleParkToTwinkleParkLobby, 90,
            {804, 65, 1771.5f}
        },


        // MRMain
        {MrMainToSsMain, LevelAndActIDs_MysticRuins1, 0, StationToMrMain, 56.25f, {0, 228, 1207}},
        {MrMainToChaos4, LevelAndActIDs_MysticRuins1, 0, Chaos4ToMrMain, 180, {80, 87, 180}},
        {MrMainToEggHornet, LevelAndActIDs_MysticRuins1, 0, EggHornetToMrMain, 0, {950, 142, 950}},
        {MrMainToSkyChase1, LevelAndActIDs_MysticRuins1, 0, SkyChase1ToMrMain, 90, {1561, 206, 900}},
        {MrMainToEcOutside, LevelAndActIDs_MysticRuins1, 0, EcOutsideToMrMain, 147.5f, {-70, -385, 1264}},
        {MrMainToBridge, LevelAndActIDs_MysticRuins1, 0, BridgeToMrMain, 147.5f, {-70, -385, 1264}},
        {MrMainToJungle, LevelAndActIDs_MysticRuins1, 2, JungleToMrMain, 211, {-200.86f, 81.5, -69.51f}},
        {MrMainToMrChaoGarden, LevelAndActIDs_MysticRuins1, 4, MrChaoGardenToMrMain, 111, {1696, 17.5, -86}},
        {MrMainToAngelIsland, LevelAndActIDs_MysticRuins1, 1, AngelIslandToMrMain, 270, {-347, 120, 869}},
        {MrMainToWindyValley, LevelAndActIDs_MysticRuins1, 3, WindyValleyToMrMain, 145, {640, 80, -143}},

        // Angel Island
        {AngelIslandToMrMain, LevelAndActIDs_MysticRuins2, 0, MrMainToAngelIsland, 90, {0, 15, 0}},
        {AngelIslandToIceCap, LevelAndActIDs_MysticRuins2, 1, IceCapToAngelIsland, 280, {-1425, 53, 353}},
        {AngelIslandToRedMountain, LevelAndActIDs_MysticRuins2, 2, RedMountainToAngelIsland, 268, {-1955, -335, 1652}},
        {AngelIslandToPastAltar, LevelAndActIDs_MysticRuins2, 3, PastAltarToAngelIsland, 90, {-2.5f, -225, 2397.5f}},

        //Past Altar
        {PastAltarToAngelIsland, LevelAndActIDs_Past2, 1, AngelIslandToPastAltar, 180, {0, 24, 247.5f}},
        {PastAltarToPastMain, LevelAndActIDs_Past2, 0, PastMainToPastAltar, 0.0f, {223.44f, -9.5, 1815.62f}},

        //Past Main
        {PastMainToPastAltar, LevelAndActIDs_Past1, 0, PastAltarToPastMain, 0.0f, {1.907f, 28, 1512.719f}},
        {PastMainToJungle, LevelAndActIDs_Past1, 2, JungleToPastMain, 90, {-151.5f, 315, 0}},

        // Jungle
        {JungleToMrMain, LevelAndActIDs_MysticRuins3, 0, MrMainToJungle, 317.36f, {-1143, 369, 418}},
        {JungleToLostWorld, LevelAndActIDs_MysticRuins3, 2, LostWorldToJungle, 180, {-516, 100, -994}},
        {
            JungleToLostWorldAlternative, LevelAndActIDs_MysticRuins3, 1, LostWorldToJungleAlternative, 0,
            {-516, 103, -1327}
        },
        {JungleToFinalEggTower, LevelAndActIDs_MysticRuins3, 4, FinalEggTowerToJungle, 180, {71, 17, -1687.5}},
        {JungleToSandHill, LevelAndActIDs_MysticRuins3, 3, SandHillToJungle, 270, {-1555.5, 55, -69.5}},
        {JungleToPastMain, LevelAndActIDs_MysticRuins3, 5, PastMainToJungle, 180, {-667, 105.5f, -1181}},

        // Final Egg Tower
        {FinalEggTowerToJungle, LevelAndActIDs_MysticRuins4, 0, JungleToFinalEggTower, 0.0f, {0, 124, 166.5}},
        {
            FinalEggTowerToFinalEggAlternative, LevelAndActIDs_MysticRuins4, 1, FinalEggToFinalEggTowerAlternative,
            180,
            {0, 124, -155}
        },
        {FinalEggTowerToFinalEgg, LevelAndActIDs_MysticRuins4, 2, FinalEggToFinalEggTower, 115, {175, 135, -25.75}},
        {FinalEggTowerToBetaEggViper, LevelAndActIDs_MysticRuins4, 3, BetaEggViperToFinalEggTower, 225, {0, 16, 0}},
        {FinalEggTowerToEcInside, LevelAndActIDs_MysticRuins4, 3, EcInsideToFinalEggTower, 180, {0, 15, -175}},


        // Egg Carrier Outside (Untransformed)
        {
            EcOutsideToEcInsideEggLift, LevelAndActIDs_EggCarrierOutside1, 3, EcInsideToEcOutsideEggLift, 0.0f,
            {0, 750, 970}
        },
        {
            EcOutsideToEcInsideMonorail, LevelAndActIDs_EggCarrierOutside1, 0, EcInsideToEcOutsideMonorail, 270,
            {311.5f, 595.7f, -342.7f}
        },
        {
            EcOutsideToEcInsideMonorail, LevelAndActIDs_EggCarrierOutside1, 0, EcInsideToEcOutsideMonorail, 270,
            {311.5f, 595.7f, -422}
        },
        {EcOutsideToSsMain, LevelAndActIDs_EggCarrierOutside1, 0, SsMainToEcOutside, 90, {326, 584.4f, -723}},
        {EcOutsideToMrMain, LevelAndActIDs_EggCarrierOutside1, 0, MrMainToEcOutside, 270, {-326, 584.4f, -723}},
        {EcOutsideToSkyChase2, LevelAndActIDs_EggCarrierOutside1, 0, SkyChase2ToEcOutside, 180, {0, 715, -1100}},
        {EcOutsideToPool, LevelAndActIDs_EggCarrierOutside1, 1, PoolToEcOutside, 0.0f, {0, 759.5f, 1074.2f}},
        {
            EcOutsideToChaos6ZeroBeta, LevelAndActIDs_EggCarrierOutside1, 0, Chaos6ZeroBetaToEcOutside, 0,
            {0, 765.5f, -385.69f}
        },
        {EcOutsideToCaptainRoom, LevelAndActIDs_EggCarrierOutside1, 2, CaptainRoomToEcOutside, 180, {0, 755, 438}},

        // Bridge (Transformed)
        {
            BridgeToEcInsideMonorail, LevelAndActIDs_EggCarrierOutside2, 0, EcInsideToBridgeMonorail, 270,
            {311.5f, 595.7f, -342.7f}
        },
        {
            BridgeToEcInsideMonorail, LevelAndActIDs_EggCarrierOutside2, 0, EcInsideToBridgeMonorail, 270,
            {311.5f, 595.7f, -422}
        },
        {BridgeToSsMain, LevelAndActIDs_EggCarrierOutside2, 0, SsMainToBridge, 90, {326, 584.4f, -723}},
        {BridgeToMrMain, LevelAndActIDs_EggCarrierOutside2, 0, MrMainToBridge, 270, {-326, 584.4f, -723}},
        {BridgeToSkyChase2, LevelAndActIDs_EggCarrierOutside2, 0, SkyChase2ToBridge, 180, {0, 665, -1100}},
        {
            BridgeToChaos6ZeroBeta, LevelAndActIDs_EggCarrierOutside2, 0, Chaos6ZeroBetaToBridge, 0,
            {0, 765.5f, -385.69f}
        },
        {BridgeToSkyDeck, LevelAndActIDs_EggCarrierOutside2, 1, SkyDeckToBridge, 0, {0, 767, 391}},


        // Deck (Transformed)
        {DeckToEcInsideEggLift, LevelAndActIDs_EggCarrierOutside3, 0, EcInsideToDeckEggLift, 0.0f, {0, 1540, 3462}},
        {DeckToPool, LevelAndActIDs_EggCarrierOutside3, 1, PoolToDeck, 0.0f, {0, 1551.5897f, 3566.501f}},
        {DeckToCaptainRoom, LevelAndActIDs_EggCarrierOutside3, 4, CaptainRoomToDeck, 180, {0, 1725, 2923}},
        {DeckToPrivateRoom, LevelAndActIDs_EggCarrierOutside3, 2, PrivateRoomToDeck, 244.37f, {79.65f, 1535, 2875.8f}},
        {
            DeckToPrivateRoomAlternative, LevelAndActIDs_EggCarrierOutside3, 3, PrivateRoomToDeckAlternative, 180,
            {-54, 1655, 2972.5f}
        },

        // Captain Room
        {CaptainRoomToEcOutside, LevelAndActIDs_EggCarrierOutside4, 0, EcOutsideToCaptainRoom, 90, {34.5, 113, 0}},
        {CaptainRoomToDeck, LevelAndActIDs_EggCarrierOutside4, 0, DeckToCaptainRoom, 90, {0, 1725, 2923}},
        {CaptainRoomToPrivateRoom, LevelAndActIDs_EggCarrierOutside4, 0, PrivateRoomToCaptainRoom, 0, {-80, 113, 0}},

        // Private Room
        {PrivateRoomToCaptainRoom, LevelAndActIDs_EggCarrierOutside5, 2, CaptainRoomToPrivateRoom, 270, {-83, 37, 0}},
        {PrivateRoomToDeck, LevelAndActIDs_EggCarrierOutside5, 0, DeckToPrivateRoom, 180, {-39, 15, -52.5f}},
        {
            PrivateRoomToDeckAlternative, LevelAndActIDs_EggCarrierOutside5, 1, DeckToPrivateRoomAlternative, 90,
            {204, 15, 111}
        },

        // Pool
        {PoolToEcOutside, LevelAndActIDs_EggCarrierOutside6, 0, EcOutsideToPool, 270, {4.5, 25, 25}},
        {PoolToDeck, LevelAndActIDs_EggCarrierOutside6, 0, DeckToPool, 270, {4.5, 25, 25}},
        {PoolToSkyDeck, LevelAndActIDs_EggCarrierOutside6, 1, SkyDeckToPool, 270, {67, -54.5f, 0}},


        // Arsenal
        {ArsenalToEcInside, LevelAndActIDs_EggCarrierInside1, 0, EcInsideToArsenal, 270, {-106, 123, 0}},


        // Egg Carrier Inside
        {
            EcInsideToEcOutsideEggLift, LevelAndActIDs_EggCarrierInside2, 0, EcOutsideToEcInsideEggLift, 180,
            {0, 65, -330.25f}
        },
        {EcInsideToDeckEggLift, LevelAndActIDs_EggCarrierInside2, 0, DeckToEcInsideEggLift, 180, {0, 65, -330.25f}},
        {
            EcInsideToEcOutsideMonorail, LevelAndActIDs_EggCarrierInside2, 0, EcOutsideToEcInsideMonorail, 90,
            {60, 22, 0}
        },
        {
            EcInsideToEcOutsideMonorail, LevelAndActIDs_EggCarrierInside2, 0, EcOutsideToEcInsideMonorail, 90,
            {60, 22, -80}
        },
        {EcInsideToBridgeMonorail, LevelAndActIDs_EggCarrierInside2, 0, BridgeToEcInsideMonorail, 90, {60, 22, 0}},
        {EcInsideToBridgeMonorail, LevelAndActIDs_EggCarrierInside2, 0, BridgeToEcInsideMonorail, 90, {60, 22, -80}},

        {EcInsideToHotShelter, LevelAndActIDs_EggCarrierInside2, 1, HotShelterToEcInside, 0.0f, {0, 15, 245}},
        {
            EcInsideToHedgehogHammer, LevelAndActIDs_EggCarrierInside2, 3, HedgehogHammerToEcInside, 315,
            {-62, 15, 192.5}
        },
        {EcInsideToWaterTank, LevelAndActIDs_EggCarrierInside2, 4, WaterTankToEcInside, 270, {-183, 95, -280}},
        {EcInsideToArsenal, LevelAndActIDs_EggCarrierInside2, 5, ArsenalToEcInside, 90, {183.5, 95, 0}},

        {EcInsideToFinalEggTower, LevelAndActIDs_EggCarrierInside2, 2, FinalEggTowerToEcInside, 45, {62, 15, 192.5}},
        {EcInsideToWarpHall, LevelAndActIDs_EggCarrierInside2, 6, WarpHallToEcInside, 180, {0, 75, -560}},

        // Hedgehog Hammer
        {HedgehogHammerToEcInside, LevelAndActIDs_EggCarrierInside3, 1, EcInsideToHedgehogHammer, 90, {90, 15, 0}},
        {
            HedgehogHammerToPrisonHall, LevelAndActIDs_EggCarrierInside3, 0, PrisonHallToHedgehogHammer, 270,
            {-90, 15, 0}
        },

        // Prison Hall
        {
            PrisonHallToHedgehogHammer, LevelAndActIDs_EggCarrierInside4, 0, HedgehogHammerToPrisonHall, 90,
            {144, 15, 60}
        },

        // Water Tank
        {WaterTankToEcInside, LevelAndActIDs_EggCarrierInside5, 0, EcInsideToWaterTank, 90, {95.5, 71, 0}},

        // Warp Hall
        {WarpHallToEcInside, LevelAndActIDs_EggCarrierInside6, 0, EcInsideToWarpHall, 0, {0, 15, 62.5}},
        {WarpHallToEcChaoGarden, LevelAndActIDs_EggCarrierInside6, 1, EcChaoGardenToWarpHall, 90, {0, 20, 0}},

        // SS Chao Garden
        {SsChaoGardenToHotel, LevelAndActIDs_SSGarden, 0, HotelToSsChaoGarden, 0, {-0.03f, 15, 234.52f}},
        // Mr Chao Garden
        {MrChaoGardenToMrMain, LevelAndActIDs_MRGarden, 0, MrMainToMrChaoGarden, 90, {-18.19F, 30, -170}},
        // Ec ChaoGarden
        {EcChaoGardenToWarpHall, LevelAndActIDs_ECGarden, 0, WarpHallToEcChaoGarden, 0.0f, {-288.75f, 20, -99.12f}},


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

        // Sky Deck
        {SkyDeckToBridge, LevelAndActIDs_SkyDeck1, 0, BridgeToSkyDeck, 0.0f, {0, 0, 0}},
        {SkyDeckToPool, LevelAndActIDs_SkyDeck1, 0, PoolToSkyDeck, 0.0f, {0, 0, 0}},

        // Chaos 0
        {Chaos0ToCityHall, LevelAndActIDs_Chaos0, 1, CityHallToChaos0, 0, {0, 0, 0}},
        // Chaos 2
        {Chaos2ToHotel, LevelAndActIDs_Chaos2, 0, HotelToChaos2, 0, {0, 0, 0}},
        // Egg Walker
        {EggWalkerToStation, LevelAndActIDs_EggWalker, 0, StationToEggWalker, 0, {0, 0, 0}},
        // Chaos 4
        {Chaos4ToMrMain, LevelAndActIDs_Chaos4, 0, MrMainToChaos4, 0, {0, 0, 0}},

        // Chaos 6
        {Chaos6ZeroBetaToEcOutside, LevelAndActIDs_Chaos6Sonic, 0, EcOutsideToChaos6ZeroBeta, 0, {0, 0, 0}},
        {Chaos6ZeroBetaToBridge, LevelAndActIDs_Chaos6Sonic, 0, BridgeToChaos6ZeroBeta, 0, {0, 0, 0}},

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
        // Sky Chase 2
        {SkyChase2ToEcOutside, LevelAndActIDs_SkyChase2, 0, EcOutsideToSkyChase2, 0, {0, 0, 0}},
        {SkyChase2ToBridge, LevelAndActIDs_SkyChase2, 0, BridgeToSkyChase2, 0, {0, 0, 0}},


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
    std::vector<AdventureFieldEntrance*> possibleEntrances;
    for (auto& entrance : _entranceList)
    {
        if (entrance.levelAndActId == sourceLocation)
        {
            for (const auto& destEntrance : _entranceList)
            {
                if (destEntrance.levelAndActId == destinationLocation &&
                    destEntrance.connectsTo == entrance.entranceId)
                {
                    possibleEntrances.push_back(&entrance);
                }
            }
        }
    }

    if (possibleEntrances.empty())
        return static_cast<EntranceId>(-1);

    const NJS_POINT3& playerPos = EntityData1Ptrs[0]->Position;
    float minDist = FLT_MAX;
    auto closestId = static_cast<EntranceId>(-1);

    for (const auto* entrance : possibleEntrances)
    {
        const NJS_POINT3& pos = entrance->indicatorPosition;
        float dist = (playerPos.x - pos.x) * (playerPos.x - pos.x) +
            (playerPos.y - pos.y) * (playerPos.y - pos.y) +
            (playerPos.z - pos.z) * (playerPos.z - pos.z);
        if (dist < minDist)
        {
            minDist = dist;
            closestId = entrance->entranceId;
        }
    }

    return closestId;
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
        case CaptainRoomToEcOutside:
            actualEntranceId = CaptainRoomToDeck;
            break;
        case EcOutsideToCaptainRoom:
            actualEntranceId = DeckToCaptainRoom;
            break;
        case EcOutsideToEcInsideMonorail:
            actualEntranceId = BridgeToEcInsideMonorail;
            break;
        case EcOutsideToEcInsideEggLift:
            actualEntranceId = DeckToEcInsideEggLift;
            break;
        case EcInsideToEcOutsideMonorail:
            actualEntranceId = EcInsideToBridgeMonorail;
            break;
        case EcInsideToEcOutsideEggLift:
            actualEntranceId = EcInsideToDeckEggLift;
            break;
        case EcOutsideToSsMain:
            actualEntranceId = BridgeToSsMain;
            break;
        case EcOutsideToMrMain:
            actualEntranceId = BridgeToMrMain;
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
        case CaptainRoomToDeck:
            actualEntranceId = CaptainRoomToEcOutside;
            break;
        case DeckToCaptainRoom:
            actualEntranceId = EcOutsideToCaptainRoom;
            break;
        case BridgeToEcInsideMonorail:
            actualEntranceId = EcOutsideToEcInsideMonorail;
            break;
        case DeckToEcInsideEggLift:
            actualEntranceId = EcOutsideToEcInsideEggLift;
            break;
        case EcInsideToBridgeMonorail:
            actualEntranceId = EcInsideToEcOutsideMonorail;
            break;
        case EcInsideToDeckEggLift:
            actualEntranceId = EcInsideToEcOutsideEggLift;
            break;
        case BridgeToSsMain:
            actualEntranceId = EcOutsideToSsMain;
            break;
        case BridgeToMrMain:
            actualEntranceId = EcOutsideToMrMain;
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
