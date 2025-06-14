#include "AdventureFieldEntranceManager.h"


AdventureFieldEntranceManager::AdventureFieldEntranceManager(Options& options): _options(options),
    _adventureFieldEntranceMap(AdventureFieldEntranceMap::Init()),
    _doorIndicatorManager(DoorIndicatorManager::Init())
{
    _setNextLevelAndActCutsceneModeHook.Hook(OnSetNextLevelAndActCutsceneMode);
    _getEntranceSs.Hook(OnGetEntranceSs);

    _isBarricadeGoneHook.Hook(OnIsBarricadeGone);
    _isStationDoorOpenHook.Hook(OnIsStationDoorOpen);
    _isHotelDoorOpenHook.Hook(OnIsHotelDoorOpen);
    _twinkleParkLobbyDoorFromStationHook.Hook(OnTwinkleParkLobbyDoorFromStation);
    _ssBoxLoadHook.Hook(OnSsBoxLoad);
    _elevatorOutHook.Hook(OnElevatorOut);
    _elevatorInSceneChangeHook.Hook(OnElevatorInSceneChange);

    //Avoid the distance check for the Twinkle Park door
    WriteData<1>((void*)0x63E737, 0xEB);
}


void AdventureFieldEntranceManager::OnSetNextLevelAndActCutsceneMode(const Uint8 level, const Uint8 act)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _setNextLevelAndActCutsceneModeHook.Original(level, act);

    PrintDebug("------AdventureFieldEntranceManager: Setting next level and act to %d, %d \n", level, act);
    AdventureFieldEntrance* newEntrance = _instance->_adventureFieldEntranceMap.GetNewConnection(
        GET_LEVEL_ACT(CurrentLevel, CurrentAct),GET_LEVEL_ACT(level, act));


    if (newEntrance != nullptr)
    {
        PrintDebug("------AdventureFieldEntranceManager: Found new entrance %d, %d \n",
                   GET_LEVEL(newEntrance->levelAndActId), GET_ACT(newEntrance->levelAndActId));
        _setNextLevelAndActCutsceneModeHook.Original(
            GET_LEVEL(newEntrance->levelAndActId), GET_ACT(newEntrance->levelAndActId));
        SetEntranceNumber(newEntrance->entranceNumber);
        return;
    }
    _setNextLevelAndActCutsceneModeHook.Original(level, act);
}

void AdventureFieldEntranceManager::OnGetEntranceSs(taskwk* twp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _getEntranceSs.Original(twp);

    if (GET_LEVEL_ACT(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare3)
    {
        if (GetLevelEntranceID() == 1)
        {
            twp->pos = {395, -120, 1200};
            twp->ang = {0, 0xC000, 0};
            return;
        }
    }
    _getEntranceSs.Original(twp);
}


bool AdventureFieldEntranceManager::IsDoorOpen(const EntranceId entranceId)
{
    //TODO: Implement the logic to check if the door is open based on the entranceId
    return true;
}

bool AdventureFieldEntranceManager::ShowDisableDoorIndicator(const EntranceId entranceId)
{
    //TODO: Implement the logic to check if the indicator should be shown based on the entranceId
    return !IsDoorOpen(entranceId);
}


void AdventureFieldEntranceManager::ShowLevelEntranceArrows()
{
    for (AdventureFieldEntrance adventureFieldEntrance : _adventureFieldEntranceMap.GetEntrances())
    {
        if (CurrentStageAndAct != adventureFieldEntrance.levelAndActId)
            continue;

        if (!ShowDisableDoorIndicator(adventureFieldEntrance.entranceId))
            continue;

        _doorIndicatorManager.DrawDisable(adventureFieldEntrance.indicatorPosition,
                                          adventureFieldEntrance.indicatorAngle);
    }
}


// -------- Function hooks for gating the world --------

BOOL AdventureFieldEntranceManager::OnIsBarricadeGone()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isBarricadeGoneHook.Original();

    if (GET_LEVEL_ACT(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4)
        return _instance->IsDoorOpen(SsMainToCityHall);

    return _instance->IsDoorOpen(CityHallToSsMain);
}

int AdventureFieldEntranceManager::OnIsStationDoorOpen()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isStationDoorOpenHook.Original();

    if (GET_LEVEL_ACT(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4)
        return _instance->IsDoorOpen(SsMainToStation);

    return _instance->IsDoorOpen(StationToSsMain);
}

BOOL AdventureFieldEntranceManager::OnIsHotelDoorOpen()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isHotelDoorOpenHook.Original();

    if (GET_LEVEL_ACT(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4)
        return _instance->IsDoorOpen(SsMainToHotel);

    return _instance->IsDoorOpen(HotelToSsMain);
}


TaskFunc(SomethingAboutTPDoor, 0x63E670);


void AdventureFieldEntranceManager::OnTwinkleParkLobbyDoorFromStation(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _twinkleParkLobbyDoorFromStationHook.Original(tp);

    // return _twinkleParkLobbyDoorFromStationHook.Original(tp);
    const bool isDoorOpen = _instance->IsDoorOpen(SsMainToTwinkleParkLobby);
    if (!isDoorOpen)
        return _twinkleParkLobbyDoorFromStationHook.Original(tp);


    if (IsPlayerInsideSphere(&tp->twp->pos, 30.0))
    {
        tp->exec = SomethingAboutTPDoor;
        PlaySound(530, 0, 0, 0);
    }
    _twinkleParkLobbyDoorFromStationHook.Original(tp);
}

//We make the box behave like it does for Big
void AdventureFieldEntranceManager::OnSsBoxLoad(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _ssBoxLoadHook.Original(tp);

    // Change jnz to jz
    WriteData<1>((void*)0x636B84, 0x74);
    // Change cmp eax, 7 to cmp eax, 9
    WriteData<1>((void*)0x636B83, 0x09);

    return _ssBoxLoadHook.Original(tp);
}

void AdventureFieldEntranceManager::OnElevatorOut(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _elevatorOutHook.Original(tp);

    OEleboxIn(reinterpret_cast<ObjectMaster*>(tp));
}

int AdventureFieldEntranceManager::OnElevatorInSceneChange(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _elevatorInSceneChangeHook.Original(tp);

    if (GET_LEVEL_ACT(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare3)
    {
        // From Sewers to SSMain
        WriteData<1>((void*)0x63D7DC, 0x02); //Entrance
        WriteData<1>((void*)0x63D7E5, LevelIDs_StationSquare); //Level
        WriteData<1>((void*)0x63D7E3, 0x03); //Act
    }
    else if (IsNearPosition(tp->twp->pos, 400, 45, 1445))
    {
        // From SSMain to Sewers
        WriteData<1>((void*)0x63D7DC, 0x01); //Entrance
        WriteData<1>((void*)0x63D7E5, LevelIDs_StationSquare); //Level
        WriteData<1>((void*)0x63D7E3, 0x02); //Act
    }
    else
    {
        // SpeedHighway
        WriteData<1>((void*)0x63D7DC, 0x02); //Entrance
        WriteData<1>((void*)0x63D7E5, LevelIDs_SpeedHighway); //Level
        if (CurrentCharacter == Characters_Knuckles)
            WriteData<1>((void*)0x63D7E3, 0x02); //Act
        else
            WriteData<1>((void*)0x63D7E3, 0x00); //Act
    }
    return _elevatorInSceneChangeHook.Original(tp);
}
