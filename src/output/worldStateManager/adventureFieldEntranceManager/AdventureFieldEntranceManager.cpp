#include "AdventureFieldEntranceManager.h"

UsercallFunc(int, twinkleCircuitDoorHook, (char tpChar), (tpChar), 0x63F810, rEAX, rESI);
UsercallFunc(int, twinkleParkDoorHook, (char tpChar), (tpChar), 0x63EA90, rEAX, rESI);
UsercallFunc(signed int, mrCartHook, (task* tp), (tp), 0x53DC60, rEAX, rESI);
UsercallFuncVoid(sceneChangeMrHook, (int a1), (a1), 0x539220, rEBX);
UsercallFuncVoid(sceneChangeECInsideHook, (int a1, int a2), (a1,a2), 0x52D690, rEAX, rECX);
UsercallFuncVoid(sceneChangeLogicECOusideHook, (int a1), (a1), 0x524FE0, rEAX);
UsercallFunc(int, eggCarrierInsideEggDoorHook, (const taskwk* twp), (twp), 0x52B420, rEAX, rESI);
UsercallFunc(int, eggCarrierOutsideEggDoorHook, (const taskwk* twp), (twp), 0x524070, rEAX, rESI);
UsercallFunc(int, skyDeckDoorHook, (taskwk* twp), (twp), 0x51DEB0, rEAX, rESI);


AdventureFieldEntranceManager::AdventureFieldEntranceManager(Options& options, Settings& settings,
                                                             GameStatus& gameStatus,
                                                             ArchipelagoMessenger& archipelagoMessenger) :
    _options(options), _settings(settings), _gameStatus(gameStatus), _archipelagoMessenger(archipelagoMessenger),
    _adventureFieldEntranceMap(AdventureFieldEntranceMap::Init(options)),
    _doorIndicatorManager(DoorIndicatorManager::Init()),
    _mapManager(MapManager::Init(options, gameStatus, _adventureFieldEntranceMap))
{
    _setNextLevelAndActCutsceneModeHook.Hook(OnSetNextLevelAndActCutsceneMode);
    _setNextLevelAndActHook.Hook(OnSetNextLevelAndAct);
    _setNextLevelAndActChaoGardenHook.Hook(OnSetNextLevelAndActChaoGarden);
    _finishedLevelMaybeHook.Hook(OnFinishedLevelMaybe);
    _movePlayerToStartPointHook.Hook(OnMovePlayerToStartPoint);
    _getEntranceEc.Hook(OnGetEntranceEc);
    _setStartPos_ReturnToFieldHook.Hook(OnSetStartPosReturnToField);

    _isBarricadeGoneHook.Hook(OnIsBarricadeGone);
    _wallMainHook.Hook(OnWallMain);
    _ssCarMainHook.Hook(OnSsCarMain);
    _isStationDoorOpenHook.Hook(OnIsStationDoorOpen);
    _isCasinoStationDoorOpenHook.Hook(OnIsCasinoStationDoorOpen);
    _isHotelFrontDoorOpenHook.Hook(OnIsHotelFrontDoorOpen);
    _isHotelBackDoorOpenHook.Hook(OnIsHotelBackDoorOpen);
    _isHotelPoolDoorOpenHook.Hook(OnIsHotelPoolDoorOpen);
    _isTwinkleParkElevatorOpenHook.Hook(OnIsTwinkleParkElevatorOpen);
    _twinkleParkLobbyDoorFromStationHook.Hook(OnTwinkleParkLobbyDoorFromStation);
    _twinkleParkLobbyDoorToStationHook.Hook(OnTwinkleParkLobbyDoorToStation);
    _ssBoxLoadHook.Hook(OnSsBoxLoad);
    _isSpeedHighwayElevatorOpen.Hook(OnIsSpeedHighwayElevatorOpen);
    _isChaos2ElevatorOpen.Hook(OnIsChaos2ElevatorOpen);
    _speedHighwayElevatorHook.Hook(OnSpeedHighwayElevator);
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
    _elevatorMainHook.Hook(OnElevatorMain);
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
    sceneChangeLogicECOusideHook.Hook(OnSceneChangeLogicECOuside);
    eggCarrierInsideEggDoorHook.Hook(OnEggCarrierInsideEggDoor);
    eggCarrierOutsideEggDoorHook.Hook(OnEggCarrierOutsideEggDoor);
    skyDeckDoorHook.Hook(OnSkyDeckDoor);
    _eggCapHook.Hook(OnEggCap);
    _springMainHook.Hook(OnSpringMain);
    _isMonorailEnabledHook.Hook(OnIsMonorailEnabled);
    _isOutsideEggLiftEnabledHook.Hook(OnIsOutsideEggLiftEnabled);
    _isInsideEggLiftEnabledHook.Hook(OnIsInsideEggLiftEnabled);
    _loadPoolDoorHook.Hook(OnLoadPoolDoor);
    _isEcBoatEnabledHook.Hook(IsEcBoatEnabled);
    _isEcRaftEnabledHook.Hook(IsEcRaftEnabled);
    _hiddenGateMainHook.Hook(OnHiddenGateMain);
    //Allows players to return to the adventure field when quitting boss fights
    WriteData<1>((void*)0x415F46, 0x19); // Change the comparison value from 3 to 9
    WriteData<1>((void*)0x638BF6, 0x09);
    // Change the jump from jz (0x74) to jnz (0x75)
    WriteData<1>((void*)0x638C00, 0x75);

    if (_settings.adventureFieldDoorOverride == AdventureFieldDoorOverrideAllClosed)
        this->_doorLogicStrategy = std::make_unique<EverythingClosedDoorLogicStrategy>();
    else
        this->_doorLogicStrategy = std::make_unique<EverythingOpenedDoorLogicStrategy>(_adventureFieldEntranceMap);

    _mapManager.SetDoorLogicStrategy(this->_doorLogicStrategy.get());
}

void AdventureFieldEntranceManager::UpdateGatingMethod()
{
    if (_settings.adventureFieldDoorOverride == AdventureFieldDoorOverrideDisabled)
    {
        if (_options.gatingMode == EmblemGating)
        {
            this->_doorLogicStrategy = std::make_unique<EmblemGatingDoorLogicStrategy>(
                _options, _gameStatus, _adventureFieldEntranceMap);
        }
        else if (_options.gatingMode == KeyItemGating)
        {
            this->_doorLogicStrategy = std::make_unique<KeyItemDoorLogicStrategy>(_options, _gameStatus);
        }
        else
        {
            this->_doorLogicStrategy = std::make_unique<EverythingOpenedDoorLogicStrategy>(_adventureFieldEntranceMap);
        }
    }
    else if (_settings.adventureFieldDoorOverride == AdventureFieldDoorOverrideAllOpened)
    {
        this->_doorLogicStrategy = std::make_unique<EverythingOpenedDoorLogicStrategy>(_adventureFieldEntranceMap);
    }
    else
    {
        this->_doorLogicStrategy = std::make_unique<EverythingClosedDoorLogicStrategy>();
    }
    _mapManager.SetDoorLogicStrategy(this->_doorLogicStrategy.get());
}

void AdventureFieldEntranceManager::UpdateRandomEntrances()
{
    _adventureFieldEntranceMap.UpdateRandomEntrances();
}

bool AdventureFieldEntranceManager::IsDoorOpen(const EntranceId entranceId)
{
    return _doorLogicStrategy->IsDoorOpen(entranceId);
}

void AdventureFieldEntranceManager::OnSetNextLevelAndAct(const Uint8 level, const Uint8 act)
{
    LevelAndActIDs currentLevelAndAct = static_cast<LevelAndActIDs>(CurrentStageAndAct);
    if (CurrentChaoStage == SADXChaoStage_EggCarrier)
        currentLevelAndAct = LevelAndActIDs_ECGarden;
    else if (CurrentChaoStage == SADXChaoStage_StationSquare)
        currentLevelAndAct = LevelAndActIDs_SSGarden;
    else if (CurrentChaoStage == SADXChaoStage_MysticRuins)
        currentLevelAndAct = LevelAndActIDs_MRGarden;

    AdventureFieldEntrance* newEntrance = _instance->_adventureFieldEntranceMap.GetNewConnection(
        currentLevelAndAct, GET_LEVEL_ACT(level, act), _instance->_isEggCarrierTransformed);
    if (newEntrance != nullptr)
    {
        auto levelActAndId = newEntrance->levelAndActId;
        if ((GET_LEVEL(levelActAndId) >= LevelIDs_EmeraldCoast
                && GET_LEVEL(levelActAndId) <= LevelIDs_E101R)
            || (GET_LEVEL(levelActAndId) >= LevelIDs_TwinkleCircuit
                && GET_LEVEL(levelActAndId) <= LevelIDs_SandHill))
            levelActAndId = _instance->_adventureFieldEntranceMap.CalculateCorrectAct(levelActAndId);

        if (levelActAndId == LevelAndActIDs_HedgehogHammer)
        {
            AdventureFieldEntrance* currentEntrance = _instance->_adventureFieldEntranceMap.GetCurrentEntrance(
                currentLevelAndAct, GET_LEVEL_ACT(level, act));
            _setNextLevelAndActHook.Original(
                GET_LEVEL(currentEntrance->levelAndActId), GET_ACT(currentEntrance->levelAndActId));
            SetEntranceNumber(currentEntrance->entranceNumber);
        }
        else
        {
            _setNextLevelAndActHook.Original(
                GET_LEVEL(levelActAndId), GET_ACT(levelActAndId));
            SetEntranceNumber(newEntrance->entranceNumber);
        }
        _instance->_gameStatus.map.SetEntranceVisited(newEntrance->entranceId, true);
        _instance->_gameStatus.map.SetEntranceVisited(newEntrance->connectsTo, true);
        _instance->_archipelagoMessenger.SetMapStatus();
        return;
    }
    _setNextLevelAndActHook.Original(level, act);
}

task* AdventureFieldEntranceManager::OnSetNextLevelAndActChaoGarden(Uint8 level, Uint8 act)
{
    _instance->OnSetNextLevelAndActCutsceneMode(level, act);
    return nullptr;
}

void AdventureFieldEntranceManager::OnSetNextLevelAndActCutsceneMode(const Uint8 level, const Uint8 act)
{
    LevelAndActIDs currentLevelAndAct = static_cast<LevelAndActIDs>(CurrentStageAndAct);
    if (CurrentChaoStage == SADXChaoStage_EggCarrier)
        currentLevelAndAct = LevelAndActIDs_ECGarden;

    else if (CurrentChaoStage == SADXChaoStage_StationSquare)
        currentLevelAndAct = LevelAndActIDs_SSGarden;

    else if (CurrentChaoStage == SADXChaoStage_MysticRuins)
        currentLevelAndAct = LevelAndActIDs_MRGarden;

    AdventureFieldEntrance* newEntrance = _instance->_adventureFieldEntranceMap.GetNewConnection(
        currentLevelAndAct, GET_LEVEL_ACT(level, act), _instance->_isEggCarrierTransformed);

    if (newEntrance != nullptr)
    {
        auto levelActAndId = newEntrance->levelAndActId;
        if ((GET_LEVEL(levelActAndId) >= LevelIDs_EmeraldCoast
                && GET_LEVEL(levelActAndId) <= LevelIDs_E101R)
            || (GET_LEVEL(levelActAndId) >= LevelIDs_TwinkleCircuit
                && GET_LEVEL(levelActAndId) <= LevelIDs_SandHill))
            levelActAndId = _instance->_adventureFieldEntranceMap.CalculateCorrectAct(levelActAndId);

        if (levelActAndId == LevelAndActIDs_HedgehogHammer)
        {
            AdventureFieldEntrance* currentEntrance = _instance->_adventureFieldEntranceMap.GetCurrentEntrance(
                currentLevelAndAct, GET_LEVEL_ACT(level, act));
            _setNextLevelAndActCutsceneModeHook.Original(
                GET_LEVEL(currentEntrance->levelAndActId), GET_ACT(currentEntrance->levelAndActId));
            SetEntranceNumber(currentEntrance->entranceNumber);
        }
        else
        {
            _setNextLevelAndActCutsceneModeHook.Original(
                GET_LEVEL(levelActAndId), GET_ACT(levelActAndId));
            SetEntranceNumber(newEntrance->entranceNumber);
        }
        _instance->_gameStatus.map.SetEntranceVisited(newEntrance->entranceId, true);
        _instance->_gameStatus.map.SetEntranceVisited(newEntrance->connectsTo, true);
        _instance->_archipelagoMessenger.SetMapStatus();
        return;
    }
    _setNextLevelAndActCutsceneModeHook.Original(level, act);
}

//When leaving a level, check if we quiting the adventure game
Sint32 AdventureFieldEntranceManager::OnFinishedLevelMaybe()
{
    if (GameState == MD_GAME_ABORT)
        _instance->_isEggCarrierTransformed = false;
    return _finishedLevelMaybeHook.Original();
}

void AdventureFieldEntranceManager::OnMovePlayerToStartPoint(taskwk* twp)
{
    _movePlayerToStartPointHook.Original(twp);

    LevelAndActIDs levelAndAct = GET_LEVEL_ACT(CurrentLevel, CurrentAct);

    if (levelAndAct == LevelAndActIDs_StationSquare1)
    {
        if (GetLevelEntranceID() == 3)
        {
            twp->pos = {270, 0, 480};
            twp->ang = {0, 0x4000, 0};
        }
    }
    if (levelAndAct == LevelAndActIDs_StationSquare2)
    {
        if (GetLevelEntranceID() == 4)
        {
            twp->pos = {-400, -3, 990};
            twp->ang = {0, 0x4000, 0};
        }
    }
    else if (levelAndAct == LevelAndActIDs_StationSquare3)
    {
        if (GetLevelEntranceID() == 1)
        {
            twp->pos = {395, -120, 1200};
            twp->ang = {0, 0xC000, 0};
        }
    }
    else if (levelAndAct == LevelAndActIDs_StationSquare6)
    {
        if (GetLevelEntranceID() == 0)
        {
            twp->pos = {688.13f, 50, 1771.5f};
            twp->ang = {0, 0, 0};
        }
    }
    else if (levelAndAct == LevelAndActIDs_StationSquare4)
    {
        if (GetLevelEntranceID() == 4)
        {
            twp->pos = {566.5, 50, 1771.5};
            twp->ang = {0, 0x8000, 0};
        }
    }
    else if (levelAndAct == LevelAndActIDs_MysticRuins1)
    {
        if (GetLevelEntranceID() == 8)
        {
            twp->pos = {950, 127, 921};
            twp->ang = {0, 0x8278, 0};
        }
        if (GetLevelEntranceID() == 9)
        {
            twp->pos = {1413, 209, 814};
            twp->ang = {0, 0xD14D, 0};
        }
    }
    else if (levelAndAct == LevelAndActIDs_MysticRuins2)
    {
        if (GetLevelEntranceID() == 3)
        {
            twp->pos = {-2.5, -240, 2454};
            twp->ang = {0, 0x4000, 0};
        }
    }
    else if (levelAndAct == LevelAndActIDs_MysticRuins3)
    {
        if (GetLevelEntranceID() == 3)
        {
            twp->pos = {-1500, 50, -70};
            twp->ang = {0, 0x0000, 0};
        }
        else if (GetLevelEntranceID() == 5)
        {
            twp->pos = {-667, 90.5f, -1150};
            twp->ang = {0, 0x4000, 0};
        }
    }
    else if (levelAndAct == LevelAndActIDs_MysticRuins4)
    {
        if (GetLevelEntranceID() == 4)
        {
            twp->pos = {1.22f, 8, 36.75};
            twp->ang = {0, 0x4000, 0};
        }
    }
    else if (levelAndAct == LevelAndActIDs_Past2)
    {
        if (GetLevelEntranceID() == 1)
        {
            twp->pos = {0, 10, 300};
            twp->ang = {0, 0x4000, 0};
        }
    }
    else if (levelAndAct == LevelAndActIDs_Past1)
    {
        if (GetLevelEntranceID() == 2)
        {
            twp->pos = {-151.5f, 300, 30};
            twp->ang = {0, 0x4000, 0};
        }
    }
    else if (levelAndAct == LevelAndActIDs_EggCarrierOutside1)
    {
        if (GetLevelEntranceID() == 9)
        {
            twp->pos = {0, 753, -335};
            twp->ang = {0, 0x4000, 0};
        }
    }
    else if (levelAndAct == LevelAndActIDs_EggCarrierOutside2)
    {
        if (GetLevelEntranceID() == 0)
        {
            twp->pos = {0, 650, -1000};
            twp->ang = {0, 0x4000, 0};
        }
        if (GetLevelEntranceID() == 1)
        {
            twp->pos = {0, 728, 345};
            twp->ang = {0, 0xC000, 0};
        }
        if (GetLevelEntranceID() == 2)
        {
            twp->pos = {356, 569, -422};
            twp->ang = {0, 0xC000, 0};
        }
        if (GetLevelEntranceID() == 6)
        {
            twp->pos = {-306, 570, -722};
            twp->ang = {0, 0x0000, 0};
        }
        if (GetLevelEntranceID() == 7)
        {
            twp->pos = {306, 570, -722};
            twp->ang = {0, 0x8000, 0};
        }
        if (GetLevelEntranceID() == 9)
        {
            twp->pos = {0, 753, -335};
            twp->ang = {0, 0x4000, 0};
        }
    }
    else if (levelAndAct == LevelAndActIDs_EggCarrierInside2)
    {
        if (GetLevelEntranceID() == 2)
        {
            twp->pos = {50, 0, 178};
            twp->ang = {0, 0xA000, 0};
        }
        if (GetLevelEntranceID() == 7)
        {
            twp->pos = {0, 49, -372};
            twp->ang = {0, 0xC000, 0};
        }
    }
}

void AdventureFieldEntranceManager::OnGetEntranceEc(taskwk* twp)
{
    if (CurrentStageAndAct == LevelAndActIDs_EggCarrierInside2)
    {
        if (GetLevelEntranceID() == 2)
        {
            twp->pos = {47, 0, 172};
            twp->ang = {0, 0xA000, 0};
            return;
        }
    }
    _getEntranceEc.Original(twp);
}

void AdventureFieldEntranceManager::OnSetStartPosReturnToField()
{
    SetNextLevelAndAct(LastLevel, LastAct);
}

void AdventureFieldEntranceManager::OnFrame()
{
    _mapManager.OnFrame();
    if (CurrentStageAndAct == LevelAndActIDs_EggCarrierOutside4)
    {
        bool isTransformed = false;
        if (CurrentCharacter == Characters_Sonic)
            isTransformed = EventFlagArray[FLAG_SONIC_EC_TRANSFORM];
        else if (CurrentCharacter == Characters_Tails)
            isTransformed = EventFlagArray[FLAG_MILES_EC_TRANSFORM];
        else if (CurrentCharacter == Characters_Knuckles)
            isTransformed = EventFlagArray[FLAG_KNUCKLES_EC_TRANSFORM];
        else if (CurrentCharacter == Characters_Amy)
            isTransformed = EventFlagArray[FLAG_AMY_EC_TRANSFORM];
        else if (CurrentCharacter == Characters_Gamma)
            isTransformed = EventFlagArray[FLAG_E102_EC_TRANSFORM];
        else if (CurrentCharacter == Characters_Big)
            isTransformed = EventFlagArray[FLAG_BIG_EC_TRANSFORM];

        if (isTransformed != _isEggCarrierTransformed)
            _isEggCarrierTransformed = isTransformed;
    }
} // -------- Function hooks for gating the world --------

BOOL AdventureFieldEntranceManager::OnIsBarricadeGone()
{
    if (CurrentStageAndAct == LevelAndActIDs_StationSquare4)
        return _instance->IsDoorOpen(SsMainToCityHall);

    return _instance->IsDoorOpen(CityHallToSsMain);
}

void AdventureFieldEntranceManager::OnWallMain(task* tp)
{
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
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1 && !_instance->IsDoorOpen(CityHallToSsMain))
        return FreeTask(tp);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4 && !_instance->IsDoorOpen(SsMainToCityHall))
        return FreeTask(tp);

    return _ssCarMainHook.Original(tp);
}

int AdventureFieldEntranceManager::OnIsStationDoorOpen()
{
    if (CurrentStageAndAct == LevelAndActIDs_StationSquare4)
        return _instance->IsDoorOpen(SsMainToStation);

    return _instance->IsDoorOpen(StationToSsMain);
}

BOOL AdventureFieldEntranceManager::OnIsCasinoStationDoorOpen()
{
    return _instance->IsDoorOpen(StationToCasino);
}

BOOL AdventureFieldEntranceManager::OnIsHotelFrontDoorOpen()
{
    if (CurrentStageAndAct == LevelAndActIDs_StationSquare4)
        return _instance->IsDoorOpen(SsMainToHotel);

    return _instance->IsDoorOpen(HotelToSsMain);
}

BOOL AdventureFieldEntranceManager::OnIsHotelBackDoorOpen()
{
    if (CurrentStageAndAct == LevelAndActIDs_StationSquare2)
        return _instance->IsDoorOpen(CasinoToHotel);

    return _instance->IsDoorOpen(HotelToCasino);
}

BOOL AdventureFieldEntranceManager::OnIsHotelPoolDoorOpen()
{
    return _instance->IsDoorOpen(HotelToHotelPool);
}

BOOL AdventureFieldEntranceManager::OnIsTwinkleParkElevatorOpen()
{
    return _instance->IsDoorOpen(SsMainToTwinkleParkTunnel);
}

TaskFunc(SomethingAboutTPDoorA, 0x63E670);

void AdventureFieldEntranceManager::OnTwinkleParkLobbyDoorFromStation(task* tp)
{
    //We disable the distance check, and we manually check if the entrance is accessible
    WriteData<1>((void*)0x63E737, 0xEB);

    const bool isDoorOpen = _instance->IsDoorOpen(TwinkleParkTunnelToTwinkleParkLobby);
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
    //We disable the distance check, and we manually check if the entrance is accessible
    WriteData<1>((void*)0x63E477, 0xEB);
    const bool isDoorOpen = _instance->IsDoorOpen(TwinkleParkLobbyToTwinkleParkTunnel);
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
    // Change jnz to jz
    WriteData<1>((void*)0x636B84, 0x74);
    // Change cmp eax, 7 to cmp eax, 9
    WriteData<1>((void*)0x636B83, 0x09);

    return _ssBoxLoadHook.Original(tp);
}

BOOL AdventureFieldEntranceManager::OnIsSpeedHighwayElevatorOpen()
{
    return true;
}

BOOL AdventureFieldEntranceManager::OnIsChaos2ElevatorOpen()
{
    return true;
}

void AdventureFieldEntranceManager::OnSpeedHighwayElevator(ObjectMaster* tp)
{
    OEleboxIn(tp);
}

void AdventureFieldEntranceManager::OnElevatorOut(task* tp)
{
    if (CurrentStageAndAct == LevelAndActIDs_StationSquare4 && !_instance->IsDoorOpen(
        TwinkleParkTunnelToSewers))
        return _elevatorOutHook.Original(tp);

    _elevatorInHook.Original(tp);
}

void AdventureFieldEntranceManager::OnElevatorIn(task* tp)
{
    if (CurrentStageAndAct == LevelAndActIDs_StationSquare3 && !_instance->IsDoorOpen(
        SewersToTwinkleParkTunnel))
        return _elevatorOutHook.Original(tp);

    _elevatorInHook.Original(tp);
}

int AdventureFieldEntranceManager::OnElevatorInSceneChange(task* tp)
{
    if (CurrentStageAndAct == LevelAndActIDs_StationSquare3)
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
    if (_instance->IsDoorOpen(CityHallToSewers))
        return _sewerCarHandlePickUpHook.Original(tp);

    //Big won't be able to pick up the car 
    return DrawCar(tp);
}

BOOL AdventureFieldEntranceManager::OnSpawnSewerCar()
{
    if (CurrentCharacter == Characters_Big)
        return false;

    return _instance->IsDoorOpen(CityHallToSewers);
}

void AdventureFieldEntranceManager::OnCollisionCube(task* tp)
{
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
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare3 && CurrentCharacter == Characters_Big)
        return FreeTask(tp);
    return _characterUpgradeMainHook.Original(tp);
}

void AdventureFieldEntranceManager::OnSsBoatMain(task* tp)
{
    if (!_instance->IsDoorOpen(SsMainToEcOutside))
        return FreeTask(tp);
    return _ssBoatMainHook.Original(tp);
} // Speed Highway
//TODO: Check/move the unlock part to the main manager
BOOL AdventureFieldEntranceManager::OnIsSpeedHighwayShutterOpen()
{
    return _instance->IsDoorOpen(SsMainToSpeedHighway);
}

void AdventureFieldEntranceManager::OnLoadSpeedHighwayShutter(task* tp)
{
    //TODO: Animate instead of removing the task
    if (_instance->IsDoorOpen(SsMainToSpeedHighway))
        return FreeTask(tp);

    _loadSpeedHighwayShutterHook.Original(tp);
}

void AdventureFieldEntranceManager::OnLoadSpeedHighwayShutter2(task* tp)
{
    //TODO: Animate instead of removing the task
    if (_instance->IsDoorOpen(SsMainToSpeedHighway))
        return FreeTask(tp);

    _loadSpeedHighwayShutter2Hook.Original(tp);
}

BOOL AdventureFieldEntranceManager::OnIsEmeraldCoastOpen()
{
    if (CurrentCharacter == Characters_Gamma)
        return false;

    return _instance->IsDoorOpen(HotelPoolToEmeraldCoast);
}

void AdventureFieldEntranceManager::OnLoadEmeraldCoastGateTargets(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
        && !_instance->IsDoorOpen(HotelPoolToEmeraldCoast))
        FreeTask(tp);
    else
        _loadEmeraldCoastGateTargetsHook.Original(tp);
}

void AdventureFieldEntranceManager::OnElevatorMain(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
        && IsNearPosition(tp->twp->pos, -399.99f, 0, 1700)
        && !_instance->IsDoorOpen(HotelToSsChaoGarden))
        tp->twp->mode = 8;

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
        && IsNearPosition(tp->twp->pos, -399.99f, 0, 1665)
        && !_instance->IsDoorOpen(HotelToChaos2))
        tp->twp->mode = 8;

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_SSGarden
        && !_instance->IsDoorOpen(SsChaoGardenToHotel))
        tp->twp->mode = 8;
    _elevatorMainHook.Original(tp);
}

BOOL AdventureFieldEntranceManager::OnIsCasinoOpen()
{
    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
        return _isCasinoOpenHook.Original() && _instance->IsDoorOpen(CasinoToCasinopolis);

    if (CurrentCharacter == Characters_Knuckles)
        return GetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_ENTRANCE_CASINO)) && _instance->IsDoorOpen(
            CasinoToCasinopolis);

    return _instance->IsDoorOpen(CasinoToCasinopolis);
}

BOOL AdventureFieldEntranceManager::OnIsTrainInService()
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare2)
        return _instance->IsDoorOpen(StationToMrMain);

    return _instance->IsDoorOpen(MrMainToStation);
}

EntranceId GetBossEntrance()
{
    switch (levelact(CurrentLevel, CurrentAct))
    {
    case LevelAndActIDs_StationSquare2:
        return CasinoToEggWalker;
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
    case LevelAndActIDs_MysticRuins3:
        return JungleToPastMain;
    case LevelAndActIDs_Past1:
        return PastMainToJungle;
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
    case LevelAndActIDs_EggCarrierInside6:
        return WarpHallToEcChaoGarden;
    case LevelAndActIDs_ECGarden:
        return EcChaoGardenToWarpHall;
    default:
        return InvalidEntranceId;
    }
}

void AdventureFieldEntranceManager::OnEcWarpMain(task* tp)
{
    if (_instance->IsDoorOpen(GetBossEntrance()))
        return _ecWarpMainHook.Original(tp);

    tp->twp->wtimer = 0;
    _ecWarpMainHook.Original(tp);
}

TaskFunc(ClosedToyShopDoorMain, 0x63E9A0);

void AdventureFieldEntranceManager::OnOpenToyShopDoorMain(task* tp)
{
    if (_instance->IsDoorOpen(SewersToCityHall))
        return _openToyShopDoorMainHook.Original(tp);

    ClosedToyShopDoorMain(tp);
}

BOOL AdventureFieldEntranceManager::OnIsCityHallDoorOpen()
{
    return _instance->IsDoorOpen(CityHallToSpeedHighway);
}

//We don't create Knuckles barricade if he doesn't have access to the level
void AdventureFieldEntranceManager::OnLoadKnucklesBarricade(task* tp)
{
    if (CurrentCharacter == Characters_Knuckles && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1)
        if (!_instance->IsDoorOpen(CityHallToSpeedHighway))
            return FreeTask(tp);

    _loadKnucklesBarricadeHook.Original(tp);
}

int AdventureFieldEntranceManager::OnTwinkleCircuitDoor(const char character)
{
    return _instance->IsDoorOpen(TwinkleParkLobbyToTwinkleCircuit);
}

int AdventureFieldEntranceManager::OnTwinkleParkDoor(const char character)
{
    return _instance->IsDoorOpen(TwinkleParkLobbyToTwinklePark);
}

void AdventureFieldEntranceManager::OnMrRaftMain(task* tp)
{
    if (!_instance->IsDoorOpen(MrMainToEcOutside))
        return FreeTask(tp);
    return _mrRaftMainHook.Original(tp);
}

int AdventureFieldEntranceManager::OnMrCartMain(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3)
        return _instance->IsDoorOpen(JungleToMrMain);
    if (tp->twp->scl.x > 0)
        return _instance->IsDoorOpen(MrMainToMrChaoGarden);
    return _instance->IsDoorOpen(MrMainToJungle);
}

BOOL AdventureFieldEntranceManager::OnIsAngelIslandOpen()
{
    return _instance->IsDoorOpen(MrMainToAngelIsland);
}

void AdventureFieldEntranceManager::OnMysticRuinsKey(task* tp)
{
    // We don't spawn the golden/silver keys for knuckles if he can't enter LostWorld
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 && CurrentCharacter == Characters_Knuckles)
    {
        if (!_instance->IsDoorOpen(JungleToLostWorldAlternative))
            return;

        return _mysticRuinsKeyHook.Original(tp);
    }

    const int bufferCharacter = CurrentCharacter;
    CurrentCharacter = Characters_Sonic;
    _mysticRuinsKeyHook.Original(tp);
    CurrentCharacter = bufferCharacter;
}

void AdventureFieldEntranceManager::OnMysticRuinsLock(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 && CurrentCharacter == Characters_Knuckles)
    {
        if (!_instance->IsDoorOpen(JungleToLostWorldAlternative))
            return;

        return _mysticRuinsLockHook.Original(tp);
    }
    const int bufferCharacter = CurrentCharacter;
    CurrentCharacter = Characters_Sonic;
    _mysticRuinsLockHook.Original(tp);
    CurrentCharacter = bufferCharacter;
}

BOOL AdventureFieldEntranceManager::OnIsWindyValleyOpen()
{
    return _instance->IsDoorOpen(MrMainToWindyValley);
}

BOOL AdventureFieldEntranceManager::OnPreventMrStoneSpawn()
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 && CurrentCharacter == Characters_Knuckles)
        return false;

    return true;
}

int AdventureFieldEntranceManager::OnGetCharacterId(char index)
{
    return CurrentCharacter;
}

void AdventureFieldEntranceManager::OnPastSceneChange(task* tp)
{
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
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3)
        return _instance->IsDoorOpen(JungleToFinalEggTower);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && IsNearPosition(
        entity->Position, 0, 109, 175))
        return _instance->IsDoorOpen(FinalEggTowerToJungle);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && IsNearPosition(
        entity->Position, 0, 109, -175))
        return _instance->IsDoorOpen(FinalEggTowerToFinalEggAlternative);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && IsNearPosition(
        entity->Position, 0, 0, -185.69f, 7.071068f))
        return _instance->IsDoorOpen(FinalEggTowerToEcInside);
    return _isFinalEggEggmanDoorOpenHook.Original(entity);
}

//Prevents the monkey from blocking the entrance to Red Mountain for knuckles
BOOL AdventureFieldEntranceManager::OnIsMonkeyDoorOpen(int a1)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1)
        return true;

    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Gamma)
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
            || CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Knuckles)
            return FreeTask(tp);
        if (!_instance->_instance->IsDoorOpen(AngelIslandToRedMountain))
            return FreeTask(tp);
    }
    _loadMonkeyCageHook.Original(tp);
}

void AdventureFieldEntranceManager::OnChangeSceneCave2(task* tp)
{
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
    return _instance->IsDoorOpen(JungleToLostWorld);
}

BOOL AdventureFieldEntranceManager::OnIsSandHillOpen()
{
    return _instance->IsDoorOpen(JungleToSandHill);
}

void AdventureFieldEntranceManager::OnLoadSceneChangeMr(task* tp)
{
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
    //Angel Island
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        // Ice Cap
        if (newScene == 1)
        {
            if (_instance->IsDoorOpen(IceCaveToIceCap))
            {
                return SetNextLevelAndAct_CutsceneMode(
                    GET_LEVEL(LevelAndActIDs_IceCap1), GET_ACT(LevelAndActIDs_IceCap1));
            }
            return;
        }

        // Ice Cap
        if (newScene == 0)
        {
            return SetNextLevelAndAct_CutsceneMode(
                GET_LEVEL(LevelAndActIDs_RedMountain1), GET_ACT(LevelAndActIDs_RedMountain1));
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
        if (newScene == 4)
        {
            if (_instance->IsDoorOpen(FinalEggTowerToJungle))
            {
                return SetNextLevelAndAct_CutsceneMode(
                    GET_LEVEL(LevelAndActIDs_MysticRuins3), GET_ACT(LevelAndActIDs_MysticRuins3));
            }
            return;
        }
        if (newScene == 5)
        {
            if (_instance->IsDoorOpen(FinalEggTowerToEcInside))
            {
                return SetNextLevelAndAct_CutsceneMode(
                    GET_LEVEL(LevelAndActIDs_EggCarrierInside2), GET_ACT(LevelAndActIDs_EggCarrierInside2));
            }
            return;
        }
    }

    // Jungle
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3)
    {
        if (newScene == 5)
        {
            if (_instance->IsDoorOpen(JungleToFinalEggTower))
            {
                return SetNextLevelAndAct_CutsceneMode(
                    GET_LEVEL(LevelAndActIDs_MysticRuins4), GET_ACT(LevelAndActIDs_MysticRuins4));
            }
            return;
        }
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
    if (!_instance->IsDoorOpen(JungleToLostWorldAlternative))
        return false;

    if (CurrentCharacter != Characters_Knuckles)
        return true;

    return EventFlagArray[FLAG_KNUCKLES_MR_REDCUBE] && EventFlagArray[FLAG_KNUCKLES_MR_BLUECUBE];
}

// Removed the ladder on Ice Cap
void AdventureFieldEntranceManager::OnLoadLongLadderMr(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        if (!_instance->IsDoorOpen(IceCaveToIceCap))
        {
            return FreeTask(tp);
        }
    }
    _loadLongLadderMrHook.Original(tp);
}

// HotShelter
void AdventureFieldEntranceManager::OnSceneChangeEcInside(int a1, int a2)
{
    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierInside2)
        return sceneChangeECInsideHook.Original(a1, a2);

    taskwk* twp = (taskwk*)a1;
    if (IsNearPosition(twp->pos, 0, 0, 287))
    {
        camerahax_adventurefields();
        return SetNextLevelAndAct_CutsceneMode(
            GET_LEVEL(LevelAndActIDs_HotShelter1), GET_ACT(LevelAndActIDs_HotShelter1));
    }
    if (IsNearPosition(twp->pos, 86, -3, 216))
    {
        camerahax_adventurefields();
        return SetNextLevelAndAct_CutsceneMode(
            GET_LEVEL(LevelAndActIDs_MysticRuins4), GET_ACT(LevelAndActIDs_MysticRuins4));
    }
    return sceneChangeECInsideHook.Original(a1, a2);
}

void AdventureFieldEntranceManager::OnSceneChangeLogicECOuside(int a1)
{
    unsigned int v1 = *(_DWORD*)(a1 + 20); // ebx
    Uint8 act = 0; // [esp+0h] [ebp-2h]
    Uint8 level = 0; // [esp+1h] [ebp-1h]
    SetLevelEntrance(*(BYTE*)(a1 + 28) & 0xF);
    if (v1 > 5)
    {
        if (v1 == 256)
        {
            act = 2;
            level = 6;
        }
    }
    else
    {
        level = 29;
        act = v1 & 0xF;
    }
    camerahax_adventurefields();
    j_SetNextLevelAndAct_CutsceneMode(level, act);
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
        // Warp/Chao Garden door
        if (twp->smode == 3)
        {
            if (!_instance->IsDoorOpen(EcInsideToWarpHall))
                return false;

            if (!IsPlayerNearDoor(twp))
                return false;

            //EGGMAN puzzle solved
            return EventFlagArray[40];
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
        // Left door
        if (twp->smode == 5)
        {
            if (!_instance->IsDoorOpen(EcInsideToFinalEggTower))
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
    // Warp Hall
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierInside6)
    {
        if (!_instance->IsDoorOpen(WarpHallToEcInside))
            return false;

        if (!IsPlayerNearDoor(twp))
            return false;
        return true;
    }
    return eggCarrierInsideEggDoorHook.Original(twp);
}

int AdventureFieldEntranceManager::OnEggCarrierOutsideEggDoor(const taskwk* twp)
{
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
        if (IsNearPosition(twp->pos, 73.79, 1520, 2873))
        {
            if (!_instance->IsDoorOpen(DeckToPrivateRoom))
                return false;

            if (!IsPlayerNearDoor(twp))
                return false;
            return true;
        }
        if (IsNearPosition(twp->pos, -54, 1640, 2968))
        {
            if (!_instance->IsDoorOpen(DeckToPrivateRoomAlternative))
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
    // Private room
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside5)
    {
        if (IsNearPosition(twp->pos, 28, 0, -34) || IsNearPosition(twp->pos, 28, 0, 34))
        {
            if (!IsPlayerNearDoor(twp))
                return false;
            return true;
        }
        if (IsNearPosition(twp->pos, -39, 0, -60))
        {
            if (!_instance->IsDoorOpen(PrivateRoomToDeck))
                return false;

            if (!IsPlayerNearDoor(twp))
                return false;
            return true;
        }
        if (IsNearPosition(twp->pos, 212, 0, 111))
        {
            if (!_instance->IsDoorOpen(PrivateRoomToDeckAlternative))
                return false;

            if (!IsPlayerNearDoor(twp))
                return false;
            return true;
        }
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
    //Bridge
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside2)
    {
        if (!_instance->IsDoorOpen(BridgeToSkyDeck))
            return false;

        if (!IsPlayerNearDoor(twp))
            return false;
        return true;
    }
    if (!IsPlayerNearDoor(twp))
        return false;
    return true;
}

void AdventureFieldEntranceManager::OnEggCap(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside4)
    {
        if (_instance->IsDoorOpen(CaptainRoomToPrivateRoom))
            return FreeTask(tp);
    }
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside5)
    {
        if (_instance->IsDoorOpen(PrivateRoomToCaptainRoom))
            return FreeTask(tp);
    }
    return _eggCapHook.Original(tp);
}

void AdventureFieldEntranceManager::OnSpringMain(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside5)
    {
        if (!_instance->IsDoorOpen(PrivateRoomToCaptainRoom) && IsNearPosition(tp->twp->pos, -83.42f, 0, 0.54f))
            return FreeTask(tp);
    }
    return _springMainHook.Original(tp);
}

BOOL AdventureFieldEntranceManager::OnIsMonorailEnabled()
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside1)
        return _instance->IsDoorOpen(EcOutsideToEcInsideMonorail);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside2)
        return _instance->IsDoorOpen(BridgeToEcInsideMonorail);

    return _instance->IsDoorOpen(EcInsideToEcOutsideMonorail);
}

BOOL AdventureFieldEntranceManager::OnIsOutsideEggLiftEnabled()
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside1)
        return _instance->IsDoorOpen(EcOutsideToEcInsideEggLift);
    return _instance->IsDoorOpen(DeckToEcInsideEggLift);
}

BOOL AdventureFieldEntranceManager::OnIsInsideEggLiftEnabled()
{
    return _instance->IsDoorOpen(EcInsideToEcOutsideEggLift);
}

void AdventureFieldEntranceManager::OnLoadPoolDoor(task* tp)
{
    if (!_instance->IsDoorOpen(PoolToSkyDeck))
        return _loadPoolDoorHook.Original(tp);
    FreeTask(tp);
}

BOOL AdventureFieldEntranceManager::IsEcBoatEnabled()
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside1 && _instance->IsDoorOpen(
        EcOutsideToSsMain))
        return true;
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside2 && _instance->
        IsDoorOpen(BridgeToSsMain))
        return true;
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4 && _instance->IsDoorOpen(SsMainToEcOutside))
        return true;
    return false;
}

BOOL AdventureFieldEntranceManager::IsEcRaftEnabled()
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside1 && _instance->IsDoorOpen(
        EcOutsideToMrMain))
        return true;
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside2 && _instance->
        IsDoorOpen(BridgeToMrMain))
        return true;
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4 && _instance->IsDoorOpen(MrMainToEcOutside))
        return true;
    return false;
}

void AdventureFieldEntranceManager::OnHiddenGateMain(task* tp)
{
    if (IsNearPosition(tp->twp->pos, -0.02f, 20.34f, -191.17f))
        return FreeTask(tp);
    return _hiddenGateMainHook.Original(tp);
}
