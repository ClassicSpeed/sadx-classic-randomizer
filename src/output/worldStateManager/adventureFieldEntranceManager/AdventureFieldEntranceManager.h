#pragma once
#include "AdventureFieldEntranceMap.h"
#include "../../../pch.h"
#include "../../../configuration/options/Options.h"
#include "../doorIndicatorManager/DoorIndicatorManager.h"

class AdventureFieldEntranceManager
{
public:
    static AdventureFieldEntranceManager& Init(Options& options)
    {
        if (_instance == nullptr)
            _instance = new AdventureFieldEntranceManager(options);
        return *_instance;
    }

    void ShowLevelEntranceArrows();

private:
    explicit AdventureFieldEntranceManager(Options& options);
    inline static AdventureFieldEntranceManager* _instance = nullptr;
    Options& _options;
    AdventureFieldEntranceMap& _adventureFieldEntranceMap;
    DoorIndicatorManager& _doorIndicatorManager;

    bool IsDoorOpen(EntranceId entranceId);
    bool ShowDisableDoorIndicator(EntranceId entranceId);

    inline static FunctionHook<void, Uint8, Uint8> _setNextLevelAndActCutsceneModeHook{0x4145D0};
    static void OnSetNextLevelAndActCutsceneMode(Uint8 level, Uint8 act);

    inline static FunctionHook<void, taskwk*> _getEntranceSs{0x62F6D0};
    static void OnGetEntranceSs(taskwk* tp);

    inline static FunctionHook<BOOL> _isBarricadeGoneHook{0x6389F0};
    static BOOL OnIsBarricadeGone();

    inline static FunctionHook<BOOL> _isStationDoorOpenHook{0x63AB70};
    static BOOL OnIsStationDoorOpen();

    inline static FunctionHook<BOOL> _isHotelFrontDoorOpenHook{0x630900};
    static BOOL OnIsHotelFrontDoorOpen();

    inline static FunctionHook<BOOL> _isHotelBackDoorOpenHook{0x630970};
    static BOOL OnIsHotelBackDoorOpen();

    inline static FunctionHook<void, task*> _twinkleParkLobbyDoorFromStationHook{0x63E6F0};
    static void OnTwinkleParkLobbyDoorFromStation(task* tp);

    inline static FunctionHook<void, task*> _ssBoxLoadHook{0x636B30};
    static void OnSsBoxLoad(task* tp);

    inline static FunctionHook<void, task*> _elevatorOutHook{0x63DB90};
    static void OnElevatorOut(task* tp);

    inline static FunctionHook<int, task*> _elevatorInSceneChangeHook{0x63D7C0};
    static int OnElevatorInSceneChange(task* tp);

    inline static FunctionHook<void, task*> _sewerCarMainHook{0x639920};
    static void OnSewerCarMain(task* tp);

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

    inline static FunctionHook<BOOL> _isChaos2DoorOpenHook{0x638D50};
    static BOOL OnIsChaos2DoorOpen();

    inline static FunctionHook<void, task*> _loadHotelElevatorHook{0x639380};
    static void OnLoadHotelElevator(task* tp);

    inline static FunctionHook<BOOL> _isCasinoOpenHook{0x6383E0};
    static BOOL OnIsCasinoOpen();

    inline static FunctionHook<BOOL> _isTrainInServiceHook{0x539C60};
    static BOOL OnIsTrainInService();
};
