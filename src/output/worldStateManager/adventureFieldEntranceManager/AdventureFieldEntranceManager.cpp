#include "AdventureFieldEntranceManager.h"

UsercallFunc(int, twinkleCircuitDoorHook, (char tpChar), (tpChar), 0x63F810, rEAX, rESI);
UsercallFunc(int, twinkleParkDoorHook, (char tpChar), (tpChar), 0x63EA90, rEAX, rESI);
UsercallFunc(signed int, mrCartHook, (task* tp), (tp), 0x53DC60, rEAX, rESI);
UsercallFuncVoid(sceneChangeMrHook, (int a1), (a1), 0x539220, rEBX);
UsercallFuncVoid(sceneChangeECInsideHook, (int a1, int a2), (a1,a2), 0x52D690, rEAX, rECX);
UsercallFunc(int, eggCarrierInsideEggDoorHook, (const taskwk* twp), (twp), 0x52B420, rEAX, rESI);
UsercallFunc(int, eggCarrierOutsideEggDoorHook, (const taskwk* twp), (twp), 0x524070, rEAX, rESI);
UsercallFunc(int, skyDeckDoorHook, (taskwk* twp), (twp), 0x51DEB0, rEAX, rESI);

AdventureFieldEntranceManager::AdventureFieldEntranceManager(Options& options, GameStatus& gameStatus) :
    _options(options), _gameStatus(gameStatus),
    _adventureFieldEntranceMap(AdventureFieldEntranceMap::Init()),
    _doorIndicatorManager(DoorIndicatorManager::Init())
{
    _setNextLevelAndActCutsceneModeHook.Hook(OnSetNextLevelAndActCutsceneMode);
    _getEntranceSs.Hook(OnGetEntranceSs);
    _getEntranceEc.Hook(OnGetEntranceEc);

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
    eggCarrierInsideEggDoorHook.Hook(OnEggCarrierInsideEggDoor);
    eggCarrierOutsideEggDoorHook.Hook(OnEggCarrierOutsideEggDoor);
    skyDeckDoorHook.Hook(OnSkyDeckDoor);
    _eggCapHook.Hook(OnEggCap);
    _springMainHook.Hook(OnSpringMain);
    _isMonorailEnabledHook.Hook(OnIsMonorailEnabled);
    _isOutsideEggLiftEnabledHook.Hook(OnIsOutsideEggLiftEnabled);
    _isInsideEggLiftEnabledHook.Hook(OnIsInsideEggLiftEnabled);
    _loadPoolDoorHook.Hook(OnLoadPoolDoor);
    _isEggCarrierSunkHook.Hook(IsEggCarrierSunk);
    _isEcBoatEnabledHook.Hook(IsEcBoatEnabled);
    _isEcRaftEnabledHook.Hook(IsEcRaftEnabled);
    _hiddenGateMainHook.Hook(OnHiddenGateMain);
    _chaoWarpMainHook.Hook(OnChaoWarpMain);
    _chaoGardenChanceSceneHook.Hook(OnChaoGardenChanceScene);


    //Allows players to return to the adventure field when quitting boss fights
    WriteData<1>((void*)0x415F46, 0x19);


    // Change the comparison value from 3 to 9
    WriteData<1>((void*)0x638BF6, 0x09);
    // Change the jump from jz (0x74) to jnz (0x75)
    WriteData<1>((void*)0x638C00, 0x75);

    // this->_doorLogicStrategy = std::make_unique<DefaultDoorLogicStrategy>(options, gameStatus);
    this->_doorLogicStrategy = std::make_unique<EmblemGatingDoorLogicStrategy>(
        options, gameStatus, _adventureFieldEntranceMap);
}

bool AdventureFieldEntranceManager::IsDoorOpen(const EntranceId entranceId)
{
    return _doorLogicStrategy->IsDoorOpen(entranceId);
}

bool AdventureFieldEntranceManager::ShowDisableDoorIndicator(const EntranceId entranceId)
{
    return _doorLogicStrategy->ShowDisableDoorIndicator(entranceId);
}


void AdventureFieldEntranceManager::OnSetNextLevelAndActCutsceneMode(const Uint8 level, const Uint8 act)
{
    if (!_instance->_options.emblemGating)
        return _setNextLevelAndActCutsceneModeHook.Original(level, act);

    PrintDebug("------AdventureFieldEntranceManager: Setting next level and act to %d, %d \n", level, act);
    LevelAndActIDs currentLevelAndAct = static_cast<LevelAndActIDs>(CurrentStageAndAct);
    if (CurrentChaoStage == SADXChaoStage_EggCarrier)
    {
        currentLevelAndAct = LevelAndActIDs_ECGarden;
    }
    else if (CurrentChaoStage == SADXChaoStage_StationSquare)
    {
        currentLevelAndAct = LevelAndActIDs_SSGarden;
    }
    else if (CurrentChaoStage == SADXChaoStage_MysticRuins)
    {
        currentLevelAndAct = LevelAndActIDs_MRGarden;
    }

    AdventureFieldEntrance* newEntrance = _instance->_adventureFieldEntranceMap.GetNewConnection(
        currentLevelAndAct, GET_LEVEL_ACT(level, act), _instance->_isEggCarrierTransformed);


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
    if (!_instance->_options.emblemGating)
        return _getEntranceSs.Original(twp);

    if (CurrentStageAndAct == LevelAndActIDs_StationSquare3)
    {
        if (GetLevelEntranceID() == 1)
        {
            twp->pos = {395, -120, 1200};
            twp->ang = {0, 0xC000, 0};
            return;
        }
    }
    else if (CurrentStageAndAct == LevelAndActIDs_StationSquare6)
    {
        if (GetLevelEntranceID() == 0)
        {
            twp->pos = {688.13f, 50, 1771.5f};
            twp->ang = {0, 0, 0};
            return;
        }
    }
    else if (CurrentStageAndAct == LevelAndActIDs_StationSquare4)
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

void AdventureFieldEntranceManager::OnGetEntranceEc(taskwk* twp)
{
    if (!_instance->_options.emblemGating)
        return _getEntranceEc.Original(twp);

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

inline NJS_TEXANIM emblem_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 1, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM line_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 2, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_0_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 3, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_1_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 4, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_2_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 5, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_3_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 6, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_4_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 7, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_5_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 8, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_6_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 9, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_7_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 10, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_8_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 11, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_9_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 12, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM base_map[] = {{18, 18, 9, 9, 255, 255, 0, 0, 13, NJD_SPRITE_COLOR}};

// Helper to get the correct number anim
inline NJS_TEXANIM* GetNumberAnim(int num)
{
    static NJS_TEXANIM* number_anims[] = {
        number_0_lock_anim, number_1_lock_anim, number_2_lock_anim, number_3_lock_anim, number_4_lock_anim,
        number_5_lock_anim, number_6_lock_anim, number_7_lock_anim, number_8_lock_anim, number_9_lock_anim
    };
    return (num >= 0 && num <= 9) ? number_anims[num] : number_0_lock_anim;
}

void AdventureFieldEntranceManager::ShowDoorEmblemRequirement(AdventureFieldEntrance adventureFieldEntrance)
{
    njSetTexture(&entranceTextList);
    njPushMatrix(0);
    float angleRad = adventureFieldEntrance.indicatorAngle * (3.14159265f / 180.0f);
    float offsetX = 0.02f * sinf(angleRad);
    float offsetZ = 0.02f * cosf(angleRad);

    njTranslate(0, adventureFieldEntrance.indicatorPosition.x + offsetX, adventureFieldEntrance.indicatorPosition.y,
                adventureFieldEntrance.indicatorPosition.z + offsetZ);
    njRotateY(0, 0x10000 * (adventureFieldEntrance.indicatorAngle / 360.0f));
    njColorBlendingMode(NJD_SOURCE_COLOR, NJD_COLOR_BLENDING_SRCALPHA);
    njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
    SetMaterial(255, 255, 255, 255);
    NJS_SPRITE mySprite = {{0}, 1, 1, 0, &entranceTextList, emblem_lock_anim};
    njDrawSprite3D(&mySprite, 0, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
    njPopMatrix(1u);


    njSetTexture(&entranceTextList);
    njPushMatrix(0);
    offsetX = 0.01f * sinf(angleRad);
    offsetZ = 0.01f * cosf(angleRad);

    njTranslate(0, adventureFieldEntrance.indicatorPosition.x + offsetX, adventureFieldEntrance.indicatorPosition.y,
                adventureFieldEntrance.indicatorPosition.z + offsetZ);
    njRotateY(0, 0x10000 * (adventureFieldEntrance.indicatorAngle / 360.0f));
    njColorBlendingMode(NJD_SOURCE_COLOR, NJD_COLOR_BLENDING_SRCALPHA);
    njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
    SetMaterial(255, 255, 255, 255);
    NJS_SPRITE mySprite2 = {{0}, 1, 1, 0, &entranceTextList, line_lock_anim};
    njDrawSprite3D(&mySprite2, 0, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
    njPopMatrix(1u);

    auto entranceValue = _options.entranceEmblemValueMap.find(adventureFieldEntrance.entranceId);

    if (entranceValue == _options.entranceEmblemValueMap.end())
    {
        const auto oppositeEntrance = _adventureFieldEntranceMap.GetReplacementConnection(
            adventureFieldEntrance.entranceId, false);
        entranceValue = _options.entranceEmblemValueMap.find(oppositeEntrance);
    }
    if (entranceValue != _options.entranceEmblemValueMap.end())
    {
        ShowNumberDynamic(adventureFieldEntrance, _gameStatus.unlock.currentEmblems, -10, 2, -0.01f, 4, false);
        ShowNumberDynamic(adventureFieldEntrance, entranceValue->second, 2, -2, -0.04f, 4, true);
    }
}

void AdventureFieldEntranceManager::ShowLevelEntranceArrows()
{
    LevelAndActIDs currentLevelAndAct = static_cast<LevelAndActIDs>(CurrentStageAndAct);
    if (CurrentChaoStage == SADXChaoStage_EggCarrier)
    {
        currentLevelAndAct = LevelAndActIDs_ECGarden;
    }
    else if (CurrentChaoStage == SADXChaoStage_StationSquare)
    {
        currentLevelAndAct = LevelAndActIDs_SSGarden;
    }
    else if (CurrentChaoStage == SADXChaoStage_MysticRuins)
    {
        currentLevelAndAct = LevelAndActIDs_MRGarden;
    }

    for (AdventureFieldEntrance adventureFieldEntrance : _adventureFieldEntranceMap.GetEntrances())
    {
        if (currentLevelAndAct != adventureFieldEntrance.levelAndActId)
            continue;

        if (!ShowDisableDoorIndicator(adventureFieldEntrance.entranceId))
            continue;

        ShowDoorEmblemRequirement(adventureFieldEntrance);
    }
    for (AdventureFieldEntrance adventureFieldEntrance : _adventureFieldEntranceMap.GetStaticEntrances())
    {
        if (currentLevelAndAct != adventureFieldEntrance.levelAndActId)
            continue;

        if (!ShowDisableDoorIndicator(adventureFieldEntrance.entranceId))
            continue;

        ShowDoorEmblemRequirement(adventureFieldEntrance);
    }


    for (const auto& button : HeldButtons)
        if (button & WhistleButtons && Current_CharObj2 != nullptr)
            this->ShowMap();
}

void AdventureFieldEntranceManager::ShowNumberDynamic(const AdventureFieldEntrance& entrance, int number, float x,
                                                      float y, float zBase, float xStep, bool leftJustify)
{
    if (number < 0 || number > 999) return;

    int hundreds = number / 100;
    int tens = (number / 10) % 10;
    int ones = number % 10;

    if (number >= 100)
    {
        showNumber(entrance, x, y, hundreds, zBase);
        showNumber(entrance, x + xStep, y, tens, zBase - 0.01f);
        showNumber(entrance, x + 2 * xStep, y, ones, zBase - 0.02f);
    }
    else if (number >= 10)
    {
        if (leftJustify)
        {
            showNumber(entrance, x, y, tens, zBase - 0.01f);
            showNumber(entrance, x + xStep, y, ones, zBase - 0.02f);
        }
        else
        {
            showNumber(entrance, x + xStep, y, tens, zBase - 0.01f);
            showNumber(entrance, x + 2 * xStep, y, ones, zBase - 0.02f);
        }
    }
    else
    {
        if (leftJustify)
        {
            showNumber(entrance, x, y, ones, zBase - 0.02f);
        }
        else
        {
            showNumber(entrance, x + 2 * xStep, y, ones, zBase - 0.02f);
        }
    }
}


void AdventureFieldEntranceManager::ShowNumberDynamicMap(int number, float x, float y)
{
    if (number < 0 || number > 999) return;

    int hundreds = number / 100;
    int tens = (number / 10) % 10;
    int ones = number % 10;

    if (number >= 100)
    {
        showNumberMap(x + 10, y, hundreds);
        showNumberMap(x, y, tens);
        showNumberMap(x - 10, y, ones);
    }
    else if (number >= 10)
    {
        showNumberMap(x + 5, y, tens);
        showNumberMap(x - 5, y, ones);
    }
    else
    {
        showNumberMap(x, y, ones);
    }
}

void AdventureFieldEntranceManager::showNumber(const AdventureFieldEntrance& adventureFieldEntrance, const float posX,
                                               const float posY, const int number, const float zOffset)
{
    const float angleRad = adventureFieldEntrance.indicatorAngle * (3.14159265f / 180.0f);
    const float offsetX = posX * cosf(angleRad);
    const float offsetZ = -posX * sinf(angleRad);

    const float clipOffsetX = zOffset * sinf(angleRad);
    const float clipOffsetZ = zOffset * cosf(angleRad);

    njSetTexture(&entranceTextList);
    njPushMatrix(0);
    njTranslate(0,
                adventureFieldEntrance.indicatorPosition.x - offsetX + clipOffsetX,
                adventureFieldEntrance.indicatorPosition.y + posY,
                adventureFieldEntrance.indicatorPosition.z - offsetZ + clipOffsetZ);
    njRotateY(0, 0x10000 * (adventureFieldEntrance.indicatorAngle / 360.0f));
    SetMaterial(255, 255, 255, 255);
    NJS_SPRITE numRight = {{0}, 1, 1, 0, &entranceTextList, GetNumberAnim(number)};
    njDrawSprite3D(&numRight, 0, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
    njPopMatrix(1u);
}


void AdventureFieldEntranceManager::showNumberMap(const float posX, const float posY, const int number)
{
    njPushMatrix(0);
    njSetTexture(&entranceTextList);
    NJS_SPRITE numberSprite = {
        {_nj_screen_.cx - posX, _nj_screen_.cy - posY, 1}, -3, -3, 0, &entranceTextList, GetNumberAnim(number)
    };
    njRotateX(0, 0x8000);
    njDrawSprite2D_ForcePriority(&numberSprite, 0, 300, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
    njPopMatrix(1u);
}

void AdventureFieldEntranceManager::DrawEntrancePoint(float x, float y)
{
    const float actualX = 450 - (900.0 * x / 1024.0);
    const float actualY = 450 - (900.0 * y / 1024.0);

    const float squareSize = 6.0f;
    float halfSize = squareSize / 2.0f;
    DrawRect_Queue(_nj_screen_.cx - actualX - halfSize,
                   _nj_screen_.cy - actualY - halfSize,
                   _nj_screen_.cx - actualX + halfSize,
                   _nj_screen_.cy - actualY + halfSize,
                   22250,
                   0xFFFFFFFF,
                   QueuedModelFlagsB_EnableZWrite);
}

void AdventureFieldEntranceManager::DrawLine(float x1, float y1, float x2, float y2)
{
    const float actualX1 = 450 - (900.0 * x1 / 1024.0);
    const float actualY1 = 450 - (900.0 * y1 / 1024.0);
    const float actualX2 = 450 - (900.0 * x2 / 1024.0);
    const float actualY2 = 450 - (900.0 * y2 / 1024.0);

    // Calculate direction vector
    float dx = actualX2 - actualX1;
    float dy = actualY2 - actualY1;
    float length = sqrtf(dx * dx + dy * dy);

    // Perpendicular vector (normalized)
    float px = -dy / length;
    float py = dx / length;

    float halfThickness = 1.0f;

    // Offset points perpendicular to the line
    float ox = px * halfThickness;
    float oy = py * halfThickness;

    NJS_POINT2 points[] = {
        {_nj_screen_.cx - (actualX1 + ox), _nj_screen_.cy - (actualY1 + oy)},
        {_nj_screen_.cx - (actualX1 - ox), _nj_screen_.cy - (actualY1 - oy)},
        {_nj_screen_.cx - (actualX2 - ox), _nj_screen_.cy - (actualY2 - oy)},
        {_nj_screen_.cx - (actualX2 + ox), _nj_screen_.cy - (actualY2 + oy)},
    };

    NJS_COLOR linecol[4];
    NJS_POINT2COL linep2;

    linep2.p = points;
    linep2.col = linecol;
    linep2.tex = NULL;
    linep2.num = 4;

    // linep2.col[0].color = 0x66F1EB9C;
    // linep2.col[1].color = 0x66F1EB9C;
    // linep2.col[2].color = 0x66F1EB9C;
    // linep2.col[3].color = 0x66F1EB9C;
    linep2.col[0].color = 0xFFFFFFFF;
    linep2.col[1].color = 0xFFFFFFFF;
    linep2.col[2].color = 0xFFFFFFFF;
    linep2.col[3].color = 0xFFFFFFFF;

    Draw2DLinesMaybe_Queue(&linep2, 4, 62041.496f, NJD_FILL | NJD_TRANSPARENT, QueuedModelFlagsB_SomeTextureThing);
}


void AdventureFieldEntranceManager::MakeConnection(float x1, float y1, float x2, float y2)
{
    DrawEntrancePoint(x1, y1);
    DrawEntrancePoint(x2, y2);
    DrawLine(x1, y1, x2, y2);
}

void AdventureFieldEntranceManager::DrawEmblemNumberInMap(AdventureFieldEntrance adventureFieldEntrance, int doorCost)
{
    auto entranceValue = entranceLocationInMap.find(adventureFieldEntrance.entranceId);

    if (entranceValue == entranceLocationInMap.end())
        return;


    const float x = 450 - (900.0 * entranceValue->second.x / 1024.0);
    const float y = 450 - (900.0 * entranceValue->second.y / 1024.0);


    njPushMatrix(0);
    njSetTexture(&entranceTextList);
    NJS_SPRITE myTestEmblem = {
        {_nj_screen_.cx - x, _nj_screen_.cy - y, 1}, -1.5, -1.5, 0, &entranceTextList, emblem_lock_anim
    };
    njRotateX(0, 0x8000);
    njDrawSprite2D_ForcePriority(&myTestEmblem, 0, 300, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
    njPopMatrix(1u);
    ShowNumberDynamicMap(doorCost, x, y);
}

void AdventureFieldEntranceManager::DrawMapEmblem(AdventureFieldEntrance adventureFieldEntrance)
{
    auto entranceValue = _options.entranceEmblemValueMap.find(adventureFieldEntrance.entranceId);

    if (entranceValue == _options.entranceEmblemValueMap.end())
    {
        const auto oppositeEntrance = _adventureFieldEntranceMap.GetReplacementConnection(
            adventureFieldEntrance.entranceId, false);
        entranceValue = _options.entranceEmblemValueMap.find(oppositeEntrance);
    }
    if (entranceValue == _options.entranceEmblemValueMap.end())
        return;


    if (_gameStatus.unlock.currentEmblems >= entranceValue->second)
        return;

    int doorCost = entranceValue->second;
    DrawEmblemNumberInMap(adventureFieldEntrance, doorCost);
}

void AdventureFieldEntranceManager::DrawConnectionsInMap(const AdventureFieldEntrance& adventureFieldEntrance)
{
    //If both entrance and connection are on the map, draw line
    auto entranceFrom = entranceLocationInMap.find(adventureFieldEntrance.entranceId);

    if (entranceFrom == entranceLocationInMap.end())
        return;


    auto entranceToId = _instance->_adventureFieldEntranceMap.GetReplacementConnection(
        adventureFieldEntrance.entranceId,
        _isEggCarrierTransformed);
    auto entranceTo = entranceLocationInMap.find(entranceToId);

    if (entranceTo == entranceLocationInMap.end())
        DrawEntrancePoint(entranceFrom->second.x, entranceFrom->second.y);
    else
        MakeConnection(entranceFrom->second.x, entranceFrom->second.y, entranceTo->second.x, entranceTo->second.y);
}

void AdventureFieldEntranceManager::ShowMap()
{
    njPushMatrix(0);
    njSetTexture(&entranceTextList);
    NJS_SPRITE mySprite = {{_nj_screen_.cx, _nj_screen_.cy, 1}, -50, -50, 0, &entranceTextList, base_map};
    njRotateX(0, 0x8000);
    njDrawSprite2D_ForcePriority(&mySprite, 0, 200, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
    njPopMatrix(1u);

    for (AdventureFieldEntrance adventureFieldEntrance : _adventureFieldEntranceMap.GetEntrances())
    {
        DrawConnectionsInMap(adventureFieldEntrance);
        DrawMapEmblem(adventureFieldEntrance);
    }
    for (AdventureFieldEntrance adventureFieldEntrance : _adventureFieldEntranceMap.GetStaticEntrances())
    {
        DrawMapEmblem(adventureFieldEntrance);
    }


    /*   
       NJS_POINT2 points[] = {
           {_nj_screen_.cx - 220, _nj_screen_.cy - 165},
           {_nj_screen_.cx - 225, _nj_screen_.cy - 165},
           {_nj_screen_.cx - 220, _nj_screen_.cy - 160}
       };
       NJS_COLOR color[3] = {
           {0xFFD4AF37},
           {0xFFD4AF37},
           {0xFFD4AF37},
       };
       NJS_POINT2COL point2Col;
       point2Col.p = points;
       point2Col.col = color;
       njDrawTriangle2D(&point2Col, 1, 300, NJD_TRANSPARENT);*/

    /*
        MakeConnection(109, 221, 70, 256);
    
        MakeConnection(615, 717, 653, 717);
        MakeConnection(717, 672, 773, 655);
        MakeConnection(812, 616, 860, 600);
        MakeConnection(750, 781, 789, 789);
        MakeConnection(702, 850, 702, 884);*/


    // DrawEntrancePoint(0, 0);
    // DrawEntrancePoint(0, 1024);
    // DrawEntrancePoint(1024, 0);
    // DrawEntrancePoint(1024, 1024);


    // DrawEntrancePoint(0, 0);
    // DrawEntrancePoint(0, 1024);


    // DrawEntrancePoint(220.0f, 163.0f);
    //
    // DrawEntrancePoint(335.0f, 165.0f);
    // DrawEntrancePoint(342.0f, 124.0f);
    //
    // DrawLine(335, 165, 342, 124);


    // DrawRect_Queue(_nj_screen_.cx - 217,
    //                _nj_screen_.cy - 160,
    //                _nj_screen_.cx - 223,
    //                _nj_screen_.cy - 166, 62041.496f,
    //                0xFFFF0000,
    //                QueuedModelFlagsB_EnableZWrite);

    // njPushMatrix(0);
    // njSetTexture(&entranceTextList);
    // NJS_SPRITE myTestEmblem = {{_nj_screen_.cx-220, _nj_screen_.cy-165, 1}, -1.5, -1.5, 0, &entranceTextList, emblem_lock_anim};
    // njRotateX(0, 0x8000);
    // njDrawSprite2D_ForcePriority(&myTestEmblem, 0, 300, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
    // njPopMatrix(1u);
    // njPushMatrix(0);
    // njSetTexture(&entranceTextList);
    // NJS_SPRITE myTestNumber = {{_nj_screen_.cx-220, _nj_screen_.cy-165, 1}, -3, -3, 0, &entranceTextList, number_5_lock_anim};
    // njRotateX(0, 0x8000);
    // njDrawSprite2D_ForcePriority(&myTestNumber, 0, 400, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
    // njPopMatrix(1u);
}


// -------- Function hooks for gating the world --------

BOOL AdventureFieldEntranceManager::OnIsBarricadeGone()
{
    if (!_instance->_options.emblemGating)
        return _isBarricadeGoneHook.Original();

    if (CurrentStageAndAct == LevelAndActIDs_StationSquare4)
        return _instance->IsDoorOpen(SsMainToCityHall);

    return _instance->IsDoorOpen(CityHallToSsMain);
}


void AdventureFieldEntranceManager::OnWallMain(task* tp)
{
    if (!_instance->_options.emblemGating)
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
    if (!_instance->_options.emblemGating)
        return _ssCarMainHook.Original(tp);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1 && !_instance->IsDoorOpen(CityHallToSsMain))
        return FreeTask(tp);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4 && !_instance->IsDoorOpen(SsMainToCityHall))
        return FreeTask(tp);

    return _ssCarMainHook.Original(tp);
}

int AdventureFieldEntranceManager::OnIsStationDoorOpen()
{
    if (!_instance->_options.emblemGating)
        return _isStationDoorOpenHook.Original();

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
    if (!_instance->_options.emblemGating)
        return _isHotelFrontDoorOpenHook.Original();

    if (CurrentStageAndAct == LevelAndActIDs_StationSquare4)
        return _instance->IsDoorOpen(SsMainToHotel);

    return _instance->IsDoorOpen(HotelToSsMain);
}

BOOL AdventureFieldEntranceManager::OnIsHotelBackDoorOpen()
{
    if (!_instance->_options.emblemGating)
        return _isHotelBackDoorOpenHook.Original();

    if (CurrentStageAndAct == LevelAndActIDs_StationSquare2)
        return _instance->IsDoorOpen(CasinoToHotel);

    return _instance->IsDoorOpen(HotelToCasino);
}

BOOL AdventureFieldEntranceManager::OnIsHotelPoolDoorOpen()
{
    if (!_instance->_options.emblemGating)
        return _isHotelPoolDoorOpenHook.Original();

    return _instance->IsDoorOpen(HotelToHotelPool);
}

BOOL AdventureFieldEntranceManager::OnIsTwinkleParkElevatorOpen()
{
    if (!_instance->_options.emblemGating)
        return _isTwinkleParkElevatorOpenHook.Original();

    return _instance->IsDoorOpen(SsMainToTwinkleParkTunnel);
}

TaskFunc(SomethingAboutTPDoorA, 0x63E670);

void AdventureFieldEntranceManager::OnTwinkleParkLobbyDoorFromStation(task* tp)
{
    if (!_instance->_options.emblemGating)
        return _twinkleParkLobbyDoorFromStationHook.Original(tp);

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
    if (!_instance->_options.emblemGating)
        return _twinkleParkLobbyDoorToStationHook.Original(tp);


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
    if (!_instance->_options.emblemGating)
        return _ssBoxLoadHook.Original(tp);

    // Change jnz to jz
    WriteData<1>((void*)0x636B84, 0x74);
    // Change cmp eax, 7 to cmp eax, 9
    WriteData<1>((void*)0x636B83, 0x09);

    return _ssBoxLoadHook.Original(tp);
}

void AdventureFieldEntranceManager::OnElevatorOut(task* tp)
{
    if (!_instance->_options.emblemGating)
        return _elevatorOutHook.Original(tp);

    if (CurrentStageAndAct == LevelAndActIDs_StationSquare4 && !_instance->IsDoorOpen(
        TwinkleParkTunnelToSewers))
        return _elevatorOutHook.Original(tp);

    _elevatorInHook.Original(tp);
}

void AdventureFieldEntranceManager::OnElevatorIn(task* tp)
{
    if (!_instance->_options.emblemGating)
        return _elevatorInHook.Original(tp);

    if (CurrentStageAndAct == LevelAndActIDs_StationSquare3 && !_instance->IsDoorOpen(
        SewersToTwinkleParkTunnel))
        return _elevatorOutHook.Original(tp);

    _elevatorInHook.Original(tp);
}


int AdventureFieldEntranceManager::OnElevatorInSceneChange(task* tp)
{
    if (!_instance->_options.emblemGating)
        return _elevatorInSceneChangeHook.Original(tp);

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
    if (!_instance->_options.emblemGating)
        return _sewerCarHandlePickUpHook.Original(tp);

    if (_instance->IsDoorOpen(CityHallToSewers))
        return _sewerCarHandlePickUpHook.Original(tp);

    //Big won't be able to pick up the car 
    return DrawCar(tp);
}

BOOL AdventureFieldEntranceManager::OnSpawnSewerCar()
{
    if (!_instance->_options.emblemGating)
        return _spawnSewerCarHook.Original();

    if (CurrentCharacter == Characters_Big)
        return false;

    return _instance->IsDoorOpen(CityHallToSewers);
}


void AdventureFieldEntranceManager::OnCollisionCube(task* tp)
{
    if (!_instance->_options.emblemGating)
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
    if (!_instance->_options.emblemGating)
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
    if (!_instance->_options.emblemGating)
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
    if (!_instance->_options.emblemGating)
        return _characterUpgradeMainHook.Original(tp);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare3 && CurrentCharacter == Characters_Big)
        return FreeTask(tp);
    return _characterUpgradeMainHook.Original(tp);
}

void AdventureFieldEntranceManager::OnSsBoatMain(task* tp)
{
    if (!_instance->_options.emblemGating)
        return _ssBoatMainHook.Original(tp);

    if (!_instance->IsDoorOpen(SsMainToEcOutside))
        return FreeTask(tp);
    return _ssBoatMainHook.Original(tp);
}


// Speed Highway
//TODO: Check/move the unlock part to the main manager
BOOL AdventureFieldEntranceManager::OnIsSpeedHighwayShutterOpen()
{
    if (!_instance->_options.emblemGating)
        return _isSpeedHighwayShutterOpenHook.Original();
    return _instance->IsDoorOpen(SsMainToSpeedHighway);
}

void AdventureFieldEntranceManager::OnLoadSpeedHighwayShutter(task* tp)
{
    if (!_instance->_options.emblemGating)
        _loadSpeedHighwayShutterHook.Original(tp);
    //TODO: Animate instead of removing the task
    if (_instance->IsDoorOpen(SsMainToSpeedHighway))
        return FreeTask(tp);

    _loadSpeedHighwayShutterHook.Original(tp);
}

void AdventureFieldEntranceManager::OnLoadSpeedHighwayShutter2(task* tp)
{
    if (!_instance->_options.emblemGating)
        return _loadSpeedHighwayShutter2Hook.Original(tp);
    //TODO: Animate instead of removing the task
    if (_instance->IsDoorOpen(SsMainToSpeedHighway))
        return FreeTask(tp);

    _loadSpeedHighwayShutter2Hook.Original(tp);
}

BOOL AdventureFieldEntranceManager::OnIsEmeraldCoastOpen()
{
    if (!_instance->_options.emblemGating)
        return _isEmeraldCoastOpenHook.Original();

    if (CurrentCharacter == Characters_Gamma)
        return false;

    return _instance->IsDoorOpen(HotelPoolToEmeraldCoast);
}

void AdventureFieldEntranceManager::OnLoadEmeraldCoastGateTargets(task* tp)
{
    if (!_instance->_options.emblemGating)
        return _loadEmeraldCoastGateTargetsHook.Original(tp);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
        && !_instance->IsDoorOpen(HotelPoolToEmeraldCoast))
        FreeTask(tp);
    else
        _loadEmeraldCoastGateTargetsHook.Original(tp);
}


void AdventureFieldEntranceManager::OnElevatorMain(task* tp)
{
    if (!_instance->_options.emblemGating)
        return _elevatorMainHook.Original(tp);


    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
        && IsNearPosition(tp->twp->pos, -399.99f, 0, 1700)
        && !_instance->IsDoorOpen(HotelToSsChaoGarden))
        tp->twp->mode = 8;

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
        && IsNearPosition(tp->twp->pos, -399.99f, 0, 1665)
        && !_instance->IsDoorOpen(HotelToSsChaoGarden))
        tp->twp->mode = 8;

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_SSGarden
        && !_instance->IsDoorOpen(SsChaoGardenToHotel))
        tp->twp->mode = 8;
    _elevatorMainHook.Original(tp);
}


BOOL AdventureFieldEntranceManager::OnIsCasinoOpen()
{
    if (!_instance->_options.emblemGating)
        return _isCasinoOpenHook.Original();

    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
        return _isCasinoOpenHook.Original() && _instance->IsDoorOpen(CasinoToCasinopolis);

    if (CurrentCharacter == Characters_Knuckles)
        return GetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_ENTRANCE_CASINO)) && _instance->IsDoorOpen(
            CasinoToCasinopolis);

    return _instance->IsDoorOpen(CasinoToCasinopolis);
}


BOOL AdventureFieldEntranceManager::OnIsTrainInService()
{
    if (!_instance->_options.emblemGating)
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
    if (!_instance->_options.emblemGating)
        return _ecWarpMainHook.Original(tp);

    if (_instance->IsDoorOpen(GetBossEntrance()))
        return _ecWarpMainHook.Original(tp);

    tp->twp->wtimer = 0;
    _ecWarpMainHook.Original(tp);
}


TaskFunc(ClosedToyShopDoorMain, 0x63E9A0);

void AdventureFieldEntranceManager::OnOpenToyShopDoorMain(task* tp)
{
    if (!_instance->_options.emblemGating)
        return _openToyShopDoorMainHook.Original(tp);

    if (_instance->IsDoorOpen(SewersToCityHall))
        return _openToyShopDoorMainHook.Original(tp);

    ClosedToyShopDoorMain(tp);
}


BOOL AdventureFieldEntranceManager::OnIsCityHallDoorOpen()
{
    if (!_instance->_options.emblemGating)
        return _isCityHallDoorOpenHook.Original();

    return _instance->IsDoorOpen(CityHallToSpeedHighway);
}

//We don't create Knuckles barricade if he doesn't have access to the level
void AdventureFieldEntranceManager::OnLoadKnucklesBarricade(task* tp)
{
    if (!_instance->_options.emblemGating)
        return _loadKnucklesBarricadeHook.Original(tp);

    if (CurrentCharacter == Characters_Knuckles && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1)
        if (!_instance->IsDoorOpen(CityHallToSpeedHighway))
            return FreeTask(tp);

    _loadKnucklesBarricadeHook.Original(tp);
}

int AdventureFieldEntranceManager::OnTwinkleCircuitDoor(const char character)
{
    if (!_instance->_options.emblemGating)
        return twinkleCircuitDoorHook.Original(character);

    return _instance->IsDoorOpen(TwinkleParkLobbyToTwinkleCircuit);
}

int AdventureFieldEntranceManager::OnTwinkleParkDoor(const char character)
{
    if (!_instance->_options.emblemGating)
        return twinkleParkDoorHook.Original(character);

    return _instance->IsDoorOpen(TwinkleParkLobbyToTwinklePark);
}

void AdventureFieldEntranceManager::OnMrRaftMain(task* tp)
{
    if (!_instance->_options.emblemGating)
        return _mrRaftMainHook.Original(tp);

    if (!_instance->IsDoorOpen(MrMainToEcOutside))
        return FreeTask(tp);
    return _mrRaftMainHook.Original(tp);
}

int AdventureFieldEntranceManager::OnMrCartMain(task* tp)
{
    if (!_instance->_options.emblemGating)
        return mrCartHook.Original(tp);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3)
        return _instance->IsDoorOpen(JungleToMrMain);
    if (tp->twp->scl.x > 0)
        return _instance->IsDoorOpen(MrMainToMrChaoGarden);
    return _instance->IsDoorOpen(MrMainToJungle);
}


BOOL AdventureFieldEntranceManager::OnIsAngelIslandOpen()
{
    if (!_instance->_options.emblemGating)
        return _isAngelIslandOpenHook.Original();
    return _instance->IsDoorOpen(MrMainToAngelIsland);
}


void AdventureFieldEntranceManager::OnMysticRuinsKey(task* tp)
{
    if (!_instance->_options.emblemGating)
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
    if (!_instance->_options.emblemGating)
        return _mysticRuinsLockHook.Original(tp);
    const int bufferCharacter = CurrentCharacter;
    CurrentCharacter = Characters_Sonic;
    _mysticRuinsLockHook.Original(tp);
    CurrentCharacter = bufferCharacter;
}


BOOL AdventureFieldEntranceManager::OnIsWindyValleyOpen()
{
    if (!_instance->_options.emblemGating)
        return _isWindyValleyOpenHook.Original();

    return EventFlagArray[FLAG_SONIC_MR_WINDYSTONE];
}

BOOL AdventureFieldEntranceManager::OnPreventMrStoneSpawn()
{
    if (!_instance->_options.emblemGating)
        return _preventMrStoneSpawnHook.Original();

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
        return _instance->IsDoorOpen(AngelIslandToIceCave);
    return false;
}

int AdventureFieldEntranceManager::OnGetCharacterId(char index)
{
    if (!_instance->_options.emblemGating)
        return _getCharacterIdHook.Original(index);
    return CurrentCharacter;
}

void AdventureFieldEntranceManager::OnPastSceneChange(task* tp)
{
    if (!_instance->_options.emblemGating)
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
    if (!_instance->_options.emblemGating)
        return _isFinalEggEggmanDoorOpenHook.Original(entity);

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
    if (!_instance->_options.emblemGating)
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
    if (!_instance->_options.emblemGating)
        return _isLostWorldFrontEntranceOpenHook.Original();

    return _instance->IsDoorOpen(JungleToLostWorld);
}

BOOL AdventureFieldEntranceManager::OnIsSandHillOpen()
{
    if (!_instance->_options.emblemGating)
        return _isSandHillOpenHook.Original();

    return _instance->IsDoorOpen(JungleToSandHill);
}

void AdventureFieldEntranceManager::OnLoadSceneChangeMr(task* tp)
{
    if (!_instance->_options.emblemGating)
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
    if (!_instance->_options.emblemGating)
        sceneChangeMrHook.Original(newScene);


    // Ice Cap
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        if (newScene == 1)
        {
            if (_instance->IsDoorOpen(IceCaveToIceCap))
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
    if (!_instance->_options.emblemGating)
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
    if (!_instance->_options.emblemGating)
        return _loadLongLadderMrHook.Original(tp);

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
    if (!_instance->_options.emblemGating)
        return sceneChangeECInsideHook.Original(a1, a2);


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
    if (!_instance->_options.emblemGating)
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
    if (!_instance->_options.emblemGating)
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
    if (!_instance->_options.emblemGating)
        return skyDeckDoorHook.Original(twp);

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
    if (!_instance->_options.emblemGating)
        return _eggCapHook.Original(tp);

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
    if (!_instance->_options.emblemGating)
        return _springMainHook.Original(tp);

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside5)
    {
        if (!_instance->IsDoorOpen(PrivateRoomToCaptainRoom) && IsNearPosition(tp->twp->pos, -83.42f, 0, 0.54f))
            return FreeTask(tp);
    }
    return _springMainHook.Original(tp);
}


BOOL AdventureFieldEntranceManager::OnIsMonorailEnabled()
{
    if (!_instance->_options.emblemGating)
        return _isMonorailEnabledHook.Original();
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside1)
        return _instance->IsDoorOpen(EcOutsideToEcInsideMonorail);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside2)
        return _instance->IsDoorOpen(BridgeToEcInsideMonorail);

    return _instance->IsDoorOpen(EcInsideToEcOutsideMonorail);
}

BOOL AdventureFieldEntranceManager::OnIsOutsideEggLiftEnabled()
{
    if (!_instance->_options.emblemGating)
        return _isOutsideEggLiftEnabledHook.Original();
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside1)
        return _instance->IsDoorOpen(EcOutsideToEcInsideEggLift);
    return _instance->IsDoorOpen(DeckToEcInsideEggLift);
}


BOOL AdventureFieldEntranceManager::OnIsInsideEggLiftEnabled()
{
    if (!_instance->_options.emblemGating)
        return _isInsideEggLiftEnabledHook.Original();
    return _instance->IsDoorOpen(EcInsideToEcOutsideEggLift);
}

void AdventureFieldEntranceManager::OnLoadPoolDoor(task* tp)
{
    if (!_instance->_options.emblemGating)
        return _loadPoolDoorHook.Original(tp);

    if (!_instance->IsDoorOpen(PoolToSkyDeck))
        return _loadPoolDoorHook.Original(tp);
    FreeTask(tp);
}

BOOL AdventureFieldEntranceManager::IsEggCarrierSunk()
{
    if (!_instance->_options.emblemGating)
        return _isEggCarrierSunkHook.Original();
    return true;
}

BOOL AdventureFieldEntranceManager::IsEcBoatEnabled()
{
    if (!_instance->_options.emblemGating)
        return _isEcBoatEnabledHook.Original();
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
    if (!_instance->_options.emblemGating)
        return _isEcRaftEnabledHook.Original();
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
    if (!_instance->_options.emblemGating)
        return _hiddenGateMainHook.Original(tp);
    if (IsNearPosition(tp->twp->pos, -0.02f, 20.34f, -191.17f))
        return FreeTask(tp);
    return _hiddenGateMainHook.Original(tp);
}

void AdventureFieldEntranceManager::OnChaoWarpMain(task* tp)
{
    if (!_instance->_options.emblemGating)
        return _chaoWarpMainHook.Original(tp);

    if (CurrentChaoStage == SADXChaoStage_EggCarrier)
    {
        if (IsNearPosition(tp->twp->pos, -288.75f, 5, -99.12f))
        {
            if (!_instance->IsDoorOpen(EcChaoGardenToWarpHall))
                tp->twp->wtimer = 0;
        }
    }
    _chaoWarpMainHook.Original(tp);
}

task* AdventureFieldEntranceManager::OnChaoGardenChanceScene(int a1, int a2)
{
    if (!_instance->_options.emblemGating)
        return _chaoGardenChanceSceneHook.Original(a1, a2);
    if (CurrentChaoStage == SADXChaoStage_StationSquare)
    {
        if (!_instance->IsDoorOpen(SsChaoGardenToHotel))
            return nullptr;
    }
    //TODO: This won't work for DC, need to change in the future
    else if (CurrentChaoStage == SADXChaoStage_MysticRuins)
    {
        if (!_instance->IsDoorOpen(MrChaoGardenToMrMain))
            return nullptr;
    }
    return _chaoGardenChanceSceneHook.Original(a1, a2);
}
