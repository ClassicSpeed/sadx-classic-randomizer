#include "AdventureFieldEntranceManager.h"

UsercallFunc(int, twinkleCircuitDoorHook, (char tpChar), (tpChar), 0x63F810, rEAX, rESI);
UsercallFunc(int, twinkleParkDoorHook, (char tpChar), (tpChar), 0x63EA90, rEAX, rESI);
UsercallFunc(signed int, mrCartHook, (task* tp), (tp), 0x53DC60, rEAX, rESI);
UsercallFuncVoid(sceneChangeMrHook, (int a1), (a1), 0x539220, rEBX);
UsercallFuncVoid(sceneChangeECInsideHook, (int a1, int a2), (a1,a2), 0x52D690, rEAX, rECX);
UsercallFunc(int, eggCarrierInsideEggDoorHook, (const taskwk* twp), (twp), 0x52B420, rEAX, rESI);
UsercallFunc(int, eggCarrierOutsideEggDoorHook, (const taskwk* twp), (twp), 0x524070, rEAX, rESI);
UsercallFunc(int, skyDeckDoorHook, (taskwk* twp), (twp), 0x51DEB0, rEAX, rESI);

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
    _mysticRuinsKeyHook.Hook(OnMysticRuinsKey);
    _mysticRuinsLockHook.Hook(OnMysticRuinsLock);
    _isWindyValleyOpenHook.Hook(OnIsWindyValleyOpen);
    _preventMrStoneSpawnHook.Hook(OnPreventMrStoneSpawn);
    _getCharacterIdHook.Hook(OnGetCharacterId);
    _pastSceneChangeHook.Hook(OnPastSceneChange);
    _isFinalEggEggmanDoorOpenHook.Hook(OnIsFinalEggEggmanDoorOpen);
    _isMonkeyDoorOpenHook.Hook(OnIsMonkeyDoorOpen);
    _loadMonkeyCageHook.Hook(OnLoadMonkeyCage);
    _changeSceneCave2Hook.Hook(OnChangeSceneCave2);
    _isLostWorldFrontEntranceOpenHook.Hook(OnIsLostWorldFrontEntranceOpen);
    _isSandHillOpenHook.Hook(OnIsSandHillOpen);
    _loadSceneChangeMrHook.Hook(OnLoadSceneChangeMr);
    sceneChangeMrHook.Hook(OnSceneChangeMr);
    _isLostWorldBackEntranceOpenHook.Hook(OnIsLostWorldBackEntranceOpen);
    _loadLongLadderMrHook.Hook(OnLoadLongLadderMr);
    sceneChangeECInsideHook.Hook(OnSceneChangeEcInside);
    eggCarrierInsideEggDoorHook.Hook(OnEggCarrierInsideEggDoor);
    eggCarrierOutsideEggDoorHook.Hook(OnEggCarrierOutsideEggDoor);
    skyDeckDoorHook.Hook(OnSkyDeckDoor);


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
        GET_LEVEL_ACT(CurrentLevel, CurrentAct), GET_LEVEL_ACT(level, act), _instance->_isEggCarrierTransformed);


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
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        //We find the angel island to mrmain wall and delete it
        if (_instance->IsDoorOpen(AngelIslandToMrMain) && IsNearPosition(tp->twp->pos, -22.45f, 12.04f, 11.62f))
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
    case LevelAndActIDs_MysticRuins2:
        return AngelIslandToPastAltar;
    case LevelAndActIDs_Past2:
        return PastAltarToAngelIsland;
    case LevelAndActIDs_MysticRuins4:
        return FinalEggTowerToBetaEggViper;
    case LevelAndActIDs_EggCarrierOutside1:
        if (EntityData1Ptrs[0]->Position.z > -500)
            return EcOutsideToChaos6ZeroBeta;
        return EcOutsideToSkyChase2;
    case LevelAndActIDs_EggCarrierOutside2:
        if (EntityData1Ptrs[0]->Position.z > -500)
            return BridgeToChaos6ZeroBeta;
        return BridgeToSkyChase2;
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


void AdventureFieldEntranceManager::OnMysticRuinsKey(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _mysticRuinsKeyHook.Original(tp);


    // We don't spawn the golden/silver keys for knuckles if he can't enter LostWorld
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 && CurrentCharacter == Characters_Knuckles)
    {
        if (!_instance->IsDoorOpen(JungleToLostWorldAlternative))
            return;

        return _mysticRuinsKeyHook.Original(tp);
    }


    // We prevent the wind stone from spawning if the player cannot access the Windy Valley entrance
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1
        && !_instance->IsDoorOpen(MrMainToWindyValley))
        if (IsNearPosition(tp->twp->pos, 1392.5, 191.5, 863.5))
            return;

    const int bufferCharacter = CurrentCharacter;
    CurrentCharacter = Characters_Sonic;
    _mysticRuinsKeyHook.Original(tp);
    CurrentCharacter = bufferCharacter;
}

void AdventureFieldEntranceManager::OnMysticRuinsLock(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _mysticRuinsLockHook.Original(tp);
    const int bufferCharacter = CurrentCharacter;
    CurrentCharacter = Characters_Sonic;
    _mysticRuinsLockHook.Original(tp);
    CurrentCharacter = bufferCharacter;
}


BOOL AdventureFieldEntranceManager::OnIsWindyValleyOpen()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isWindyValleyOpenHook.Original();

    return EventFlagArray[FLAG_SONIC_MR_WINDYSTONE];
}

BOOL AdventureFieldEntranceManager::OnPreventMrStoneSpawn()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _preventMrStoneSpawnHook.Original();
    return false;
}

int AdventureFieldEntranceManager::OnGetCharacterId(char index)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _getCharacterIdHook.Original(index);
    return CurrentCharacter;
}

void AdventureFieldEntranceManager::OnPastSceneChange(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _pastSceneChangeHook.Original(tp);

    // Past Main
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_Past1
        && IsNearPosition(tp->twp->pos, 1.907, 13, 1512.719))
    {
        if (!_instance->IsDoorOpen(PastMainToPastAltar))
            return FreeTask(tp);
    }
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_Past2
        && IsNearPosition(tp->twp->pos, 223.44, -2, 1836.12))
    {
        if (!_instance->IsDoorOpen(PastAltarToPastMain))
            return FreeTask(tp);
    }

    _pastSceneChangeHook.Original(tp);
}


BOOL AdventureFieldEntranceManager::OnIsFinalEggEggmanDoorOpen(EntityData1* entity)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isFinalEggEggmanDoorOpenHook.Original(entity);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3)
        return _instance->IsDoorOpen(JungleToFinalEggTower);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && IsNearPosition(
        entity->Position, 0, 109, 175))
        return _instance->IsDoorOpen(FinalEggTowerToJungle);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && IsNearPosition(
        entity->Position, 0, 109, -175))
        return _instance->IsDoorOpen(FinalEggTowerToFinalEggAlternative);


    return _isFinalEggEggmanDoorOpenHook.Original(entity);
}


//Prevents the monkey from blocking the entrance to Red Mountain for knuckles
BOOL AdventureFieldEntranceManager::OnIsMonkeyDoorOpen(int a1)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1)
        return true;

    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Gamma
        || CurrentCharacter == Characters_Knuckles)
        return _isMonkeyDead(1) && _instance->_instance->IsDoorOpen(AngelIslandToRedMountain);

    //For everyone else, we return true if we are in the main mystic ruins area
    return _instance->_instance->IsDoorOpen(AngelIslandToRedMountain);
}

// We only load the monkey if it's needed for opening the door
void AdventureFieldEntranceManager::OnLoadMonkeyCage(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        if (CurrentCharacter == Characters_Tails || CurrentCharacter == Characters_Big
            || CurrentCharacter == Characters_Amy)
            return FreeTask(tp);
        if (!_instance->_instance->IsDoorOpen(AngelIslandToRedMountain))
            return FreeTask(tp);
    }
    _loadMonkeyCageHook.Original(tp);
}

void AdventureFieldEntranceManager::OnChangeSceneCave2(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _changeSceneCave2Hook.Original(tp);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2
        && IsNearPosition(tp->twp->pos, 56, -100, -13))
    {
        if (!_instance->IsDoorOpen(AngelIslandToMrMain))
            return FreeTask(tp);
    }

    _changeSceneCave2Hook.Original(tp);
}

BOOL AdventureFieldEntranceManager::OnIsLostWorldFrontEntranceOpen()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isLostWorldFrontEntranceOpenHook.Original();

    return _instance->IsDoorOpen(JungleToLostWorld);
}

BOOL AdventureFieldEntranceManager::OnIsSandHillOpen()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isSandHillOpenHook.Original();

    return _instance->IsDoorOpen(JungleToSandHill);
}

void AdventureFieldEntranceManager::OnLoadSceneChangeMr(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _loadSceneChangeMrHook.Original(tp);

    // Final Egg
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && tp->twp->ang.x == 3)
    {
        if (!_instance->IsDoorOpen(FinalEggTowerToFinalEgg))
        {
            return FreeTask(tp);
        }
    }

    _loadSceneChangeMrHook.Original(tp);
}


// MysticRuins
void AdventureFieldEntranceManager::OnSceneChangeMr(const int newScene)
{
    if (!_instance->_options.adventureFieldRandomized)
        sceneChangeMrHook.Original(newScene);


    // Ice Cap
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        if (newScene == 1)
        {
            if (_instance->IsDoorOpen(AngelIslandToIceCap))
            {
                return SetNextLevelAndAct_CutsceneMode(
                    GET_LEVEL(LevelAndActIDs_IceCap1), GET_ACT(LevelAndActIDs_IceCap1));
            }
            return;
        }
    }

    //  Final Egg 
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4)
    {
        if (newScene == 2)
        {
            if (_instance->IsDoorOpen(FinalEggTowerToFinalEggAlternative))
            {
                return SetNextLevelAndAct_CutsceneMode(
                    GET_LEVEL(LevelAndActIDs_FinalEgg3), GET_ACT(LevelAndActIDs_FinalEgg3));
            }
            return;
        }
        if (newScene == 3)
        {
            if (_instance->IsDoorOpen(FinalEggTowerToFinalEgg))
            {
                return SetNextLevelAndAct_CutsceneMode(
                    GET_LEVEL(LevelAndActIDs_FinalEgg1), GET_ACT(LevelAndActIDs_FinalEgg1));
            }
            return;
        }
    }

    // Lost world
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3)
    {
        if (newScene == 6)
        {
            if (_instance->IsDoorOpen(JungleToLostWorld))
            {
                return SetNextLevelAndAct_CutsceneMode(
                    GET_LEVEL(LevelAndActIDs_LostWorld1), GET_ACT(LevelAndActIDs_LostWorld1));
            }
            return;
        }
        if (newScene == 7)
        {
            if (_instance->IsDoorOpen(JungleToLostWorldAlternative))
            {
                return SetNextLevelAndAct_CutsceneMode(
                    GET_LEVEL(LevelAndActIDs_LostWorld2), GET_ACT(LevelAndActIDs_LostWorld2));
            }
            return;
        }
    }

    sceneChangeMrHook.Original(newScene);
}


//Makes knuckles able to enter the lost world using the keys and everyone without them
BOOL AdventureFieldEntranceManager::OnIsLostWorldBackEntranceOpen()
{
    if (!_instance->_options.adventureFieldRandomized)
        return _isLostWorldBackEntranceOpenHook.Original();

    if (!_instance->IsDoorOpen(JungleToLostWorldAlternative))
        return false;

    if (CurrentCharacter != Characters_Knuckles)
        return true;

    return EventFlagArray[FLAG_KNUCKLES_MR_REDCUBE] && EventFlagArray[FLAG_KNUCKLES_MR_BLUECUBE];
}


// Removed the ladder on Ice Cap
void AdventureFieldEntranceManager::OnLoadLongLadderMr(task* tp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return _loadLongLadderMrHook.Original(tp);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        if (!_instance->IsDoorOpen(AngelIslandToIceCap))
        {
            return FreeTask(tp);
        }
    }
    _loadLongLadderMrHook.Original(tp);
}


// HotShelter
void AdventureFieldEntranceManager::OnSceneChangeEcInside(int a1, int a2)
{
    if (!_instance->_options.adventureFieldRandomized)
        return sceneChangeECInsideHook.Original(a1, a2);


    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierInside2)
        return sceneChangeECInsideHook.Original(a1, a2);

    const int doorId = *(_DWORD*)(a1 + 20);
    if (doorId != 512)
        return sceneChangeECInsideHook.Original(a1, a2);


    camerahax_adventurefields();
    return SetNextLevelAndAct_CutsceneMode(
        GET_LEVEL(LevelAndActIDs_HotShelter1), GET_ACT(LevelAndActIDs_HotShelter1));
}


bool AdventureFieldEntranceManager::IsPlayerNearDoor(const taskwk* twp)
{
    const EntityData1* player = EntityData1Ptrs[0];
    const double dz = player->Position.z - twp->pos.z;
    const double dy = player->Position.y - twp->pos.y;
    const double dx = player->Position.x - twp->pos.x;
    const double distance = dx * dx + dy * dy + dz * dz;
    return squareroot(distance) <= 50.0;
}

int AdventureFieldEntranceManager::OnEggCarrierInsideEggDoor(const taskwk* twp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return eggCarrierInsideEggDoorHook.Original(twp);
    // Arsenal
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierInside1)
    {
        if (!_instance->IsDoorOpen(ArsenalToEcInside))
            return false;

        if (!IsPlayerNearDoor(twp))
            return false;
        return true;
    }
    //EC inside main
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierInside2)
    {
        // Middle door
        if (twp->smode == 6)
        {
            if (!_instance->IsDoorOpen(EcInsideToHotShelter))
                return false;

            if (!IsPlayerNearDoor(twp))
                return false;

            if (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big)
                return IsSwitchPressed(1);
            return true;
        }
        // Hedgehog hammer door
        if (twp->smode == 2)
        {
            if (!_instance->IsDoorOpen(EcInsideToHedgehogHammer))
                return false;

            if (!IsPlayerNearDoor(twp))
                return false;

            if (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big)
                return IsSwitchPressed(0);
            return true;
        }
        // Arsenal door
        if (twp->smode == 0 && IsNearPosition(twp->pos, 190, 80.1, 0))
        {
            if (!_instance->IsDoorOpen(EcInsideToArsenal))
                return false;
            if (!IsPlayerNearDoor(twp))
                return false;
            return true;
        }
        // Water Tank door
        if (twp->smode == 0 && IsNearPosition(twp->pos, -190, 80.1, -280))
        {
            if (!_instance->IsDoorOpen(EcInsideToWaterTank))
                return false;
            if (!IsPlayerNearDoor(twp))
                return false;
            return true;
        }
        return eggCarrierInsideEggDoorHook.Original(twp);
    }

    // Hedgehog hammer 
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierInside3)
    {
        if (twp->smode == 4)
        {
            if (!_instance->IsDoorOpen(HedgehogHammerToEcInside))
                return false;

            if (!IsPlayerNearDoor(twp))
                return false;
            return true;
        }
        if (twp->smode == 1)
        {
            if (!_instance->IsDoorOpen(HedgehogHammerToPrisonHall))
                return false;

            if (!IsPlayerNearDoor(twp))
                return false;
            return true;
        }
        return eggCarrierInsideEggDoorHook.Original(twp);
    }
    // Prison hall
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierInside4)
    {
        if (twp->smode == 1)
        {
            if (!_instance->IsDoorOpen(PrisonHallToHedgehogHammer))
                return false;

            if (!IsPlayerNearDoor(twp))
                return false;
            return true;
        }
        return eggCarrierInsideEggDoorHook.Original(twp);
    }

    // Arsenal
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierInside5)
    {
        if (!_instance->IsDoorOpen(WaterTankToEcInside))
            return false;

        if (!IsPlayerNearDoor(twp))
            return false;
        return true;
    }
    return eggCarrierInsideEggDoorHook.Original(twp);
}


int AdventureFieldEntranceManager::OnEggCarrierOutsideEggDoor(const taskwk* twp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return eggCarrierOutsideEggDoorHook.Original(twp);

    // EC outside 
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside1)
    {
        if (IsNearPosition(twp->pos, 0, 744.5, 1080.7))
        {
            if (!_instance->IsDoorOpen(EcOutsideToPool))
                return false;

            if (!IsPlayerNearDoor(twp))
                return false;
            return true;
        }

        if (IsNearPosition(twp->pos, 0, 740, 433))
        {
            if (!_instance->IsDoorOpen(EcOutsideToCaptainRoom))
                return false;

            if (!IsPlayerNearDoor(twp))
                return false;
            return true;
        }
    }
    // Deck (transformed)
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside3)
    {
        if (IsNearPosition(twp->pos, 0, 1536.5897, 3574.001))
        {
            if (!_instance->IsDoorOpen(DeckToPool))
                return false;

            if (!IsPlayerNearDoor(twp))
                return false;
            return true;
        }
        if (IsNearPosition(twp->pos, 0, 1710, 2918))
        {
            if (!_instance->IsDoorOpen(DeckToCaptainRoom))
                return false;

            if (!IsPlayerNearDoor(twp))
                return false;
            return true;
        }
    }
    // Captain's room
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside4)
    {
        if (!_instance->IsDoorOpen(CaptainRoomToEcOutside))
            return false;

        if (!IsPlayerNearDoor(twp))
            return false;
        return true;
    }
    // Pool
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside6)
    {
        if (!_instance->IsDoorOpen(PoolToEcOutside))
            return false;

        if (!IsPlayerNearDoor(twp))
            return false;
        return true;
    }

    return eggCarrierOutsideEggDoorHook.Original(twp);
}


int AdventureFieldEntranceManager::OnSkyDeckDoor(taskwk* twp)
{
    if (!_instance->_options.adventureFieldRandomized)
        return skyDeckDoorHook.Original(twp);

    if (!_instance->IsDoorOpen(BridgeToSkyDeck))
        return false;

    if (!IsPlayerNearDoor(twp))
        return false;
    return true;
}
