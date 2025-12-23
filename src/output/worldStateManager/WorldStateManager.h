#pragma once

#include "../../pch.h"
#include <algorithm>
#include "../../configuration/options/Options.h"
#include "adventureFieldEntranceManager/AdventureFieldEntranceManager.h"
#include "setObjectManager/SetObjectManager.h"
#include "../archipelagoMessenger/ArchipelagoMessenger.h"


class WorldStateManager : public IOnFrame
{
public:
    static WorldStateManager& Init(Options& options, Settings& settings, GameStatus& gameStatus,
                                   ArchipelagoMessenger& archipelagoMessenger)
    {
        if (_instance == nullptr)
            _instance = new WorldStateManager(options, settings, gameStatus, archipelagoMessenger);
        return *_instance;
    }

    void OnFrame() override;
    void SetLevelEntrances();
    void UpdateVisitedLevels(int visitedLevel);

private:
    explicit WorldStateManager(Options& options, Settings& settings, GameStatus& gameStatus,
                               ArchipelagoMessenger& archipelagoMessenger);
    inline static WorldStateManager* _instance = nullptr;
    Options& _options;
    Settings& _settings;
    GameStatus& _gameStatus;
    SetObjectManager& _setObjectManager;
    AdventureFieldEntranceManager& _adventureFieldEntranceManager;
    // LevelEntranceManager& _levelEntranceManager;

    inline DataPointer(int, _showExitMenuTwinkleCircuit, 0x3C5D430);
    inline DataArray(int16_t, _chaoStatValues, 0x8895C8, 0x402);


    inline static FunctionHook<void, task*> _twinkleCircuitResultsMaybeHook{0x4DAFB0};
    static void OnTwinkleCircuitResultsMaybe(task* tp);
};
