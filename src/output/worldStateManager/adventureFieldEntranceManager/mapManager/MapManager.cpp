#include "MapManager.h"

static NJS_POINT2 mapToScreen(Float x, Float y)
{
    constexpr float CENTER = 450.0f;
    constexpr float SCALE = 900.0f / 1024.0f;
    return {CENTER - (SCALE * x), CENTER - (SCALE * y)};
}

void drawSprite2D(NJS_TEXANIM* anim, float screenX, float screenY, int priority = 300, float scale = 1.5f)
{
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

MapManager::MapManager(Options& options, GameStatus& gameStatus, AdventureFieldEntranceMap& adventureFieldEntranceMap) :
    _options(options), _gameStatus(gameStatus), _adventureFieldEntranceMap(adventureFieldEntranceMap)
{
}

void MapManager::OnFrame()
{
    for (const auto& button : HeldButtons)
        if (button & WhistleButtons && Current_CharObj2 != nullptr)
            this->ShowMap();

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

    for (const auto& entrance : _adventureFieldEntranceMap.GetEntrances())
    {
        if (currentLevelAndAct != entrance.levelAndActId)
            continue;

        if (!ShowDisableDoorIndicator(entrance.entranceId))
            continue;

        ShowDoorEmblemRequirement(entrance);
    }
    for (const auto& entrance : _adventureFieldEntranceMap.GetStaticEntrances())
    {
        if (currentLevelAndAct != entrance.levelAndActId)
            continue;

        if (!ShowDisableDoorIndicator(entrance.entranceId))
            continue;

        ShowDoorEmblemRequirement(entrance);
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
        DrawMapEmblem(entrance, false);
    }
    for (const auto& entrance : _adventureFieldEntranceMap.GetStaticEntrances())
    {
        DrawMapEmblem(entrance, true);
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
        adventureFieldEntrance.entranceId, _gameStatus.map.isEggCarrierTransformed);
    auto entranceLocationTo = entranceLocationInMap.find(entranceToId);

    if (entranceLocationTo == entranceLocationInMap.end())
    {
        DrawEntrancePoint(entranceLocationFrom->second.x, entranceLocationFrom->second.y);
        auto entranceTo = _instance->_adventureFieldEntranceMap.FindEntranceById(entranceToId);
        DrawLevelInitialsInMap(entranceTo, entranceLocationFrom->second.x, entranceLocationFrom->second.y);
    }
    else
        MakeConnection(entranceLocationFrom->second.x, entranceLocationFrom->second.y, entranceLocationTo->second.x,
                       entranceLocationTo->second.y);
}

NJS_TEXANIM* MapManager::getInitialsFromEntrance(AdventureFieldEntrance* entranceTo)
{
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
        locationInMap = {769, 139};
    else if (CurrentStageAndAct == LevelAndActIDs_StationSquare2)
        locationInMap = {621, 272};
    else if (CurrentStageAndAct == LevelAndActIDs_StationSquare3)
        locationInMap = {929, 161};
    else if (CurrentStageAndAct == LevelAndActIDs_StationSquare4)
        locationInMap = {764, 374};
    else if (CurrentStageAndAct == LevelAndActIDs_StationSquare5)
        locationInMap = {599, 446};
    else if (CurrentStageAndAct == LevelAndActIDs_StationSquare6)
        locationInMap = {930, 442};
    else if (CurrentStageAndAct == LevelAndActIDs_MysticRuins1)
        locationInMap = {300, 276};
    else if (CurrentStageAndAct == LevelAndActIDs_MysticRuins2)
        locationInMap = {223, 484};
    else if (CurrentStageAndAct == LevelAndActIDs_MysticRuins3)
        locationInMap = {327, 104};
    else if (CurrentStageAndAct == LevelAndActIDs_MysticRuins4)
        locationInMap = {561, 63};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierInside1)
        locationInMap = {586, 720};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierInside2)
        locationInMap = {702, 743};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierInside3)
        locationInMap = {792, 634};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierInside4)
        locationInMap = {882, 567};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierInside5)
        locationInMap = {814, 788};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierInside6)
        locationInMap = {714, 900};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierOutside1)
        locationInMap = {446, 622};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierOutside2)
        locationInMap = {304, 585};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierOutside3)
        locationInMap = {306, 910};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierOutside4)
        locationInMap = {292, 758};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierOutside5)
        locationInMap = {201, 776};
    else if (CurrentStageAndAct == LevelAndActIDs_EggCarrierOutside6)
        locationInMap = {448, 932};
    else if (CurrentStageAndAct == LevelAndActIDs_Past1)
        locationInMap = {110, 129};
    else if (CurrentStageAndAct == LevelAndActIDs_Past2)
        locationInMap = {83, 424};
    else
        return;


    auto point = mapToScreen(locationInMap.x, locationInMap.y);

    std::clock_t now = std::clock();
    double ms = double(now) * 1000.0 / CLOCKS_PER_SEC;
    int phase = static_cast<int>(ms / 250.0) & 1; // 0 or 1
    point.y += (phase == 0) ? 10.0f : 0.0f;

    drawSprite2D(location_map_anim, point.x, point.y);
}


void MapManager::DrawMapEmblem(AdventureFieldEntrance adventureFieldEntrance, bool isStatic)
{
    const auto oppositeEntranceId = _adventureFieldEntranceMap.GetReplacementConnection(
        adventureFieldEntrance.entranceId, false);

    const auto oppositeEntrance = _adventureFieldEntranceMap.FindEntranceById(oppositeEntranceId);

    if (oppositeEntrance == nullptr)
        return;

    if (_adventureFieldEntranceMap.CalculateCorrectAct(oppositeEntrance->levelAndActId) ==
        LevelAndActIDs_HedgehogHammer)
    {
        auto entranceValue = entranceLocationInMap.find(adventureFieldEntrance.entranceId);

        if (entranceValue == entranceLocationInMap.end())
            return;

        auto point = mapToScreen(entranceValue->second.x, entranceValue->second.y);
        drawSprite2D(blocked_anim, point.x, point.y);
        return;
    }


    //Searches for emblem requirement
    auto entranceValue = _options.entranceEmblemValueMap.find(adventureFieldEntrance.entranceId);

    if (entranceValue == _options.entranceEmblemValueMap.end())
    {
        entranceValue = _options.entranceEmblemValueMap.find(oppositeEntranceId);
    }

    if (entranceValue == _options.entranceEmblemValueMap.end() || _gameStatus.unlock.currentEmblems >= entranceValue->
        second)
    {
        if (!_gameStatus.map.IsEntranceVisited(adventureFieldEntrance.entranceId) && !isStatic)
            DrawNewInMap(adventureFieldEntrance);
        return;
    }

    int doorCost = entranceValue->second;
    DrawEmblemNumberInMap(adventureFieldEntrance, doorCost);
}

void MapManager::DrawLevelInitialsInMap(AdventureFieldEntrance* entranceTo, Float entranceX,
                                        Float entranceY)
{
    auto point = mapToScreen(entranceX, entranceY);
    NJS_TEXANIM* texanim = getInitialsFromEntrance(entranceTo);
    drawSprite2D(texanim, point.x, point.y);
}


void MapManager::DrawNewInMap(AdventureFieldEntrance adventureFieldEntrance)
{
    auto entranceValue = entranceLocationInMap.find(adventureFieldEntrance.entranceId);

    if (entranceValue == entranceLocationInMap.end())
        return;

    auto point = mapToScreen(entranceValue->second.x, entranceValue->second.y);
    drawSprite2D(new_logo_map_anim, point.x, point.y);
}


void MapManager::DrawEmblemNumberInMap(AdventureFieldEntrance adventureFieldEntrance, int doorCost)
{
    auto entranceValue = entranceLocationInMap.find(adventureFieldEntrance.entranceId);

    if (entranceValue == entranceLocationInMap.end())
        return;

    auto point = mapToScreen(entranceValue->second.x, entranceValue->second.y);
    drawSprite2D(emblem_lock_anim, point.x, point.y);
    ShowNumberDynamicMap(doorCost, point.x, point.y);
}

void MapManager::ShowNumberDynamicMap(int number, float x, float y)
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


void MapManager::MakeConnection(float x1, float y1, float x2, float y2)
{
    DrawEntrancePoint(x1, y1);
    DrawEntrancePoint(x2, y2);
    DrawLine(x1, y1, x2, y2);
}

void MapManager::DrawLine(float x1, float y1, float x2, float y2)
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

    float halfThickness = 1.0f;

    // Offset points perpendicular to the line
    float ox = px * halfThickness;
    float oy = py * halfThickness;

    NJS_POINT2 points[] = {
        {_nj_screen_.cx - (p1.x + ox), _nj_screen_.cy - (p1.y + oy)},
        {_nj_screen_.cx - (p1.x - ox), _nj_screen_.cy - (p1.y - oy)},
        {_nj_screen_.cx - (p2.x - ox), _nj_screen_.cy - (p2.y - oy)},
        {_nj_screen_.cx - (p2.x + ox), _nj_screen_.cy - (p2.y + oy)},
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

void MapManager::DrawEntrancePoint(float x, float y)
{
    auto point = mapToScreen(x, y);

    const float squareSize = 6.0f;
    float halfSize = squareSize / 2.0f;
    DrawRect_Queue(_nj_screen_.cx - point.x - halfSize,
                   _nj_screen_.cy - point.y - halfSize,
                   _nj_screen_.cx - point.x + halfSize,
                   _nj_screen_.cy - point.y + halfSize,
                   22250,
                   0xFFFFFFFF,
                   QueuedModelFlagsB_EnableZWrite);
}


void MapManager::showNumberMap(const float posX, const float posY, const int number)
{
    drawSprite2D(GetNumberAnim(number), posX, posY, 300, 3);
}


bool MapManager::ShowDisableDoorIndicator(const EntranceId entranceId)
{
    return _doorLogicStrategy->ShowDisableDoorIndicator(entranceId);
}


void MapManager::ShowDoorEmblemRequirement(AdventureFieldEntrance adventureFieldEntrance)
{
    const auto oppositeEntranceId = _adventureFieldEntranceMap.GetReplacementConnection(
        adventureFieldEntrance.entranceId, false);

    const auto oppositeEntrance = _adventureFieldEntranceMap.FindEntranceById(oppositeEntranceId);

    if (oppositeEntrance == nullptr)
        return;

    if (_adventureFieldEntranceMap.CalculateCorrectAct(oppositeEntrance->levelAndActId) ==
        LevelAndActIDs_HedgehogHammer)
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
        NJS_SPRITE mySprite = {{0}, 1, 1, 0, &entranceTextList, blocked_anim};
        njDrawSprite3D(&mySprite, 0, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
        njPopMatrix(1u);
        return;
    }

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
    SetMaterial(255, 255, 255, 255);
    NJS_SPRITE numRight = {{0}, 1, 1, 0, &entranceTextList, GetNumberAnim(number)};
    njDrawSprite3D(&numRight, 0, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
    njPopMatrix(1u);
}
