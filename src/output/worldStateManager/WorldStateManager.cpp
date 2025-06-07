#include "WorldStateManager.h"

UsercallFuncVoid(sceneChangeMrHook, (int a1), (a1), 0x539220, rEBX);
UsercallFunc(int, twinkleParkDoorHook, (char tpChar), (tpChar), 0x63EA90, rEAX, rESI);
UsercallFunc(int, twinkleCircuitDoorHook, (char tpChar), (tpChar), 0x63F810, rEAX, rESI);
UsercallFunc(int, eggCarrierEggDoorHook, (int a1), (a1), 0x52B420, rEAX, rESI);
UsercallFunc(int, eggCarrierOutsideDoorHook, (int a1), (a1), 0x524070, rEAX, rESI);
UsercallFuncVoid(sceneChangeECInsideHook, (int a1, int a2), (a1,a2), 0x52D690, rEAX, rECX);
UsercallFuncVoid(sceneChangeECOutsideHook, (int a1), (a1), 0x524FE0, rEAX);
UsercallFunc(int, skyDeckDoorHook, (EntityData1 * a1), (a1), 0x51DEB0, rEAX, rESI);
UsercallFuncVoid(lostWorldEntranceCollisionHook, (int a1), (a1), 0x532960, rEDI);
UsercallFuncVoid(finalEggDoorCheckAHook, (int a1), (a1), 0x53C130, rEAX);
UsercallFunc(int16_t, finalEggDoorCheckBHook, (int a1), (a1), 0x53BC70, rAX, rEAX);
DataArray(int, IslandDoorFlags, 0x111E010, 8);

WorldStateManager::WorldStateManager(Options& options, Settings& settings, GameStatus& gameStatus): _options(options),
    _settings(settings), _gameStatus(gameStatus)
{
    _doorIndicatorManager = DoorIndicatorManager();

    _collisionCubeHook.Hook(OnCollisionCube);
    _collisionCylinderHook.Hook(OnCollisionCylinder);
    _isChaos2DoorOpenHook.Hook(OnIsChaos2DoorOpen);
    _isStationDoorOpenHook.Hook(OnIsStationDoorOpen);
    _isHotelDoorOpenHook.Hook(OnIsHotelDoorOpen);
    _isCasinoHotelDoorOpenHook.Hook(OnIsCasinoHotelDoorOpen);
    _isCasinoStationDoorOpenHook.Hook(OnIsCasinoStationDoorOpen);
    _getEntranceMRuinsHook.Hook(OnGetEntranceMRuins);
    _getEntranceEggCarrierHook.Hook(OnGetEntranceEggCarrier);
    _getEntrancePastHook.Hook(OnGetEntrancePast);
    _setTimeOfDayHook.Hook(OnSetTimeOfDay);
    _adventureSetLevelAndActHook.Hook(OnAdventureSetLevelAndAct);
    _prepareLevelHook.Hook(OnPrepareLevel);
    _countSetItemsMaybeHook.Hook(OnCountSetItemsMaybe);
    _emblemMainHook.Hook(OnEmblemMain);
    _missionSetLoadHook.Hook(OnMissionSetLoad);
    _finishedLevelMaybeHook.Hook(OnFinishedLevelMaybe);
    _mysticRuinsKeyHook.Hook(OnMysticRuinsKey);
    _employeeCardHook.Hook(OnEmployeeCard);
    _bigHud_DrawWeightAndLifeHook.Hook(OnBigHud_DrawWeightAndLife);
    _setStartPosReturnToFieldHook.Hook(OnSetStartPosReturnToField);
    _sceneChangeMainStationSquareHook.Hook(OnSceneChangeMainStationSquare);
    _setNextLevelAndActCutsceneModeHook.Hook(OnSetNextLevelAndActCutsceneMode);
    _twinkleCircuitResultsMaybeHook.Hook(OnTwinkleCircuitResultsMaybe);
    _isEmeraldCoastOpenHook.Hook(OnIsEmeraldCoastOpen);
    _loadEmeraldCoastGateTargetsHook.Hook(OnLoadEmeraldCoastGateTargets);
    _isWindyValleyOpenHook.Hook(OnIsWindyValleyOpen);
    _isCasinoOpenHook.Hook(OnIsCasinoOpen);
    _isSpeedHighwayShutterOpenHook.Hook(OnIsSpeedHighwayShutterOpen);
    _loadSpeedHighwayShutterHook.Hook(OnLoadSpeedHighwayShutter);
    _loadSpeedHighwayShutter2Hook.Hook(OnLoadSpeedHighwayShutter2);
    _oHighEleHook.Hook(OnOHighEle);
    _isCityHallDoorOpenHook.Hook(OnIsCityHallDoorOpen);
    _loadBarricadeHook.Hook(OnLoadBarricade);
    _isFinalEggGammaDoorOpenHook.Hook(OnIsFinalEggGammaDoorOpen);
    _loadSceneChangeMrHook.Hook(OnLoadSceneChangeMr);
    _isFinalEggTowerActiveHook.Hook(OnIsFinalEggTowerActive);
    _isFinalEggDoorActiveHook.Hook(OnIsFinalEggDoorActive);
    _isLostWorldBackEntranceOpenHook.Hook(OnIsLostWorldBackEntranceOpen);
    _isLostWorldFrontEntranceOpenHook.Hook(OnIsLostWorldFrontEntranceOpen);
    _isAngelIslandOpenHook.Hook(OnIsAngelIslandOpen);
    _isMonkeyDoorOpenHook.Hook(OnIsMonkeyDoorOpen);
    _loadMonkeyCageHook.Hook(OnLoadMonkeyCage);
    _loadLongLadderMrHook.Hook(OnLoadLongLadderMr);
    _preventKeyStoneFromSpawningHook.Hook(OnPreventKeyStoneFromSpawning);
    _loadPoolWaterHook.Hook(OnLoadPoolWater);
    _loadPoolDoorHook.Hook(OnLoadPoolDoor);


    sceneChangeMrHook.Hook(OnSceneChangeMr);
    twinkleParkDoorHook.Hook(OnTwinkleParkDoor);
    twinkleCircuitDoorHook.Hook(OnTwinkleCircuitDoor);
    eggCarrierEggDoorHook.Hook(OnEggCarrierEggDoor);
    eggCarrierOutsideDoorHook.Hook(OnEggCarrierOutsideDoor);
    sceneChangeECInsideHook.Hook(OnSceneChangeEcInside);
    sceneChangeECOutsideHook.Hook(OnSceneChangeEcOutside);
    skyDeckDoorHook.Hook(OnSkyDeckDoor);
    lostWorldEntranceCollisionHook.Hook(OnLostWorldEntranceCollision);
    finalEggDoorCheckAHook.Hook(OnFinalEggDoorCheckA);
    finalEggDoorCheckBHook.Hook(OnFinalEggDoorCheckB);

    WriteCall(reinterpret_cast<void*>(0x5264C5), &HandleWarp);
    WriteCall(reinterpret_cast<void*>(0x528271), &HandleHedgehogHammer);
    WriteCall(reinterpret_cast<void*>(0x537F52), &HandleWindyValleyEntrance);
    WriteCall(reinterpret_cast<void*>(0x537F64), &HandleWindyValleyEntrance);

    //We allow Tails and Big to enter the Master Emerald Shrine
    IslandDoorFlags[Characters_Tails] = FLAG_SONIC_MR_ISLANDDOOR;
    IslandDoorFlags[Characters_Big] = FLAG_SONIC_MR_ISLANDDOOR;
    IslandDoorFlags[Characters_Amy] = FLAG_SONIC_MR_ISLANDDOOR;

    //We replace the checkpoint for a warp object from the Egg Carrier
    ObjList_SSquare[WARP_STATION_SQUARE] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];
    ObjList_MRuins[WARP_MYSTIC_RUINS] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];
    ObjList_MRuins[EMBLEM_MYSTIC_RUINS].Distance = 1000000.0f;
    ObjList_MRuins[EMBLEM_MYSTIC_RUINS].UseDistance = 1;
    ObjList_ECarrier0[WARP_EGG_CARRIER_OUTSIDE] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];
    ObjList_Past[WARP_PAST] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];

    WriteData<1>((char*)0x004A6B8C, LEON_TIMER1); // Leon timer 1
    WriteData<1>((char*)0x004A81C1, LEON_TIMER2); // Leon timer 2
    WriteData((float**)0x004CD75A, &_nj_screen_.w); // From SADXFE
    WriteData((float**)0x004CD77C, &_nj_screen_.h); // From SADXFE


    if (settings.chaoStatsMultiplier > 1)
    {
        for (int i = 0x00; i < 0x402; i++)
        {
            _chaoStatValues[i] = _chaoStatValues[i] * settings.chaoStatsMultiplier;
        }
    }
}

void WorldStateManager::OnCollisionCube(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        //We find the cube collision that prevent tails from entering the Master Emerald Shrine and delete it
        if (IsNearPosition(tp->twp->pos, -1075, -215, -1040))
            FreeTask(tp);
    }
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_Casinopolis2)
    {
        //We find the cube collision that prevent sonic from entering the life capsule path in SADX and delete it
        if (IsNearPosition(tp->twp->pos, 1, -1715, 2767))
            FreeTask(tp);
    }
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1
        && _instance->_gameStatus.unlock.keyDynamite)
    {
        //We find the cube collision that we created for the dynamite and delete it
        if (IsNearPosition(tp->twp->pos, -393, 120, 890))
            FreeTask(tp);
    }
    else
        _collisionCubeHook.Original(tp);
}

void WorldStateManager::OnCollisionCylinder(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1)
    {
        //We find the cylinder collision that prevent sonic from clipping into the city hall in the DC conversion
        if (IsNearPosition(tp->twp->pos, 322, -15, 245))
            FreeTask(tp);
            //We find the second cylinder collision
        else if (IsNearPosition(tp->twp->pos, 216, -15, 245))
            FreeTask(tp);
    }
    else
        _collisionCylinderHook.Original(tp);
}


// //We pretend that the egg carrier is sunk so that the hedgehog hammer works
bool WorldStateManager::HandleHedgehogHammer()
{
    return GetEventFlag(EventFlags_Amy_WarriorFeather);
}

void WorldStateManager::HandleWarp()
{
    DisableController(0);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1 && CurrentCharacter == Characters_Sonic)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos0, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare2 && CurrentCharacter ==
        Characters_Tails)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggWalker, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && CurrentCharacter == Characters_Sonic)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggViper, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && CurrentCharacter == Characters_Gamma)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_E101, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1 && (CurrentCharacter == Characters_Sonic
            || CurrentCharacter == Characters_Tails || CurrentCharacter == Characters_Knuckles)
        && EntityData1Ptrs[0]->Position.y < 100)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos4, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1
        && (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
        && EntityData1Ptrs[0]->Position.y > 100 && EntityData1Ptrs[0]->Position.y < 150)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggHornet, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1 && (CurrentCharacter == Characters_Sonic
        || CurrentCharacter == Characters_Tails) && EntityData1Ptrs[0]->Position.y > 150)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_SkyChase1, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && CurrentCharacter == Characters_Gamma)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_E101R, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && CurrentCharacter == Characters_Amy)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Zero, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && EntityData1Ptrs[0]->Position.z > -500
        && (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Big))

        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos6, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && (CurrentCharacter == Characters_Knuckles))
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos6, 1);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && EntityData1Ptrs[0]->Position.z < -500
        && (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails))
        SetNextLevelAndAct_CutsceneMode(LevelIDs_SkyChase2, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Past, 1);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_Past2)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_MysticRuins, 1);

    else
        SetNextLevelAndAct_CutsceneMode(LevelIDs_ECGarden, 0);
}


void WorldStateManager::ShowLevelEntranceArrows()
{
    if (!this->_options.entranceRandomizer)
        return;
    if (!this->_settings.showEntranceIndicators)
        return;
    for (LevelArrow levelArrow : _levelArrows)
    {
        if (CurrentStageAndAct != levelArrow.levelAndAct)
            continue;

        if (!_instance->levelEntrances.canEnter(levelArrow.entrance, CurrentCharacter))
            _doorIndicatorManager.DrawDisable(levelArrow.postion, levelArrow.angle);
        else if (levelArrow.isForCharacter(static_cast<Characters>(CurrentCharacter)))
            _doorIndicatorManager.DrawCorrect(levelArrow.postion, levelArrow.angle);
        else
            _doorIndicatorManager.DrawOtherDoor(levelArrow.postion, levelArrow.angle);
    }
}

void WorldStateManager::OnFrame()
{
    if (DemoPlaying > 0)
        return;
    if (CurrentLevel == LevelIDs_PerfectChaos)
        return;

    if (_options.skyChaseChecks && (CurrentCharacter == Characters_Sonic || (CurrentCharacter == Characters_Tails && !
        _options.missionModeEnabled)))
        EventFlagArray[33] = 1;

    if (Current_CharObj2 != nullptr && EntityData1Ptrs[0] != nullptr)
        this->ShowLevelEntranceArrows();

    if (this->_settings.eggCarrierTransformationCutscene)
    {
        if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside4)
            _eggCarrierSunk = false;
        else
            _eggCarrierSunk = true;
    }

    if (CurrentLevel >= LevelIDs_TwinkleCircuit && CurrentLevel <= LevelIDs_SandHill)
        GameMode = GameModes_Adventure_ActionStg;
    else if (GameMode == GameModes_Adventure_Field || GameMode == GameModes_Adventure_ActionStg)
        GameMode = GameModes_Mission;
}


// Allow Knuckles to fight Chaos 2
BOOL WorldStateManager::OnIsChaos2DoorOpen()
{
    return CurrentCharacter == Characters_Knuckles;
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
    return _instance->_gameStatus.unlock.keyHotelBackKey;
}

BOOL WorldStateManager::OnIsCasinoStationDoorOpen()
{
    return _instance->_gameStatus.unlock.keyStationBackKey;
}


//TODO: Register it?
//TODO: Create a spawn point for Sky Deck/Egg Hornet
// We create a custom spawn point after exiting sand hill
void WorldStateManager::OnGetEntranceMRuins(EntityData1* a1)
{
    _getEntranceMRuinsHook.Original(a1);
    if (LastLevel == LevelIDs_SandHill)
    {
        a1->Position.x = -1500;
        a1->Position.y = 50;
        a1->Position.z = -70;
        a1->Rotation.x = 0;
        a1->Rotation.y = 4000;
        a1->Rotation.z = 0;
    }
    else if (LastLevel == LevelIDs_Past)
    {
        a1->Position.x = -2.5f;
        a1->Position.y = -240;
        a1->Position.z = 2480;
        a1->Rotation.x = 0;
        a1->Rotation.y = 4000;
        a1->Rotation.z = 0;
    }
}

// We spawn in the middle on the runway for the transformed Egg Carrier
void WorldStateManager::OnGetEntranceEggCarrier(EntityData1* a1)
{
    _getEntranceEggCarrierHook.Original(a1);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside2 && LevelEntrance == 0)
    {
        a1->Position.x = 0;
        a1->Position.y = 650;
        a1->Position.z = -1000;
        a1->Rotation.x = 0;
        a1->Rotation.y = 0x4000;
        a1->Rotation.z = 0;
    }
}

//TODO: check if this is needed
// We spawn in front of the Master Emerald Shrine in the past when time traveling
void WorldStateManager::OnGetEntrancePast(EntityData1* a1)
{
    _getEntrancePastHook.Original(a1);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_Past2 && LastLevel == LevelIDs_MysticRuins)
    {
        a1->Position.x = 0;
        a1->Position.y = 10;
        a1->Position.z = 380;
        a1->Rotation.x = 0;
        a1->Rotation.y = 0x4000;
        a1->Rotation.z = 0;
    }
}

// Set starting location when we get a game over
void WorldStateManager::OnSetTimeOfDay(Sint8 time)
{
    _setTimeOfDayHook.Original(time);
    if (GameState == MD_GAME_CONTINUE)
        _instance->SetStartingArea();
}

// Set starting location when starting the adventure
void WorldStateManager::OnAdventureSetLevelAndAct()
{
    _adventureSetLevelAndActHook.Original();
    _instance->SetStartingArea();
}

void WorldStateManager::SetStartingArea()
{
    if (LastStoryFlag == 1)
        return;
    switch (this->_options.GetCharacterStartingArea(static_cast<Characters>(CurrentCharacter)))
    {
    case StationSquareMain:
        SetLevelAndAct(LevelIDs_StationSquare, 3);
        break;
    case Station:
        SetLevelAndAct(LevelIDs_StationSquare, 1);
        SetEntranceNumber(0);
        break;
    case HotelArea:
        SetLevelAndAct(LevelIDs_StationSquare, 4);
        break;
    case CasinoArea:
        SetLevelAndAct(LevelIDs_StationSquare, 1);
        SetEntranceNumber(2);
        break;
    case TwinkleParkArea:
        SetLevelAndAct(LevelIDs_StationSquare, 5);
        break;
    case MysticRuinsMain:
        SetLevelAndAct(LevelIDs_MysticRuins, 0);
        break;
    case Jungle:
        SetLevelAndAct(LevelIDs_MysticRuins, 2);
        break;
    case EggCarrierOutside:
        SetLevelAndAct(LevelIDs_EggCarrierOutside, 0);
        break;
    case EggCarrierInside:
        ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_EC_TRANSFORM));
        ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_EC_TRANSFORM));
        ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_EC_TRANSFORM));
        ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_EC_TRANSFORM));
        ClearEventFlag(static_cast<EventFlags>(FLAG_E102_EC_TRANSFORM));
        ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_EC_TRANSFORM));
        SetLevelAndAct(LevelIDs_EggCarrierInside, 1);
        break;
    case AngelIsland:
        SetLevelAndAct(LevelIDs_MysticRuins, 1);
        SetEntranceNumber(1);
        break;
    case EggCarrierFrontDeck:
    case NoStatingArea:
        SetLevelAndAct(LevelIDs_StationSquare, 3);
        break;
    }
}

void WorldStateManager::UpdateLevelEntrances()
{
    this->levelEntrances = LevelEntrances();

    for (const auto& [first, second] : _options.levelEntrancesMap)
    {
        const auto levelEntrance = static_cast<Levels>(first);
        const auto actualLevel = static_cast<Levels>(second);
        levelEntrances.addRelationship(levelEntrance, actualLevel);
    }

    this->_gameStatus.visitedLevels.emeraldCoastEntranceActualLevel = levelEntrances.
        getLevelInitialsFromEntrance(EmeraldCoast);
    this->_gameStatus.visitedLevels.windyValleyEntranceActualLevel = levelEntrances.
        getLevelInitialsFromEntrance(WindyValley);
    this->_gameStatus.visitedLevels.casinopolisEntranceActualLevel = levelEntrances.
        getLevelInitialsFromEntrance(Casinopolis);
    this->_gameStatus.visitedLevels.iceCapEntranceActualLevel = levelEntrances.getLevelInitialsFromEntrance(IceCap);
    this->_gameStatus.visitedLevels.twinkleParkEntranceActualLevel = levelEntrances.
        getLevelInitialsFromEntrance(TwinklePark);
    this->_gameStatus.visitedLevels.speedHighwayEntranceActualLevel = levelEntrances.
        getLevelInitialsFromEntrance(SpeedHighway);
    this->_gameStatus.visitedLevels.redMountainEntranceActualLevel = levelEntrances.
        getLevelInitialsFromEntrance(RedMountain);
    this->_gameStatus.visitedLevels.skyDeckEntranceActualLevel = levelEntrances.getLevelInitialsFromEntrance(SkyDeck);
    this->_gameStatus.visitedLevels.lostWorldEntranceActualLevel = levelEntrances.
        getLevelInitialsFromEntrance(LostWorld);
    this->_gameStatus.visitedLevels.finalEggEntranceActualLevel = levelEntrances.getLevelInitialsFromEntrance(FinalEgg);
    this->_gameStatus.visitedLevels.hotShelterEntranceActualLevel = levelEntrances.
        getLevelInitialsFromEntrance(HotShelter);
}

//TODO:  Move to visitedLevels?
void WorldStateManager::UpdateVisitedLevels(const int visitedLevel)
{
    const LevelIDs visitedEntrance = levelEntrances.getEntranceLevelIdFromLevel(static_cast<LevelIDs>(visitedLevel));
    switch (visitedEntrance)
    {
    case LevelIDs_EmeraldCoast:
        _gameStatus.visitedLevels.emeraldCoastEntranceVisited = true;
        break;
    case LevelIDs_WindyValley:
        _gameStatus.visitedLevels.windyValleyEntranceVisited = true;
        break;
    case LevelIDs_Casinopolis:
        _gameStatus.visitedLevels.casinopolisEntranceVisited = true;
        break;
    case LevelIDs_IceCap:
        _gameStatus.visitedLevels.iceCapEntranceVisited = true;
        break;
    case LevelIDs_TwinklePark:
        _gameStatus.visitedLevels.twinkleParkEntranceVisited = true;
        break;
    case LevelIDs_SpeedHighway:
        _gameStatus.visitedLevels.speedHighwayEntranceVisited = true;
        break;
    case LevelIDs_RedMountain:
        _gameStatus.visitedLevels.redMountainEntranceVisited = true;
        break;
    case LevelIDs_SkyDeck:
        _gameStatus.visitedLevels.skyDeckEntranceVisited = true;
        break;
    case LevelIDs_LostWorld:
        _gameStatus.visitedLevels.lostWorldEntranceVisited = true;
        if (CurrentCharacter == Characters_Knuckles)
            _gameStatus.visitedLevels.lostWorldEntranceVisitedAsKnuckles = true;
        break;
    case LevelIDs_FinalEgg:
        _gameStatus.visitedLevels.finalEggEntranceVisited = true;
        break;
    case LevelIDs_HotShelter:
        _gameStatus.visitedLevels.hotShelterEntranceVisited = true;
        break;
    default: break;
    }
}

SETEntry CreateSetEntry(const int16_t objectType, const NJS_VECTOR& position, const NJS_INT_POINT3 rotation = {0, 0, 0},
                        const NJS_VECTOR& scale = {1, 1, 1})
{
    SETEntry setEntry;
    setEntry.ObjectType = objectType;
    setEntry.XRotation = rotation.x;
    setEntry.YRotation = rotation.y;
    setEntry.ZRotation = rotation.z;
    setEntry.Position = position;
    setEntry.Properties = scale;
    return setEntry;
}

//TODO: Either move to its own class or make this the main thing world state manager does
void AddSetToLevel(const SETEntry& newSetEntry, const LevelAndActIDs levelAndAct, const Characters character)
{
    if (CurrentCharacter == character && levelact(CurrentLevel, CurrentAct) == levelAndAct)
    {
        SETObjData* setObjData = &SETTable[SETTable_Count];
        setObjData->Flags |= 0x8000u;

        setObjData->SETEntry = new SETEntry(newSetEntry);

        setObjData->LoadCount = 0;
        SETTable_Count += 1;
    }
}

const SETEntry FINAL_EGG_SPRING = CreateSetEntry(1, {-52.21f, -3240.81f, -190.0f});
const SETEntry SEWERS_SPRING = CreateSetEntry(1, {505, -89, 635},
                                              {0, 0, 0}, {0.3f, 0, 51});


const SETEntry COLLISION_CUBE_MR = CreateSetEntry(COLLISION_CUBE_MYSTIC_RUINS, {-393.62f, 120, 890.06f},
                                                  {0xFEFF, 0x4BF1, 0xFD6A}, {60, 80, 10});
const SETEntry RED_MOUNTAIN_SCENE_CHANGE_MR = CreateSetEntry(SCENE_CHANGE_MYSTIC_RUINS, {-2100, -304, 1650},
                                                             {0, 0, 0}, {40, 50, 0});

const SETEntry ICE_CAP_SCENE_CHANGE_MR = CreateSetEntry(SCENE_CHANGE_MYSTIC_RUINS, {-1450, 95, 360},
                                                        {1, 0, 0}, {20, 5, 0});
const SETEntry ICE_CAP_LADDER_MR = CreateSetEntry(LONG_LADDER_MYSTIC_RUINS, {-1450, 40, 360},
                                                  {0, 0XC800, 0}, {0, 0, 0});

const SETEntry CAVE_WIND_CHANGE_SCENE_MR = CreateSetEntry(CAVE_WIND_CHANGE_SCENE_MYSTIC_RUINS, {-727, 168, 744});


const SETEntry RED_MOUNTAIN_DOOR_MR = CreateSetEntry(RED_MOUNTAIN_DOOR_MYSTIC_RUINS, {-1960.7f, -350.19f, 1652.01f},
                                                     {0x1, 0xBEFB, 0xFF6E}, {0.3f, 0, 0});

const SETEntry ICE_CAP_SPRING = CreateSetEntry(1, {-1070, -35, 236},
                                               {0, 0, 0}, {0.3f, -1.25f, 1});

const SETEntry BEACH_GATE_SS = CreateSetEntry(BEACH_GATE_STATION_SQUARE, {-525, -10, 2098},
                                              {0, 0x2000, 0});

const SETEntry CITY_HALL_SCENE_CHANGE_SS = CreateSetEntry(SCENE_CHANGE_STATION_SQUARE, {270, -1, 234},
                                                          {0, 0, 0X402}, {8, 3.2, 0});

//Egg Carrier
const SETEntry EGG_CARRIER_TRANSFORM_AREA_SPRING = CreateSetEntry(1, {-83.42, 0, 0.54});

//Station Square Bosses
const SETEntry WARP_CHAOS0 = CreateSetEntry(WARP_STATION_SQUARE, {270, 0, 450});

const SETEntry WARP_EGG_WALKER = CreateSetEntry(WARP_STATION_SQUARE, {-400, -3, 955});


//Mystic Ruins Bosses
const SETEntry WARP_EGG_HORNET = CreateSetEntry(WARP_MYSTIC_RUINS, {950, 127, 950});

const SETEntry WARP_CHAOS4 = CreateSetEntry(WARP_MYSTIC_RUINS, {80, 72, 180});

const SETEntry WARP_EGG_VIPER = CreateSetEntry(WARP_MYSTIC_RUINS, {0, 0, 0});

const SETEntry WARP_E101 = CreateSetEntry(WARP_MYSTIC_RUINS, {0, 0, 0});

//Egg Carrier Bosses
const SETEntry WARP_CHAOS6 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 750.5f, -385.69f});

const SETEntry WARP_ZERO = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 750.5f, -385.69f});

const SETEntry WARP_E101_MK2 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 750.5f, -385.69f});

//Sky Chase
const SETEntry WARP_SKY_CHASE_1_WITHOUT_RUNWAY = CreateSetEntry(WARP_MYSTIC_RUINS, {1561, 191, 900}, {0, 0x1C00, 0});
const SETEntry WARP_SKY_CHASE_1_WITH_RUNWAY = CreateSetEntry(WARP_MYSTIC_RUINS, {1561, 201, 900}, {0, 0x1C00, 0});
const SETEntry WARP_SKY_CHASE_2_EC1 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 700, -1100});
const SETEntry WARP_SKY_CHASE_2_EC2 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 650, -1100});

//Past
const SETEntry WARP_TO_PAST = CreateSetEntry(WARP_MYSTIC_RUINS, {-2.5f, -240, 2397.5f});
const SETEntry WARP_FROM_PAST = CreateSetEntry(WARP_PAST, {0, 7, 247.5f});

//We make the game load Sonic's set files for Angel Island when playing as Tails or Big
Sint32 WorldStateManager::OnPrepareLevel()
{
    Sint32 result;
    if ((CurrentCharacter == Characters_Tails || CurrentCharacter == Characters_Big) &&
        levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        const char* originalCharId = CharIDStrings[CurrentCharacter];
        CharIDStrings[CurrentCharacter] = "S";
        result = _prepareLevelHook.Original();
        CharIDStrings[CurrentCharacter] = originalCharId;
    }
    else
    {
        result = _prepareLevelHook.Original();
    }
    return result;
}

void WorldStateManager::OnCountSetItemsMaybe()
{
    _countSetItemsMaybeHook.Original();

    if (DemoPlaying > 0)
        return;

    for (int i = 0; i < SETTable_Count; ++i)
    {
        const SETObjData* objData = &SETTable[i];
        if (objData->SETEntry != nullptr)
        {
            //We delete the wall that prevent tails from entering the Emerald Coast
            if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
                && objData->SETEntry->ObjectType == WALL_THAT_PUSHES_YOU_STATION_SQUARE)
            {
                objData->SETEntry->Properties = {0, 0, 0};
            }
        }
    }

    //Warp point
    LoadPVM("EC_ALIFE", ADV01C_TEXLISTS[3]);

    //Buyon enemy
    LoadPVM("E_BUYON", &E_BUYON_TEXLIST);

    //Cop
    LoadPVM("NISEPAT", &NISEPAT_TEXLIST);

    //Sky Chase Tarjet
    LoadNoNamePVM(&TARGET_TEXLIST);

    if (_instance->_settings.eggCarrierTransformationCutscene
        && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside4)
        LoadPVM("EC_SKY", &EC_SKY_TEXLIST);

    //Freeze trap
    LoadNoNamePVM(&stx_ice0_TEXLIST);

    AddSetToLevel(FINAL_EGG_SPRING, LevelAndActIDs_FinalEgg3, Characters_Sonic);
    AddSetToLevel(SEWERS_SPRING, LevelAndActIDs_StationSquare3, Characters_Sonic);

    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Sonic);
    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Tails);
    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Knuckles);
    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Amy);
    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Big);
    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Gamma);

    AddSetToLevel(RED_MOUNTAIN_SCENE_CHANGE_MR, LevelAndActIDs_MysticRuins2, Characters_Tails);
    AddSetToLevel(RED_MOUNTAIN_DOOR_MR, LevelAndActIDs_MysticRuins2, Characters_Tails);
    AddSetToLevel(RED_MOUNTAIN_SCENE_CHANGE_MR, LevelAndActIDs_MysticRuins2, Characters_Big);
    AddSetToLevel(RED_MOUNTAIN_DOOR_MR, LevelAndActIDs_MysticRuins2, Characters_Big);

    AddSetToLevel(ICE_CAP_LADDER_MR, LevelAndActIDs_MysticRuins2, Characters_Knuckles);
    AddSetToLevel(ICE_CAP_SCENE_CHANGE_MR, LevelAndActIDs_MysticRuins2, Characters_Knuckles);
    AddSetToLevel(ICE_CAP_LADDER_MR, LevelAndActIDs_MysticRuins2, Characters_Gamma);
    AddSetToLevel(ICE_CAP_SCENE_CHANGE_MR, LevelAndActIDs_MysticRuins2, Characters_Gamma);

    AddSetToLevel(CAVE_WIND_CHANGE_SCENE_MR, LevelAndActIDs_MysticRuins1, Characters_Amy);

    AddSetToLevel(ICE_CAP_SPRING, LevelAndActIDs_MysticRuins2, Characters_Amy);

    AddSetToLevel(EGG_CARRIER_TRANSFORM_AREA_SPRING, LevelAndActIDs_EggCarrierOutside5, Characters_Amy);
    AddSetToLevel(EGG_CARRIER_TRANSFORM_AREA_SPRING, LevelAndActIDs_EggCarrierOutside5, Characters_Knuckles);
    AddSetToLevel(EGG_CARRIER_TRANSFORM_AREA_SPRING, LevelAndActIDs_EggCarrierOutside5, Characters_Big);
    AddSetToLevel(EGG_CARRIER_TRANSFORM_AREA_SPRING, LevelAndActIDs_EggCarrierOutside5, Characters_Gamma);

    //Emerald Coast
    AddSetToLevel(BEACH_GATE_SS, LevelAndActIDs_StationSquare5, Characters_Sonic);

    //Speed Highway (City Hall)
    AddSetToLevel(CITY_HALL_SCENE_CHANGE_SS, LevelAndActIDs_StationSquare1, Characters_Big);
    AddSetToLevel(CITY_HALL_SCENE_CHANGE_SS, LevelAndActIDs_StationSquare1, Characters_Sonic);

    if (_instance->_options.bossChecks)
    {
        //Station Square Bosses
        AddSetToLevel(WARP_CHAOS0, LevelAndActIDs_StationSquare1, Characters_Sonic);
        AddSetToLevel(WARP_EGG_WALKER, LevelAndActIDs_StationSquare2, Characters_Tails);

        //Mystic Ruins Bosses
        AddSetToLevel(WARP_EGG_HORNET, LevelAndActIDs_MysticRuins1, Characters_Sonic);
        AddSetToLevel(WARP_EGG_HORNET, LevelAndActIDs_MysticRuins1, Characters_Tails);

        AddSetToLevel(WARP_CHAOS4, LevelAndActIDs_MysticRuins1, Characters_Sonic);
        AddSetToLevel(WARP_CHAOS4, LevelAndActIDs_MysticRuins1, Characters_Tails);
        AddSetToLevel(WARP_CHAOS4, LevelAndActIDs_MysticRuins1, Characters_Knuckles);

        AddSetToLevel(WARP_EGG_VIPER, LevelAndActIDs_MysticRuins4, Characters_Sonic);
        AddSetToLevel(WARP_E101, LevelAndActIDs_MysticRuins4, Characters_Gamma);

        //Egg Carrier Bosses
        AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside1, Characters_Sonic);
        AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside2, Characters_Sonic);

        AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside1, Characters_Knuckles);
        AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside2, Characters_Knuckles);

        AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside1, Characters_Big);
        AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside2, Characters_Big);

        AddSetToLevel(WARP_ZERO, LevelAndActIDs_EggCarrierOutside1, Characters_Amy);
        AddSetToLevel(WARP_ZERO, LevelAndActIDs_EggCarrierOutside2, Characters_Amy);

        AddSetToLevel(WARP_E101_MK2, LevelAndActIDs_EggCarrierOutside1, Characters_Gamma);
        AddSetToLevel(WARP_E101_MK2, LevelAndActIDs_EggCarrierOutside2, Characters_Gamma);
    }
    if (_instance->_options.skyChaseChecks)
    {
        AddSetToLevel(WARP_SKY_CHASE_1_WITH_RUNWAY, LevelAndActIDs_MysticRuins1, Characters_Sonic);
        if (_instance->_options.missionModeEnabled)
            AddSetToLevel(WARP_SKY_CHASE_1_WITHOUT_RUNWAY, LevelAndActIDs_MysticRuins1, Characters_Tails);
        else
            AddSetToLevel(WARP_SKY_CHASE_1_WITH_RUNWAY, LevelAndActIDs_MysticRuins1, Characters_Tails);

        AddSetToLevel(WARP_SKY_CHASE_2_EC1, LevelAndActIDs_EggCarrierOutside1, Characters_Sonic);
        AddSetToLevel(WARP_SKY_CHASE_2_EC2, LevelAndActIDs_EggCarrierOutside2, Characters_Sonic);

        AddSetToLevel(WARP_SKY_CHASE_2_EC1, LevelAndActIDs_EggCarrierOutside1, Characters_Tails);
        AddSetToLevel(WARP_SKY_CHASE_2_EC2, LevelAndActIDs_EggCarrierOutside2, Characters_Tails);
    }

    //Time Travel 
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Sonic);
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Tails);
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Knuckles);
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Amy);
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Gamma);
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Big);

    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Sonic);
    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Tails);
    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Knuckles);
    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Amy);
    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Gamma);
    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Big);
}

// We move the emblem a little higher so Cream can get it.
//Move a little lower since it clips with the ground
void WorldStateManager::OnEmblemMain(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1 && CurrentCharacter == Characters_Tails)
        if (IsNearPosition(tp->twp->pos, 388, -5.5, 490.5))
        {
            tp->twp->pos.y = -4;
        }

    _emblemMainHook.Original(tp);
}

void WorldStateManager::OnMissionSetLoad()
{
    if (!_instance->_options.missionModeEnabled)
        return;

    _missionSetLoadHook.Original();

    for (int i = 0; i < MissionSetCount; ++i)
    {
        const SETObjData* objData = &MissionSETTable[i];
        if (objData->SETEntry != nullptr)
        {
            const NJS_VECTOR position = objData->SETEntry->Position;
            //We move the mission switch from Big's bed
            if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 &&
                IsNearPosition(position, 1296, 131.5, -727.5))
            {
                objData->SETEntry->Position = {1333, 120, -707};
            }
            //We move the mission card in the sewer, so it doesn't clip with the spring
            if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare3 &&
                IsNearPosition(position, 506.5, -88.5, 635.5))
            {
                objData->SETEntry->Position = {position.x, -70, position.z};
            }

            //We move the mission card 51 in the jungle, so Gamma can get it even if the Snake door is open
            if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 &&
                IsNearPosition(position, -512.5, 205, -1124))
            {
                objData->SETEntry->Position = {-515.9674, 70.18237, -989.24146};
            }
        }
    }
}

//TODO: Later, check if we can make the quit option in a boss return us to the field
//Hook to change the level after beating the boss
Sint32 WorldStateManager::OnFinishedLevelMaybe()
{
    const Sint32 response = _finishedLevelMaybeHook.Original();
    if (GameState != MD_GAME_END)
        return response;

    if (CurrentLevel == LevelIDs_Chaos0)
    {
        SetNextLevelAndAct(LevelIDs_StationSquare, 0);
        SetEntranceNumber(0);
    }
    else if (CurrentLevel == LevelIDs_Chaos2)
    {
        SetNextLevelAndAct(LevelIDs_StationSquare, 4);
        SetEntranceNumber(5);
    }
    else if (CurrentLevel == LevelIDs_Chaos4)
    {
        SetNextLevelAndAct(LevelIDs_MysticRuins, 0);
        SetEntranceNumber(5);
    }
    else if (CurrentLevel == LevelIDs_Chaos6 || CurrentLevel == LevelIDs_Zero
        || CurrentLevel == LevelIDs_E101R || CurrentLevel == LevelIDs_SkyChase2)
    {
        SetEntranceNumber(0);
        SetNextLevelAndAct(LevelIDs_EggCarrierOutside, LastAct);
    }
    else if (CurrentLevel == LevelIDs_EggHornet || CurrentLevel == LevelIDs_SkyChase1)
    {
        SetNextLevelAndAct(LevelIDs_MysticRuins, 0);
        SetEntranceNumber(0);
    }
    else if (CurrentLevel == LevelIDs_EggWalker)
    {
        SetNextLevelAndAct(LevelIDs_StationSquare, 1);
        SetEntranceNumber(1);
    }
    else if (CurrentLevel == LevelIDs_EggViper || CurrentLevel == LevelIDs_E101)
    {
        SetNextLevelAndAct(LevelIDs_MysticRuins, 3);
        SetEntranceNumber(3);
    }
    else if (CurrentLevel == LevelIDs_TwinkleCircuit)
    {
        SetNextLevelAndAct(LevelIDs_StationSquare, 5);
        SetEntranceNumber(2);
    }
    return response;
}

void WorldStateManager::OnMysticRuinsKey(task* tp)
{
    // We prevent the wind stone from spawning if the player doesn't have the item
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1
        && (!_instance->_gameStatus.unlock.keyWindStone
            || !_instance->levelEntrances.canEnter(WindyValley, CurrentCharacter)))
        if (IsNearPosition(tp->twp->pos, 1392.5, 191.5, 863.5))
            return;
    // We don't spawn the golden/silver keys for knuckles if he can't enter LostWorld
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 && CurrentCharacter == Characters_Knuckles)
    {
        if (!_instance->levelEntrances.canEnter(LostWorld, CurrentCharacter))
            return;
    }
    _mysticRuinsKeyHook.Original(tp);
}

void WorldStateManager::OnEmployeeCard(task* tp)
{
    // We prevent the Employee card from spawning if the player doesn't have the item, or he can't use it
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4
        && (!_instance->_gameStatus.unlock.keyEmployeeCard
            || !_instance->levelEntrances.canEnter(SpeedHighway, CurrentCharacter)))
        return;
    _employeeCardHook.Original(tp);
}

// We make Big's hud think we are not in the mission mode
void WorldStateManager::OnBigHud_DrawWeightAndLife()
{
    const GameModes bufferGameMode = GameMode;
    if (CurrentLevel >= LevelIDs_StationSquare && CurrentLevel <= LevelIDs_Past)
        GameMode = GameModes_Adventure_Field;
    else
        GameMode = GameModes_Adventure_ActionStg;
    _bigHud_DrawWeightAndLifeHook.Original();
    GameMode = bufferGameMode;
}

void WorldStateManager::OnSetStartPosReturnToField(task* tp)
{
    if (CurrentLevel < LevelIDs_EmeraldCoast || CurrentLevel > LevelIDs_HotShelter)
    {
        _setStartPosReturnToFieldHook.Original(tp);
        return;
    }
    // TODO: Register return positions for all characters
    const short currentLevelBuffer = CurrentLevel;
    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails
        || CurrentCharacter == Characters_Knuckles)
        CurrentLevel = LevelIDs_SpeedHighway;
    else
        CurrentLevel = LevelIDs_HotShelter;

    _setStartPosReturnToFieldHook.Original(tp);
    CurrentLevel = currentLevelBuffer;

    const LevelIDs entranceLevel = _instance->
                                   levelEntrances.getEntranceLevelIdFromLevel(static_cast<LevelIDs>(CurrentLevel));

    switch (entranceLevel)
    {
    case LevelIDs_EmeraldCoast:
        FieldStartPos->Position = {-492.79999, 10, 2053.8};
        FieldStartPos->YRot = 0x0DBA9;
        break;
    case LevelIDs_WindyValley:
        FieldStartPos->Position = {644.90002, 59.099998, -155.0};
        FieldStartPos->YRot = 0x6000;
        break;
    case LevelIDs_TwinklePark:
        FieldStartPos->Position = {785.29999, 50.0, 1771.7};
        FieldStartPos->YRot = 0x7AB7;
        break;
    case LevelIDs_SpeedHighway:
        if (CurrentCharacter == Characters_Knuckles)
        {
            FieldStartPos->Position = {272.0, 4.0, 294.89999};
            FieldStartPos->YRot = 0x3D0C;
        }
        else
        {
            FieldStartPos->Position = {347.79999, 0.0, 1370.3};
            FieldStartPos->YRot = 0x7FB9;
        }
        break;
    case LevelIDs_RedMountain:
        FieldStartPos->Position = {-1945.7, -351.5, 1646.6};
        FieldStartPos->YRot = 0x5F9;
        break;
    case LevelIDs_SkyDeck:
        if (CurrentCharacter == Characters_Knuckles)
        {
            FieldStartPos->Position = {290.0, 17.0, 0.0};
            FieldStartPos->YRot = 0x8000;
        }
        else
        {
            FieldStartPos->Position = {0.0, 655.0, 146.0};
            FieldStartPos->YRot = 0x0C000;
        }
        break;
    case LevelIDs_LostWorld:
        if (CurrentCharacter == Characters_Knuckles)
        {
            FieldStartPos->Position = {-515.90002, 16.6, -1446.0};
            FieldStartPos->YRot = 0xC000;
        }
        else
        {
            FieldStartPos->Position = {-515.0, 92.0, -1054.0};
            FieldStartPos->YRot = 0x4000;
        }
        break;
    case LevelIDs_IceCap:
        FieldStartPos->Position = {-1290.0, 27.5, 315.0};
        FieldStartPos->YRot = 0x0EC68;
        break;
    case LevelIDs_Casinopolis:
        FieldStartPos->Position = {-572.5, -2.5, 939.5};
        FieldStartPos->YRot = 0x1F17;
        break;
    case LevelIDs_FinalEgg:
        if (CurrentCharacter == Characters_Gamma)
        {
            FieldStartPos->Position = {-0.5, 108.8, -138.10001};
            FieldStartPos->YRot = 0x4537;
        }
        else
        {
            FieldStartPos->Position = {133.39999, 108.4, -7.1999998};
            FieldStartPos->YRot = 0x70EF;
        }
        break;
    case LevelIDs_HotShelter:
        FieldStartPos->Position = {0.0, 14.0, 160.0};
        FieldStartPos->YRot = 0xC000;
        break;
    default: ;
    }
}

void WorldStateManager::OnSceneChangeMainStationSquare(task* tp)
{
    const auto& pos = tp->twp->pos;

    // Emerald Coast Entrance
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
        && _instance->levelEntrances.canEnter(EmeraldCoast, CurrentCharacter)
        && IsNearPosition(pos, -585, -20, 2135))
    {
        tp->twp->ang.z = _instance->levelEntrances.getLevelAndActIdFromEntrance(
            EmeraldCoast, CurrentCharacter);
    }
    //  Casinopolis
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare2
        && _instance->levelEntrances.canEnter(Casinopolis, CurrentCharacter)
        && IsNearPosition(pos, -644, -2, 880))
    {
        tp->twp->ang.z = _instance->levelEntrances.getLevelAndActIdFromEntrance(
            Casinopolis, CurrentCharacter);
    }

    // TwinklePark
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare6
        && _instance->levelEntrances.canEnter(TwinklePark, CurrentCharacter)
        && IsNearPosition(pos, 855, 45, 1770))
    {
        tp->twp->ang.z = _instance->levelEntrances.getLevelAndActIdFromEntrance(
            TwinklePark, CurrentCharacter);
    }

    // SpeedHighway (City Hall)
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1
        && _instance->levelEntrances.canEnter(SpeedHighway, CurrentCharacter)
        && IsNearPosition(pos, 270.5, -2, 234))
    {
        tp->twp->ang.z = _instance->levelEntrances.getLevelAndActIdFromEntrance(
            SpeedHighway, CurrentCharacter);
    }

    _sceneChangeMainStationSquareHook.Original(tp);
}

void WorldStateManager::OnSetNextLevelAndActCutsceneMode(Uint8 level, Uint8 act)
{
    // TODO: Maybe do this with all of the levels?
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4)
    {
        const EntityData1* player = EntityData1Ptrs[0];
        if (IsNearPosition(player->Position, 475, 20, 1375, 75))
        {
            const LevelAndActIDs levelAndAct = _instance->levelEntrances.getLevelAndActIdFromEntrance(
                SpeedHighway, CurrentCharacter);
            _setNextLevelAndActCutsceneModeHook.Original(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
            return;
        }
    }

    if (level == LevelIDs_TwinkleCircuit)
    {
        if (!_instance->_options.multipleTwinkleCircuitChecks)
        {
            _setNextLevelAndActCutsceneModeHook.Original(level, 0);
        }
        else
        {
            switch (CurrentCharacter)
            {
            case Characters_Sonic:
                // Samba GP Track
                _setNextLevelAndActCutsceneModeHook.Original(level, 2);
                break;
            case Characters_Tails:
                //Similar to original but with more stuff
                _setNextLevelAndActCutsceneModeHook.Original(level, 1);
                break;
            case Characters_Knuckles:
                //Harder Track with many sharp curves
                _setNextLevelAndActCutsceneModeHook.Original(level, 5);
                break;
            case Characters_Amy:
                //Original Track
                _setNextLevelAndActCutsceneModeHook.Original(level, 0);
                break;
            case Characters_Gamma:
                //Easier, round Track
                _setNextLevelAndActCutsceneModeHook.Original(level, 4);
                break;
            case Characters_Big:
                //Track with large walls
                _setNextLevelAndActCutsceneModeHook.Original(level, 3);
                break;
            default:
                _setNextLevelAndActCutsceneModeHook.Original(level, 0);
                break;
            }
        }
        return;
    }
    _setNextLevelAndActCutsceneModeHook.Original(level, act);
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
// TODO: Separate doors opening or not from the level entrances

// WindyValley
void WorldStateManager::HandleWindyValleyEntrance()
{
    if (_instance->levelEntrances.canEnter(WindyValley, CurrentCharacter))
    {
        const LevelAndActIDs levelAndAct = _instance->levelEntrances.getLevelAndActIdFromEntrance(
            WindyValley, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
}

// MysticRuins
void WorldStateManager::OnSceneChangeMr(const int newScene)
{
    // Jungle Final Egg tower
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 && newScene == 5)
    {
        SetNextLevelAndAct_CutsceneMode(LevelIDs_MysticRuins, 3);
        SetLevelEntrance(0);
    }
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && newScene == 4)
    {
        SetNextLevelAndAct_CutsceneMode(LevelIDs_MysticRuins, 2);
        SetLevelEntrance(4);
    }
    // Final Egg
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4
        && _instance->levelEntrances.canEnter(FinalEgg, CurrentCharacter) && (newScene == 2 || newScene ==
            3))
    {
        const LevelAndActIDs levelAndAct = _instance->levelEntrances.getLevelAndActIdFromEntrance(
            FinalEgg, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
    // Lost World
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3
        && _instance->levelEntrances.canEnter(LostWorld, CurrentCharacter) && (newScene == 6 || newScene ==
            7))
    {
        const LevelAndActIDs levelAndAct = _instance->levelEntrances.getLevelAndActIdFromEntrance(
            LostWorld, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
    // Ice Cap
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2
        && _instance->levelEntrances.canEnter(IceCap, CurrentCharacter) && newScene == 1)
    {
        const LevelAndActIDs levelAndAct = _instance->levelEntrances.getLevelAndActIdFromEntrance(
            IceCap, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
    // Red Mountain
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2
        && _instance->levelEntrances.canEnter(RedMountain, CurrentCharacter) && newScene == 0)
    {
        const LevelAndActIDs levelAndAct = _instance->levelEntrances.getLevelAndActIdFromEntrance(
            RedMountain, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
    else
    {
        sceneChangeMrHook.Original(newScene);
    }
}


// HotShelter
void WorldStateManager::OnSceneChangeEcInside(int a1, int a2)
{
    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierInside2)
        return sceneChangeECInsideHook.Original(a1, a2);

    const int doorId = *(_DWORD*)(a1 + 20);
    if (doorId != 512)
        return sceneChangeECInsideHook.Original(a1, a2);

    const LevelAndActIDs levelAndAct = _instance->levelEntrances.getLevelAndActIdFromEntrance(
        HotShelter, CurrentCharacter);
    camerahax_adventurefields();
    SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
}


// SkyDeck
void WorldStateManager::OnSceneChangeEcOutside(int a1)
{
    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierOutside6 && levelact(CurrentLevel, CurrentAct) !=
        LevelAndActIDs_EggCarrierOutside2)
        return sceneChangeECOutsideHook.Original(a1);
    const int doorId = *(_DWORD*)(a1 + 20);
    if (doorId != 256)
        return sceneChangeECOutsideHook.Original(a1);
    const LevelAndActIDs levelAndAct = _instance->levelEntrances.getLevelAndActIdFromEntrance(
        SkyDeck, CurrentCharacter);
    camerahax_adventurefields();
    SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
}

// Handles the Emerald Coast entrance
BOOL WorldStateManager::OnIsEmeraldCoastOpen()
{
    if (CurrentCharacter == Characters_Gamma)
        return false;
    return _instance->levelEntrances.canEnter(EmeraldCoast, CurrentCharacter);
}

void WorldStateManager::OnLoadEmeraldCoastGateTargets(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
        && !_instance->levelEntrances.canEnter(EmeraldCoast, CurrentCharacter))
        FreeTask(tp);
    else
        _loadEmeraldCoastGateTargetsHook.Original(tp);
}

// Handles the Windy Valley entrance
// Makes Sonic, Tails and Gamma use the winds stone
BOOL WorldStateManager::OnIsWindyValleyOpen()
{
    if (CurrentCharacter == Characters_Sonic)
        return EventFlagArray[FLAG_SONIC_MR_WINDYSTONE] && _instance->levelEntrances.canEnter(
            WindyValley, CurrentCharacter);

    if (CurrentCharacter == Characters_Tails)
        return EventFlagArray[FLAG_MILES_MR_WINDYSTONE] && _instance->levelEntrances.canEnter(
            WindyValley, CurrentCharacter);

    if (CurrentCharacter == Characters_Gamma)
        return EventFlagArray[FLAG_E102_MR_WINDYSTONE] && _instance->levelEntrances.canEnter(
            WindyValley, CurrentCharacter);
    return _instance->levelEntrances.canEnter(WindyValley, CurrentCharacter) && _instance->
        _gameStatus.unlock.keyWindStone;
}

// Handles the Casinopolis entrance
BOOL WorldStateManager::OnIsCasinoOpen()
{
    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
        return _isCasinoOpenHook.Original() && _instance->levelEntrances.canEnter(
            Casinopolis, CurrentCharacter);

    //We open the casino door for knuckles despite any story flags
    if (CurrentCharacter == Characters_Knuckles)
        return GetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_ENTRANCE_CASINO)) && _instance->
            levelEntrances.canEnter(Casinopolis, CurrentCharacter);

    return _instance->levelEntrances.canEnter(Casinopolis, CurrentCharacter);
}

// Handles the Twinkle Park door
int WorldStateManager::OnTwinkleParkDoor(const char character)
{
    return _instance->levelEntrances.canEnter(TwinklePark, CurrentCharacter);
}

// Handles the Twinkle Circuit door
int WorldStateManager::OnTwinkleCircuitDoor(const char character)
{
    return _instance->_options.twinkleCircuitCheck;
}


// Speed Highway
BOOL WorldStateManager::OnIsSpeedHighwayShutterOpen()
{
    if (CurrentCharacter == Characters_Sonic)
        return _isSpeedHighwayShutterOpenHook.Original();
    return _instance->levelEntrances.canEnter(SpeedHighway, CurrentCharacter)
        && _instance->_gameStatus.unlock.keyEmployeeCard;
}

void WorldStateManager::OnLoadSpeedHighwayShutter(task* tp)
{
    if ((CurrentCharacter == Characters_Gamma || CurrentCharacter == Characters_Amy || CurrentCharacter ==
            Characters_Big)
        && _instance->levelEntrances.canEnter(SpeedHighway, CurrentCharacter)
        && _instance->_gameStatus.unlock.keyEmployeeCard)
        FreeTask(tp);
    else
        _loadSpeedHighwayShutterHook.Original(tp);
}

void WorldStateManager::OnLoadSpeedHighwayShutter2(task* tp)
{
    if ((CurrentCharacter == Characters_Gamma || CurrentCharacter == Characters_Amy || CurrentCharacter ==
            Characters_Big)
        && _instance->levelEntrances.canEnter(SpeedHighway, CurrentCharacter)
        && _instance->_gameStatus.unlock.keyEmployeeCard)
        FreeTask(tp);
    else
        _loadSpeedHighwayShutter2Hook.Original(tp);
}

void WorldStateManager::OnOHighEle(ObjectMaster* tp)
{
    OEleboxIn(tp);
}

BOOL WorldStateManager::OnIsCityHallDoorOpen()
{
    return _instance->levelEntrances.canEnter(SpeedHighway, CurrentCharacter) &&
        _isCityHallDoorOpenHook.Original();
}

//We don't create Knuckles barricade if he doesn't have access to the level
void WorldStateManager::OnLoadBarricade(task* tp)
{
    if (CurrentCharacter == Characters_Knuckles && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1)
        if (!_instance->levelEntrances.canEnter(SpeedHighway, CurrentCharacter))
            return FreeTask(tp);

    _loadBarricadeHook.Original(tp);
}

BOOL WorldStateManager::OnIsFinalEggGammaDoorOpen(EntityData1* entity)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3)
        return true;

    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_MysticRuins4)
        return _isFinalEggGammaDoorOpenHook.Original(entity);

    if (entity->Position.y < 100)
        return _isFinalEggGammaDoorOpenHook.Original(entity);

    if (entity->Position.z < -150)
    {
        if (CurrentCharacter != Characters_Gamma)
            return false;
        return _instance->levelEntrances.canEnter(FinalEgg, CurrentCharacter);
    }
    return true;
}

void WorldStateManager::OnLoadSceneChangeMr(task* tp)
{
    // Final Egg
    if ((CurrentCharacter != Characters_Gamma)
        && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && tp->twp->ang.x == 3)
    {
        if (!_instance->levelEntrances.canEnter(FinalEgg, CurrentCharacter))
        {
            return FreeTask(tp);
        }
    }

    //Ice Cap
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2 && tp->twp->ang.x == 1)
    {
        if (!_instance->levelEntrances.canEnter(IceCap, CurrentCharacter))
        {
            return FreeTask(tp);
        }
    }

    _loadSceneChangeMrHook.Original(tp);
}

void WorldStateManager::OnFinalEggDoorCheckA(const int a1)
{
    const int bufferCharacter = CurrentCharacter;
    CurrentCharacter = Characters_Sonic;
    finalEggDoorCheckAHook.Original(a1);
    CurrentCharacter = bufferCharacter;
}

short WorldStateManager::OnFinalEggDoorCheckB(const int a1)
{
    const int bufferCharacter = CurrentCharacter;
    CurrentCharacter = Characters_Sonic;
    const int result = finalEggDoorCheckBHook.Original(a1);
    CurrentCharacter = bufferCharacter;
    return result;
}

BOOL WorldStateManager::OnIsFinalEggTowerActive()
{
    return true;
}

BOOL WorldStateManager::OnIsFinalEggDoorActive()
{
    return true;
}

//Makes knuckles able to enter the lost world using the keys
BOOL WorldStateManager::OnIsLostWorldBackEntranceOpen()
{
    if (CurrentCharacter == Characters_Knuckles)
        return ((EventFlagArray[FLAG_KNUCKLES_MR_REDCUBE] && EventFlagArray[FLAG_KNUCKLES_MR_BLUECUBE]) ||
                _instance->_gameStatus.visitedLevels.lostWorldEntranceVisitedAsKnuckles)
            && _instance->levelEntrances.canEnter(LostWorld, CurrentCharacter);

    return false;
}

//Allows everyone to enter Lost World
BOOL WorldStateManager::OnIsLostWorldFrontEntranceOpen()
{
    if (CurrentCharacter == Characters_Knuckles)
        return false;
    return _instance->levelEntrances.canEnter(LostWorld, CurrentCharacter);
}

void WorldStateManager::OnLostWorldEntranceCollision(const int a1)
{
    const int bufferCharacter = CurrentCharacter;
    CurrentCharacter = Characters_Sonic;
    lostWorldEntranceCollisionHook.Original(a1);
    CurrentCharacter = bufferCharacter;
}

BOOL WorldStateManager::OnIsAngelIslandOpen()
{
    return _instance->_gameStatus.unlock.keyDynamite;
}

//Prevents the monkey from blocking the entrance to Red Mountain for knuckles
BOOL WorldStateManager::OnIsMonkeyDoorOpen(int a1)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1)
        return true;

    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Gamma
        || CurrentCharacter == Characters_Knuckles)
        return _isMonkeyDead(1) && _instance->levelEntrances.canEnter(RedMountain, CurrentCharacter);

    //For everyone else, we return true if we are in the main mystic ruins area
    return _instance->levelEntrances.canEnter(RedMountain, CurrentCharacter);
}

// We only load the monkey if it's needed for opening the door
void WorldStateManager::OnLoadMonkeyCage(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        if (CurrentCharacter == Characters_Tails || CurrentCharacter == Characters_Big
            || CurrentCharacter == Characters_Amy)
            return FreeTask(tp);
        if (!_instance->levelEntrances.canEnter(RedMountain, CurrentCharacter))
            return FreeTask(tp);
    }
    _loadMonkeyCageHook.Original(tp);
}

// Removed the ladder on Ice Cap
void WorldStateManager::OnLoadLongLadderMr(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        if (!_instance->levelEntrances.canEnter(IceCap, CurrentCharacter))
        {
            return FreeTask(tp);
        }
    }
    _loadLongLadderMrHook.Original(tp);
}

BOOL WorldStateManager::OnPreventKeyStoneFromSpawning(int a1)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2
        && ((CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Knuckles
            || CurrentCharacter == Characters_Gamma) && _instance->levelEntrances.canEnter(
            IceCap, CurrentCharacter)))
    {
        return _instance->_gameStatus.unlock.keyIceStone;
    }

    return _preventKeyStoneFromSpawningHook.Original(a1);
}

// HotShelter
int WorldStateManager::OnEggCarrierEggDoor(const int a1)
{
    // Middle door
    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierInside2)
        return eggCarrierEggDoorHook.Original(a1);

    if (*reinterpret_cast<BYTE*>(a1 + 1) != 6)
        return eggCarrierEggDoorHook.Original(a1);

    if (!_instance->levelEntrances.canEnter(HotShelter, CurrentCharacter))
        return false;

    const EntityData1* player = EntityData1Ptrs[0];
    const double dz = player->Position.z - *(float*)(a1 + 40);
    const double dy = player->Position.y - *(float*)(a1 + 36);
    const double dx = player->Position.x - *(float*)(a1 + 32);
    const double distance = dx * dx + dy * dy + dz * dz;
    if (squareroot(distance) > 50.0)
        return false;

    if (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big)
        return IsSwitchPressed(1);
    return true;
}

int WorldStateManager::OnEggCarrierOutsideDoor(const int a1)
{
    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierOutside1)
        return eggCarrierOutsideDoorHook.Original(a1);

    const int doorId = *reinterpret_cast<BYTE*>(a1 + 1);
    if (doorId != 1)
        return eggCarrierOutsideDoorHook.Original(a1);

    const EntityData1* player = EntityData1Ptrs[0];
    const double dz = player->Position.z - *(float*)(a1 + 40);
    const double dy = player->Position.y - *(float*)(a1 + 36);
    const double dx = player->Position.x - *(float*)(a1 + 32);
    const double distance = dx * dx + dy * dy + dz * dz;
    if (squareroot(distance) > 50.0)
        return false;
    return true;
}


void WorldStateManager::OnLoadPoolWater(task* tp)
{
    if (CurrentCharacter != Characters_Knuckles)
        return _loadPoolWaterHook.Original(tp);

    if (!_instance->levelEntrances.canEnter(SkyDeck, CurrentCharacter))
        return _loadPoolWaterHook.Original(tp);

    FreeTask(tp);
}

void WorldStateManager::OnLoadPoolDoor(task* tp)
{
    if (CurrentCharacter != Characters_Knuckles)
        return _loadPoolDoorHook.Original(tp);

    if (!_instance->levelEntrances.canEnter(SkyDeck, CurrentCharacter))
        return _loadPoolDoorHook.Original(tp);
    FreeTask(tp);
}

int WorldStateManager::OnSkyDeckDoor(EntityData1* a1)
{
    if (!_instance->levelEntrances.canEnter(SkyDeck, CurrentCharacter))
        return false;

    if (CurrentCharacter != Characters_Knuckles
        && levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierOutside2)
        return false;

    if (CurrentCharacter == Characters_Knuckles
        && levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierOutside6)
        return false;

    const EntityData1* player = EntityData1Ptrs[0];
    const double dz = player->Position.z - a1->Position.z;
    const double dy = player->Position.y - a1->Position.y;
    const double dx = player->Position.x - a1->Position.x;
    const double distance = squareroot(dx * dx + dy * dy + dz * dz);

    return distance <= 50.0;
}
