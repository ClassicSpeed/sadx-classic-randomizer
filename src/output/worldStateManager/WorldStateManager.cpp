#include "WorldStateManager.h"


WorldStateManager::WorldStateManager(Options& options, Settings& settings, GameStatus& gameStatus,
                                     ArchipelagoMessenger& archipelagoMessenger) : _options(options),
    _settings(settings), _gameStatus(gameStatus),
    _setObjectManager(SetObjectManager::Init(options, settings)),
    _adventureFieldEntranceManager(
        AdventureFieldEntranceManager::Init(options, settings, gameStatus, archipelagoMessenger))
{
    _twinkleCircuitResultsMaybeHook.Hook(OnTwinkleCircuitResultsMaybe);


    if (settings.chaoStatsMultiplier > 1)
    {
        for (int i = 0x00; i < 0x402; i++)
        {
            _chaoStatValues[i] = _chaoStatValues[i] * settings.chaoStatsMultiplier;
        }
    }
}

void WorldStateManager::OnFrame()
{
    if (DemoPlaying > 0)
        return;
    if (CurrentLevel == LevelIDs_PerfectChaos)
        return;

    _setObjectManager.OnFrame();
    _adventureFieldEntranceManager.OnFrame();
}

void WorldStateManager::SetLevelEntrances()
{
    _adventureFieldEntranceManager.UpdateRandomEntrances();
}

void WorldStateManager::UpdateVisitedLevels(const int visitedLevel)
{
    // _levelEntranceManager.UpdateVisitedLevels(visitedLevel);
}

void WorldStateManager::UpdateGatingMethod()
{
    _adventureFieldEntranceManager.UpdateGatingMethod();
}

void WorldStateManager::OnTwinkleCircuitResultsMaybe(task* tp)
{
    if (CurrentLevel == LevelIDs_TwinkleCircuit && _showExitMenuTwinkleCircuit == 1)
    {
        SetNextLevelAndAct_CutsceneMode(LevelIDs_StationSquare, GET_ACT(LevelAndActIDs_StationSquare6));
        _showExitMenuTwinkleCircuit = 0;
        return;
    }

    _twinkleCircuitResultsMaybeHook.Original(tp);
}
