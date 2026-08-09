#pragma once
#include "../../../../pch.h"
#include "../../../../configuration/options/Options.h"
#include "../../../../configuration/gameStatus/GameStatus.h"
#include "../DoorLogic/IDoorLogicStrategy.h"

typedef struct {
    Float  x;
    Float  y;
    Uint32  color;
} MapPoint;


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
    void ShowDoorIcon(NJS_POINT3 position, float angle, NJS_TEXANIM* anim, float offset = 0.02f);
    bool ShouldShowName(LevelAndActIDs levelAndActId);
    void ShowDoorName(AdventureFieldEntrance adventureFieldEntrance);
    void ShowNumberDynamic(const AdventureFieldEntrance& entrance, int number, float x, float y, float zBase,
                           float xStep,
                           bool leftJustify);
    void showNumber(const AdventureFieldEntrance& adventureFieldEntrance, float posX, float posY, int number,
                    float zOffset);
    void DrawEntrancePoint(float x, float y);
    void DrawLine(float x1, float y1, Uint32 color1, float x2, float y2, Uint32 color2);
    void MakeConnection(const MapPoint& point1, const MapPoint& point2);
    void DrawEmblemNumberInMap(AdventureFieldEntrance adventureFieldEntrance, int doorCost);
    void DrawNewInMap(AdventureFieldEntrance adventureFieldEntrance);
    void DrawPlayerLocation();
    void DrawEntrancesInMap(AdventureFieldEntrance adventureFieldEntrance, bool isStatic);
    NJS_TEXANIM* getInitialsFromEntrance(AdventureFieldEntrance* entranceTo);
    NJS_TEXANIM* getFullNameFromEntrance(AdventureFieldEntrance* entranceTo);
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

    Uint32  _stationSquareLineColor = 0xFF0000FF;
    Uint32  _mysticRuinsLineColor = 0xFF00FF00;
    Uint32  _pastLineColor = 0xFFFFEE00;
    Uint32  _eggCarrierLineColor = 0xFFFF0000;

    
    std::map<int, MapPoint> entranceLocationInMap = {

        // City Hall
        {CityHallToSsMain, {860, 197, _stationSquareLineColor}},
        {CityHallToSewers, {824, 128, _stationSquareLineColor}},
        {CityHallToSpeedHighway, {775, 37, _stationSquareLineColor}},
        {CityHallToChaos0, {775, 81, _stationSquareLineColor}},
        // Station
        {StationToSsMain, {677, 294, _stationSquareLineColor}},
        {StationToMrMain, {647, 237, _stationSquareLineColor}},
        {StationToCasino, {603, 259, _stationSquareLineColor}},
        //Casino
        {CasinoToStation, {603, 259, _stationSquareLineColor}},
        {CasinoToCasinopolis, {530, 188, _stationSquareLineColor}},
        {CasinoToHotel, {572, 324, _stationSquareLineColor}},
        {CasinoToEggWalker, {584, 198, _stationSquareLineColor}},
        // Sewers
        {SewersToCityHall, {928, 85, _stationSquareLineColor}},
        {SewersToTwinkleParkTunnel, {933, 323, _stationSquareLineColor}},
        // SSMain
        {SsMainToHotel, {675, 416, _stationSquareLineColor}},
        {SsMainToStation, {722, 334, _stationSquareLineColor}},
        {SsMainToCityHall, {860, 235, _stationSquareLineColor}},
        {SsMainToTwinkleParkTunnel, {824, 391, _stationSquareLineColor}},
        {SsMainToBridge, {762, 465, _stationSquareLineColor}},
        {SsMainToSpeedHighway, {838, 341, _stationSquareLineColor}},
        // Hotel
        {HotelToSsMain, {603, 398, _stationSquareLineColor}},
        {HotelToCasino, {572, 358, _stationSquareLineColor}},
        {HotelToSsChaoGarden, {552, 406, _stationSquareLineColor}},
        {HotelToChaos2, {552, 375, _stationSquareLineColor}},
        {HotelToHotelPool, {567, 432, _stationSquareLineColor}},
        // Hotel Pool
        {HotelPoolToHotel, {567, 432, _stationSquareLineColor}},
        {HotelPoolToEmeraldCoast, {508, 528, _stationSquareLineColor}},
        // Twinkle Park Tunnel
        {TwinkleParkTunnelToSsMain, {824, 391, _stationSquareLineColor}},
        {TwinkleParkTunnelToTwinkleParkLobby, {867, 433, _stationSquareLineColor}},
        {TwinkleParkTunnelToSewers, {826, 362, _stationSquareLineColor}},
        // Twinkle Park Lobby
        {TwinkleParkLobbyToTwinkleParkTunnel, {914, 433, _stationSquareLineColor}},
        {TwinkleParkLobbyToTwinklePark, {976, 433, _stationSquareLineColor}},
        {TwinkleParkLobbyToTwinkleCircuit, {953, 413, _stationSquareLineColor}},
        // MRMain
        {MrMainToStation, {292, 342, _mysticRuinsLineColor}},
        {MrMainToBridge, {269, 351, _mysticRuinsLineColor}},
        {MrMainToAngelIsland, {229, 307, _mysticRuinsLineColor}},
        {MrMainToWindyValley, {348, 207, _mysticRuinsLineColor}},
        {MrMainToJungle, {256, 203, _mysticRuinsLineColor}},
        {MrMainToChaos4, {298, 228, _mysticRuinsLineColor}},
        {MrMainToEggHornet, {377, 300, _mysticRuinsLineColor}},
        {MrMainToMrChaoGarden, {464, 211, _mysticRuinsLineColor}},
        {MrMainToSkyChase1, {446, 319, _mysticRuinsLineColor}},
        // Angel Island
        {AngelIslandToMrMain, {254, 462, _mysticRuinsLineColor}},
        {AngelIslandToIceCave, {216, 451, _mysticRuinsLineColor}},
        {AngelIslandToRedMountain, {88, 445, _mysticRuinsLineColor}},
        {AngelIslandToPastAltar, {153, 560, _mysticRuinsLineColor}},
        // Ice Cave
        {IceCaveToAngelIsland, {216, 451, _mysticRuinsLineColor}},
        {IceCaveToIceCap, {174, 414, _mysticRuinsLineColor}},
        // Past Altar
        {PastAltarToAngelIsland, {113, 309, _pastLineColor}},
        {PastAltarToPastMain, {109, 189, _pastLineColor}},
        // Past Main
        {PastMainToPastAltar, {112, 146, _pastLineColor}},
        {PastMainToJungle, {88, 71, _pastLineColor}},
        // Jungle
        {JungleToMrMain, {256, 157, _mysticRuinsLineColor}},
        {JungleToLostWorld, {285, 94, _mysticRuinsLineColor}},
        {JungleToLostWorldAlternative, {285, 48, _mysticRuinsLineColor}},
        {JungleToFinalEggTower, {318, 26, _mysticRuinsLineColor}},
        {JungleToSandHill, {241, 129, _mysticRuinsLineColor}},
        {JungleToPastMain, {263, 71, _mysticRuinsLineColor}},
        // Final Egg Tower
        {FinalEggTowerToJungle, {485, 77, _mysticRuinsLineColor}},
        {FinalEggTowerToFinalEgg, {525, 118, _mysticRuinsLineColor}},
        {FinalEggTowerToFinalEggAlternative, {569, 77, _mysticRuinsLineColor}},
        {FinalEggTowerToBetaEggViper, {525, 77, _mysticRuinsLineColor}},
        {FinalEggTowerToEcInside, {555, 105, _mysticRuinsLineColor}},
        // Bridge (Transformed) 
        {BridgeToSsMain, {442, 600, _eggCarrierLineColor}},
        {BridgeToMrMain, {366, 600, _eggCarrierLineColor}},
        {BridgeToSkyDeck, {405, 701, _eggCarrierLineColor}},
        {BridgeToSkyChase2, {403, 562, _eggCarrierLineColor}},
        {BridgeToChaos6ZeroBeta, {404, 628, _eggCarrierLineColor}},
        {BridgeToEcInsideMonorail, {437, 629, _eggCarrierLineColor}},
        // Deck (Transformed) 
        {DeckToPool, {404, 820, _eggCarrierLineColor}},
        {DeckToCaptainRoom, {404, 760, _eggCarrierLineColor}},
        {DeckToPrivateRoom, {419, 740, _eggCarrierLineColor}},
        {DeckToPrivateRoomAlternative, {389, 740, _eggCarrierLineColor}},
        {DeckToEcInsideEggLift, {404, 791, _eggCarrierLineColor}},
        // Captain Room
        {CaptainRoomToDeck, {245, 885, _eggCarrierLineColor}},
        {CaptainRoomToPrivateRoom, {186, 881, _eggCarrierLineColor}},
        // Private Room
        {PrivateRoomToCaptainRoom, {146, 734, _eggCarrierLineColor}},
        {PrivateRoomToDeck, {171, 713, _eggCarrierLineColor}},
        {PrivateRoomToDeckAlternative, {249, 768, _eggCarrierLineColor}},
        // Pool
        {PoolToDeck, {404, 882, _eggCarrierLineColor}},
        {PoolToSkyDeck, {404, 913, _eggCarrierLineColor}},
        // Arsenal
        {ArsenalToEcInside, {614, 723, _eggCarrierLineColor}},
        // Egg Carrier Inside
        {EcInsideToDeckEggLift, {700, 807, _eggCarrierLineColor}},
        {EcInsideToBridgeMonorail, {674, 699, _eggCarrierLineColor}},
        {EcInsideToHotShelter, {700, 646, _eggCarrierLineColor}},
        {EcInsideToHedgehogHammer, {722, 665, _eggCarrierLineColor}},
        {EcInsideToFinalEggTower, {678, 665, _eggCarrierLineColor}},
        {EcInsideToWarpHall, {701, 867, _eggCarrierLineColor}},
        {EcInsideToArsenal, {650, 723, _eggCarrierLineColor}},
        {EcInsideToWaterTank, {750, 793, _eggCarrierLineColor}},
        // Hedgehog Hammer
        {HedgehogHammerToEcInside, {771, 620, _eggCarrierLineColor}},
        {HedgehogHammerToPrisonHall, {814, 579, _eggCarrierLineColor}},
        // Prison Hall
        {PrisonHallToHedgehogHammer, {831, 553, _eggCarrierLineColor}},
        // Water Tank
        {WaterTankToEcInside, {796, 793, _eggCarrierLineColor}},
        // Warp Hall
        {WarpHallToEcInside, {701, 899, _eggCarrierLineColor}},
        {WarpHallToEcChaoGarden, {701, 924, _eggCarrierLineColor}},

    };
};
