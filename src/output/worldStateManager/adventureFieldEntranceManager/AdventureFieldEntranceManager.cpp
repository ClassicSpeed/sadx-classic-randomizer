#include "AdventureFieldEntranceManager.h"

UsercallFunc(int, twinkleCircuitDoorHook, (char tpChar), (tpChar), 0x63F810, rEAX, rESI);
UsercallFunc(int, twinkleParkDoorHook, (char tpChar), (tpChar), 0x63EA90, rEAX, rESI);
UsercallFunc(signed int, mrCartHook, (task* tp), (tp), 0x53DC60, rEAX, rESI);

AdventureFieldEntranceManager::AdventureFieldEntranceManager(Options& options): _options(options),
    _adventureFieldEntranceMap(AdventureFieldEntranceMap::Init()),
    _doorIndicatorManager(DoorIndicatorManager::Init())
{
    _setNextLevelAndActCutsceneModeHook.Hook(OnSetNextLevelAndActCutsceneMode);
    _getEntranceSs.Hook(OnGetEntranceSs);

    _isBarricadeGoneHook.Hook(OnIsBarricadeGone);
    _wallMainHook.Hook(OnWallMain);
    _ssCarMainHook.Hook(OnSsCarMain);
    _isStationDoorOpenHook.Hook(OnIsStationDoorOpen);
    _isHotelFrontDoorOpenHook.Hook(OnIsHotelFrontDoorOpen);
    _isHotelBackDoorOpenHook.Hook(OnIsHotelBackDoorOpen);
    _twinkleParkLobbyDoorFromStationHook.Hook(OnTwinkleParkLobbyDoorFromStation);
    _twinkleParkLobbyDoorToStationHook.Hook(OnTwinkleParkLobbyDoorToStation);
    _ssBoxLoadHook.Hook(OnSsBoxLoad);
    _elevatorInHook.Hook(OnElevatorIn);
    _elevatorOutHook.Hook(OnElevatorOut);
    _elevatorInSceneChangeHook.Hook(OnElevatorInSceneChange);
    _sewerCarHandlePickUpHook.Hook(OnSewerCarHandlePickUp);
    _spawnSewerCarHook.Hook(OnSpawnSewerCar);
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
    _isCasinoOpenHook.Hook(OnIsCasinoOpen);
    _isTrainInServiceHook.Hook(OnIsTrainInService);
    _ecWarpMainHook.Hook(OnEcWarpMain);
    _openToyShopDoorMainHook.Hook(OnOpenToyShopDoorMain);
    _isCityHallDoorOpenHook.Hook(OnIsCityHallDoorOpen);
    _loadKnucklesBarricadeHook.Hook(OnLoadKnucklesBarricade);
    twinkleCircuitDoorHook.Hook(OnTwinkleCircuitDoor);
    twinkleParkDoorHook.Hook(OnTwinkleParkDoor);
    _mrRaftMainHook.Hook(OnMrRaftMain);
    mrCartHook.Hook(OnMrCartMain);
    _isAngelIslandOpenHook.Hook(OnIsAngelIslandOpen);


    //Allows players to return to the adventure field when quitting boss fights
    WriteData<1>((void*)0x415F46, 0x19);


    // Change the comparison value from 3 to 9
    WriteData<1>((void*)0x638BF6, 0x09);
    // Change the jump from jz (0x74) to jnz (0x75)
    WriteData<1>((void*)0x638C00, 0x75);
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
    else if (GET_LEVEL_ACT(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare6)
    {
        if (GetLevelEntranceID() == 0)
        {
            twp->pos = {688.13f, 50, 1771.5f};
            twp->ang = {0, 0, 0};
            return;
        }
    }
    else if (GET_LEVEL_ACT(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4)
    {
        if (GetLevelEntranceID() == 4)
        {
            twp->pos = {566.5, 50, 1771.5};
            twp->ang = {0, 0x8000, 0};
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


void AdventureFieldEntranceManager::OnWallMain(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _wallMainHook.Original(tp);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1)
    {
        //We find the city hall to ssmain wall and delete it
        if (_instance->IsDoorOpen(CityHallToSsMain) && IsNearPosition(tp->twp->pos, 622.61f, 0, 878))
            return FreeTask(tp);
    }
    return _wallMainHook.Original(tp);
}

void AdventureFieldEntranceManager::OnSsCarMain(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _ssCarMainHook.Original(tp);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1 && !_instance->IsDoorOpen(CityHallToSsMain))
        return FreeTask(tp);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4 && !_instance->IsDoorOpen(SsMainToCityHall))
        return FreeTask(tp);

    return _ssCarMainHook.Original(tp);
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

TaskFunc(SomethingAboutTPDoorA, 0x63E670);

void AdventureFieldEntranceManager::OnTwinkleParkLobbyDoorFromStation(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _twinkleParkLobbyDoorFromStationHook.Original(tp);

    //We disable the distance check, and we manually check if the entrance is accessible
    WriteData<1>((void*)0x63E737, 0xEB);

    const bool isDoorOpen = _instance->IsDoorOpen(SsMainToTwinkleParkLobby);
    if (!isDoorOpen)
        return _twinkleParkLobbyDoorFromStationHook.Original(tp);


    if (IsPlayerInsideSphere(&tp->twp->pos, 30.0))
    {
        tp->exec = SomethingAboutTPDoorA;
        PlaySound(530, 0, 0, 0);
    }
    _twinkleParkLobbyDoorFromStationHook.Original(tp);
}

TaskFunc(SomethingAboutTPDoorB, 0x63E3B0);

void AdventureFieldEntranceManager::OnTwinkleParkLobbyDoorToStation(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _twinkleParkLobbyDoorToStationHook.Original(tp);


    //We disable the distance check, and we manually check if the entrance is accessible
    WriteData<1>((void*)0x63E477, 0xEB);
    const bool isDoorOpen = _instance->IsDoorOpen(TwinkleParkLobbyToSsMain);
    if (!isDoorOpen)
        return _twinkleParkLobbyDoorToStationHook.Original(tp);


    if (IsPlayerInsideSphere(&tp->twp->pos, 20.0))
    {
        tp->exec = SomethingAboutTPDoorB;
        PlaySound(530, 0, 0, 0);
    }
    _twinkleParkLobbyDoorToStationHook.Original(tp);
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

    _elevatorInHook.Original(tp);
}

void AdventureFieldEntranceManager::OnElevatorIn(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _elevatorInHook.Original(tp);

    if (GET_LEVEL_ACT(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare3 && !_instance->IsDoorOpen(
        SewersToSsMain))
        return _elevatorOutHook.Original(tp);

    _elevatorInHook.Original(tp);
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


TaskFunc(DrawCar, 0x639790);

void AdventureFieldEntranceManager::OnSewerCarHandlePickUp(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _sewerCarHandlePickUpHook.Original(tp);

    if (_instance->IsDoorOpen(CityHallToSewers))
        return _sewerCarHandlePickUpHook.Original(tp);

    //Big won't be able to pick up the car 
    return DrawCar(tp);
}

BOOL AdventureFieldEntranceManager::OnSpawnSewerCar()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _spawnSewerCarHook.Original();

    if (CurrentCharacter == Characters_Big)
        return false;

    return _instance->IsDoorOpen(CityHallToSewers);
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

    // Sewers-toy shop door
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare3
        && IsNearPosition(tp->twp->pos, 401, -2, 632, 3))
    {
        if (_instance->IsDoorOpen(SewersToCityHall))
        {
            if (CurrentCharacter == Characters_Big)
                tp->twp->pos = {418, 0, 635};
        }
        else
        {
            return;
        }
    }


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

    if (!_instance->IsDoorOpen(SsMainToEcOutside))
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


BOOL AdventureFieldEntranceManager::OnIsCasinoOpen()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isCasinoOpenHook.Original();

    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
        return _isCasinoOpenHook.Original() && _instance->IsDoorOpen(StationToCasinopolis);

    if (CurrentCharacter == Characters_Knuckles)
        return GetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_ENTRANCE_CASINO)) && _instance->IsDoorOpen(
            StationToCasinopolis);

    return _instance->IsDoorOpen(StationToCasinopolis);
}


BOOL AdventureFieldEntranceManager::OnIsTrainInService()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isTrainInServiceHook.Original();

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare2)
        return _instance->IsDoorOpen(StationToMrMain);

    return _instance->IsDoorOpen(MrMainToSsMain);
}


EntranceId GetBossEntrance()
{
    switch (levelact(CurrentLevel, CurrentAct))
    {
    case LevelAndActIDs_StationSquare2:
        return StationToEggWalker;
    case LevelAndActIDs_StationSquare1:
        return CityHallToChaos0;
    case LevelAndActIDs_MysticRuins1:
        if (EntityData1Ptrs[0]->Position.y < 100)
            return MrMainToChaos4;
        if (EntityData1Ptrs[0]->Position.y < 150)
            return MrMainToEggHornet;
        return MrMainToSkyChase1;
    default:
        return InvalidEntranceId;
    }
}

void AdventureFieldEntranceManager::OnEcWarpMain(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _ecWarpMainHook.Original(tp);

    if (_instance->IsDoorOpen(GetBossEntrance()))
        return _ecWarpMainHook.Original(tp);

    tp->twp->wtimer = 0;
    _ecWarpMainHook.Original(tp);
}


TaskFunc(ClosedToyShopDoorMain, 0x63E9A0);

void AdventureFieldEntranceManager::OnOpenToyShopDoorMain(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _openToyShopDoorMainHook.Original(tp);

    if (_instance->IsDoorOpen(SewersToCityHall))
        return _openToyShopDoorMainHook.Original(tp);

    ClosedToyShopDoorMain(tp);
}


BOOL AdventureFieldEntranceManager::OnIsCityHallDoorOpen()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isCityHallDoorOpenHook.Original();

    return _instance->IsDoorOpen(CityHallToSpeedHighway);
}

//We don't create Knuckles barricade if he doesn't have access to the level
void AdventureFieldEntranceManager::OnLoadKnucklesBarricade(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _loadKnucklesBarricadeHook.Original(tp);

    if (CurrentCharacter == Characters_Knuckles && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1)
        if (!_instance->IsDoorOpen(CityHallToSpeedHighway))
            return FreeTask(tp);

    _loadKnucklesBarricadeHook.Original(tp);
}

int AdventureFieldEntranceManager::OnTwinkleCircuitDoor(const char character)
{
    if (!_instance->_options.adventureFieldRandomized)
        return twinkleCircuitDoorHook.Original(character);

    return _instance->IsDoorOpen(TwinkleParkLobbyToTwinkleCircuit);
}

int AdventureFieldEntranceManager::OnTwinkleParkDoor(const char character)
{
    if (!_instance->_options.adventureFieldRandomized)
        return twinkleParkDoorHook.Original(character);

    return _instance->IsDoorOpen(TwinkleParkLobbyToTwinklePark);
}

void AdventureFieldEntranceManager::OnMrRaftMain(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _mrRaftMainHook.Original(tp);

    if (!_instance->IsDoorOpen(MrMainToEcOutside))
        return FreeTask(tp);
    return _mrRaftMainHook.Original(tp);
}

int AdventureFieldEntranceManager::OnMrCartMain(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return mrCartHook.Original(tp);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3)
        return _instance->IsDoorOpen(JungleToMrMain);
    if (tp->twp->scl.x > 0)
        return _instance->IsDoorOpen(MrMainToMrChaoGarden);
    return _instance->IsDoorOpen(MrMainToJungle);
}


BOOL AdventureFieldEntranceManager::OnIsAngelIslandOpen()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isAngelIslandOpenHook.Original();
    return _instance->IsDoorOpen(MrMainToAngelIsland);
}
