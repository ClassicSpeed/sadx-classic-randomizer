#include "WorldStateManager.h"


WorldStateManager::WorldStateManager(Options& options, Settings& settings, GameStatus& gameStatus): _options(options),
    _settings(settings), _gameStatus(gameStatus),
    _setObjectManager(SetObjectManager::Init(options, settings)),
    // _levelEntranceManager(LevelEntranceManager::Init(options, settings, gameStatus))
    _adventureFieldEntranceManager(AdventureFieldEntranceManager::Init(options))
{
    _collisionCubeHook.Hook(OnCollisionCube);
    //TODO: Undo
    // _isStationDoorOpenHook.Hook(OnIsStationDoorOpen);
    // _isHotelDoorOpenHook.Hook(OnIsHotelDoorOpen);
    _isCasinoHotelDoorOpenHook.Hook(OnIsCasinoHotelDoorOpen);
    _isCasinoStationDoorOpenHook.Hook(OnIsCasinoStationDoorOpen);
    _mysticRuinsKeyHook.Hook(OnMysticRuinsKey);
    _employeeCardHook.Hook(OnEmployeeCard);
    _twinkleCircuitResultsMaybeHook.Hook(OnTwinkleCircuitResultsMaybe);
    _isWindyValleyOpenHook.Hook(OnIsWindyValleyOpen);
    _isAngelIslandOpenHook.Hook(OnIsAngelIslandOpen);
    _preventKeyStoneFromSpawningHook.Hook(OnPreventKeyStoneFromSpawning);


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

    // if (Current_CharObj2 != nullptr && EntityData1Ptrs[0] != nullptr)
    //     _levelEntranceManager.ShowLevelEntranceArrows();

    _setObjectManager.OnFrame();
    _adventureFieldEntranceManager.ShowLevelEntranceArrows();
}

void WorldStateManager::SetLevelEntrances()
{
    // _levelEntranceManager.SetLevelEntrances();
}

void WorldStateManager::UpdateVisitedLevels(const int visitedLevel)
{
    // _levelEntranceManager.UpdateVisitedLevels(visitedLevel);
}

void WorldStateManager::OnCollisionCube(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1
        && _instance->_gameStatus.unlock.keyDynamite)
    {
        //We find the cube collision that we created for the dynamite and delete it
        if (IsNearPosition(tp->twp->pos, -393, 120, 890))
            FreeTask(tp);
    }
    else
        _collisionCubeHook.Original(tp);
}

BOOL WorldStateManager::OnIsStationDoorOpen()
{
    return _instance->_gameStatus.unlock.keyStationFrontKey;
}

BOOL WorldStateManager::OnIsHotelDoorOpen()
{
    return _instance->_gameStatus.unlock.keyHotelFrontKey;
}

BOOL WorldStateManager::OnIsCasinoHotelDoorOpen()
{
    if (_instance->_options.adventureFieldRandomized)
        return _isCasinoHotelDoorOpenHook.Original();
    return _instance->_gameStatus.unlock.keyHotelBackKey;
}

BOOL WorldStateManager::OnIsCasinoStationDoorOpen()
{
    return _instance->_gameStatus.unlock.keyStationBackKey;
}


void WorldStateManager::OnMysticRuinsKey(task* tp)
{
    // We prevent the wind stone from spawning if the player doesn't have the item
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1
        && !_instance->_gameStatus.unlock.keyWindStone)
        if (IsNearPosition(tp->twp->pos, 1392.5, 191.5, 863.5))
            return;

    _mysticRuinsKeyHook.Original(tp);
}

void WorldStateManager::OnEmployeeCard(task* tp)
{
    // We prevent the Employee card from spawning if the player doesn't have the item
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4
        && !_instance->_gameStatus.unlock.keyEmployeeCard
    )
        return;
    _employeeCardHook.Original(tp);
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

// TODO: Separate key items from story flags

// Handles the Windy Valley entrance
// Makes Sonic, Tails and Gamma use the winds stone
BOOL WorldStateManager::OnIsWindyValleyOpen()
{
    //TODO: Test if this works
    return _isWindyValleyOpenHook.Original() && _instance->_gameStatus.unlock.keyWindStone;
}

BOOL WorldStateManager::OnIsAngelIslandOpen()
{
    return _instance->_gameStatus.unlock.keyDynamite;
}

BOOL WorldStateManager::OnPreventKeyStoneFromSpawning(int a1)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2
        && (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Knuckles
            || CurrentCharacter == Characters_Gamma))
    {
        return _instance->_gameStatus.unlock.keyIceStone && _preventKeyStoneFromSpawningHook.Original(a1);
    }

    return _preventKeyStoneFromSpawningHook.Original(a1);
}
