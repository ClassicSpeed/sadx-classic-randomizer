#pragma once
#include "../../../../pch.h"
#include "../../../../configuration/options/Options.h"
#include "../../../../configuration/gameStatus/GameStatus.h"
#include "../DoorLogic/IDoorLogicStrategy.h"


class MapManager : public IOnFrame
{
public:
    static MapManager& Init(Options& options, GameStatus& gameStatus,
                            AdventureFieldEntranceMap& _adventureFieldEntranceMap)
    {
        if (_instance == nullptr)
            _instance = new MapManager(options, gameStatus, _adventureFieldEntranceMap);
        return *_instance;
    }

    void OnFrame() override;
    void SetDoorLogicStrategy(IDoorLogicStrategy* doorLogicStrategy);

private:
    IDoorLogicStrategy* _doorLogicStrategy;
    void ShowMap();
    void showNumberMap(float posX, float posY, int number);
    bool ShowDisableDoorIndicator(EntranceId entranceId);
    void ShowDoorEmblemRequirement(AdventureFieldEntrance adventureFieldEntrance);
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
    void DrawMapEmblem(AdventureFieldEntrance adventureFieldEntrance, bool isStatic);
    NJS_TEXANIM* getInitialsFromEntrance(AdventureFieldEntrance* entranceTo);
    void DrawLevelInitialsInMap(AdventureFieldEntrance* entranceTo, Float entranceX, Float entranceY);
    void DrawConnectionsInMap(const AdventureFieldEntrance& adventureFieldEntrance);
    void ShowNumberDynamicMap(int number, float x, float y);

    explicit MapManager(Options& options, GameStatus& gameStatus,
                        AdventureFieldEntranceMap& _adventureFieldEntranceMap);
    inline static MapManager* _instance = nullptr;
    Options& _options;
    GameStatus& _gameStatus;
    AdventureFieldEntranceMap& _adventureFieldEntranceMap;

    std::map<int, NJS_POINT2> entranceLocationInMap = {

        // City Hall
        {CityHallToSsMain, {848, 198}},
        {CityHallToSewers, {820, 132}},
        {CityHallToSpeedHighway, {768, 39}},
        {CityHallToChaos0, {768, 82}},
        // Station
        {StationToSsMain, {704, 321}},
        {StationToMrMain, {681, 263}},
        {StationToCasino, {642, 288}},
        //Casino
        {CasinoToStation, {642, 288}},
        {CasinoToCasinopolis, {559, 203}},
        {CasinoToHotel, {603, 330}},
        {CasinoToEggWalker, {616, 216}},
        // Sewers
        {SewersToCityHall, {928, 91}},
        {SewersToTwinkleParkTunnel, {927, 313}},
        // SSMain
        {SsMainToHotel, {687, 405}},
        {SsMainToStation, {734, 331}},
        {SsMainToCityHall, {853, 227}},
        {SsMainToTwinkleParkTunnel, {814, 387}},
        {SsMainToEcOutside, {765, 444}},
        {SsMainToBridge, {765, 444}},
        {SsMainToSpeedHighway, {839, 338}},
        // Hotel
        {HotelToSsMain, {628, 396}},
        {HotelToCasino, {591, 376}},
        {HotelToSsChaoGarden, {578, 401}},
        {HotelToChaos2, {578, 389}},
        {HotelToHotelPool, {590, 420}},
        // Hotel Pool
        {HotelPoolToHotel, {590, 420}},
        {HotelPoolToEmeraldCoast, {530, 504}},
        // Twinkle Park Tunnel
        {TwinkleParkTunnelToSsMain, {814, 387}},
        {TwinkleParkTunnelToTwinkleParkLobby, {857, 426}},
        {TwinkleParkTunnelToSewers, {820, 362}},
        // Twinkle Park Lobby
        {TwinkleParkLobbyToTwinkleParkTunnel, {914, 433}},
        {TwinkleParkLobbyToTwinklePark, {955, 436}},
        {TwinkleParkLobbyToTwinkleCircuit, {937, 417}},
        // MRMain
        {MrMainToStation, {297, 335}},
        {MrMainToEcOutside, {286, 352}},
        {MrMainToBridge, {286, 352}},
        {MrMainToAngelIsland, {225, 297}},
        {MrMainToWindyValley, {346, 213}},
        {MrMainToJungle, {268, 216}},
        {MrMainToChaos4, {299, 237}},
        {MrMainToEggHornet, {371, 303}},
        {MrMainToMrChaoGarden, {443, 219}},
        {MrMainToSkyChase1, {428, 305}},
        // Angel Island
        {AngelIslandToMrMain, {285, 419}},
        {AngelIslandToIceCave, {249, 412}},
        {AngelIslandToRedMountain, {143, 420}},
        {AngelIslandToPastAltar, {206, 530}},
        // Ice Cave
        {IceCaveToAngelIsland, {249, 412}},
        {IceCaveToIceCap, {208, 387}},
        // Past Altar
        {PastAltarToAngelIsland, {85, 388}},
        {PastAltarToPastMain, {72, 260}},
        // Past Main
        {PastMainToPastAltar, {107, 222}},
        {PastMainToJungle, {85, 130}},
        // Jungle
        {JungleToMrMain, {254, 156}},
        {JungleToLostWorld, {290, 76}},
        {JungleToLostWorldAlternative, {291, 49}},
        {JungleToFinalEggTower, {321, 29}},
        {JungleToSandHill, {242, 126}},
        {JungleToPastMain, {276, 63}},
        // Final Egg Tower
        {FinalEggTowerToJungle, {524, 86}},
        {FinalEggTowerToFinalEgg, {559, 123}},
        {FinalEggTowerToFinalEggAlternative, {593, 91}},
        {FinalEggTowerToBetaEggViper, {558, 86}},
        {FinalEggTowerToEcInside, {589, 111}},
        // Egg Carrier Outside (Untransformed)
        {EcOutsideToSsMain, {483, 626}},
        {EcOutsideToMrMain, {409, 625}},
        {EcOutsideToSkyChase2, {447, 592}},
        {EcOutsideToChaos6ZeroBeta, {446, 648}},
        {EcOutsideToEcInsideMonorail, {474, 675}},
        {EcOutsideToEcInsideEggLift, {446, 779}},
        {EcOutsideToCaptainRoom, {447, 731}},
        {EcOutsideToPool, {447, 797}},
        // Bridge (Transformed) 
        {BridgeToSsMain, {343, 586}},
        {BridgeToMrMain, {274, 587}},
        {BridgeToSkyDeck, {310, 680}},
        {BridgeToSkyChase2, {307, 551}},
        {BridgeToChaos6ZeroBeta, {307, 610}},
        {BridgeToEcInsideMonorail, {336, 636}},
        // Deck (Transformed) 
        {DeckToPool, {308, 938}},
        {DeckToCaptainRoom, {304, 875}},
        {DeckToPrivateRoom, {323, 868}},
        {DeckToPrivateRoomAlternative, {289, 868}},
        {DeckToEcInsideEggLift, {306, 923}},
        // Captain Room
        {CaptainRoomToEcOutside, {310, 769}},
        {CaptainRoomToDeck, {310, 769}},
        {CaptainRoomToPrivateRoom, {309, 741}},
        // Private Room
        {PrivateRoomToCaptainRoom, {176, 728}},
        {PrivateRoomToDeck, {189, 749}},
        {PrivateRoomToDeckAlternative, {156, 791}},
        // Pool
        {PoolToEcOutside, {450, 872}},
        {PoolToDeck, {450, 872}},
        {PoolToSkyDeck, {448, 904}},
        // Arsenal
        {ArsenalToEcInside, {615, 719}},
        // Egg Carrier Inside
        {EcInsideToEcOutsideEggLift, {702, 795}},
        {EcInsideToEcOutsideMonorail, {688, 708}},
        {EcInsideToDeckEggLift, {702, 795}},
        {EcInsideToBridgeMonorail, {688, 708}},
        {EcInsideToHotShelter, {702, 665}},
        {EcInsideToHedgehogHammer, {716, 671}},
        {EcInsideToFinalEggTower, {686, 671}},
        {EcInsideToWarpHall, {703, 853}},
        {EcInsideToArsenal, {652, 718}},
        {EcInsideToWaterTank, {750, 783}},
        // Hedgehog Hammer
        {HedgehogHammerToEcInside, {774, 654}},
        {HedgehogHammerToPrisonHall, {813, 615}},
        // Prison Hall
        {PrisonHallToHedgehogHammer, {860, 600}},
        // Water Tank
        {WaterTankToEcInside, {791, 788}},
        // Warp Hall
        {WarpHallToEcInside, {702, 885}},
        {WarpHallToEcChaoGarden, {701, 901}},

    };
};
