#include "LevelEntranceManager.h"

UsercallFuncVoid(sceneChangeMrHook, (int a1), (a1), 0x539220, rEBX);
UsercallFuncVoid(sceneChangeECInsideHook, (int a1, int a2), (a1,a2), 0x52D690, rEAX, rECX);
UsercallFuncVoid(sceneChangeECOutsideHook, (int a1), (a1), 0x524FE0, rEAX);
UsercallFunc(int, twinkleParkDoorHook, (char tpChar), (tpChar), 0x63EA90, rEAX, rESI);
UsercallFunc(int, eggCarrierInsideEggDoorHook, (int a1), (a1), 0x52B420, rEAX, rESI);
UsercallFunc(int, eggCarrierOutsideDoorHook, (int a1), (a1), 0x524070, rEAX, rESI);
UsercallFunc(int, skyDeckDoorHook, (EntityData1 * a1), (a1), 0x51DEB0, rEAX, rESI);

LevelEntranceManager::LevelEntranceManager(Options& options, Settings& settings, GameStatus& gameStatus):
    _options(options), _settings(settings), _gameStatus(gameStatus), _doorIndicatorManager(DoorIndicatorManager::Init())
{
    _mysticRuinsKeyHook.Hook(OnMysticRuinsKey);
    _employeeCardHook.Hook(OnEmployeeCard);
    _setStartPosReturnToFieldHook.Hook(OnSetStartPosReturnToField);
    _sceneChangeMainStationSquareHook.Hook(OnSceneChangeMainStationSquare);
    _setNextLevelAndActCutsceneModeHook.Hook(OnSetNextLevelAndActCutsceneMode);
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
    _isLostWorldBackEntranceOpenHook.Hook(OnIsLostWorldBackEntranceOpen);
    _isLostWorldFrontEntranceOpenHook.Hook(OnIsLostWorldFrontEntranceOpen);
    _isMonkeyDoorOpenHook.Hook(OnIsMonkeyDoorOpen);
    _loadMonkeyCageHook.Hook(OnLoadMonkeyCage);
    _loadLongLadderMrHook.Hook(OnLoadLongLadderMr);
    _loadPoolWaterHook.Hook(OnLoadPoolWater);
    _loadPoolDoorHook.Hook(OnLoadPoolDoor);
    _preventKeyStoneFromSpawningHook.Hook(OnPreventKeyStoneFromSpawning);

    eggCarrierInsideEggDoorHook.Hook(OnEggCarrierEggDoor);
    eggCarrierOutsideDoorHook.Hook(OnEggCarrierOutsideDoor);
    skyDeckDoorHook.Hook(OnSkyDeckDoor);
    twinkleParkDoorHook.Hook(OnTwinkleParkDoor);
    sceneChangeECOutsideHook.Hook(OnSceneChangeEcOutside);
    sceneChangeMrHook.Hook(OnSceneChangeMr);
    sceneChangeECInsideHook.Hook(OnSceneChangeEcInside);

    WriteCall(reinterpret_cast<void*>(0x537F52), &HandleWindyValleyEntrance);
    WriteCall(reinterpret_cast<void*>(0x537F64), &HandleWindyValleyEntrance);
}

void LevelEntranceManager::SetLevelEntrances()
{
    this->_levelEntrances = LevelEntrances();

    for (const auto& [first, second] : _options.levelEntrancesMap)
    {
        const auto levelEntrance = static_cast<Levels>(first);
        const auto actualLevel = static_cast<Levels>(second);
        _levelEntrances.addRelationship(levelEntrance, actualLevel);
    }

    this->_gameStatus.visitedLevels.emeraldCoastEntranceActualLevel = _levelEntrances.
        getLevelInitialsFromEntrance(EmeraldCoast);
    this->_gameStatus.visitedLevels.windyValleyEntranceActualLevel = _levelEntrances.
        getLevelInitialsFromEntrance(WindyValley);
    this->_gameStatus.visitedLevels.casinopolisEntranceActualLevel = _levelEntrances.
        getLevelInitialsFromEntrance(Casinopolis);
    this->_gameStatus.visitedLevels.iceCapEntranceActualLevel = _levelEntrances.getLevelInitialsFromEntrance(IceCap);
    this->_gameStatus.visitedLevels.twinkleParkEntranceActualLevel = _levelEntrances.
        getLevelInitialsFromEntrance(TwinklePark);
    this->_gameStatus.visitedLevels.speedHighwayEntranceActualLevel = _levelEntrances.
        getLevelInitialsFromEntrance(SpeedHighway);
    this->_gameStatus.visitedLevels.redMountainEntranceActualLevel = _levelEntrances.
        getLevelInitialsFromEntrance(RedMountain);
    this->_gameStatus.visitedLevels.skyDeckEntranceActualLevel = _levelEntrances.getLevelInitialsFromEntrance(SkyDeck);
    this->_gameStatus.visitedLevels.lostWorldEntranceActualLevel = _levelEntrances.
        getLevelInitialsFromEntrance(LostWorld);
    this->_gameStatus.visitedLevels.finalEggEntranceActualLevel = _levelEntrances.
        getLevelInitialsFromEntrance(FinalEgg);
    this->_gameStatus.visitedLevels.hotShelterEntranceActualLevel = _levelEntrances.
        getLevelInitialsFromEntrance(HotShelter);
}

void LevelEntranceManager::ShowLevelEntranceArrows()
{
    if (!this->_options.entranceRandomizer)
        return;
    if (!this->_settings.showEntranceIndicators)
        return;
    for (LevelArrow levelArrow : _levelArrows)
    {
        if (CurrentStageAndAct != levelArrow.levelAndAct)
            continue;

        if (!_instance->_levelEntrances.canEnter(levelArrow.entrance, CurrentCharacter))
            _doorIndicatorManager.DrawDisable(levelArrow.postion, levelArrow.angle);
        else if (levelArrow.isForCharacter(static_cast<Characters>(CurrentCharacter)))
            _doorIndicatorManager.DrawCorrect(levelArrow.postion, levelArrow.angle);
        else
            _doorIndicatorManager.DrawOtherDoor(levelArrow.postion, levelArrow.angle);
    }
}

void LevelEntranceManager::UpdateVisitedLevels(const int visitedLevel)
{
    const LevelIDs visitedEntrance = _levelEntrances.getEntranceLevelIdFromLevel(static_cast<LevelIDs>(visitedLevel));
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


void LevelEntranceManager::OnMysticRuinsKey(task* tp)
{
    // We prevent the wind stone from spawning if the player doesn't have that level
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1
        && !_instance->_levelEntrances.canEnter(WindyValley, CurrentCharacter))
        if (IsNearPosition(tp->twp->pos, 1392.5, 191.5, 863.5))
            return;

    // We don't spawn the golden/silver keys for knuckles if he can't enter LostWorld
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 && CurrentCharacter == Characters_Knuckles)
    {
        if (!_instance->_levelEntrances.canEnter(LostWorld, CurrentCharacter))
            return;
    }
    _mysticRuinsKeyHook.Original(tp);
}

void LevelEntranceManager::OnEmployeeCard(task* tp)
{
    // We prevent the Employee card from spawning if the player can't use it
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4
        && !_instance->_levelEntrances.canEnter(SpeedHighway, CurrentCharacter))
        return;

    _employeeCardHook.Original(tp);
}


void LevelEntranceManager::OnSetStartPosReturnToField(task* tp)
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
                                   _levelEntrances.getEntranceLevelIdFromLevel(static_cast<LevelIDs>(CurrentLevel));

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

void LevelEntranceManager::OnSceneChangeMainStationSquare(task* tp)
{
    const auto& pos = tp->twp->pos;

    // Emerald Coast Entrance
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
        && _instance->_levelEntrances.canEnter(EmeraldCoast, CurrentCharacter)
        && IsNearPosition(pos, -585, -20, 2135))
    {
        tp->twp->ang.z = _instance->_levelEntrances.getLevelAndActIdFromEntrance(
            EmeraldCoast, CurrentCharacter);
    }
    //  Casinopolis
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare2
        && _instance->_levelEntrances.canEnter(Casinopolis, CurrentCharacter)
        && IsNearPosition(pos, -644, -2, 880))
    {
        tp->twp->ang.z = _instance->_levelEntrances.getLevelAndActIdFromEntrance(
            Casinopolis, CurrentCharacter);
    }

    // TwinklePark
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare6
        && _instance->_levelEntrances.canEnter(TwinklePark, CurrentCharacter)
        && IsNearPosition(pos, 855, 45, 1770))
    {
        tp->twp->ang.z = _instance->_levelEntrances.getLevelAndActIdFromEntrance(
            TwinklePark, CurrentCharacter);
    }

    // SpeedHighway (City Hall)
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1
        && _instance->_levelEntrances.canEnter(SpeedHighway, CurrentCharacter)
        && IsNearPosition(pos, 270.5, -2, 234))
    {
        tp->twp->ang.z = _instance->_levelEntrances.getLevelAndActIdFromEntrance(
            SpeedHighway, CurrentCharacter);
    }

    _sceneChangeMainStationSquareHook.Original(tp);
}

void LevelEntranceManager::OnSetNextLevelAndActCutsceneMode(Uint8 level, Uint8 act)
{
    // TODO: Maybe do this with all of the levels?
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4)
    {
        const EntityData1* player = EntityData1Ptrs[0];
        if (IsNearPosition(player->Position, 475, 20, 1375, 75))
        {
            const LevelAndActIDs levelAndAct = _instance->_levelEntrances.getLevelAndActIdFromEntrance(
                SpeedHighway, CurrentCharacter);
            _setNextLevelAndActCutsceneModeHook.Original(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
            return;
        }
    }

    _setNextLevelAndActCutsceneModeHook.Original(level, act);
}

// WindyValley
void LevelEntranceManager::HandleWindyValleyEntrance()
{
    if (_instance->_levelEntrances.canEnter(WindyValley, CurrentCharacter))
    {
        const LevelAndActIDs levelAndAct = _instance->_levelEntrances.getLevelAndActIdFromEntrance(
            WindyValley, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
}

// MysticRuins
void LevelEntranceManager::OnSceneChangeMr(const int newScene)
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
        && _instance->_levelEntrances.canEnter(FinalEgg, CurrentCharacter) && (newScene == 2 || newScene ==
            3))
    {
        const LevelAndActIDs levelAndAct = _instance->_levelEntrances.getLevelAndActIdFromEntrance(
            FinalEgg, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
    // Lost World
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3
        && _instance->_levelEntrances.canEnter(LostWorld, CurrentCharacter) && (newScene == 6 || newScene ==
            7))
    {
        const LevelAndActIDs levelAndAct = _instance->_levelEntrances.getLevelAndActIdFromEntrance(
            LostWorld, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
    // Ice Cap
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2
        && _instance->_levelEntrances.canEnter(IceCap, CurrentCharacter) && newScene == 1)
    {
        const LevelAndActIDs levelAndAct = _instance->_levelEntrances.getLevelAndActIdFromEntrance(
            IceCap, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
    // Red Mountain
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2
        && _instance->_levelEntrances.canEnter(RedMountain, CurrentCharacter) && newScene == 0)
    {
        const LevelAndActIDs levelAndAct = _instance->_levelEntrances.getLevelAndActIdFromEntrance(
            RedMountain, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
    else
    {
        sceneChangeMrHook.Original(newScene);
    }
}


// HotShelter
void LevelEntranceManager::OnSceneChangeEcInside(int a1, int a2)
{
    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierInside2)
        return sceneChangeECInsideHook.Original(a1, a2);

    const int doorId = *(_DWORD*)(a1 + 20);
    if (doorId != 512)
        return sceneChangeECInsideHook.Original(a1, a2);

    const LevelAndActIDs levelAndAct = _instance->_levelEntrances.getLevelAndActIdFromEntrance(
        HotShelter, CurrentCharacter);
    camerahax_adventurefields();
    SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
}

// SkyDeck
void LevelEntranceManager::OnSceneChangeEcOutside(int a1)
{
    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierOutside6 && levelact(CurrentLevel, CurrentAct) !=
        LevelAndActIDs_EggCarrierOutside2)
        return sceneChangeECOutsideHook.Original(a1);
    const int doorId = *(_DWORD*)(a1 + 20);
    if (doorId != 256)
        return sceneChangeECOutsideHook.Original(a1);
    const LevelAndActIDs levelAndAct = _instance->_levelEntrances.getLevelAndActIdFromEntrance(
        SkyDeck, CurrentCharacter);
    camerahax_adventurefields();
    SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
}


// Handles the Emerald Coast entrance
BOOL LevelEntranceManager::OnIsEmeraldCoastOpen()
{
    if (CurrentCharacter == Characters_Gamma)
        return false;
    return _instance->_levelEntrances.canEnter(EmeraldCoast, CurrentCharacter);
}

void LevelEntranceManager::OnLoadEmeraldCoastGateTargets(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
        && !_instance->_levelEntrances.canEnter(EmeraldCoast, CurrentCharacter))
        FreeTask(tp);
    else
        _loadEmeraldCoastGateTargetsHook.Original(tp);
}

// Handles the Windy Valley entrance
// Makes Sonic, Tails and Gamma use the winds stone
BOOL LevelEntranceManager::OnIsWindyValleyOpen()
{
    if (CurrentCharacter == Characters_Sonic)
        return EventFlagArray[FLAG_SONIC_MR_WINDYSTONE] && _instance->_levelEntrances.canEnter(
            WindyValley, CurrentCharacter);

    if (CurrentCharacter == Characters_Tails)
        return EventFlagArray[FLAG_MILES_MR_WINDYSTONE] && _instance->_levelEntrances.canEnter(
            WindyValley, CurrentCharacter);

    if (CurrentCharacter == Characters_Gamma)
        return EventFlagArray[FLAG_E102_MR_WINDYSTONE] && _instance->_levelEntrances.canEnter(
            WindyValley, CurrentCharacter);
    return _instance->_levelEntrances.canEnter(WindyValley, CurrentCharacter);
}

// Handles the Casinopolis entrance
BOOL LevelEntranceManager::OnIsCasinoOpen()
{
    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
        return _isCasinoOpenHook.Original() && _instance->_levelEntrances.canEnter(
            Casinopolis, CurrentCharacter);

    //We open the casino door for knuckles despite any story flags
    if (CurrentCharacter == Characters_Knuckles)
        return GetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_ENTRANCE_CASINO)) && _instance->
            _levelEntrances.canEnter(Casinopolis, CurrentCharacter);

    return _instance->_levelEntrances.canEnter(Casinopolis, CurrentCharacter);
}

// Handles the Twinkle Park door
int LevelEntranceManager::OnTwinkleParkDoor(const char character)
{
    return _instance->_levelEntrances.canEnter(TwinklePark, CurrentCharacter);
}


// Speed Highway
//TODO: Check/move the unlock part to the main manager
BOOL LevelEntranceManager::OnIsSpeedHighwayShutterOpen()
{
    if (CurrentCharacter == Characters_Sonic)
        return _isSpeedHighwayShutterOpenHook.Original();
    return _instance->_levelEntrances.canEnter(SpeedHighway, CurrentCharacter)
        && _instance->_gameStatus.unlock.keyEmployeeCard;
}

void LevelEntranceManager::OnLoadSpeedHighwayShutter(task* tp)
{
    //TODO: Animate instead of removing the task
    if ((CurrentCharacter == Characters_Gamma || CurrentCharacter == Characters_Amy || CurrentCharacter ==
            Characters_Big)
        && _instance->_levelEntrances.canEnter(SpeedHighway, CurrentCharacter)
        && _instance->_gameStatus.unlock.keyEmployeeCard)
        FreeTask(tp);
    else
        _loadSpeedHighwayShutterHook.Original(tp);
}

void LevelEntranceManager::OnLoadSpeedHighwayShutter2(task* tp)
{
    //TODO: Animate instead of removing the task
    if ((CurrentCharacter == Characters_Gamma || CurrentCharacter == Characters_Amy || CurrentCharacter ==
            Characters_Big)
        && _instance->_levelEntrances.canEnter(SpeedHighway, CurrentCharacter)
        && _instance->_gameStatus.unlock.keyEmployeeCard)
        FreeTask(tp);
    else
        _loadSpeedHighwayShutter2Hook.Original(tp);
}


void LevelEntranceManager::OnOHighEle(ObjectMaster* tp)
{
    OEleboxIn(tp);
}


BOOL LevelEntranceManager::OnIsCityHallDoorOpen()
{
    return _instance->_levelEntrances.canEnter(SpeedHighway, CurrentCharacter) &&
        _isCityHallDoorOpenHook.Original();
}

//We don't create Knuckles barricade if he doesn't have access to the level
void LevelEntranceManager::OnLoadBarricade(task* tp)
{
    if (CurrentCharacter == Characters_Knuckles && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1)
        if (!_instance->_levelEntrances.canEnter(SpeedHighway, CurrentCharacter))
            return FreeTask(tp);

    _loadBarricadeHook.Original(tp);
}

BOOL LevelEntranceManager::OnIsFinalEggGammaDoorOpen(EntityData1* entity)
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
        return _instance->_levelEntrances.canEnter(FinalEgg, CurrentCharacter);
    }
    return true;
}

void LevelEntranceManager::OnLoadSceneChangeMr(task* tp)
{
    // Final Egg
    if ((CurrentCharacter != Characters_Gamma)
        && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && tp->twp->ang.x == 3)
    {
        if (!_instance->_levelEntrances.canEnter(FinalEgg, CurrentCharacter))
        {
            return FreeTask(tp);
        }
    }

    //Ice Cap
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2 && tp->twp->ang.x == 1)
    {
        if (!_instance->_levelEntrances.canEnter(IceCap, CurrentCharacter))
        {
            return FreeTask(tp);
        }
    }

    _loadSceneChangeMrHook.Original(tp);
}

//Makes knuckles able to enter the lost world using the keys
BOOL LevelEntranceManager::OnIsLostWorldBackEntranceOpen()
{
    if (CurrentCharacter == Characters_Knuckles)
        return ((EventFlagArray[FLAG_KNUCKLES_MR_REDCUBE] && EventFlagArray[FLAG_KNUCKLES_MR_BLUECUBE]) ||
                _instance->_gameStatus.visitedLevels.lostWorldEntranceVisitedAsKnuckles)
            && _instance->_levelEntrances.canEnter(LostWorld, CurrentCharacter);

    return false;
}

//Allows everyone to enter Lost World
BOOL LevelEntranceManager::OnIsLostWorldFrontEntranceOpen()
{
    if (CurrentCharacter == Characters_Knuckles)
        return false;
    return _instance->_levelEntrances.canEnter(LostWorld, CurrentCharacter);
}

//Prevents the monkey from blocking the entrance to Red Mountain for knuckles
BOOL LevelEntranceManager::OnIsMonkeyDoorOpen(int a1)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1)
        return true;

    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Gamma
        || CurrentCharacter == Characters_Knuckles)
        return _isMonkeyDead(1) && _instance->_levelEntrances.canEnter(RedMountain, CurrentCharacter);

    //For everyone else, we return true if we are in the main mystic ruins area
    return _instance->_levelEntrances.canEnter(RedMountain, CurrentCharacter);
}

// We only load the monkey if it's needed for opening the door
void LevelEntranceManager::OnLoadMonkeyCage(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        if (CurrentCharacter == Characters_Tails || CurrentCharacter == Characters_Big
            || CurrentCharacter == Characters_Amy)
            return FreeTask(tp);
        if (!_instance->_levelEntrances.canEnter(RedMountain, CurrentCharacter))
            return FreeTask(tp);
    }
    _loadMonkeyCageHook.Original(tp);
}

// Removed the ladder on Ice Cap
void LevelEntranceManager::OnLoadLongLadderMr(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        if (!_instance->_levelEntrances.canEnter(IceCap, CurrentCharacter))
        {
            return FreeTask(tp);
        }
    }
    _loadLongLadderMrHook.Original(tp);
}


// HotShelter
int LevelEntranceManager::OnEggCarrierEggDoor(const int a1)
{
    // Middle door
    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierInside2)
        return eggCarrierInsideEggDoorHook.Original(a1);

    if (*reinterpret_cast<BYTE*>(a1 + 1) != 6)
        return eggCarrierInsideEggDoorHook.Original(a1);

    if (!_instance->_levelEntrances.canEnter(HotShelter, CurrentCharacter))
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

int LevelEntranceManager::OnEggCarrierOutsideDoor(const int a1)
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


void LevelEntranceManager::OnLoadPoolWater(task* tp)
{
    if (CurrentCharacter != Characters_Knuckles)
        return _loadPoolWaterHook.Original(tp);

    if (!_instance->_levelEntrances.canEnter(SkyDeck, CurrentCharacter))
        return _loadPoolWaterHook.Original(tp);

    FreeTask(tp);
}

void LevelEntranceManager::OnLoadPoolDoor(task* tp)
{
    if (CurrentCharacter != Characters_Knuckles)
        return _loadPoolDoorHook.Original(tp);

    if (!_instance->_levelEntrances.canEnter(SkyDeck, CurrentCharacter))
        return _loadPoolDoorHook.Original(tp);
    FreeTask(tp);
}

int LevelEntranceManager::OnSkyDeckDoor(EntityData1* a1)
{
    if (!_instance->_levelEntrances.canEnter(SkyDeck, CurrentCharacter))
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

BOOL LevelEntranceManager::OnPreventKeyStoneFromSpawning(int a1)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2
        && ((CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Knuckles
            || CurrentCharacter == Characters_Gamma) && _instance->_levelEntrances.canEnter(
            IceCap, CurrentCharacter)))
    {
        return true;
    }

    return _preventKeyStoneFromSpawningHook.Original(a1);
}
