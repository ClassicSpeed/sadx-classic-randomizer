#include "AdventureFieldEntranceManager.h"


AdventureFieldEntranceManager::AdventureFieldEntranceManager(Options& options): _options(options),
    _adventureFieldEntranceMap(AdventureFieldEntranceMap::Init()),
    _doorIndicatorManager(DoorIndicatorManager::Init())
{
    _setNextLevelAndActCutsceneModeHook.Hook(OnSetNextLevelAndActCutsceneMode);
    _getEntranceSs.Hook(OnGetEntranceSs);

    _isBarricadeGoneHook.Hook(OnIsBarricadeGone);
    _isStationDoorOpenHook.Hook(OnIsStationDoorOpen);
    _isHotelFrontDoorOpenHook.Hook(OnIsHotelFrontDoorOpen);
    _isHotelBackDoorOpenHook.Hook(OnIsHotelBackDoorOpen);
    _twinkleParkLobbyDoorFromStationHook.Hook(OnTwinkleParkLobbyDoorFromStation);
    _ssBoxLoadHook.Hook(OnSsBoxLoad);
    _elevatorOutHook.Hook(OnElevatorOut);
    _elevatorInSceneChangeHook.Hook(OnElevatorInSceneChange);
    _sewerCarMainHook.Hook(OnSewerCarMain);
    _collisionCubeHook.Hook(OnCollisionCube);
    _collisionSphereHook.Hook(OnCollisionSphere);
    _sceneChangeMainStationSquareHook.Hook(OnSceneChangeMainStationSquare);
    _characterUpgradeMainHook.Hook(OnCharacterUpgradeMain);
    _ssBoatMainHook.Hook(OnSsBoatMain);
    _isSpeedHighwayShutterOpenHook.Hook(OnIsSpeedHighwayShutterOpen);
    _loadSpeedHighwayShutterHook.Hook(OnLoadSpeedHighwayShutter);
    _loadSpeedHighwayShutter2Hook.Hook(OnLoadSpeedHighwayShutter2);
    _isEmeraldCoastOpenHook.Hook(OnIsEmeraldCoastOpen);
    _loadEmeraldCoastGateTargetsHook.Hook(OnLoadEmeraldCoastGateTargets);
    _isChaos2DoorOpenHook.Hook(OnIsChaos2DoorOpen);
    _loadHotelElevatorHook.Hook(OnLoadHotelElevator);

    //Avoid the distance check for the Twinkle Park door
    WriteData<1>((void*)0x63E737, 0xEB);
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

BOOL AdventureFieldEntranceManager::OnIsHotelFrontDoorOpen()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isHotelFrontDoorOpenHook.Original();

    if (GET_LEVEL_ACT(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4)
        return _instance->IsDoorOpen(SsMainToHotel);

    return _instance->IsDoorOpen(HotelToSsMain);
}

BOOL AdventureFieldEntranceManager::OnIsHotelBackDoorOpen()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isHotelBackDoorOpenHook.Original();

    if (GET_LEVEL_ACT(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare2)
        return _instance->IsDoorOpen(StationToHotel);

    return _instance->IsDoorOpen(HotelToStation);
}

TaskFunc(SomethingAboutTPDoor, 0x63E670);

void AdventureFieldEntranceManager::OnTwinkleParkLobbyDoorFromStation(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _twinkleParkLobbyDoorFromStationHook.Original(tp);

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

    if (GET_LEVEL_ACT(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4 && !_instance->IsDoorOpen(
        SsMainToSewers))
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

void AdventureFieldEntranceManager::OnSewerCarMain(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _sewerCarMainHook.Original(tp);

    FreeTask(tp);
}

void AdventureFieldEntranceManager::OnCollisionCube(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _collisionCubeHook.Original(tp);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare3)
    {
        //We find the cube collision that prevent Big from going up the sewers and delete it
        if (IsNearPosition(tp->twp->pos, 415, -70, 860, 30))
            return FreeTask(tp);
    }
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1)
    {
        //We find the cube collision that prevent Gamma from entering the sewers and delete it
        if (IsNearPosition(tp->twp->pos, 359, -26, 956))
            return FreeTask(tp);
    }

    _collisionCubeHook.Original(tp);
}

void AdventureFieldEntranceManager::OnCollisionSphere(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _collisionSphereHook.Original(tp);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1)
    {
        //We find the sphere collision that prevent Gamma from entering the sewers and delete it
        if (IsNearPosition(tp->twp->pos, 367, -8, 963))
            return FreeTask(tp);
    }

    _collisionSphereHook.Original(tp);
}

void AdventureFieldEntranceManager::OnSceneChangeMainStationSquare(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _sceneChangeMainStationSquareHook.Original(tp);

    // Big sewers-toy shop door
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare3 && CurrentCharacter == Characters_Big
        && IsNearPosition(tp->twp->pos, 401, -2, 632, 2))
        tp->twp->pos = {418, 0, 635};


    _sceneChangeMainStationSquareHook.Original(tp);
}

void AdventureFieldEntranceManager::OnCharacterUpgradeMain(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _characterUpgradeMainHook.Original(tp);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare3 && CurrentCharacter == Characters_Big)
        return FreeTask(tp);
    return _characterUpgradeMainHook.Original(tp);
}

void AdventureFieldEntranceManager::OnSsBoatMain(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _ssBoatMainHook.Original(tp);

    if (!_instance->IsDoorOpen(CityHallToSsMain))
        return FreeTask(tp);
    return _ssBoatMainHook.Original(tp);
}


// Speed Highway
//TODO: Check/move the unlock part to the main manager
BOOL AdventureFieldEntranceManager::OnIsSpeedHighwayShutterOpen()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isSpeedHighwayShutterOpenHook.Original();
    return _instance->IsDoorOpen(SsMainToSpeedHighway);
}

void AdventureFieldEntranceManager::OnLoadSpeedHighwayShutter(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        _loadSpeedHighwayShutterHook.Original(tp);
    //TODO: Animate instead of removing the task
    if (_instance->IsDoorOpen(SsMainToSpeedHighway))
        return FreeTask(tp);

    _loadSpeedHighwayShutterHook.Original(tp);
}

void AdventureFieldEntranceManager::OnLoadSpeedHighwayShutter2(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _loadSpeedHighwayShutter2Hook.Original(tp);
    //TODO: Animate instead of removing the task
    if (_instance->IsDoorOpen(SsMainToSpeedHighway))
        return FreeTask(tp);

    _loadSpeedHighwayShutter2Hook.Original(tp);
}

BOOL AdventureFieldEntranceManager::OnIsEmeraldCoastOpen()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isEmeraldCoastOpenHook.Original();

    if (CurrentCharacter == Characters_Gamma)
        return false;

    return _instance->IsDoorOpen(HotelToEmeraldCoast);
}

void AdventureFieldEntranceManager::OnLoadEmeraldCoastGateTargets(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _loadEmeraldCoastGateTargetsHook.Original(tp);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
        && !_instance->IsDoorOpen(HotelToEmeraldCoast))
        FreeTask(tp);
    else
        _loadEmeraldCoastGateTargetsHook.Original(tp);
}


BOOL AdventureFieldEntranceManager::OnIsChaos2DoorOpen()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isChaos2DoorOpenHook.Original();
    return _instance->IsDoorOpen(HotelToChaos2);
}

TaskFunc(ClosedElevatorMain, 0x6391F0);

void AdventureFieldEntranceManager::OnLoadHotelElevator(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _loadHotelElevatorHook.Original(tp);

    _loadHotelElevatorHook.Original(tp);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
        && !_instance->IsDoorOpen(HotelToSsChaoGarden))
        tp->exec = ClosedElevatorMain;
}
