#include "MapManager.h"

static NJS_POINT2 mapToScreen(Float x, Float y)
{
    float valueX = -(x - 512) / 512 * _nj_screen_.h / 2;
    float valueY = _nj_screen_.cy - y / 1024 * _nj_screen_.h;

    return {valueX * 0.8301f, valueY * 0.8301f};
}


void drawSprite2D(NJS_TEXANIM* anim, float screenX, float screenY, int priority = 300, float scale = 1.5f)
{
    scale = scale * _nj_screen_.h / 1080;

    njPushMatrix(0);
    njSetTexture(&entranceTextList);
    SetMaterial(255, 255, 255, 255);
    NJS_SPRITE s = {
        {_nj_screen_.cx - screenX, _nj_screen_.cy - screenY, 1}, -scale, -scale, 0, &entranceTextList, anim
    };
    njRotateX(0, 0x8000);
    njDrawSprite2D_ForcePriority(&s, 0, priority, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
    njPopMatrix(1u);
}

MapManager::MapManager(Options& options, Settings& settings, GameStatus& gameStatus,
                       AdventureFieldEntranceMap& adventureFieldEntranceMap) :
    _options(options), _settings(settings), _gameStatus(gameStatus),
    _adventureFieldEntranceMap(adventureFieldEntranceMap)
{
}

void MapManager::OnFrame()
{
    if (Current_CharObj2 == nullptr)
        return;

    if ((ControllerPointers[0]->HeldButtons & Buttons_Y && _settings.mapButton == MapButtonY) ||
        (ControllerPointers[0]->HeldButtons & Buttons_D && _settings.mapButton == MapButtonSelect) ||
        (ControllerPointers[0]->HeldButtons & Buttons_Z && _settings.mapButton == MapButtonRightBumper) ||
        (ControllerPointers[0]->HeldButtons & Buttons_C && _settings.mapButton == MapButtonLeftBumper))
    {
        this->ShowMap();
    }

    if ((CurrentLevel >= LevelIDs_EmeraldCoast && CurrentLevel <= LevelIDs_E101R) ||
        (CurrentLevel >= LevelIDs_TwinkleCircuit && CurrentLevel <= LevelIDs_SandHill))
        return;

    if (GameMode == GameModes_Menu)
        return;

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

    // Dynamic entrances: show name
    for (const auto& entrance : _adventureFieldEntranceMap.GetEntrances())
    {
        if (currentLevelAndAct != entrance.levelAndActId)
            continue;

        DoorState doorState = _doorLogicStrategy->GetDoorState(entrance.entranceId);
        if (doorState == DoorLocked)
            ShowDoorRequirement(entrance);
        else if (doorState == DoorBlocked)
            ShowBlockedDoor(entrance);
        else
            ShowDoorName(entrance);
    }

    for (const auto& entrance : _adventureFieldEntranceMap.GetStaticEntrances())
    {
        if (currentLevelAndAct != entrance.levelAndActId)
            continue;

        DoorState doorState = _doorLogicStrategy->GetDoorState(entrance.entranceId);
        if (doorState == DoorLocked)
            ShowDoorRequirement(entrance);
        else if (doorState == DoorBlocked)
            ShowBlockedDoor(entrance);
    }
}

void MapManager::SetDoorLogicStrategy(IDoorLogicStrategy* doorLogicStrategy)
{
    this->_doorLogicStrategy = doorLogicStrategy;
}

void MapManager::ShowMap()
{
    drawSprite2D(base_map, 0, 0, 300, 50);

    for (const auto& entrance : _adventureFieldEntranceMap.GetEntrances())
    {
        DrawConnectionsInMap(entrance);
        DrawEntrancesInMap(entrance, false);
    }
    for (const auto& entrance : _adventureFieldEntranceMap.GetStaticEntrances())
    {
        DrawEntrancesInMap(entrance, true);
    }
    DrawPlayerLocation();
}


void MapManager::DrawConnectionsInMap(const AdventureFieldEntrance& adventureFieldEntrance)
{
    //If both entrance and connection are on the map, draw line
    auto entranceLocationFrom = entranceLocationInMap.find(adventureFieldEntrance.entranceId);

    if (entranceLocationFrom == entranceLocationInMap.end())
        return;


    auto entranceToId = _instance->_adventureFieldEntranceMap.GetReplacementConnection(
        adventureFieldEntrance.entranceId);
    auto entranceLocationTo = entranceLocationInMap.find(entranceToId);

    if (entranceLocationTo == entranceLocationInMap.end())
    {
        DrawEntrancePoint(entranceLocationFrom->second.x, entranceLocationFrom->second.y);
        auto entranceTo = _instance->_adventureFieldEntranceMap.FindEntranceById(entranceToId);
        DrawLevelInitialsInMap(entranceTo, entranceLocationFrom->second.x, entranceLocationFrom->second.y);
    }
    else
        MakeConnection(entranceLocationFrom->second, entranceLocationTo->second);
}

NJS_TEXANIM* MapManager::getInitialsFromEntrance(AdventureFieldEntrance* entranceTo)
{
    if (!_gameStatus.map.IsEntranceVisited(entranceTo->entranceId) && _options.entranceRandomizer !=
        NoEntranceRandomization)
        return question_mark_anim;

    LevelAndActIDs levelActAndId = _instance->_adventureFieldEntranceMap.CalculateCorrectAct(entranceTo->levelAndActId);
    LevelIDs level = static_cast<LevelIDs>(GET_LEVEL(levelActAndId));
    switch (level)
    {
    case LevelIDs_EmeraldCoast:
        return emerald_coast_map_anim;
    case LevelIDs_WindyValley:
        return windy_valley_map_anim;
    case LevelIDs_TwinklePark:
        return twinkle_park_map_anim;
    case LevelIDs_SpeedHighway:
        return speed_highway_map_anim;
    case LevelIDs_RedMountain:
        return red_mountain_map_anim;
    case LevelIDs_SkyDeck:
        return sky_deck_map_anim;
    case LevelIDs_LostWorld:
        return lost_world_map_anim;
    case LevelIDs_IceCap:
        return ice_cap_map_anim;
    case LevelIDs_Casinopolis:
        return casinopolis_map_anim;
    case LevelIDs_FinalEgg:
        return final_egg_map_anim;
    case LevelIDs_HotShelter:
        return hot_shelter_map_anim;
    case LevelIDs_Chaos0:
        return chaos_0_map_anim;
    case LevelIDs_Chaos2:
        return chaos_2_map_anim;
    case LevelIDs_Chaos4:
        return chaos_4_map_anim;
    case LevelIDs_Chaos6:
        return chaos_6_map_anim;
    case LevelIDs_EggHornet:
        return egg_hornet_map_anim;
    case LevelIDs_EggWalker:
        return egg_walker_map_anim;
    case LevelIDs_EggViper:
        return egg_viper_map_anim;
    case LevelIDs_Zero:
        return zero_map_anim;
    case LevelIDs_E101:
        return beta_1_map_anim;
    case LevelIDs_E101R:
        return beta_2_map_anim;
    case LevelIDs_TwinkleCircuit:
        return twinkle_circuit_map_anim;
    case LevelIDs_SkyChase1:
        return sky_chase_1_map_anim;
    case LevelIDs_SkyChase2:
        return sky_chase_2_map_anim;
    case LevelIDs_SandHill:
        return sand_hill_map_anim;
    case LevelIDs_SSGarden:
        return ss_garden_map_anim;
    case LevelIDs_ECGarden:
        return ec_garden_map_anim;
    case LevelIDs_MRGarden:
        return mr_garden_map_anim;
    default:
        return line_lock_anim;
    }
}


void MapManager::DrawPlayerLocation()
{
    NJS_POINT2 locationInMap;
    if (CurrentStageAndAct == LevelAndActIDs_StationSquare1)
        locationInMap = {774, 176};
    else if (CurrentStageAndAct == LevelAndActIDs_StationSquare2)
        locationInMap = {682, 238};
    else if (CurrentStageAndAct == LevelAndActIDs_StationSquare3)
        locationInMap = {970, 240};
    else if (CurrentStageAndAct == LevelAndActIDs_StationSquare4)
        locationInMap = {750, 405};
    else if (CurrentStageAndAct == LevelAndActIDs_StationSquare5)
        locationInMap = {571, 481};
    else if (CurrentStageAndAct == LevelAndActIDs_StationSquare6)
        locationInMap = {931, 420};
    else if (CurrentStageAndAct == LevelAndActIDs_MysticRuins1)
        locationInMap = {290, 270};
    else if (CurrentStageAndAct == LevelAndActIDs_MysticRuins2)
        locationInMap = {190, 545};
    else if (CurrentStageAndAct == LevelAndActIDs_MysticRuins3)
        locationInMap = {350, 102};
    else if (CurrentStageAndAct == LevelAndActIDs_MysticRuins4)
        locationInMap = {525, 34};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierInside1)
        locationInMap = {586, 702};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierInside2)
        locationInMap = {699, 717};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierInside3)
        locationInMap = {795, 585};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierInside4)
        locationInMap = {862, 504};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierInside5)
        locationInMap = {830, 773};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierInside6)
        locationInMap = {678, 903};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierOutside1)
        locationInMap = {434, 660};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierOutside2)
        locationInMap = {434, 660};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierOutside3)
        locationInMap = {435, 727};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierOutside4)
        locationInMap = {225, 844};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierOutside5)
        locationInMap = {212, 688};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierOutside6)
        locationInMap = {419, 934};
    else if (CurrentStageAndAct == LevelAndActIDs_Past1)
        locationInMap = {80, 105};
    else if (CurrentStageAndAct == LevelAndActIDs_Past2)
        locationInMap = {80, 260};
    else
        return;


    auto point = mapToScreen(locationInMap.x, locationInMap.y);

    std::clock_t now = std::clock();
    double ms = double(now) * 1000.0 / CLOCKS_PER_SEC;
    int phase = static_cast<int>(ms / 250.0) & 1; // 0 or 1
    point.y += (phase == 0) ? 3.0f : -3.0f;

    drawSprite2D(location_map_anim, point.x, point.y);
}


void MapManager::DrawEntrancesInMap(AdventureFieldEntrance adventureFieldEntrance, bool isStatic)
{
    // We get the level on the other side of the door
    const auto oppositeEntranceId = _adventureFieldEntranceMap.GetReplacementConnection(
        adventureFieldEntrance.entranceId);

    const auto oppositeEntrance = _adventureFieldEntranceMap.FindEntranceById(oppositeEntranceId);

    if (oppositeEntrance == nullptr)
        return;

    auto entranceLocation = entranceLocationInMap.find(adventureFieldEntrance.entranceId);

    if (entranceLocation == entranceLocationInMap.end())
        return;

    auto point = mapToScreen(entranceLocation->second.x, entranceLocation->second.y);

    DoorState doorState = _doorLogicStrategy->GetDoorState(adventureFieldEntrance.entranceId);

    if (doorState == DoorUnlocked)
    {
        if (!_gameStatus.map.IsEntranceVisited(adventureFieldEntrance.entranceId) && !isStatic)
            DrawNewInMap(adventureFieldEntrance);
    }
    else if (doorState == DoorBlocked)
    {
        drawSprite2D(blocked_anim, point.x, point.y);
    }
    else if (doorState == DoorLocked)
    {
        if (_options.gatingMode == EmblemGating)
        {
            const int entranceValue = _options.GetEntranceEmblemValue(adventureFieldEntrance.entranceId,
                                                                      oppositeEntranceId);
            if (entranceValue <= 0)
                return;
            DrawEmblemNumberInMap(adventureFieldEntrance, entranceValue);
        }
        else if (_options.gatingMode == KeyItemGating)
        {
            drawSprite2D(lock_anim, point.x, point.y, 1000000);
        }
    }
}

void MapManager::DrawLevelInitialsInMap(AdventureFieldEntrance* entranceTo, Float entranceX,
                                        Float entranceY)
{
    auto point = mapToScreen(entranceX, entranceY);
    NJS_TEXANIM* texanim = getInitialsFromEntrance(entranceTo);
    drawSprite2D(texanim, point.x, point.y);
    //Draw check if completed
    if (_gameStatus.IsLevelCompleted(static_cast<LevelIDs>(GET_LEVEL(entranceTo->levelAndActId)), CurrentCharacter))
        drawSprite2D(check_anim, point.x, point.y);
}


void MapManager::DrawNewInMap(AdventureFieldEntrance adventureFieldEntrance)
{
    auto entranceLocation = entranceLocationInMap.find(adventureFieldEntrance.entranceId);

    if (entranceLocation == entranceLocationInMap.end())
        return;

    auto point = mapToScreen(entranceLocation->second.x, entranceLocation->second.y);
    std::clock_t now = std::clock();
    double ms = double(now) * 1000.0 / CLOCKS_PER_SEC;
    int phase = static_cast<int>(ms / 500.0) & 1; // 0 or 1
    point.y += (phase == 0) ? 2.0f : -2.0f;
    drawSprite2D(new_logo_map_anim, point.x, point.y, 1000000);
}


void MapManager::DrawEmblemNumberInMap(AdventureFieldEntrance adventureFieldEntrance, int doorCost)
{
    auto entranceLocation = entranceLocationInMap.find(adventureFieldEntrance.entranceId);

    if (entranceLocation == entranceLocationInMap.end())
        return;

    auto point = mapToScreen(entranceLocation->second.x, entranceLocation->second.y);
    drawSprite2D(emblem_lock_anim, point.x, point.y, 1000000);
    ShowNumberDynamicMap(doorCost, point.x, point.y);
}

void MapManager::ShowNumberDynamicMap(int number, float x, float y)
{
    if (number < 0 || number > 999) return;

    float distanceBetweenDigits = 12.0f * (_nj_screen_.h / 1080);

    int hundreds = number / 100;
    int tens = (number / 10) % 10;
    int ones = number % 10;

    if (number >= 100)
    {
        showNumberMap(x + distanceBetweenDigits, y, hundreds);
        showNumberMap(x, y, tens);
        showNumberMap(x - distanceBetweenDigits, y, ones);
    }
    else if (number >= 10)
    {
        showNumberMap(x + distanceBetweenDigits / 2, y, tens);
        showNumberMap(x - distanceBetweenDigits / 2, y, ones);
    }
    else
    {
        showNumberMap(x, y, ones);
    }
}


void MapManager::showNumberMap(const float posX, const float posY, const int number)
{
    drawSprite2D(GetNumberAnim(number), posX, posY, 1100000, 3);
}

void MapManager::MakeConnection(const MapPoint& point1, const MapPoint& point2)
{
    DrawLine(point1.x, point1.y, point2.color, point2.x, point2.y, point1.color);
    DrawEntrancePoint(point1.x, point1.y);
    DrawEntrancePoint(point2.x, point2.y);
}

void MapManager::DrawLine(float x1, float y1, Uint32 color1, float x2, float y2, Uint32 color2)
{
    const auto p1 = mapToScreen(x1, y1);
    const auto p2 = mapToScreen(x2, y2);

    // Calculate direction vector
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float length = sqrtf(dx * dx + dy * dy);

    // Perpendicular vector (normalized)
    float px = -dy / length;
    float py = dx / length;

    float halfThickness = 1.5f * (_nj_screen_.h / 1080);

    // Offset points perpendicular to the line
    float ox = px * halfThickness;
    float oy = py * halfThickness;

    NJS_POINT2 points[] = {
        {_nj_screen_.cx - (p1.x + ox), _nj_screen_.cy - (p1.y + oy)},
        {_nj_screen_.cx - (p1.x - ox), _nj_screen_.cy - (p1.y - oy)},
        {_nj_screen_.cx - (p2.x + ox), _nj_screen_.cy - (p2.y + oy)},
        {_nj_screen_.cx - (p2.x - ox), _nj_screen_.cy - (p2.y - oy)},
    };

    NJS_COLOR linecol[4];
    NJS_POINT2COL linep2;

    linep2.p = points;
    linep2.col = linecol;
    linep2.tex = NULL;
    linep2.num = 4;

    linep2.col[0].color = color1;
    linep2.col[1].color = color1;
    linep2.col[2].color = color2;
    linep2.col[3].color = color2;

    Draw2DLinesMaybe_Queue(&linep2, 4, 22348, NJD_FILL | NJD_TRANSPARENT, QueuedModelFlagsB_SomeTextureThing);
}

void MapManager::DrawEntrancePoint(float x, float y)
{
    auto point = mapToScreen(x, y);

    float squareSize = 8.0f * (_nj_screen_.h / 1080);
    float halfSize = squareSize / 2.0f;
    DrawRect_Queue(_nj_screen_.cx - point.x - halfSize,
                   _nj_screen_.cy - point.y - halfSize,
                   _nj_screen_.cx - point.x + halfSize,
                   _nj_screen_.cy - point.y + halfSize,
                   22348,
                   0xFF555555,
                   QueuedModelFlagsB_EnableZWrite);

    squareSize = 4.0f * (_nj_screen_.h / 1080);
    halfSize = squareSize / 2.0f;

    DrawRect_Queue(_nj_screen_.cx - point.x - halfSize,
                   _nj_screen_.cy - point.y - halfSize,
                   _nj_screen_.cx - point.x + halfSize,
                   _nj_screen_.cy - point.y + halfSize,
                   22348,
                   0xFFFFFFFF,
                   QueuedModelFlagsB_EnableZWrite);
}


void MapManager::ShowDoorRequirement(AdventureFieldEntrance adventureFieldEntrance)
{
    // We get the level on the other side of the door
    const auto oppositeEntranceId = _adventureFieldEntranceMap.GetReplacementConnection(
        adventureFieldEntrance.entranceId);

    const auto oppositeEntrance = _adventureFieldEntranceMap.FindEntranceById(oppositeEntranceId);

    if (oppositeEntrance == nullptr)
        return;

    if (_adventureFieldEntranceMap.CalculateCorrectAct(oppositeEntrance->levelAndActId) ==
        LevelAndActIDs_HedgehogHammer)
        return;

    if (_options.gatingMode == EmblemGating)
    {
        const int entranceValue = _options.
            GetEntranceEmblemValue(adventureFieldEntrance.entranceId, oppositeEntranceId);
        if (entranceValue <= 0)
            return;
        ShowDoorIcon(adventureFieldEntrance.indicatorPosition, adventureFieldEntrance.indicatorAngle, emblem_lock_anim);
        ShowDoorIcon(adventureFieldEntrance.indicatorPosition, adventureFieldEntrance.indicatorAngle, line_lock_anim,
                     0.01f);

        ShowNumberDynamic(adventureFieldEntrance, _gameStatus.unlock.currentEmblems, -10, 2, -0.01f, 4, false);
        ShowNumberDynamic(adventureFieldEntrance, entranceValue, 2, -2, -0.04f, 4, true);
    }
    else if (_options.gatingMode == KeyItemGating)
    {
        ShowDoorIcon(adventureFieldEntrance.indicatorPosition, adventureFieldEntrance.indicatorAngle, lock_anim);
    }
}

void MapManager::ShowBlockedDoor(AdventureFieldEntrance adventureFieldEntrance)
{
    // We get the level on the other side of the door
    const auto oppositeEntranceId = _adventureFieldEntranceMap.GetReplacementConnection(
        adventureFieldEntrance.entranceId);

    const auto oppositeEntrance = _adventureFieldEntranceMap.FindEntranceById(oppositeEntranceId);

    if (oppositeEntrance == nullptr)
        return;

    ShowDoorIcon(adventureFieldEntrance.indicatorPosition, adventureFieldEntrance.indicatorAngle, blocked_anim);
}

void LateDrawDoorIcon(void* data)
{
    njColorBlendingMode(NJD_SOURCE_COLOR, NJD_COLOR_BLENDING_SRCALPHA);
    njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
    SetMaterial(255, 255, 255, 255);
    NJS_SPRITE mySprite = {{0}, 1, 1, 0, &entranceTextList, static_cast<NJS_TEXANIM*>(data)};
    njDrawSprite3D(&mySprite, 0, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
    ResetMaterial();
}


void MapManager::ShowDoorIcon(NJS_POINT3 position, float angle, NJS_TEXANIM* anim, float offset)
{
    float angleRad = angle * (3.14159265f / 180.0f);
    float offsetX = offset * sinf(angleRad);
    float offsetZ = offset * cosf(angleRad);

    njSetTexture(&entranceTextList);
    njPushMatrix(0);

    njTranslate(0, position.x + offsetX, position.y, position.z + offsetZ);
    njRotateY(0, 0x10000 * (angle / 360.0f));
    late_SetFunc(LateDrawDoorIcon, static_cast<void*>(anim), 100000.0f, LATE_EASY);
    njPopMatrix(1u);
}

bool MapManager::ShouldShowName(LevelAndActIDs levelAndActId)
{
    if (_options.entranceRandomizer == NoEntranceRandomization)
        return false;

    bool isStage = levelAndActId >= LevelAndActIDs_EmeraldCoast1 && levelAndActId <= LevelAndActIDs_HotShelter4;
    bool isBoss = (levelAndActId >= LevelAndActIDs_Chaos0 && levelAndActId <= LevelAndActIDs_E101R) ||
        (levelAndActId >= LevelAndActIDs_TwinkleCircuit1 && levelAndActId <= LevelAndActIDs_SandHill);
    bool isChaoGarden = levelAndActId == LevelAndActIDs_SSGarden ||
        levelAndActId == LevelAndActIDs_ECGarden ||
        levelAndActId == LevelAndActIDs_MRGarden;

    switch (_options.entranceRandomizer)
    {
    case StagesRandomized:
        return isStage;
    case StagesBossesRandomized:
        return isStage || isBoss;
    case StagesBossesChaoRandomized:
        return isStage || isBoss || isChaoGarden;
    case EverythingRandomized:
        return true;
    default:
        return false;
    }
}

void MapManager::ShowDoorName(AdventureFieldEntrance adventureFieldEntrance)
{
    // if (_options.entranceRandomizer == NoEntranceRandomization)
    //     return;

    // We get the level on the other side of the door
    const auto oppositeEntranceId = _adventureFieldEntranceMap.GetReplacementConnection(
        adventureFieldEntrance.entranceId);
    const auto oppositeEntrance = _adventureFieldEntranceMap.FindEntranceById(oppositeEntranceId);
    if (oppositeEntrance == nullptr)
        return;

    //TODO: uncomment
    // if (!this->ShouldShowName(oppositeEntrance->levelAndActId))
    //     return;


    LevelAndActIDs levelActAndId = _instance->_adventureFieldEntranceMap.CalculateCorrectAct(
        oppositeEntrance->levelAndActId);
    auto level = static_cast<LevelIDs>(GET_LEVEL(levelActAndId));

    NJS_TEXANIM* background_anim = getNameBackground(level);
    if (background_anim != nullptr)
        ShowDoorIcon(adventureFieldEntrance.indicatorPosition, adventureFieldEntrance.indicatorAngle, background_anim);


    auto fullName_anim = getFullNameFromEntrance(levelActAndId, oppositeEntrance->entranceId);
    if (fullName_anim != nullptr)
        ShowDoorIcon(adventureFieldEntrance.indicatorPosition, adventureFieldEntrance.indicatorAngle,
                     fullName_anim, 0.01f);
}

NJS_TEXANIM* MapManager::getNameBackground(LevelIDs level)
{
    switch (level)
    {
    case LevelIDs_HedgehogHammer:
    case LevelIDs_EmeraldCoast:
    case LevelIDs_WindyValley:
    case LevelIDs_TwinklePark:
    case LevelIDs_SpeedHighway:
    case LevelIDs_RedMountain:
    case LevelIDs_SkyDeck:
    case LevelIDs_LostWorld:
    case LevelIDs_IceCap:
    case LevelIDs_Casinopolis:
    case LevelIDs_FinalEgg:
    case LevelIDs_HotShelter:
        switch (CurrentCharacter)
        {
        case Characters_Sonic:
            return sonic_background_anim;
        case Characters_Tails:
            return tails_background_anim;
        case Characters_Knuckles:
            return knuckles_background_anim;
        case Characters_Amy:
            return amy_background_anim;
        case Characters_Gamma:
            return gamma_background_anim;
        case Characters_Big:
            return big_background_anim;
        default:
            return nullptr;
        }
    case LevelIDs_Chaos0:
    case LevelIDs_Chaos2:
    case LevelIDs_Chaos4:
    case LevelIDs_Chaos6:
    case LevelIDs_PerfectChaos:
    case LevelIDs_EggHornet:
    case LevelIDs_EggWalker:
    case LevelIDs_EggViper:
    case LevelIDs_Zero:
    case LevelIDs_E101:
    case LevelIDs_E101R:
        return boss_background_anim;
    case LevelIDs_TwinkleCircuit:
    case LevelIDs_SkyChase1:
    case LevelIDs_SkyChase2:
    case LevelIDs_SandHill:
        return sublevel_background_anim;
    case LevelIDs_StationSquare:
    case LevelIDs_SSGarden:
        return station_square_background_anim;
    case LevelIDs_MysticRuins:
    case LevelIDs_MRGarden:
        return mystic_ruins_background_anim;
    case LevelIDs_EggCarrierOutside:
    case LevelIDs_EggCarrierInside:
    case LevelIDs_ECGarden:
        return egg_carrier_background_anim;
    case LevelIDs_Past:
        return past_background_anim;
    default:
        return nullptr;
    }
}


NJS_TEXANIM* MapManager::getFullNameFromEntrance(LevelAndActIDs levelAndAct, EntranceId entranceId)
{
    // TODO: check how to implement
    // if (!_gameStatus.map.IsEntranceVisited(entranceTo->entranceId) && _options.entranceRandomizer !=
    //     NoEntranceRandomization)
    //     // return question_mark_anim;
    //     return city_hall_full_map_anim;

    switch (levelAndAct)
    {
    case LevelAndActIDs_StationSquare1:
        return city_hall_full_map_anim;
    case LevelAndActIDs_StationSquare2:
        if (entranceId == CasinoToHotel || entranceId == CasinoToEggWalker || entranceId == CasinoToCasinopolis)
            return casino_full_map_anim;
        return station_full_map_anim;
    case LevelAndActIDs_StationSquare3:
        return sewers_full_map_anim;
    case LevelAndActIDs_StationSquare4:
        if (entranceId == TwinkleParkTunnelToTwinkleParkLobby || entranceId == TwinkleParkTunnelToSewers)
            return tp_tunnel_full_map_anim;
        return ss_main_full_map_anim;
    case LevelAndActIDs_StationSquare5:
        if (entranceId == HotelPoolToEmeraldCoast)
            return ss_pool_full_map_anim;
        return hotel_full_map_anim;
    case LevelAndActIDs_StationSquare6:
        return tp_lobby_full_map_anim;
    /*case LevelIDs_EmeraldCoast:
        return emerald_coast_map_anim;
    case LevelIDs_WindyValley:
        return windy_valley_map_anim;
    case LevelIDs_TwinklePark:
        return twinkle_park_map_anim;
    case LevelIDs_SpeedHighway:
        return speed_highway_map_anim;
    case LevelIDs_RedMountain:
        return red_mountain_map_anim;
    case LevelIDs_SkyDeck:
        return sky_deck_map_anim;
    case LevelIDs_LostWorld:
        return lost_world_map_anim;
    case LevelIDs_IceCap:
        return ice_cap_map_anim;
    case LevelIDs_Casinopolis:
        return casinopolis_map_anim;
    case LevelIDs_FinalEgg:
        return final_egg_map_anim;
    case LevelIDs_HotShelter:
        return hot_shelter_map_anim;
    case LevelIDs_Chaos0:
        return chaos_0_map_anim;
    case LevelIDs_Chaos2:
        return chaos_2_map_anim;
    case LevelIDs_Chaos4:
        return chaos_4_map_anim;
    case LevelIDs_Chaos6:
        return chaos_6_map_anim;
    case LevelIDs_EggHornet:
        return egg_hornet_map_anim;
    case LevelIDs_EggWalker:
        return egg_walker_map_anim;
    case LevelIDs_EggViper:
        return egg_viper_map_anim;
    case LevelIDs_Zero:
        return zero_map_anim;
    case LevelIDs_E101:
        return beta_1_map_anim;
    case LevelIDs_E101R:
        return beta_2_map_anim;
    case LevelIDs_TwinkleCircuit:
        return twinkle_circuit_map_anim;
    case LevelIDs_SkyChase1:
        return sky_chase_1_map_anim;
    case LevelIDs_SkyChase2:
        return sky_chase_2_map_anim;
    case LevelIDs_SandHill:
        return sand_hill_map_anim;
    case LevelIDs_SSGarden:
        return ss_garden_map_anim;
    case LevelIDs_ECGarden:
        return ec_garden_map_anim;
    case LevelIDs_MRGarden:
        return mr_garden_map_anim;*/
    default:
        // return nullptr;
        return question_mark_anim;
    }
}


void MapManager::ShowNumberDynamic(const AdventureFieldEntrance& entrance, int number, float x,
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

void MapManager::showNumber(const AdventureFieldEntrance& adventureFieldEntrance, const float posX,
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
    late_SetFunc(LateDrawDoorIcon, static_cast<void*>(GetNumberAnim(number)), 100000.0f, LATE_EASY);
    njPopMatrix(1u);
}
