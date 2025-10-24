#pragma once
#include "AdventureFieldEntranceMap.h"
#include "../../../pch.h"
#include "../../../configuration/options/Options.h"
#include "../doorIndicatorManager/DoorIndicatorManager.h"
#include "DoorLogic/IDoorLogicStrategy.h"
#include "DoorLogic/KeyItemDoorLogicStrategy.h"
#include "DoorLogic/EmblemGatingDoorLogicStrategy.h"

class AdventureFieldEntranceManager
{
public:
    static AdventureFieldEntranceManager& Init(Options& options, GameStatus& gameStatus)
    {
        if (_instance == nullptr)
            _instance = new AdventureFieldEntranceManager(options, gameStatus);
        return *_instance;
    }

    void showNumber(const AdventureFieldEntrance& adventureFieldEntrance, float posX, float posY, int number,
                    float zOffset);
    void showNumberMap(float posX, float posY, int number);
    void DrawEntrancePoint(float x, float y);
    void DrawLine(float x1, float y1, float x2, float y2);
    void MakeConnection(float x1, float y1, float x2, float y2);
    void DrawEmblemNumberInMap(AdventureFieldEntrance adventureFieldEntrance, int doorCost);
    void DrawMapEmblem(AdventureFieldEntrance adventureFieldEntrance);
    void ShowMap();
    void ShowDoorEmblemRequirement(AdventureFieldEntrance adventureFieldEntrance);
    void ShowLevelEntranceArrows();
    void ShowNumberDynamic(const AdventureFieldEntrance& entrance, int number, float x, float y, float zBase,
                           float xStep, bool leftJustify);
    void ShowNumberDynamicMap(int number, float x, float y);

private:
    explicit AdventureFieldEntranceManager(Options& options, GameStatus& gameStatus);
    inline static AdventureFieldEntranceManager* _instance = nullptr;
    Options& _options;
    GameStatus& _gameStatus;
    AdventureFieldEntranceMap& _adventureFieldEntranceMap;
    DoorIndicatorManager& _doorIndicatorManager;
    bool _isEggCarrierTransformed = false;
    std::unique_ptr<IDoorLogicStrategy> _doorLogicStrategy;

    bool IsDoorOpen(EntranceId entranceId);
    bool ShowDisableDoorIndicator(EntranceId entranceId);

    inline static FunctionHook<void, Uint8, Uint8> _setNextLevelAndActCutsceneModeHook{0x4145D0};
    static void OnSetNextLevelAndActCutsceneMode(Uint8 level, Uint8 act);

    inline static FunctionHook<void, taskwk*> _getEntranceSs{0x62F6D0};
    static void OnGetEntranceSs(taskwk* twp);

    inline static FunctionHook<void, taskwk*> _getEntranceEc{0x52D820};
    static void OnGetEntranceEc(taskwk* twp);

    inline static FunctionHook<BOOL> _isBarricadeGoneHook{0x6389F0};
    static BOOL OnIsBarricadeGone();

    inline static FunctionHook<void, task*> _wallMainHook{0x4D4850};
    static void OnWallMain(task* tp);

    inline static FunctionHook<void, task*> _ssCarMainHook{0x633250};
    static void OnSsCarMain(task* tp);

    inline static FunctionHook<BOOL> _isStationDoorOpenHook{0x63AB70};
    static BOOL OnIsStationDoorOpen();

    inline static FunctionHook<BOOL> _isCasinoStationDoorOpenHook{0x638880};
    static BOOL OnIsCasinoStationDoorOpen();

    inline static FunctionHook<BOOL> _isHotelFrontDoorOpenHook{0x630900};
    static BOOL OnIsHotelFrontDoorOpen();

    inline static FunctionHook<BOOL> _isHotelBackDoorOpenHook{0x630970};
    static BOOL OnIsHotelBackDoorOpen();

    inline static FunctionHook<BOOL> _isHotelPoolDoorOpenHook{0x6309E0};
    static BOOL OnIsHotelPoolDoorOpen();

    inline static FunctionHook<BOOL> _isTwinkleParkElevatorOpenHook{0X63DBB0};
    static BOOL OnIsTwinkleParkElevatorOpen();

    inline static FunctionHook<void, task*> _twinkleParkLobbyDoorFromStationHook{0x63E6F0};
    static void OnTwinkleParkLobbyDoorFromStation(task* tp);

    inline static FunctionHook<void, task*> _twinkleParkLobbyDoorToStationHook{0x63E430};
    static void OnTwinkleParkLobbyDoorToStation(task* tp);

    inline static FunctionHook<void, task*> _ssBoxLoadHook{0x636B30};
    static void OnSsBoxLoad(task* tp);

    inline static FunctionHook<void, task*> _elevatorInHook{0x63DB70};
    static void OnElevatorIn(task* tp);

    inline static FunctionHook<void, task*> _elevatorOutHook{0x63DB90};
    static void OnElevatorOut(task* tp);

    inline static FunctionHook<int, task*> _elevatorInSceneChangeHook{0x63D7C0};
    static int OnElevatorInSceneChange(task* tp);

    inline static FunctionHook<void, task*> _sewerCarHandlePickUpHook{0x639800};
    static void OnSewerCarHandlePickUp(task* tp);

    inline static FunctionHook<BOOL> _spawnSewerCarHook{0x639740};
    static BOOL OnSpawnSewerCar();

    inline static FunctionHook<void, task*> _collisionCubeHook{0x4D47E0};
    static void OnCollisionCube(task* tp);

    inline static FunctionHook<void, task*> _collisionSphereHook{0x4D4700};
    static void OnCollisionSphere(task* tp);

    inline static FunctionHook<void, task*> _sceneChangeMainStationSquareHook{0x640850};
    static void OnSceneChangeMainStationSquare(task* tp);

    inline static FunctionHook<void, task*> _characterUpgradeMainHook{0x4BF600};
    static void OnCharacterUpgradeMain(task* tp);

    inline static FunctionHook<void, task*> _ssBoatMainHook{0x63B610};
    static void OnSsBoatMain(task* tp);

    inline static FunctionHook<BOOL> _isSpeedHighwayShutterOpenHook{0x63A2A0};
    static BOOL OnIsSpeedHighwayShutterOpen();

    inline static FunctionHook<void, task*> _loadSpeedHighwayShutterHook{0x63A530};
    static void OnLoadSpeedHighwayShutter(task* tp);

    inline static FunctionHook<void, task*> _loadSpeedHighwayShutter2Hook{0x63A500};
    static void OnLoadSpeedHighwayShutter2(task* tp);

    inline static FunctionHook<BOOL> _isEmeraldCoastOpenHook{0x639A30};
    static BOOL OnIsEmeraldCoastOpen();

    inline static FunctionHook<void, task*> _loadEmeraldCoastGateTargetsHook{0x63A0C0};
    static void OnLoadEmeraldCoastGateTargets(task* tp);

    inline static FunctionHook<void, task*> _elevatorMainHook{0x638F50};
    static void OnElevatorMain(task* tp);

    inline static FunctionHook<BOOL> _isCasinoOpenHook{0x6383E0};
    static BOOL OnIsCasinoOpen();

    inline static FunctionHook<BOOL> _isTrainInServiceHook{0x539C60};
    static BOOL OnIsTrainInService();

    inline static FunctionHook<void, task*> _ecWarpMainHook{0x526470};
    static void OnEcWarpMain(task* tp);

    inline static FunctionHook<void, task*> _openToyShopDoorMainHook{0x63E9E0};
    static void OnOpenToyShopDoorMain(task* tp);

    inline static FunctionHook<BOOL> _isCityHallDoorOpenHook{0x636BF0};
    static BOOL OnIsCityHallDoorOpen();

    inline static FunctionHook<void, task*> _loadKnucklesBarricadeHook{0x637580};
    static void OnLoadKnucklesBarricade(task* tp);

    static int __cdecl OnTwinkleCircuitDoor(char character);
    static int __cdecl OnTwinkleParkDoor(char character);

    inline static FunctionHook<void, task*> _mrRaftMainHook{0x539BB0};
    static void OnMrRaftMain(task* tp);

    static signed int __cdecl OnMrCartMain(task* tp);

    inline static FunctionHook<BOOL> _isAngelIslandOpenHook{0x534570};
    static BOOL OnIsAngelIslandOpen();

    inline static FunctionHook<void, task*> _mysticRuinsKeyHook{0x532400};
    static void OnMysticRuinsKey(task* tp);

    inline static FunctionHook<void, task*> _mysticRuinsLockHook{0x53CA60};
    static void OnMysticRuinsLock(task* tp);

    inline static FunctionHook<BOOL> _isWindyValleyOpenHook{0x536E40};
    static BOOL OnIsWindyValleyOpen();

    inline static FunctionHook<BOOL> _preventMrStoneSpawnHook{0x53C630};
    static BOOL OnPreventMrStoneSpawn();

    inline static FunctionHook<int, char> _getCharacterIdHook{0x441970};
    static int OnGetCharacterId(char index);

    inline static FunctionHook<void, task*> _pastSceneChangeHook{0x545670};
    static void OnPastSceneChange(task* tp);

    inline static FunctionHook<BOOL, EntityData1*> _isFinalEggEggmanDoorOpenHook{0x53ED30};
    static BOOL OnIsFinalEggEggmanDoorOpen(EntityData1* entity);

    inline FunctionPointer(int, _isMonkeyDead, (int a1), 0x53F920);

    inline static FunctionHook<BOOL, int> _isMonkeyDoorOpenHook{0x53E5D0};
    static BOOL OnIsMonkeyDoorOpen(int a1);

    inline static FunctionHook<void, task*> _loadMonkeyCageHook{0x540730};
    static void OnLoadMonkeyCage(task* tp);

    inline static FunctionHook<void, task*> _changeSceneCave2Hook{0x536ED0};
    static void OnChangeSceneCave2(task* tp);

    inline static FunctionHook<BOOL> _isLostWorldFrontEntranceOpenHook{0x532E60};
    static BOOL OnIsLostWorldFrontEntranceOpen();

    inline static FunctionHook<BOOL> _isSandHillOpenHook{0x53EAF0};
    static BOOL OnIsSandHillOpen();

    inline static FunctionHook<void, task*> _loadSceneChangeMrHook{0x5394F0};
    static void OnLoadSceneChangeMr(task* tp);

    static void __cdecl OnSceneChangeMr(int newScene);

    inline static FunctionHook<BOOL> _isLostWorldBackEntranceOpenHook{0x53B6C0};
    static BOOL OnIsLostWorldBackEntranceOpen();

    inline static FunctionHook<void, task*> _loadLongLadderMrHook{0x536CB0};
    static void OnLoadLongLadderMr(task* tp);

    static void __cdecl OnSceneChangeEcInside(int a1, int a2);

    static int __cdecl OnEggCarrierInsideEggDoor(const taskwk* twp);

    static int __cdecl OnEggCarrierOutsideEggDoor(const taskwk* twp);

    static bool IsPlayerNearDoor(const taskwk* twp);

    static int __cdecl OnSkyDeckDoor(taskwk* twp);

    inline static FunctionHook<void, task*> _eggCapHook{0x51FF90};
    static void OnEggCap(task* tp);

    inline static FunctionHook<void, task*> _springMainHook{0x7A4C30};
    static void OnSpringMain(task* tp);

    inline static FunctionHook<BOOL> _isMonorailEnabledHook{0x521250};
    static BOOL OnIsMonorailEnabled();

    inline static FunctionHook<BOOL> _isOutsideEggLiftEnabledHook{0x5217A0};
    static BOOL OnIsOutsideEggLiftEnabled();

    inline static FunctionHook<BOOL> _isInsideEggLiftEnabledHook{0x51B9A0};
    static BOOL OnIsInsideEggLiftEnabled();

    inline static FunctionHook<void, task*> _loadPoolDoorHook{0x51E320};
    static void OnLoadPoolDoor(task* tp);

    inline static FunctionHook<BOOL> _isEggCarrierSunkHook{0x412E70};
    static BOOL IsEggCarrierSunk();

    inline static FunctionHook<BOOL> _isEcBoatEnabledHook{0x51C7B0};
    static BOOL IsEcBoatEnabled();

    inline static FunctionHook<BOOL> _isEcRaftEnabledHook{0x51CA80};
    static BOOL IsEcRaftEnabled();

    inline static FunctionHook<void, task*> _hiddenGateMainHook{0x53C3E0};
    static void OnHiddenGateMain(task* tp);

    inline static FunctionHook<void, task*> _chaoWarpMainHook{0x7293E0};
    static void OnChaoWarpMain(task* tp);

    inline static FunctionHook<task*, int, int> _chaoGardenChanceSceneHook{0x715730};
    static task* OnChaoGardenChanceScene(int a1, int a2);

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
        {MrMainToSsMain, {297, 335}},
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
        {JungleToMrMain, {247, 146}},
        {JungleToLostWorld, {272, 92}},
        {JungleToLostWorldAlternative, {272, 74}},
        {JungleToFinalEggTower, {295, 60}},
        {JungleToSandHill, {243, 126}},
        {JungleToPastMain, {263, 83}},
        // Final Egg Tower
        {FinalEggTowerToJungle, {478, 92}},
        {FinalEggTowerToFinalEgg, {502, 119}},
        {FinalEggTowerToFinalEggAlternative, {525, 95}},
        {FinalEggTowerToBetaEggViper, {502, 95}},
        {FinalEggTowerToEcInside, {518, 111}},
        // Egg Carrier Outside (Untransformed)
        {EcOutsideToSsMain, {464, 648}},
        {EcOutsideToMrMain, {464, 648}},
        {EcOutsideToSkyChase2, {426, 590}},
        {EcOutsideToChaos6ZeroBeta, {427, 647}},
        {EcOutsideToEcInsideMonorail, {453, 670}},
        {EcOutsideToEcInsideEggLift, {427, 783}},
        {EcOutsideToCaptainRoom, {427, 729}},
        {EcOutsideToPool, {427, 797}},
        // Bridge (Transformed) 
        {BridgeToSsMain, {464, 648}},
        {BridgeToMrMain, {464, 648}},
        {BridgeToSkyDeck, {427, 690}},
        {BridgeToSkyChase2, {426, 590}},
        {BridgeToChaos6ZeroBeta, {427, 647}},
        {BridgeToEcInsideMonorail, {453, 670}},
        // Deck (Transformed) 
        {DeckToPool, {427, 797}},
        {DeckToCaptainRoom, {427, 729}},
        {DeckToPrivateRoom, {443, 720}},
        {DeckToPrivateRoomAlternative, {414, 722}},
        {DeckToEcInsideEggLift, {427, 783}},
        // Captain Room
        {CaptainRoomToEcOutside, {219, 748}},
        {CaptainRoomToDeck, {219, 748}},
        {CaptainRoomToPrivateRoom, {220, 715}},
        // Private Room
        {PrivateRoomToCaptainRoom, {318, 678}},
        {PrivateRoomToDeck, {332, 687}},
        {PrivateRoomToDeckAlternative, {298, 736}},
        // Pool
        {PoolToEcOutside, {430, 871}},
        {PoolToDeck, {430, 871}},
        {PoolToSkyDeck, {430, 887}},
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
