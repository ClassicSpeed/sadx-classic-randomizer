#pragma once
#include "../../../../pch.h"
#include "../../../../configuration/options/Options.h"
#include "../../../../configuration/gameStatus/GameStatus.h"
#include "../DoorLogic/IDoorLogicStrategy.h"


class MapManager : public IOnFrame
{
public:
    static MapManager& Init(Options& options, Settings& settings, GameStatus& gameStatus,
                            AdventureFieldEntranceMap& _adventureFieldEntranceMap)
    {
        if (_instance == nullptr)
            _instance = new MapManager(options, settings, gameStatus, _adventureFieldEntranceMap);
        return *_instance;
    }

    void OnFrame() override;
    void SetDoorLogicStrategy(IDoorLogicStrategy* doorLogicStrategy);

private:
    IDoorLogicStrategy* _doorLogicStrategy;
    void ShowMap();
    void showNumberMap(float posX, float posY, int number);
    void ShowDoorRequirement(AdventureFieldEntrance adventureFieldEntrance);
    void ShowBlockedDoor(AdventureFieldEntrance adventureFieldEntrance);
    void ShowDoorName(AdventureFieldEntrance adventureFieldEntrance);
    void ShowNumberDynamic(const AdventureFieldEntrance& entrance, int number, float x, float y, float zBase,
                           float xStep,
                           bool leftJustify);
    void showNumber(const AdventureFieldEntrance& adventureFieldEntrance, float posX, float posY, int number,
                    float zOffset);
    void DrawEntrancePoint(float x, float y);
    void DrawLine(float x1, float y1, float x2, float y2);
    void MakeConnection(float x1, float y1, float x2, float y2);
    void DrawEmblemNumberInMap(AdventureFieldEntrance adventureFieldEntrance, int doorCost);
    void DrawNewInMap(AdventureFieldEntrance adventureFieldEntrance);
    void DrawPlayerLocation();
    void DrawEntrancesInMap(AdventureFieldEntrance adventureFieldEntrance, bool isStatic);
    NJS_TEXANIM* getInitialsFromEntrance(AdventureFieldEntrance* entranceTo);
    void DrawLevelInitialsInMap(AdventureFieldEntrance* entranceTo, Float entranceX, Float entranceY);
    void DrawConnectionsInMap(const AdventureFieldEntrance& adventureFieldEntrance);
    void ShowNumberDynamicMap(int number, float x, float y);

    explicit MapManager(Options& options, Settings& settings, GameStatus& gameStatus,
                        AdventureFieldEntranceMap& _adventureFieldEntranceMap);
    inline static MapManager* _instance = nullptr;
    Options& _options;
    Settings& _settings;
    GameStatus& _gameStatus;
    AdventureFieldEntranceMap& _adventureFieldEntranceMap;

    std::map<int, NJS_POINT2> entranceLocationInMap = {

        // City Hall
        {CityHallToSsMain, {860, 197}},
        {CityHallToSewers, {824, 128}},
        {CityHallToSpeedHighway, {775, 37}},
        {CityHallToChaos0, {775, 81}},
        // Station
        {StationToSsMain, {677, 294}},
        {StationToMrMain, {647, 237}},
        {StationToCasino, {603, 259}},
        //Casino
        {CasinoToStation, {603, 259}},
        {CasinoToCasinopolis, {530, 188}},
        {CasinoToHotel, {572, 324}},
        {CasinoToEggWalker, {584, 198}},
        // Sewers
        {SewersToCityHall, {928, 85}},
        {SewersToTwinkleParkTunnel, {933, 323}},
        // SSMain
        {SsMainToHotel, {675, 416}},
        {SsMainToStation, {722, 334}},
        {SsMainToCityHall, {860, 235}},
        {SsMainToTwinkleParkTunnel, {824, 391}},
        {SsMainToBridge, {762, 465}},
        {SsMainToSpeedHighway, {838, 341}},
        // Hotel
        {HotelToSsMain, {603, 398}},
        {HotelToCasino, {572, 358}},
        {HotelToSsChaoGarden, {552, 406}},
        {HotelToChaos2, {552, 375}},
        {HotelToHotelPool, {567, 432}},
        // Hotel Pool
        {HotelPoolToHotel, {567, 432}},
        {HotelPoolToEmeraldCoast, {508, 528}},
        // Twinkle Park Tunnel
        {TwinkleParkTunnelToSsMain, {824, 391}},
        {TwinkleParkTunnelToTwinkleParkLobby, {867, 433}},
        {TwinkleParkTunnelToSewers, {826, 362}},
        // Twinkle Park Lobby
        {TwinkleParkLobbyToTwinkleParkTunnel, {914, 433}},
        {TwinkleParkLobbyToTwinklePark, {976, 433}},
        {TwinkleParkLobbyToTwinkleCircuit, {953, 413}},
        // MRMain
        {MrMainToStation, {292, 342}},
        {MrMainToBridge, {269, 351}},
        {MrMainToAngelIsland, {229, 307}},
        {MrMainToWindyValley, {348, 207}},
        {MrMainToJungle, {256, 203}},
        {MrMainToChaos4, {298, 228}},
        {MrMainToEggHornet, {377, 300}},
        {MrMainToMrChaoGarden, {464, 211}},
        {MrMainToSkyChase1, {446, 319}},
        // Angel Island
        {AngelIslandToMrMain, {254, 462}},
        {AngelIslandToIceCave, {216, 451}},
        {AngelIslandToRedMountain, {88, 445}},
        {AngelIslandToPastAltar, {153, 560}},
        // Ice Cave
        {IceCaveToAngelIsland, {216, 451}},
        {IceCaveToIceCap, {174, 414}},
        // Past Altar
        {PastAltarToAngelIsland, {113, 309}},
        {PastAltarToPastMain, {109, 189}},
        // Past Main
        {PastMainToPastAltar, {112, 146}},
        {PastMainToJungle, {88, 71}},
        // Jungle
        {JungleToMrMain, {256, 157}},
        {JungleToLostWorld, {285, 94}},
        {JungleToLostWorldAlternative, {285, 48}},
        {JungleToFinalEggTower, {318, 26}},
        {JungleToSandHill, {241, 129}},
        {JungleToPastMain, {263, 71}},
        // Final Egg Tower
        {FinalEggTowerToJungle, {485, 77}},
        {FinalEggTowerToFinalEgg, {525, 118}},
        {FinalEggTowerToFinalEggAlternative, {569, 77}},
        {FinalEggTowerToBetaEggViper, {525, 77}},
        {FinalEggTowerToEcInside, {555, 105}},
        // Bridge (Transformed) 
        {BridgeToSsMain, {442, 600}},
        {BridgeToMrMain, {366, 600}},
        {BridgeToSkyDeck, {405, 701}},
        {BridgeToSkyChase2, {403, 562}},
        {BridgeToChaos6ZeroBeta, {404, 628}},
        {BridgeToEcInsideMonorail, {437, 629}},
        // Deck (Transformed) 
        {DeckToPool, {404, 810}},
        {DeckToCaptainRoom, {404, 760}},
        {DeckToPrivateRoom, {419, 740}},
        {DeckToPrivateRoomAlternative, {389, 740}},
        {DeckToEcInsideEggLift, {404, 791}},
        // Captain Room
        {CaptainRoomToDeck, {245, 885}},
        {CaptainRoomToPrivateRoom, {186, 881}},
        // Private Room
        {PrivateRoomToCaptainRoom, {146, 734}},
        {PrivateRoomToDeck, {171, 713}},
        {PrivateRoomToDeckAlternative, {249, 768}},
        // Pool
        {PoolToDeck, {404, 882}},
        {PoolToSkyDeck, {404, 913}},
        // Arsenal
        {ArsenalToEcInside, {614, 723}},
        // Egg Carrier Inside
        {EcInsideToDeckEggLift, {700, 807}},
        {EcInsideToBridgeMonorail, {674, 699}},
        {EcInsideToHotShelter, {700, 646}},
        {EcInsideToHedgehogHammer, {722, 665}},
        {EcInsideToFinalEggTower, {678, 665}},
        {EcInsideToWarpHall, {701, 867}},
        {EcInsideToArsenal, {650, 723}},
        {EcInsideToWaterTank, {750, 793}},
        // Hedgehog Hammer
        {HedgehogHammerToEcInside, {771, 620}},
        {HedgehogHammerToPrisonHall, {814, 579}},
        // Prison Hall
        {PrisonHallToHedgehogHammer, {831, 553}},
        // Water Tank
        {WaterTankToEcInside, {796, 793}},
        // Warp Hall
        {WarpHallToEcInside, {701, 899}},
        {WarpHallToEcChaoGarden, {701, 924}},

    };
};
