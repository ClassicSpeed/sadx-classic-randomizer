#include "MapManager.h"


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
}

void MapManager::SetDoorLogicStrategy(IDoorLogicStrategy* doorLogicStrategy)
{
    this->_doorLogicStrategy = doorLogicStrategy;
}

void MapManager::ShowMap()
{
    njPushMatrix(0);
    njSetTexture(&entranceTextList);
    SetMaterial(255, 255, 255, 255);
    NJS_SPRITE mySprite = {{_nj_screen_.cx, _nj_screen_.cy, 1}, -50, -50, 0, &entranceTextList, base_map};
    njRotateX(0, 0x8000);
    njDrawSprite2D_ForcePriority(&mySprite, 0, 200, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
    njPopMatrix(1u);

    for (AdventureFieldEntrance adventureFieldEntrance : _adventureFieldEntranceMap.GetEntrances())
    {
        DrawConnectionsInMap(adventureFieldEntrance);
        DrawMapEmblem(adventureFieldEntrance, false);
    }
    for (AdventureFieldEntrance adventureFieldEntrance : _adventureFieldEntranceMap.GetStaticEntrances())
    {
        DrawMapEmblem(adventureFieldEntrance, true);
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


    const float x = 450 - (900.0 * locationInMap.x / 1024.0);
    float y = 450 - (900.0 * locationInMap.y / 1024.0);

    std::clock_t now = std::clock();
    double ms = double(now) * 1000.0 / CLOCKS_PER_SEC;
    int phase = static_cast<int>(ms / 250.0) & 1; // 0 or 1
    y += (phase == 0) ? 10.0f : 0.0f;


    njPushMatrix(0);
    njSetTexture(&entranceTextList);
    NJS_SPRITE myTestEmblem = {
        {_nj_screen_.cx - x, _nj_screen_.cy - y, 1}, -1.5, -1.5, 0, &entranceTextList, location_map_anim
    };
    njRotateX(0, 0x8000);
    njDrawSprite2D_ForcePriority(&myTestEmblem, 0, 300, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
    njPopMatrix(1u);
}


void MapManager::DrawMapEmblem(AdventureFieldEntrance adventureFieldEntrance, bool isStatic)
{
    auto entranceValue = _options.entranceEmblemValueMap.find(adventureFieldEntrance.entranceId);

    if (entranceValue == _options.entranceEmblemValueMap.end())
    {
        const auto oppositeEntrance = _adventureFieldEntranceMap.GetReplacementConnection(
            adventureFieldEntrance.entranceId, false);
        entranceValue = _options.entranceEmblemValueMap.find(oppositeEntrance);
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
    const float x = 450 - (900.0 * entranceX / 1024.0);
    const float y = 450 - (900.0 * entranceY / 1024.0);

    njPushMatrix(0);
    njSetTexture(&entranceTextList);

    NJS_TEXANIM* texanim = getInitialsFromEntrance(entranceTo);
    NJS_SPRITE myTestEmblem = {
        {_nj_screen_.cx - x, _nj_screen_.cy - y, 1}, -1.5, -1.5, 0, &entranceTextList, texanim
    };
    njRotateX(0, 0x8000);
    njDrawSprite2D_ForcePriority(&myTestEmblem, 0, 300, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
    njPopMatrix(1u);
}


void MapManager::DrawNewInMap(AdventureFieldEntrance adventureFieldEntrance)
{
    auto entranceValue = entranceLocationInMap.find(adventureFieldEntrance.entranceId);

    if (entranceValue == entranceLocationInMap.end())
        return;


    const float x = 450 - (900.0 * entranceValue->second.x / 1024.0);
    const float y = 450 - (900.0 * entranceValue->second.y / 1024.0);


    njPushMatrix(0);
    njSetTexture(&entranceTextList);
    NJS_SPRITE myTestEmblem = {
        {_nj_screen_.cx - x, _nj_screen_.cy - y, 1}, -1.5, -1.5, 0, &entranceTextList, new_logo_map_anim
    };
    njRotateX(0, 0x8000);
    njDrawSprite2D_ForcePriority(&myTestEmblem, 0, 300, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
    njPopMatrix(1u);
}


void MapManager::DrawEmblemNumberInMap(AdventureFieldEntrance adventureFieldEntrance, int doorCost)
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

void MapManager::DrawEntrancePoint(float x, float y)
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


void MapManager::showNumberMap(const float posX, const float posY, const int number)
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


bool MapManager::ShowDisableDoorIndicator(const EntranceId entranceId)
{
    return _doorLogicStrategy->ShowDisableDoorIndicator(entranceId);
}


void MapManager::ShowDoorEmblemRequirement(AdventureFieldEntrance adventureFieldEntrance)
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
