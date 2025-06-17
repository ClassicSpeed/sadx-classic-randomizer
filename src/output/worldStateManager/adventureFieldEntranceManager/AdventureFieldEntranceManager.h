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

    inline static FunctionHook<BOOL> _isHotelDoorOpenHook{0x630900};
    static BOOL OnIsHotelDoorOpen();

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
};
