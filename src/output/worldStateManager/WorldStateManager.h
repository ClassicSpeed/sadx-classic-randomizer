#pragma once

#include "../../pch.h"
#include <algorithm>
#include "../../configuration/options/Options.h"
#include "levelEntranceManager/LevelEntranceManager.h"
#include "setObjectManager/SetObjectManager.h"


class WorldStateManager : public IOnFrame
{
public:
    static WorldStateManager& Init(Options& options, Settings& settings, GameStatus& gameStatus)
    {
        if (_instance == nullptr)
            _instance = new WorldStateManager(options, settings, gameStatus);
        return *_instance;
    }

    void OnFrame() override;
    void SetLevelEntrances();
    void UpdateVisitedLevels(int visitedLevel);

private:
    explicit WorldStateManager(Options& options, Settings& settings, GameStatus& gameStatus);
    inline static WorldStateManager* _instance = nullptr;
    Options& _options;
    Settings& _settings;
    GameStatus& _gameStatus;
    SetObjectManager& _setObjectManager;
    LevelEntranceManager& _levelEntranceManager;


    inline DataPointer(int, _showExitMenuTwinkleCircuit, 0x3C5D430);
    inline DataArray(int16_t, _chaoStatValues, 0x8895C8, 0x402);


    inline static FunctionHook<void, task*> _collisionCubeHook{0x4D47E0};
    static void OnCollisionCube(task* tp);

    inline static FunctionHook<BOOL> _isStationDoorOpenHook{0x63AB70};
    static BOOL OnIsStationDoorOpen();

    inline static FunctionHook<BOOL> _isHotelDoorOpenHook{0x630900};
    static BOOL OnIsHotelDoorOpen();

    inline static FunctionHook<BOOL> _isCasinoHotelDoorOpenHook{0x630970};
    static BOOL OnIsCasinoHotelDoorOpen();

    inline static FunctionHook<BOOL> _isCasinoStationDoorOpenHook{0x638880};
    static BOOL OnIsCasinoStationDoorOpen();

    inline static FunctionHook<void, task*> _mysticRuinsKeyHook{0x532400};
    static void OnMysticRuinsKey(task* tp);

    inline static FunctionHook<void, task*> _employeeCardHook{0x63C370};
    static void OnEmployeeCard(task* tp);

    inline static FunctionHook<void, task*> _twinkleCircuitResultsMaybeHook{0x4DAFB0};
    static void OnTwinkleCircuitResultsMaybe(task* tp);

    inline static FunctionHook<BOOL> _isWindyValleyOpenHook{0x536E40};
    static BOOL OnIsWindyValleyOpen();

    inline static FunctionHook<BOOL> _isAngelIslandOpenHook{0x534570};
    static BOOL OnIsAngelIslandOpen();

    inline static FunctionHook<BOOL, int> _preventKeyStoneFromSpawningHook{0x53C630};
    static BOOL OnPreventKeyStoneFromSpawning(int a1);
};
