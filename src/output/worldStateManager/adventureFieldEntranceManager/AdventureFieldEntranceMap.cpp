#include "AdventureFieldEntranceMap.h"

//TODO: enable controls after entering the EC

//TODO: Improve performance by using a map or unordered_map for faster lookups
AdventureFieldEntranceMap::AdventureFieldEntranceMap(Options& options) : _options(options)
{
    _entranceList = {
        //TODO: MR garden - MRMain
        //Fix control disable when transitioning into the  same stage with vehicles
        //Fix icecap door?


        //City Hall
        {CityHallToSsMain, LevelAndActIDs_StationSquare1, 1, SsMainToCityHall, 50.0f, {550.79f, 14.5, 856.22f}},
        {CityHallToChaos0, LevelAndActIDs_StationSquare1, 3, Chaos0ToCityHall, 180, {270, 16, 450}},
        {CityHallToSewers, LevelAndActIDs_StationSquare1, 2, SewersToCityHall, 0, {361, 10, 941.5}},
        {CityHallToSpeedHighway, LevelAndActIDs_StationSquare1, 0, SpeedHighwayToCityHall, 180, {270, 20, 255}},

        //Station
        {StationToSsMain, LevelAndActIDs_StationSquare2, 0, SsMainToStation, 26, {59, 79, 1452}},
        {CasinoToCasinopolis, LevelAndActIDs_StationSquare2, 1, CasinopolisToCasino, 225, {-620, 12.5, 905}},
        {CasinoToHotel, LevelAndActIDs_StationSquare2, 2, HotelToCasino, 0.0f, {-445, 13, 1515}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToStation, 206, {-236.8f, 153, 1237}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToStation, 206, {-164, 153, 1204}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToStation, 206, {-115, 153, 1179}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToStation, 206, {-43, 153, 1142}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToStation, 206, {4.6f, 153, 1116.4f}},
        {StationToMrMain, LevelAndActIDs_StationSquare2, 3, MrMainToStation, 206, {76.5f, 153, 1080.7f}},
        {CasinoToEggWalker, LevelAndActIDs_StationSquare2, 4, EggWalkerToCasino, 0, {-400, 13, 955}},

        // Sewers
        {SewersToTwinkleParkTunnel, LevelAndActIDs_StationSquare3, 1, TwinkleParkTunnelToSewers, 0, {395, -87, 1323}},
        {SewersToCityHall, LevelAndActIDs_StationSquare3, 0, CityHallToSewers, 270, {433.5, 13, 635}},

        // SSMain
        {SsMainToCityHall, LevelAndActIDs_StationSquare4, 1, CityHallToSsMain, 110.8F, {443, 13, 1077}},
        {SsMainToStation, LevelAndActIDs_StationSquare4, 0, StationToSsMain, 198.81f, {28, 41, 1388}},
        {SsMainToHotel, LevelAndActIDs_StationSquare4, 3, HotelToSsMain, 270, {-168, 15, 1685}},
        {
            TwinkleParkTunnelToTwinkleParkLobby, LevelAndActIDs_StationSquare4, 4, TwinkleParkLobbyToTwinkleParkTunnel,
            90, {580, 65, 1772}
        },
        {SsMainToEcOutside, LevelAndActIDs_StationSquare4, 6, EcOutsideToSsMain, 30, {174.09f, 6, 1897.51f}},
        {SsMainToBridge, LevelAndActIDs_StationSquare4, 6, BridgeToSsMain, 30, {174.09f, 6, 1897.51f}},
        {TwinkleParkTunnelToSewers, LevelAndActIDs_StationSquare4, 2, SewersToTwinkleParkTunnel, 180, {400, 58, 1450}},
        {SsMainToSpeedHighway, LevelAndActIDs_StationSquare4, 5, SpeedHighwayToSsMain, 90, {380, 20, 1370}},

        // Hotel
        {HotelToSsMain, LevelAndActIDs_StationSquare5, 1, SsMainToHotel, 90, {-245.5, 13, 1685.25}},
        {HotelToCasino, LevelAndActIDs_StationSquare5, 3, CasinoToHotel, 180, {-370, 13, 1605}},
        {HotelPoolToEmeraldCoast, LevelAndActIDs_StationSquare5, 2, EmeraldCoastToHotelPool, 315, {-520, 10, 2093}},
        {HotelToSsChaoGarden, LevelAndActIDs_StationSquare5, 4, SsChaoGardenToHotel, 270, {-395, 13, 1700}},
        {HotelToChaos2, LevelAndActIDs_StationSquare5, 5, Chaos2ToHotel, 270, {-395, 13, 1665}},


        // Twinkle Park Lobby
        {
            TwinkleParkLobbyToTwinkleParkTunnel, LevelAndActIDs_StationSquare6, 0, TwinkleParkTunnelToTwinkleParkLobby,
            270, {675, 65, 1771.5f}
        },
        {
            TwinkleParkLobbyToTwinkleCircuit, LevelAndActIDs_StationSquare6, 2, TwinkleCircuitToTwinkleParkLobby, 180,
            {757, 65, 1735}
        },
        {
            TwinkleParkLobbyToTwinklePark, LevelAndActIDs_StationSquare6, 1, TwinkleParkToTwinkleParkLobby, 90,
            {804, 65, 1771.5f}
        },


        // MRMain
        {MrMainToStation, LevelAndActIDs_MysticRuins1, 0, StationToMrMain, 56.25f, {0, 228, 1207}},
        {MrMainToChaos4, LevelAndActIDs_MysticRuins1, 5, Chaos4ToMrMain, 180, {80, 87, 180}},
        {MrMainToEggHornet, LevelAndActIDs_MysticRuins1, 8, EggHornetToMrMain, 0, {950, 142, 950}},
        {MrMainToSkyChase1, LevelAndActIDs_MysticRuins1, 9, SkyChase1ToMrMain, 90, {1561, 206, 900}},
        {MrMainToEcOutside, LevelAndActIDs_MysticRuins1, 7, EcOutsideToMrMain, 147.5f, {-70, -385, 1264}},
        {MrMainToBridge, LevelAndActIDs_MysticRuins1, 7, BridgeToMrMain, 147.5f, {-70, -385, 1264}},
        {MrMainToJungle, LevelAndActIDs_MysticRuins1, 2, JungleToMrMain, 211, {-200.86f, 81.5, -69.51f}},
        {MrMainToMrChaoGarden, LevelAndActIDs_MysticRuins1, 4, MrChaoGardenToMrMain, 111, {1696, 17.5, -86}},
        {MrMainToAngelIsland, LevelAndActIDs_MysticRuins1, 1, AngelIslandToMrMain, 270, {-347, 120, 869}},
        {MrMainToWindyValley, LevelAndActIDs_MysticRuins1, 3, WindyValleyToMrMain, 145, {640, 80, -143}},

        // Angel Island
        {AngelIslandToMrMain, LevelAndActIDs_MysticRuins2, 0, MrMainToAngelIsland, 90, {0, 15, 0}},
        {IceCaveToIceCap, LevelAndActIDs_MysticRuins2, 2, IceCapToIceCave, 280, {-1425, 53, 353}},
        {AngelIslandToRedMountain, LevelAndActIDs_MysticRuins2, 1, RedMountainToAngelIsland, 268, {-1955, -335, 1652}},
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
        {FinalEggTowerToBetaEggViper, LevelAndActIDs_MysticRuins4, 4, BetaEggViperToFinalEggTower, 225, {0, 16, 0}},
        {FinalEggTowerToEcInside, LevelAndActIDs_MysticRuins4, 3, EcInsideToFinalEggTower, 180, {0, 15, -175}},


        // Egg Carrier Outside (Untransformed)
        {
            EcOutsideToEcInsideEggLift, LevelAndActIDs_EggCarrierOutside1, 3, EcInsideToEcOutsideEggLift, 0.0f,
            {0, 750, 970}
        },
        {
            EcOutsideToEcInsideMonorail, LevelAndActIDs_EggCarrierOutside1, 5, EcInsideToEcOutsideMonorail, 270,
            {311.5f, 595.7f, -342.7f}
        },
        {
            EcOutsideToEcInsideMonorail, LevelAndActIDs_EggCarrierOutside1, 5, EcInsideToEcOutsideMonorail, 270,
            {311.5f, 595.7f, -422}
        },
        {EcOutsideToSsMain, LevelAndActIDs_EggCarrierOutside1, 7, SsMainToEcOutside, 90, {326, 584.4f, -723}},
        {EcOutsideToMrMain, LevelAndActIDs_EggCarrierOutside1, 6, MrMainToEcOutside, 270, {-326, 584.4f, -723}},
        {EcOutsideToSkyChase2, LevelAndActIDs_EggCarrierOutside1, 0, SkyChase2ToEcOutside, 180, {0, 715, -1100}},
        {EcOutsideToPool, LevelAndActIDs_EggCarrierOutside1, 1, PoolToEcOutside, 0.0f, {0, 759.5f, 1074.2f}},
        {
            EcOutsideToChaos6ZeroBeta, LevelAndActIDs_EggCarrierOutside1, 9, Chaos6ZeroBetaToEcOutside, 0,
            {0, 765.5f, -385.69f}
        },
        {EcOutsideToCaptainRoom, LevelAndActIDs_EggCarrierOutside1, 2, CaptainRoomToEcOutside, 180, {0, 755, 438}},

        // Bridge (Transformed)
        {
            BridgeToEcInsideMonorail, LevelAndActIDs_EggCarrierOutside2, 2, EcInsideToBridgeMonorail, 270,
            {311.5f, 595.7f, -342.7f}
        },
        {
            BridgeToEcInsideMonorail, LevelAndActIDs_EggCarrierOutside2, 2, EcInsideToBridgeMonorail, 270,
            {311.5f, 595.7f, -422}
        },
        {BridgeToSsMain, LevelAndActIDs_EggCarrierOutside2, 7, SsMainToBridge, 90, {326, 584.4f, -723}},
        {BridgeToMrMain, LevelAndActIDs_EggCarrierOutside2, 6, MrMainToBridge, 270, {-326, 584.4f, -723}},
        {BridgeToSkyChase2, LevelAndActIDs_EggCarrierOutside2, 0, SkyChase2ToBridge, 180, {0, 665, -1100}},
        {
            BridgeToChaos6ZeroBeta, LevelAndActIDs_EggCarrierOutside2, 9, Chaos6ZeroBetaToBridge, 0,
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
            EcInsideToEcOutsideEggLift, LevelAndActIDs_EggCarrierInside2, 7, EcOutsideToEcInsideEggLift, 180,
            {0, 65, -330.25f}
        },
        {EcInsideToDeckEggLift, LevelAndActIDs_EggCarrierInside2, 7, DeckToEcInsideEggLift, 180, {0, 65, -330.25f}},
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
        {SpeedHighwayToSsMain, LevelAndActIDs_SpeedHighway2, 0, SsMainToSpeedHighway, 0, {0, 0, 0}},
        {SpeedHighwayToSsMain, LevelAndActIDs_SpeedHighway3, 0, SsMainToSpeedHighway, 0, {0, 0, 0}},
        {SpeedHighwayToCityHall, LevelAndActIDs_SpeedHighway1, 0, CityHallToSpeedHighway, 0, {0, 0, 0}},
        {SpeedHighwayToCityHall, LevelAndActIDs_SpeedHighway2, 0, CityHallToSpeedHighway, 0, {0, 0, 0}},
        {SpeedHighwayToCityHall, LevelAndActIDs_SpeedHighway3, 0, CityHallToSpeedHighway, 0, {0, 0, 0}},

        // Emerald Coast
        {EmeraldCoastToHotelPool, LevelAndActIDs_EmeraldCoast1, 0, HotelPoolToEmeraldCoast, 0, {0, 0, 0}},
        {EmeraldCoastToHotelPool, LevelAndActIDs_EmeraldCoast2, 0, HotelPoolToEmeraldCoast, 0, {0, 0, 0}},
        {EmeraldCoastToHotelPool, LevelAndActIDs_EmeraldCoast3, 0, HotelPoolToEmeraldCoast, 0, {0, 0, 0}},

        // Casinopolis
        {CasinopolisToCasino, LevelAndActIDs_Casinopolis1, 0, CasinoToCasinopolis, 0, {0, 0, 0}},
        {CasinopolisToCasino, LevelAndActIDs_Casinopolis2, 0, CasinoToCasinopolis, 0, {0, 0, 0}},
        {CasinopolisToCasino, LevelAndActIDs_Casinopolis3, 0, CasinoToCasinopolis, 0, {0, 0, 0}},
        {CasinopolisToCasino, LevelAndActIDs_Casinopolis4, 0, CasinoToCasinopolis, 0, {0, 0, 0}},

        // Twinkle Park
        {TwinkleParkToTwinkleParkLobby, LevelAndActIDs_TwinklePark1, 0, TwinkleParkLobbyToTwinklePark, 0, {0, 0, 0}},
        {TwinkleParkToTwinkleParkLobby, LevelAndActIDs_TwinklePark2, 0, TwinkleParkLobbyToTwinklePark, 0, {0, 0, 0}},
        {TwinkleParkToTwinkleParkLobby, LevelAndActIDs_TwinklePark3, 0, TwinkleParkLobbyToTwinklePark, 0, {0, 0, 0}},

        // Windy Valley
        {WindyValleyToMrMain, LevelAndActIDs_WindyValley1, 0, MrMainToWindyValley, 0, {0, 0, 0}},
        {WindyValleyToMrMain, LevelAndActIDs_WindyValley2, 0, MrMainToWindyValley, 0, {0, 0, 0}},
        {WindyValleyToMrMain, LevelAndActIDs_WindyValley3, 0, MrMainToWindyValley, 0, {0, 0, 0}},

        // Ice Cap
        {IceCapToIceCave, LevelAndActIDs_IceCap1, 0, IceCaveToIceCap, 0, {0, 0, 0}},
        {IceCapToIceCave, LevelAndActIDs_IceCap2, 0, IceCaveToIceCap, 0, {0, 0, 0}},
        {IceCapToIceCave, LevelAndActIDs_IceCap3, 0, IceCaveToIceCap, 0, {0, 0, 0}},
        {IceCapToIceCave, LevelAndActIDs_IceCap4, 0, IceCaveToIceCap, 0, {0, 0, 0}},

        // Red Mountain
        {RedMountainToAngelIsland, LevelAndActIDs_RedMountain1, 0, AngelIslandToRedMountain, 0, {0, 0, 0}},
        {RedMountainToAngelIsland, LevelAndActIDs_RedMountain2, 0, AngelIslandToRedMountain, 0, {0, 0, 0}},
        {RedMountainToAngelIsland, LevelAndActIDs_RedMountain3, 0, AngelIslandToRedMountain, 0, {0, 0, 0}},

        // Lost World
        {LostWorldToJungle, LevelAndActIDs_LostWorld1, 0, JungleToLostWorld, 0, {0, 0, 0}},
        {LostWorldToJungle, LevelAndActIDs_LostWorld2, 0, JungleToLostWorld, 0, {0, 0, 0}},
        {LostWorldToJungle, LevelAndActIDs_LostWorld3, 0, JungleToLostWorld, 0, {0, 0, 0}},
        {LostWorldToJungleAlternative, LevelAndActIDs_LostWorld1, 0, JungleToLostWorldAlternative, 0, {0, 0, 0}},
        {LostWorldToJungleAlternative, LevelAndActIDs_LostWorld2, 0, JungleToLostWorldAlternative, 0, {0, 0, 0}},
        {LostWorldToJungleAlternative, LevelAndActIDs_LostWorld3, 0, JungleToLostWorldAlternative, 0, {0, 0, 0}},

        // Final Egg
        {
            FinalEggToFinalEggTowerAlternative, LevelAndActIDs_FinalEgg1, 0, FinalEggTowerToFinalEggAlternative, 0,
            {0, 0, 0}
        },
        {
            FinalEggToFinalEggTowerAlternative, LevelAndActIDs_FinalEgg2, 0, FinalEggTowerToFinalEggAlternative, 0,
            {0, 0, 0}
        },
        {
            FinalEggToFinalEggTowerAlternative, LevelAndActIDs_FinalEgg3, 0, FinalEggTowerToFinalEggAlternative, 0,
            {0, 0, 0}
        },
        {FinalEggToFinalEggTower, LevelAndActIDs_FinalEgg1, 0, FinalEggTowerToFinalEgg, 0, {0, 0, 0}},
        {FinalEggToFinalEggTower, LevelAndActIDs_FinalEgg2, 0, FinalEggTowerToFinalEgg, 0, {0, 0, 0}},
        {FinalEggToFinalEggTower, LevelAndActIDs_FinalEgg3, 0, FinalEggTowerToFinalEgg, 0, {0, 0, 0}},

        // Hot Shelter
        {HotShelterToEcInside, LevelAndActIDs_HotShelter1, 0, EcInsideToHotShelter, 0.0f, {0, 0, 0}},
        {HotShelterToEcInside, LevelAndActIDs_HotShelter2, 0, EcInsideToHotShelter, 0.0f, {0, 0, 0}},
        {HotShelterToEcInside, LevelAndActIDs_HotShelter3, 0, EcInsideToHotShelter, 0.0f, {0, 0, 0}},
        {HotShelterToEcInside, LevelAndActIDs_HotShelter4, 0, EcInsideToHotShelter, 0.0f, {0, 0, 0}},

        // Sky Deck
        {SkyDeckToBridge, LevelAndActIDs_SkyDeck1, 0, BridgeToSkyDeck, 0.0f, {0, 0, 0}},
        {SkyDeckToBridge, LevelAndActIDs_SkyDeck2, 0, BridgeToSkyDeck, 0.0f, {0, 0, 0}},
        {SkyDeckToBridge, LevelAndActIDs_SkyDeck3, 0, BridgeToSkyDeck, 0.0f, {0, 0, 0}},
        {SkyDeckToPool, LevelAndActIDs_SkyDeck1, 0, PoolToSkyDeck, 0.0f, {0, 0, 0}},
        {SkyDeckToPool, LevelAndActIDs_SkyDeck2, 0, PoolToSkyDeck, 0.0f, {0, 0, 0}},
        {SkyDeckToPool, LevelAndActIDs_SkyDeck3, 0, PoolToSkyDeck, 0.0f, {0, 0, 0}},

        // Chaos 0
        {Chaos0ToCityHall, LevelAndActIDs_Chaos0, 1, CityHallToChaos0, 0, {0, 0, 0}},
        // Chaos 2
        {Chaos2ToHotel, LevelAndActIDs_Chaos2, 0, HotelToChaos2, 0, {0, 0, 0}},
        // Egg Walker
        {EggWalkerToCasino, LevelAndActIDs_EggWalker, 0, CasinoToEggWalker, 0, {0, 0, 0}},
        // Chaos 4
        {Chaos4ToMrMain, LevelAndActIDs_Chaos4, 0, MrMainToChaos4, 0, {0, 0, 0}},

        // Chaos 6
        {Chaos6ZeroBetaToEcOutside, LevelAndActIDs_Chaos6Sonic, 0, EcOutsideToChaos6ZeroBeta, 0, {0, 0, 0}},
        {Chaos6ZeroBetaToEcOutside, LevelAndActIDs_Chaos6Knuckles, 0, EcOutsideToChaos6ZeroBeta, 0, {0, 0, 0}},
        {Chaos6ZeroBetaToEcOutside, LevelAndActIDs_Zero, 0, EcOutsideToChaos6ZeroBeta, 0, {0, 0, 0}},
        {Chaos6ZeroBetaToEcOutside, LevelAndActIDs_E101R, 0, EcOutsideToChaos6ZeroBeta, 0, {0, 0, 0}},
        {Chaos6ZeroBetaToBridge, LevelAndActIDs_Chaos6Sonic, 0, BridgeToChaos6ZeroBeta, 0, {0, 0, 0}},
        {Chaos6ZeroBetaToBridge, LevelAndActIDs_Chaos6Knuckles, 0, BridgeToChaos6ZeroBeta, 0, {0, 0, 0}},
        {Chaos6ZeroBetaToBridge, LevelAndActIDs_Zero, 0, BridgeToChaos6ZeroBeta, 0, {0, 0, 0}},
        {Chaos6ZeroBetaToBridge, LevelAndActIDs_E101R, 0, BridgeToChaos6ZeroBeta, 0, {0, 0, 0}},

        // Egg Hornet
        {EggHornetToMrMain, LevelAndActIDs_EggHornet, 0, MrMainToEggHornet, 0, {0, 0, 0}},
        // Egg Viper
        {BetaEggViperToFinalEggTower, LevelAndActIDs_EggViper, 0, FinalEggTowerToBetaEggViper, 0, {0, 0, 0}},
        {BetaEggViperToFinalEggTower, LevelAndActIDs_E101, 0, FinalEggTowerToBetaEggViper, 0, {0, 0, 0}},

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
    _staticEntranceList = {
        {StationToCasino, LevelAndActIDs_StationSquare2, -1, CasinoToStation, 206, {-202, 82, 1319}},
        {CasinoToStation, LevelAndActIDs_StationSquare2, -1, StationToCasino, 26, {-206, 82, 1310}},

        {
            SsMainToTwinkleParkTunnel, LevelAndActIDs_StationSquare4, -1, TwinkleParkTunnelToSsMain, 90,
            {370, 21, 1606.5}
        },
        {
            TwinkleParkTunnelToSsMain, LevelAndActIDs_StationSquare4, -1, SsMainToTwinkleParkTunnel, 90,
            {400, 62, 1606.5}
        },

        {HotelToHotelPool, LevelAndActIDs_StationSquare5, -1, HotelPoolToHotel, 0, {-380, 15, 1828}},
        {HotelPoolToHotel, LevelAndActIDs_StationSquare5, -1, HotelToHotelPool, 180, {-380, 15, 1834}},

        {AngelIslandToIceCave, LevelAndActIDs_MysticRuins2, -1, IceCaveToAngelIsland, 270, {-480.3f, 20, 290.4f}},
        {IceCaveToAngelIsland, LevelAndActIDs_MysticRuins2, -1, AngelIslandToIceCave, 90, {-497.26f, 20, 289.4f}},
    };
}

const std::vector<AdventureFieldEntrance>& AdventureFieldEntranceMap::GetEntrances() const
{
    return _entranceList;
}

const std::vector<AdventureFieldEntrance>& AdventureFieldEntranceMap::GetStaticEntrances() const
{
    return _staticEntranceList;
}

AdventureFieldEntrance* AdventureFieldEntranceMap::GetNewConnection(
    const LevelAndActIDs sourceLocation, const LevelAndActIDs destinationLocation, const bool isEggCarrierTransformed)
{
    //We use the save entranceId when trasitioning in and out of levels
    if ((GET_LEVEL(sourceLocation) >= LevelIDs_EmeraldCoast && GET_LEVEL(sourceLocation) <= LevelIDs_E101R)
        || (GET_LEVEL(sourceLocation) >= LevelIDs_TwinkleCircuit && GET_LEVEL(sourceLocation) <= LevelIDs_SandHill))
    {
        return FindEntranceById(_lastEntranceIdUsed);
    }


    const EntranceId sourceEntranceId = FindEntranceByLocation(sourceLocation, destinationLocation);
    if (sourceEntranceId == static_cast<EntranceId>(-1))
        return nullptr;
    const EntranceId destinationEntranceId = GetReplacementConnection(sourceEntranceId, isEggCarrierTransformed);
    AdventureFieldEntrance* newEntrance = FindEntranceById(destinationEntranceId);

    if ((GET_LEVEL(newEntrance->levelAndActId) >= LevelIDs_EmeraldCoast && GET_LEVEL(newEntrance->levelAndActId) <=
            LevelIDs_E101R)
        || (GET_LEVEL(newEntrance->levelAndActId) >= LevelIDs_TwinkleCircuit && GET_LEVEL(newEntrance->levelAndActId) <=
            LevelIDs_SandHill))
    {
        _lastEntranceIdUsed = sourceEntranceId;
    }

    return newEntrance;
}

AdventureFieldEntrance* AdventureFieldEntranceMap::GetCurrentEntrance(const LevelAndActIDs sourceLocation,
                                                                      const LevelAndActIDs destinationLocation)

{
    const EntranceId sourceEntranceId = FindEntranceByLocation(sourceLocation, destinationLocation);
    if (sourceEntranceId == static_cast<EntranceId>(-1))
        return nullptr;
    return FindEntranceById(sourceEntranceId);
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

    //TODO: Save lastone used to use the reverse
    if (possibleEntrances.size() == 1 || Current_CharObj2 == nullptr || EntityData1Ptrs[0] == nullptr)
        return possibleEntrances[0]->entranceId;

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

EntranceId AdventureFieldEntranceMap::GetReplacementConnection(const EntranceId fromEntranceId,
                                                               const bool isEggCarrierTransformed)
{
    EntranceId toEntranceId = InvalidEntranceId;
    for (const auto& [entranceA, entranceB] : _entranceOriginalConnections)
    {
        if (entranceA == fromEntranceId)
            toEntranceId = entranceB;
        if (entranceB == fromEntranceId)
            toEntranceId = entranceA;
    }


    EntranceId actualEntranceId = toEntranceId;
    if (isEggCarrierTransformed)
    {
        switch (toEntranceId)
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
        switch (toEntranceId)
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

    return actualEntranceId;
}


AdventureFieldEntrance* AdventureFieldEntranceMap::FindEntranceById(const EntranceId entranceId)
{
    for (auto& entrance : _entranceList)
    {
        if (entrance.entranceId == entranceId)
            return &entrance;
    }

    for (auto& entrance : _staticEntranceList)
    {
        if (entrance.entranceId == entranceId)
            return &entrance;
    }

    return nullptr;
}


LevelAndActIDs AdventureFieldEntranceMap::CalculateCorrectAct(LevelAndActIDs levelAndActId)
{
    LevelIDs actualLevel = static_cast<LevelIDs>(GET_LEVEL(levelAndActId));
    if (actualLevel == LevelIDs_EmeraldCoast)
    {
        if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Gamma)
            levelAndActId = LevelAndActIDs_EmeraldCoast1;
        else if (CurrentCharacter == Characters_Big)
            levelAndActId = LevelAndActIDs_EmeraldCoast3;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_WindyValley)
    {
        if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Gamma)
            levelAndActId = LevelAndActIDs_WindyValley1;
        else if (CurrentCharacter == Characters_Tails)
            levelAndActId = LevelAndActIDs_WindyValley3;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    if (actualLevel == LevelIDs_TwinklePark)
    {
        if (CurrentCharacter == Characters_Sonic)
            levelAndActId = LevelAndActIDs_TwinklePark1;
        else if (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big)
            levelAndActId = LevelAndActIDs_TwinklePark2;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_SpeedHighway)
    {
        if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
            levelAndActId = LevelAndActIDs_SpeedHighway1;
        else if (CurrentCharacter == Characters_Knuckles)
            levelAndActId = LevelAndActIDs_SpeedHighway3;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_RedMountain)
    {
        if (CurrentCharacter == Characters_Sonic)
            levelAndActId = LevelAndActIDs_RedMountain1;
        else if (CurrentCharacter == Characters_Knuckles)
            levelAndActId = LevelAndActIDs_RedMountain3;
        else if (CurrentCharacter == Characters_Gamma)
            levelAndActId = LevelAndActIDs_RedMountain2;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_SkyDeck)
    {
        if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
            levelAndActId = LevelAndActIDs_SkyDeck1;
        else if (CurrentCharacter == Characters_Knuckles)
            levelAndActId = LevelAndActIDs_SkyDeck3;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_LostWorld)
    {
        if (CurrentCharacter == Characters_Sonic)
            levelAndActId = LevelAndActIDs_LostWorld1;
        else if (CurrentCharacter == Characters_Knuckles)
            levelAndActId = LevelAndActIDs_LostWorld2;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_IceCap)
    {
        if (CurrentCharacter == Characters_Sonic)
            levelAndActId = LevelAndActIDs_IceCap1;
        else if (CurrentCharacter == Characters_Tails)
            levelAndActId = LevelAndActIDs_IceCap3;
        else if (CurrentCharacter == Characters_Big)
            levelAndActId = LevelAndActIDs_IceCap4;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_Casinopolis)
    {
        if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Knuckles)
            levelAndActId = LevelAndActIDs_Casinopolis1;
        else if (CurrentCharacter == Characters_Tails)
            levelAndActId = LevelAndActIDs_Casinopolis2;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_FinalEgg)
    {
        if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Amy)
            levelAndActId = LevelAndActIDs_FinalEgg1;
        else if (CurrentCharacter == Characters_Gamma)
            levelAndActId = LevelAndActIDs_FinalEgg3;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_HotShelter)
    {
        if (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big)
            levelAndActId = LevelAndActIDs_HotShelter1;
        else if (CurrentCharacter == Characters_Gamma)
            levelAndActId = LevelAndActIDs_HotShelter3;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_Chaos0)
    {
        if (CurrentCharacter == Characters_Sonic)
            levelAndActId = LevelAndActIDs_Chaos0;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_Chaos2)
    {
        if (CurrentCharacter == Characters_Knuckles)
            levelAndActId = LevelAndActIDs_Chaos2;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_Chaos4)
    {
        if (CurrentCharacter == Characters_Sonic
            || CurrentCharacter == Characters_Tails
            || CurrentCharacter == Characters_Knuckles)
            levelAndActId = LevelAndActIDs_Chaos4;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_Chaos6)
    {
        if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Big)
            levelAndActId = LevelAndActIDs_Chaos6Sonic;
        else if (CurrentCharacter == Characters_Knuckles)
            levelAndActId = LevelAndActIDs_Chaos6Knuckles;
        else if (CurrentCharacter == Characters_Amy)
            levelAndActId = LevelAndActIDs_Zero;
        else if (CurrentCharacter == Characters_Gamma)
            levelAndActId = LevelAndActIDs_E101R;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_EggHornet)
    {
        if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
            levelAndActId = LevelAndActIDs_EggHornet;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_EggWalker)
    {
        if (CurrentCharacter == Characters_Tails)
            levelAndActId = LevelAndActIDs_EggWalker;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_EggViper)
    {
        if (CurrentCharacter == Characters_Sonic)
            levelAndActId = LevelAndActIDs_EggViper;
        else if (CurrentCharacter == Characters_Gamma)
            levelAndActId = LevelAndActIDs_E101;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_SandHill)
    {
        if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
            levelAndActId = LevelAndActIDs_SandHill;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_SkyChase1)
    {
        if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
            levelAndActId = LevelAndActIDs_SkyChase1;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_SkyChase2)
    {
        if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
            levelAndActId = LevelAndActIDs_SkyChase2;
        else
            return LevelAndActIDs_HedgehogHammer;
    }
    else if (actualLevel == LevelIDs_TwinkleCircuit)
    {
        if (_instance->_options.twinkleCircuitChecks == 1)
            levelAndActId = GET_LEVEL_ACT(LevelIDs_TwinkleCircuit, 0);
        else if (CurrentCharacter == Characters_Sonic)
            levelAndActId = GET_LEVEL_ACT(LevelIDs_TwinkleCircuit, 2);
        else if (CurrentCharacter == Characters_Tails)
            levelAndActId = GET_LEVEL_ACT(LevelIDs_TwinkleCircuit, 1);
        else if (CurrentCharacter == Characters_Knuckles)
            levelAndActId = GET_LEVEL_ACT(LevelIDs_TwinkleCircuit, 5);
        else if (CurrentCharacter == Characters_Amy)
            levelAndActId = GET_LEVEL_ACT(LevelIDs_TwinkleCircuit, 0);
        else if (CurrentCharacter == Characters_Gamma)
            levelAndActId = GET_LEVEL_ACT(LevelIDs_TwinkleCircuit, 4);
        else if (CurrentCharacter == Characters_Big)
            levelAndActId = GET_LEVEL_ACT(LevelIDs_TwinkleCircuit, 3);
    }


    return levelAndActId;
}

void AdventureFieldEntranceMap::UpdateRandomEntrances()
{
    // keep a backup of original values to avoid chaining updates
    auto backup = _entranceOriginalConnections;

    for (const auto& pair : _options.levelEntrancesMap)
    {
        const EntranceId targetKey = static_cast<EntranceId>(pair.first);
        const EntranceId sourceKey = static_cast<EntranceId>(pair.second);

        auto itTarget = _entranceOriginalConnections.find(targetKey);
        if (itTarget == _entranceOriginalConnections.end()) continue;

        auto itSource = backup.find(sourceKey);
        if (itSource == backup.end()) continue;

        itTarget->second = itSource->second;
    }
}
