#pragma once
#include "AdventureFieldEntranceMap.h"
#include "../../../pch.h"
#include "../../../configuration/options/Options.h"
#include "../doorIndicatorManager/DoorIndicatorManager.h"
#include "../../archipelagoMessenger/ArchipelagoMessenger.h"
#include "DoorLogic/IDoorLogicStrategy.h"
#include "DoorLogic/KeyItemDoorLogicStrategy.h"
#include "DoorLogic/EmblemGatingDoorLogicStrategy.h"
#include "DoorLogic/EverythingOpenedDoorLogicStrategy.h"
#include "DoorLogic/EverythingClosedDoorLogicStrategy.h"
#include "mapManager/MapManager.h"

class AdventureFieldEntranceManager
{
public:
    static AdventureFieldEntranceManager& Init(Options& options, Settings& settings, GameStatus& gameStatus,
                                               ArchipelagoMessenger& archipelagoMessenger)
    {
        if (_instance == nullptr)
            _instance = new AdventureFieldEntranceManager(options, settings, gameStatus, archipelagoMessenger);
        return *_instance;
    }

    void OnFrame();
    void UpdateGatingMethod();
    void UpdateRandomEntrances();

private:
    explicit AdventureFieldEntranceManager(Options& options, Settings& settings, GameStatus& gameStatus,
                                           ArchipelagoMessenger& archipelagoMessenger);
    inline static AdventureFieldEntranceManager* _instance = nullptr;
    Options& _options;
    Settings& _settings;
    GameStatus& _gameStatus;
    ArchipelagoMessenger& _archipelagoMessenger;
    AdventureFieldEntranceMap& _adventureFieldEntranceMap;
    DoorIndicatorManager& _doorIndicatorManager;
    MapManager& _mapManager;
    bool _isEggCarrierTransformed = false;
    std::unique_ptr<IDoorLogicStrategy> _doorLogicStrategy;

    bool IsDoorOpen(EntranceId entranceId);

    inline static FunctionHook<void, Uint8, Uint8> _setNextLevelAndActCutsceneModeHook{0x4145D0};
    static void OnSetNextLevelAndActCutsceneMode(Uint8 level, Uint8 act);

    inline static FunctionHook<void, Uint8, Uint8> _setNextLevelAndActHook{0x4145B0};
    static void OnSetNextLevelAndAct(Uint8 level, Uint8 act);

    inline static FunctionHook<task*, Uint8, Uint8> _setNextLevelAndActChaoGardenHook{0x715730};
    static task* OnSetNextLevelAndActChaoGarden(Uint8 level, Uint8 act);

    inline static FunctionHook<Sint32> _finishedLevelMaybeHook{0x414090};
    static Sint32 OnFinishedLevelMaybe();

    inline static FunctionHook<void, taskwk*> _movePlayerToStartPointHook{0x414810};
    static void OnMovePlayerToStartPoint(taskwk* twp);

    inline static FunctionHook<void, taskwk*> _getEntranceEc{0x52D820};
    static void OnGetEntranceEc(taskwk* twp);

    inline static FunctionHook<void> _setStartPos_ReturnToFieldHook{0x414500};
    static void OnSetStartPosReturnToField();

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

    inline static FunctionHook<BOOL> _isSpeedHighwayElevatorOpen{0x638CC0};
    static BOOL OnIsSpeedHighwayElevatorOpen();

    inline static FunctionHook<BOOL> _isChaos2ElevatorOpen{0x638D50};
    static BOOL OnIsChaos2ElevatorOpen();

    inline static FunctionHook<void, ObjectMaster*> _speedHighwayElevatorHook{0x6393F0};
    static void OnSpeedHighwayElevator(ObjectMaster* tp);

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

    static void __cdecl OnSceneChangeLogicECOuside(int a1);

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


    inline static FunctionHook<BOOL> _isEcBoatEnabledHook{0x51C7B0};
    static BOOL IsEcBoatEnabled();

    inline static FunctionHook<BOOL> _isEcRaftEnabledHook{0x51CA80};
    static BOOL IsEcRaftEnabled();

    inline static FunctionHook<void, task*> _hiddenGateMainHook{0x53C3E0};
    static void OnHiddenGateMain(task* tp);
};
