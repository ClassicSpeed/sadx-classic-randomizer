#include "EventDetector.h"
#include "sadx-mod-loader/SADXModLoader/include/UsercallFunctionHandler.h"
EventDetector* eventDetectorPtr;

UsercallFuncVoid(PlayCharacterDeathSound_t, (task * tp, int pid), (tp, pid), 0x446AF0, rEAX, stack4);
static void __cdecl HandlePlayCharacterDeathSound(task* tp, int pid);


UsercallFunc(bool, CheckMissionRequirements_t, (int mission, int character, int level), (mission, character, level),
             0x426AA0, rAL, rEAX, rEDX, rECX);
static bool __cdecl HandleCheckMissionRequirements(int mission, int character, int level);


UsercallFunc(bool, CheckMissionRequirementsSubgame_t, (int level, int character, int mission),
             (level, character, mission),
             0x4282D0, rEAX, rEAX, rECX, rEDX);
static bool __cdecl HandleCheckMissionRequirementsSubgame(int level, int character, int mission);


UsercallFuncVoid(OnBoaBoaPartDestroyed_t, (task * tp), (tp), 0x79F8F0, rEAX);
static void __cdecl HandleOnBoaBoaPartDestroyed(task* tp);


UsercallFuncVoid(OnCapsuleBreak_t, (task * tp), (tp), 0x4D6670, rEAX);
static void __cdecl HandleCapsuleBreak(task* tp);

UsercallFuncVoid(OnCapsuleBreakAir_t, (task * tp), (tp), 0x4C0610, rEDI);
static void __cdecl HandleCapsuleBreakAir(task* tp);

float GetShadowPos_r(float x, float y, float z, Angle3* rotation)
{
    float result = GetShadowPos(x, y, z, rotation);
    if (result == -1000000.0f)
        result = y;
    return result;
}

EventDetector::EventDetector(Randomizer& randomizer) : randomizer(randomizer)
{
    PlayCharacterDeathSound_t.Hook(HandlePlayCharacterDeathSound);
    CheckMissionRequirements_t.Hook(HandleCheckMissionRequirements);
    CheckMissionRequirementsSubgame_t.Hook(HandleCheckMissionRequirementsSubgame);
    OnBoaBoaPartDestroyed_t.Hook(HandleOnBoaBoaPartDestroyed);
    OnCapsuleBreak_t.Hook(HandleCapsuleBreak);
    OnCapsuleBreakAir_t.Hook(HandleCapsuleBreakAir);
    checkData = randomizer.GetCheckData();
    capsules = randomizer.GetCapsules();
    enemies = randomizer.GetEnemies();
    eventDetectorPtr = this;

    // Fix badniks not spawning
    WriteCall((void*)0x0049EFE7, GetShadowPos_r); // Egg Keeper
    WriteCall((void*)0x007A05EF, GetShadowPos_r); // Rhinotank
    WriteCall((void*)0x004C9012, GetShadowPos_r); // Snowman
    WriteCall((void*)0x006F7F3B, GetShadowPos_r); // Station Square cars (Egg Walker cutscene)
}

DataPointer(int, NumberOfHintsUsed, 0x3B0F138);

bool ManualMissionBCheck(const int character)
{
    switch (character)
    {
    case Characters_Knuckles:
        return NumberOfHintsUsed == 0;

    case Characters_Big:
        return BigWeightRecord >= 1000;

    default: return Rings >= 50;
    }
}

bool ManualMissionACheck(const int character, const int level)
{
    const int time = TimeFrames + 60 * (TimeSeconds + 60 * TimeMinutes);
    switch (character)
    {
    case Characters_Sonic:
        return time <= std::get<TIME_A_RANK>(SONIC_TARGET_TIMES.at(level));
    case Characters_Tails:
        return time <= std::get<TIME_A_RANK>(TAILS_TARGET_TIMES.at(level));
    case Characters_Knuckles:
        return time <= std::get<TIME_A_RANK>(KNUCKLES_TARGET_TIMES.at(level));
    case Characters_Amy:
        return time <= std::get<TIME_A_RANK>(AMY_TARGET_TIMES.at(level));
    case Characters_Gamma:
        return time > std::get<TIME_A_RANK>(GAMMA_TARGET_TIMES.at(level));
    case Characters_Big:
        return BigWeightRecord >= 2000;

    default: return false;
    }
    return false;
}

bool ManualMissionSCheck(const int character, const int level, const bool expertMode)
{
    const int time = TimeFrames + 60 * (TimeSeconds + 60 * TimeMinutes);
    switch (character)
    {
    case Characters_Sonic:
        if (expertMode)
            return time <= std::get<TIME_S_RANK_EXPERT>(SONIC_TARGET_TIMES.at(level));
        return time <= std::get<TIME_S_RANK>(SONIC_TARGET_TIMES.at(level));
    case Characters_Tails:
        if (expertMode)
            return time <= std::get<TIME_S_RANK_EXPERT>(TAILS_TARGET_TIMES.at(level));
        return time <= std::get<TIME_S_RANK>(TAILS_TARGET_TIMES.at(level));
    case Characters_Knuckles:
        if (expertMode)
            return time <= std::get<TIME_S_RANK_EXPERT>(KNUCKLES_TARGET_TIMES.at(level));
        return time <= std::get<TIME_S_RANK>(KNUCKLES_TARGET_TIMES.at(level));
    case Characters_Amy:
        if (expertMode)
            return time <= std::get<TIME_S_RANK_EXPERT>(AMY_TARGET_TIMES.at(level));
        return time <= std::get<TIME_S_RANK>(AMY_TARGET_TIMES.at(level));
    case Characters_Gamma:
        if (expertMode)
            return time > std::get<TIME_S_RANK_EXPERT>(GAMMA_TARGET_TIMES.at(level));
        return time > std::get<TIME_S_RANK>(GAMMA_TARGET_TIMES.at(level));
    case Characters_Big:
        return BigWeightRecord >= 2000 && Big_Sakana_Weight >= 5000;

    default: return false;
    }
    return false;
}

bool ManualSubLevelMissionACheck(const int level)
{
    if (level == LevelIDs_SandHill)
        return Score >= 10000;

    if (level == LevelIDs_SkyChase1)
        return Score >= 8000;

    if (level == LevelIDs_SkyChase1)
        return Score >= 20000;

    return false;
}


bool HandleCheckMissionRequirements(const int mission, const int character, const int level)
{
    //We check all other missions that were completed
    if (level <= LevelIDs_HotShelter)
    {
        //level - mission B
        if (mission == MISSION_C && eventDetectorPtr->completeMultipleLevelMissions)
        {
            if (ManualMissionBCheck(character))
            {
                SetLevelEmblemCollected(&SaveFile, character, level, MISSION_B);
                eventDetectorPtr->OnLevelEmblem(character, level, MISSION_B);
            }
        }

        //level - mission A
        if ((mission == MISSION_C || mission == MISSION_B) && eventDetectorPtr->completeMultipleLevelMissions)
        {
            if (ManualMissionACheck(character, level))
            {
                SetLevelEmblemCollected(&SaveFile, character, level, MISSION_A);
                eventDetectorPtr->OnLevelEmblem(character, level, MISSION_A);
            }
        }

        if (ManualMissionSCheck(character, level, eventDetectorPtr->randomizer.GetOptions().expertMode))
        {
            eventDetectorPtr->OnLevelEmblem(character, level, MISSION_S);
        }
    }
    return CheckMissionRequirements_t.Original(mission, character, level);
}

bool HandleCheckMissionRequirementsSubgame(const int level, const int character, const int mission)
{
    if (level >= LevelIDs_SkyChase1 && level <= LevelIDs_SandHill)
    {
        eventDetectorPtr->OnLevelEmblem(character, level, SUB_LEVEL_MISSION_B);

        //sublevel - mission A
        if (mission == SUB_LEVEL_MISSION_B)
        {
            if (ManualSubLevelMissionACheck(level))
            {
                SetLevelEmblemCollected(&SaveFile, character, level, SUB_LEVEL_MISSION_A);
                eventDetectorPtr->OnLevelEmblem(character, level, SUB_LEVEL_MISSION_A);
            }
        }
    }
    return CheckMissionRequirementsSubgame_t.Original(level, character, mission);
}

FunctionHook<void, SaveFileData*, int, signed int, int> onLevelEmblemCollected(
    0x4B4640, [](SaveFileData* saveFile, const int character, const signed int level, const int mission)-> void
    {
        onLevelEmblemCollected.Original(saveFile, character, level, mission);
        if (DemoPlaying > 0)
            return;
        eventDetectorPtr->OnLevelEmblem(character, level, mission);
    });


//FunctionPointer(void, SetEmblemCollected, (SaveFileData *savefile, signed int index), 0x4B3F30);
FunctionHook<void, SaveFileData*, signed int> OnGenericEmblemCollected(
    0x4B3F30, [](SaveFileData* savefile, signed int index)-> void
    {
        OnGenericEmblemCollected.Original(savefile, index);
        if (DemoPlaying > 0)
            return;
        eventDetectorPtr->OnGenericEmblem(index);
    });


bool EventDetector::IsTargetableCheck(const LocationData& location) const
{
    if (location.character != CurrentCharacter)
        return false;
    if (location.level != CurrentStageAndAct)
        return false;
    if (location.checked)
        return false;

    if (location.type == LocationEnemy)
    {
        if (!eventDetectorPtr->randomizer.GetOptions().enemySanity)
            return false;

        if (!eventDetectorPtr->randomizer.GetOptions().GetCharacterEnemySanity(
            static_cast<Characters>(CurrentCharacter)))
            return false;
        return true;
    }
    if (location.type == LocationCapsule)
    {
        if (!eventDetectorPtr->randomizer.GetOptions().capsuleSanity)
            return false;
        if (!eventDetectorPtr->randomizer.GetOptions().GetCharacterCapsuleSanity(
            static_cast<Characters>(CurrentCharacter)))
            return false;
        if (!eventDetectorPtr->randomizer.GetOptions().GetSpecificCapsuleSanity(
            static_cast<CapsuleType>(location.capsuleType)))
            return false;
        if (!eventDetectorPtr->randomizer.GetOptions().includePinballCapsules && location.level ==
            LevelAndActIDs_Casinopolis3)
            return false;
        return true;
    }
    return false;
}

// Function to calculate the rotated "up" vector based on player rotation
NJS_VECTOR CalculateArrowPosition(const NJS_VECTOR& playerPosition, const Rotation3& playerRotation, float offset)
{
    // Assuming playerRotation contains angles in degrees for x, y, z axes
    float pitch = playerRotation.x * (3.14 / 32768); // Rotation around X-axis
    float yaw = playerRotation.y * (3.14 / 32768); // Rotation around Y-axis
    float roll = playerRotation.z * (3.14 / 32768);; // Rotation around Z-axis

    // Default "up" vector (pointing upwards relative to the player)
    NJS_VECTOR up = {0.0f, 1.0f, 0.0f};

    // Rotate "up" vector by player's rotation
    // Apply yaw (rotation around Y-axis)
    NJS_VECTOR rotatedUp;
    rotatedUp.x = up.x * cos(yaw) - up.z * sin(yaw);
    rotatedUp.z = up.x * sin(yaw) + up.z * cos(yaw);
    rotatedUp.y = up.y; // No change in Y for yaw

    // Apply pitch (rotation around X-axis)
    float tempY = rotatedUp.y;
    rotatedUp.y = tempY * cos(pitch) - rotatedUp.z * sin(pitch);
    rotatedUp.z = tempY * sin(pitch) + rotatedUp.z * cos(pitch);

    // Apply roll (rotation around Z-axis)
    float tempX = rotatedUp.x;
    rotatedUp.x = tempX * cos(roll) - rotatedUp.y * sin(roll);
    rotatedUp.y = tempX * sin(roll) + rotatedUp.y * cos(roll);

    // Calculate arrow position by adding the rotated "up" vector to the player's position
    NJS_VECTOR arrowPosition = playerPosition;
    arrowPosition.x += rotatedUp.x * offset;
    arrowPosition.y += rotatedUp.y * offset;
    arrowPosition.z += rotatedUp.z * offset;

    return arrowPosition;
}

EntityData1* lastClosestEnemy = nullptr; // ebp
FunctionHook<void, task*> onSonicMain(0x49A9B0, [](task* tp)-> void
{
    onSonicMain.Original(tp);
    if (CurrentCharacter != Characters_Sonic)
        return;
    if (eventDetectorPtr->homingAttackIndicator == HomingAttackIndicatorDisabled)
        return;

    if (playerpwp[0]->free.sw[2] > 1 || !HomingAttackTarget_Sonic[0].entity)
    {
        lastClosestEnemy = nullptr;
        return;
    }
    if (tp->twp->mode != 8 && tp->twp->mode != 14)
    {
        lastClosestEnemy = nullptr;
        return;
    }


    float closestDistance = 10000;
    EntityData1* closestEnemy = nullptr;
    NJS_VECTOR targetPosition;
    for (int i = 0; i < HomingAttackTarget_Sonic_Index; i++)
    {
        if (HomingAttackTarget_Sonic[i].entity != nullptr)
        {
            const CollisionData* targetCollision = HomingAttackTarget_Sonic[i].entity->CollisionInfo->CollisionArray;
            targetPosition = targetCollision->center;
            if ((targetCollision->attr & 0x20) == 0)
            {
                njAddVector(&targetPosition, &HomingAttackTarget_Sonic[i].entity->Position);
            }
            njSubVector(&targetPosition, &tp->twp->pos);
            const long double angleDifference = atan2(targetPosition.z, targetPosition.x) * 65536.0 *
                0.1591549762031479;
            if (BAMS_Subtract(tp->twp->ang.y, (unsigned __int64)angleDifference) <= 20480)
            {
                if (HomingAttackTarget_Sonic[i].distance < closestDistance)
                {
                    closestEnemy = HomingAttackTarget_Sonic[i].entity;
                    closestDistance = HomingAttackTarget_Sonic[i].distance;
                }
            }
        }
    }
    if (!closestEnemy)
        return;
    const CollisionData* targetCollision = closestEnemy->CollisionInfo->CollisionArray;
    targetPosition = targetCollision->center;
    if ((targetCollision->attr & 0x20) == 0)
    {
        njAddVector(&targetPosition, &closestEnemy->Position);
    }
    njSubVector(&targetPosition, &tp->twp->pos);
    if (targetPosition.y >= 0.0)
    {
        lastClosestEnemy = nullptr;
        return;
    }
    if (lastClosestEnemy != closestEnemy)
    {
        lastClosestEnemy = closestEnemy;
        if (eventDetectorPtr->homingAttackIndicator == HomingAttackIndicatorEnabled)
            PlaySound(1, 0, 0, 0);
    }

    //DRAW INDICATOR
    njPushMatrix(0);
    njColorBlendingMode(NJD_SOURCE_COLOR, NJD_COLOR_BLENDING_ONE);
    njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_ONE);
    SetMaterialAndSpriteColor_Float(1.0, 1.0, 1.0, 0.0);
    njSetTexture(&TARGET_TEXLIST);
    targetPosition = targetCollision->center;
    njAddVector(&targetPosition, &closestEnemy->Position);
    NJS_POINT2 position;
    njProjectScreen(0, &targetPosition, &position);
    TornadoTarget_SPRITE.p.x = position.x;
    TornadoTarget_SPRITE.p.y = position.y;
    TornadoTarget_SPRITE.sx = 1.75f;
    TornadoTarget_SPRITE.sy = 1.75f;
    njDrawSprite2D_ForcePriority(&TornadoTarget_SPRITE, 0, 1000.0, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
    njPopMatrix(1u);
    njColorBlendingMode(NJD_SOURCE_COLOR, NJD_COLOR_BLENDING_SRCALPHA);
    njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
    ClampGlobalColorThing_Thing();
});


void EventDetector::OnPlayingFrame() const
{
    if (DemoPlaying > 0)
        return;

    //Ignore events given by the mod itself
    if (GameMode != GameModes_Mission)
        return;


    bool checksFound = false;
    for (const auto& check : checkData)
    {
        if ((check.second.type == LocationUpgrade || check.second.type == LocationChaoEgg) && !check.second.checked
            && GetEventFlag(static_cast<EventFlags>(check.second.eventFlag)))
        {
            randomizer.OnCheckFound(check.first);
            checksFound = true;
        }
    }
    if (checksFound)
        checkData = randomizer.GetCheckData();

    if (CurrentLevel >= LevelIDs_EmeraldCoast && CurrentLevel <= LevelIDs_HotShelter)
    {
        if (trackerArrowToggleable)
            for (const auto& button : PressedButtons)
                if (button & WhistleButtons && Current_CharObj2 != nullptr)
                    trackerArrow = !trackerArrow;

        if (!trackerArrow)
            return;

        if (Current_CharObj2 == nullptr || EntityData1Ptrs[0] == nullptr)
            return;

        Rotation3 playerRotation = EntityData1Ptrs[0]->Rotation;
        NJS_VECTOR playerPosition = EntityData1Ptrs[0]->Position;
        float offset = CurrentCharacter == Characters_Gamma || CurrentCharacter == Characters_Big ? 25.0f : 15.0f;
        NJS_VECTOR arrowPosition = CalculateArrowPosition(playerPosition, playerRotation, offset);

        float closestDistance = 1000000.0f;
        LocationData* closestLocation = nullptr;
        if (!possibleChecks.empty())
        {
            for (auto& location : possibleChecks)
            {
                float dx = arrowPosition.x - location.point.x;
                float dy = arrowPosition.y - location.point.y;
                float dz = arrowPosition.z - location.point.z;
                float distance = sqrt(dx * dx + dy * dy + dz * dz);

                if (distance < closestDistance)
                {
                    closestDistance = distance;
                    closestLocation = new LocationData();
                    closestLocation->x = location.point.x;
                    closestLocation->y = location.point.y;
                    closestLocation->z = location.point.z;
                    closestLocation->type = location.type;
                }
            }
            possibleChecks.clear();
        }
        else
        {
            for (auto& check : checkData)
            {
                const LocationData& location = check.second;
                if (IsTargetableCheck(location))
                {
                    float dx = arrowPosition.x - location.x;
                    float dy = arrowPosition.y - location.y;
                    float dz = arrowPosition.z - location.z;
                    float distance = sqrt(dx * dx + dy * dy + dz * dz);

                    if (distance < closestDistance)
                    {
                        closestDistance = distance;
                        closestLocation = &check.second;
                    }
                }
            }
        }

        if (closestLocation != nullptr)
        {
            // Calculate direction vector from player to enemy
            NJS_VECTOR direction;
            direction.x = closestLocation->x - arrowPosition.x;
            direction.y = closestLocation->y - arrowPosition.y;
            direction.z = closestLocation->z - arrowPosition.z;

            // Normalize the direction vector
            float length = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
            direction.x /= length;
            direction.y /= length;
            direction.z /= length;

            // Distance from player to triangle tip
            float height = ARROW_HEIGHT + EXTRA_ARROW_HEIGHT;
            // Width of the base of the triangle
            float baseWidth = ARROW_BASE_WIDTH + EXTRA_BASE_WIDTH;
            float extraPercentage;
            if (trackerArrowShowDistance)
            {
                const double dz = arrowPosition.z - closestLocation->z;
                const double dy = arrowPosition.y - closestLocation->y;
                const double dx = arrowPosition.x - closestLocation->x;
                const double distance = sqrt(dx * dx + dy * dy + dz * dz);


                if (distance <= MIN_ARROW_DISTANCE)
                    extraPercentage = 0;
                else if (distance >= MAX_ARROW_DISTANCE)
                    extraPercentage = 1;
                else
                    extraPercentage = (distance - MIN_ARROW_DISTANCE) / (MAX_ARROW_DISTANCE - MIN_ARROW_DISTANCE);


                // Distance from player to triangle tip
                height = ARROW_HEIGHT + EXTRA_ARROW_HEIGHT * (1 - extraPercentage);
                // Width of the base of the triangle
                baseWidth = ARROW_BASE_WIDTH + EXTRA_BASE_WIDTH * (1 - extraPercentage);
            }

            NJS_POINT3 tip;
            tip.x = arrowPosition.x + direction.x * height;
            tip.y = arrowPosition.y + direction.y * height;
            tip.z = arrowPosition.z + direction.z * height;


            NJS_VECTOR up = {0.0f, 1.0f, 0.0f}; // Arbitrary up vector, change if needed
            NJS_VECTOR right;

            // Cross product to get the perpendicular vector (right vector)
            right.x = up.y * direction.z - up.z * direction.y;
            right.y = up.z * direction.x - up.x * direction.z;
            right.z = up.x * direction.y - up.y * direction.x;

            // Normalize the right vector
            length = sqrt(right.x * right.x + right.y * right.y + right.z * right.z);
            right.x /= length;
            right.y /= length;
            right.z /= length;

            NJS_POINT3 leftBase, rightBase;

            // Left base point
            leftBase.x = arrowPosition.x - right.x * baseWidth / 2;
            leftBase.y = arrowPosition.y - right.y * baseWidth / 2;
            leftBase.z = arrowPosition.z - right.z * baseWidth / 2;

            // Right base point
            rightBase.x = arrowPosition.x + right.x * baseWidth / 2;
            rightBase.y = arrowPosition.y + right.y * baseWidth / 2;
            rightBase.z = arrowPosition.z + right.z * baseWidth / 2;

            // Calculate the second perpendicular vector
            NJS_VECTOR forward;
            forward.x = direction.y * right.z - direction.z * right.y;
            forward.y = direction.z * right.x - direction.x * right.z;
            forward.z = direction.x * right.y - direction.y * right.x;

            // Normalize the forward vector
            length = sqrt(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z);
            forward.x /= length;
            forward.y /= length;
            forward.z /= length;

            NJS_POINT3 frontBase, backBase;

            // Front base point
            frontBase.x = arrowPosition.x - forward.x * baseWidth / 2;
            frontBase.y = arrowPosition.y - forward.y * baseWidth / 2;
            frontBase.z = arrowPosition.z - forward.z * baseWidth / 2;

            // Back base point
            backBase.x = arrowPosition.x + forward.x * baseWidth / 2;
            backBase.y = arrowPosition.y + forward.y * baseWidth / 2;
            backBase.z = arrowPosition.z + forward.z * baseWidth / 2;

            // Calculate the arrow points
            NJS_POINT3 point[] = {
                {tip.x, tip.y, tip.z}, // Tip of the triangle (pointing towards the enemy)
                {leftBase.x, leftBase.y, leftBase.z}, // Left base point
                {rightBase.x, rightBase.y, rightBase.z}, // Right base point
                {tip.x, tip.y, tip.z}, // Tip of the second triangle
                {frontBase.x, frontBase.y, frontBase.z}, // Front base point
                {backBase.x, backBase.y, backBase.z} // Back base point
            };

            NJS_POINT3COL point3Col;
            point3Col.p = point;
            if (trackerArrowOverrideColor)
                if (closestLocation->type == LocationEnemy)
                    for (int i = 0; i < 6; ++i)
                        eventDetectorPtr->arrowColor[i] = enemyIndicatorColor[0];
                else if (closestLocation->type == LocationCapsule)
                    for (int i = 0; i < 6; ++i)
                        eventDetectorPtr->arrowColor[i] = capsuleIndicatorColor[0];
                else
                    for (int i = 0; i < 6; ++i)
                        eventDetectorPtr->arrowColor[i] = fishIndicatorColor[0];

            if (trackerArrowShowDistance)
            {
                uint8_t newAlpha = static_cast<uint8_t>(0xFF - (0xFF - 0x66) * extraPercentage);

                for (int i = 0; i < 6; ++i)
                {
                    eventDetectorPtr->arrowColor[i].argb.a = newAlpha;
                }
            }
            point3Col.col = eventDetectorPtr->arrowColor;
            njDrawTriangle3D(&point3Col, 6, NJD_TRANSPARENT);
        }
    }
}

void EventDetector::OnLevelEmblem(const int character, const int level, const int mission)
{
    bool checksFound = false;
    for (const auto& check : checkData)
    {
        if (check.second.type == LocationLevel && !check.second.checked
            && check.second.character == character
            && check.second.level == level
            && check.second.levelMission == mission)
        {
            randomizer.OnCheckFound(check.first);
            checksFound = true;
        }
        if (check.second.type == LocationSubLevel && !check.second.checked
            && check.second.level == level
            && check.second.levelMission == mission)
        {
            randomizer.OnCheckFound(check.first);
            checksFound = true;
        }
    }
    if (checksFound)
        checkData = randomizer.GetCheckData();
}

void EventDetector::OnGenericEmblem(const signed int index)
{
    bool checksFound = false;
    for (const auto& check : checkData)
    {
        if ((check.second.type == LocationFieldEmblem || check.second.type == LocationChaoRace) && !check.second.checked
            && check.second.emblemId == index)
        {
            randomizer.OnCheckFound(check.first);
            checksFound = true;
        }
    }
    if (checksFound)
        checkData = randomizer.GetCheckData();
}

void EventDetector::SetMultipleMissions(const bool completeMultipleMissions)
{
    this->completeMultipleLevelMissions = completeMultipleMissions;
}

void EventDetector::SetSanitySettings(const bool trackerArrow, const int trackerArrowColor,
                                      const bool trackerArrowToggleable,
                                      const bool trackerArrowShowDistance, const bool trackerArrowOverrideColor,
                                      const bool enemyIndicator, const int enemyIndicatorColor,
                                      const bool capsuleIndicator, const int capsuleIndicatorColor,
                                      const bool fishIndicator, const int fishIndicatorColor,
                                      const bool progressionIndicator, const int progressionIndicatorColor)
{
    this->trackerArrow = trackerArrow;
    this->trackerArrowToggleable = trackerArrowToggleable;
    this->trackerArrowShowDistance = trackerArrowShowDistance;
    this->trackerArrowOverrideColor = trackerArrowOverrideColor;
    this->arrowColor[0].color = trackerArrowColor;
    this->arrowColor[1].color = trackerArrowColor;
    this->arrowColor[2].color = trackerArrowColor;
    this->arrowColor[3].color = trackerArrowColor;
    this->arrowColor[4].color = trackerArrowColor;
    this->arrowColor[5].color = trackerArrowColor;

    this->enemyIndicator = enemyIndicator;
    this->enemyIndicatorColor[0].color = enemyIndicatorColor;
    this->enemyIndicatorColor[1].color = enemyIndicatorColor;
    this->enemyIndicatorColor[2].color = enemyIndicatorColor;

    this->capsuleIndicator = capsuleIndicator;
    this->capsuleIndicatorColor[0].color = capsuleIndicatorColor;
    this->capsuleIndicatorColor[1].color = capsuleIndicatorColor;
    this->capsuleIndicatorColor[2].color = capsuleIndicatorColor;

    this->fishIndicator = fishIndicator;
    this->fishIndicatorColor[0].color = fishIndicatorColor;
    this->fishIndicatorColor[1].color = fishIndicatorColor;
    this->fishIndicatorColor[2].color = fishIndicatorColor;

    this->progressionIndicator = progressionIndicator;
    this->progressionItemIndicatorColor[0].color = progressionIndicatorColor;
    this->progressionItemIndicatorColor[1].color = progressionIndicatorColor;
    this->progressionItemIndicatorColor[2].color = progressionIndicatorColor;
}

void EventDetector::setHomingAttackIndicator(const HomingAttackIndicator homingAttackIndicator)
{
    this->homingAttackIndicator = homingAttackIndicator;
}


FunctionHook<SEQ_SECTIONTBL*, int> seqGetSectionListHook(0x44EAF0, [](int playerno)-> SEQ_SECTIONTBL* {
    SEQ_SECTIONTBL* ptr = seqGetSectionListHook.Original(playerno);
    if (LastStoryFlag == 1 && eventDetectorPtr->lastStoryState == LastStoryNotStarted)
    {
        //Start Perfect Chaos fight as soon as we load the story
        ptr->stg = LevelIDs_PerfectChaos;
        ptr->act = 0;
        eventDetectorPtr->lastStoryState = LastStoryStarted;
    }
    return ptr;
});


FunctionHook<void, short> startLevelCutsceneHook(0x413C90, [](const short scene) -> void
{
    if (LastStoryFlag == 1 && eventDetectorPtr->lastStoryState == LastStoryStarted && scene == 1)
    {
        //We start the credits as soon as the fight is won
        EventFlagArray[EventFlags_SuperSonicAdventureComplete] = 1;
        WriteSaveFile();
        GameState = MD_GAME_FADEOUT_STAFFROLL;
        eventDetectorPtr->lastStoryState = LastStoryCompleted;
        eventDetectorPtr->randomizer.OnGameCompleted();
        return;
    }
    startLevelCutsceneHook.Original(scene);
});

FunctionHook<BOOL> onMissionMenuRenderHook(0x506410, []()-> BOOL
{
    eventDetectorPtr->lastStoryState = LastStoryNotStarted;
    return onMissionMenuRenderHook.Original();
});


int GetCapsuleCapsuleFromPosition(const NJS_VECTOR& position)
{
    for (const auto& capsule : eventDetectorPtr->capsules)
    {
        if (capsule.character != CurrentCharacter)
            continue;

        if (capsule.level != CurrentStageAndAct)
            continue;

        const float dx = position.x - capsule.x;
        const float dy = position.y - capsule.y;
        const float dz = position.z - capsule.z;
        const float distance = sqrt(dx * dx + dy * dy + dz * dz);

        if (distance <= 0.1)
            return capsule.locationId;
    }
    return -1;
}

void CheckCapsule(const EntityData1* entity, const bool specificCapsule)
{
    if (DemoPlaying > 0)
        return;
    if (!eventDetectorPtr->randomizer.GetOptions().capsuleSanity)
        return;
    if (!eventDetectorPtr->randomizer.GetOptions().GetCharacterCapsuleSanity(static_cast<Characters>(CurrentCharacter)))
        return;
    if (!specificCapsule)
        return;
    if (!eventDetectorPtr->randomizer.GetOptions().includePinballCapsules && levelact(CurrentLevel, CurrentAct) ==
        LevelAndActIDs_Casinopolis3)
        return;

    const int locationId = GetCapsuleCapsuleFromPosition(entity->Position);
    if (locationId > 0)
    {
        eventDetectorPtr->randomizer.OnCheckFound(locationId);
        eventDetectorPtr->checkData = eventDetectorPtr->randomizer.GetCheckData();
    }
}

FunctionHook<void, EntityData1*> onSpeedUpCapsuleBroken(0x4D6BF0, [](EntityData1* entity)-> void
{
    onSpeedUpCapsuleBroken.Original(entity);
    CheckCapsule(entity, eventDetectorPtr->randomizer.GetOptions().powerUpCapsuleSanity);
});
FunctionHook<void, EntityData1*> onInvincibilityCapsuleBroken(0x4D6D80, [](EntityData1* entity)-> void
{
    onInvincibilityCapsuleBroken.Original(entity);
    CheckCapsule(entity, eventDetectorPtr->randomizer.GetOptions().powerUpCapsuleSanity);
});
FunctionHook<void, EntityData1*> onFiveRingsCapsuleBroken(0x4D6C50, [](EntityData1* entity)-> void
{
    onFiveRingsCapsuleBroken.Original(entity);
    CheckCapsule(entity, eventDetectorPtr->randomizer.GetOptions().ringCapsuleSanity);
});
FunctionHook<void, EntityData1*> onTenRingsCapsule(0x4D6C90, [](EntityData1* entity)-> void
{
    onTenRingsCapsule.Original(entity);
    CheckCapsule(entity, eventDetectorPtr->randomizer.GetOptions().ringCapsuleSanity);
});
FunctionHook<void, EntityData1*> onRandomRingsCapsuleBroken(0x4D6CD0, [](EntityData1* entity)-> void
{
    onRandomRingsCapsuleBroken.Original(entity);
    CheckCapsule(entity, eventDetectorPtr->randomizer.GetOptions().ringCapsuleSanity);
});
FunctionHook<void, EntityData1*> onShieldCapsuleBroken(0x4D6DC0, [](EntityData1* entity)-> void
{
    onShieldCapsuleBroken.Original(entity);
    CheckCapsule(entity, eventDetectorPtr->randomizer.GetOptions().shieldCapsuleSanity);
});
FunctionHook<void, EntityData1*> onExtraLifeCapsuleBroken(0x4D6D40, [](EntityData1* entity)-> void
{
    onExtraLifeCapsuleBroken.Original(entity);
    CheckCapsule(entity, eventDetectorPtr->randomizer.GetOptions().lifeCapsuleSanity);
});
FunctionHook<void, EntityData1*> onBombCapsuleBroken(0x4D6E00, [](EntityData1* entity)-> void
{
    onBombCapsuleBroken.Original(entity);
    CheckCapsule(entity, eventDetectorPtr->randomizer.GetOptions().powerUpCapsuleSanity);
});
FunctionHook<void, EntityData1*> onElectricShieldCapsuleBroken(0x4D6E40, [](EntityData1* entity)-> void
{
    onElectricShieldCapsuleBroken.Original(entity);
    CheckCapsule(entity, eventDetectorPtr->randomizer.GetOptions().shieldCapsuleSanity);
});

//Make Sonic's capsule count as Tails'
void HandleCapsuleBreak(task* tp)
{
    if (CurrentCharacter == Characters_Tails)
    {
        if (tp && tp->twp && tp->twp->cwp && tp->twp->cwp->hit_cwp && tp->twp->cwp->hit_cwp->mytask ==
            GetPlayerTaskPointer(1))
        {
            item_info[ItemBox_CurrentItem].effect_func(tp->twp);
            DoThingWithItemBoxPowerupIndex(ItemBox_CurrentItem);
        }
    }
    OnCapsuleBreak_t.Original(tp);
}

void HandleCapsuleBreakAir(task* tp)
{
    if (CurrentCharacter == Characters_Tails)
    {
        if (tp && tp->twp && tp->twp->cwp && tp->twp->cwp->hit_cwp && tp->twp->cwp->hit_cwp->mytask ==
            GetPlayerTaskPointer(1))
        {
            item_info[ItemBox_CurrentItem].effect_func(tp->twp);
            DoThingWithItemBoxPowerupIndex(ItemBox_CurrentItem);
        }
    }
    OnCapsuleBreakAir_t.Original(tp);
}


FunctionHook<void, unsigned short> onKillHimP(0x440CD0, [](const unsigned short a1)-> void
{
    onKillHimP.Original(a1);
    eventDetectorPtr->randomizer.OnDeath();
});

FunctionHook<void> onKillHimByFallingDownP(0x446AD0, []()-> void
{
    onKillHimByFallingDownP.Original();
    eventDetectorPtr->randomizer.OnDeath();
});

void HandlePlayCharacterDeathSound(task* tp, const int pid)
{
    PlayCharacterDeathSound_t.Original(tp, pid);
    const double timePassed = (std::clock() - eventDetectorPtr->deathCooldownTimer) / static_cast<double>(
        CLOCKS_PER_SEC);
    if (timePassed > eventDetectorPtr->deathDetectionCooldown)
    {
        eventDetectorPtr->deathCooldownTimer = std::clock();
        eventDetectorPtr->randomizer.OnDeath();
    }
}


// We detect if tails just lost
FunctionHook<void, task*> onScoreDisplayMain(0x42BCC0, [](task* tp)-> void
{
    //If Tails just lost, we send a death link
    if (CurrentCharacter == Characters_Tails && RaceWinnerPlayer == 2)
        eventDetectorPtr->randomizer.OnDeath();

    return onScoreDisplayMain.Original(tp);
});


FunctionHook<void> onLoadLevelResults(0x415540, []()-> void
{
    onLoadLevelResults.Original();
    if (DemoPlaying > 0)
        return;
    if (CurrentLevel < LevelIDs_Chaos0 || CurrentLevel > LevelIDs_E101R)
        return;
    if (!eventDetectorPtr->randomizer.GetOptions().bossChecks)
        return;

    bool checksFound = false;
    for (const auto& check : eventDetectorPtr->checkData)
    {
        if (check.second.type != LocationBossFight)
            continue;

        if (eventDetectorPtr->randomizer.GetOptions().unifyEggHornet && CurrentLevel == LevelIDs_EggHornet)
        {
            if (check.second.character == -1 && check.second.level == LevelIDs_EggHornet && !check.second.checked)
            {
                eventDetectorPtr->randomizer.OnCheckFound(check.first);
                checksFound = true;
            }
        }
        else if (eventDetectorPtr->randomizer.GetOptions().unifyChaos4 && CurrentLevel == LevelIDs_Chaos4)
        {
            if (check.second.character == -1 && check.second.level == LevelIDs_Chaos4 && !check.second.checked)
            {
                eventDetectorPtr->randomizer.OnCheckFound(check.first);
                checksFound = true;
            }
        }
        else if (eventDetectorPtr->randomizer.GetOptions().unifyChaos6 && CurrentLevel == LevelIDs_Chaos6)
        {
            if (check.second.character == -1 && check.second.level == LevelIDs_Chaos6 && !check.second.checked)
            {
                eventDetectorPtr->randomizer.OnCheckFound(check.first);
                checksFound = true;
            }
        }
        else if (check.second.character == CurrentCharacter && check.second.level == CurrentLevel && !check.second.
            checked)
        {
            eventDetectorPtr->randomizer.OnCheckFound(check.first);
            checksFound = true;
        }
    }
    if (checksFound)
        eventDetectorPtr->checkData = eventDetectorPtr->randomizer.GetCheckData();
});

FunctionHook<void, ObjectMaster*> onClearMission(0x5923C0, [](ObjectMaster* obj)-> void
{
    onClearMission.Original(obj);

    const int missionNumber = 1 + **reinterpret_cast<Sint8**>(&obj->SETData.SETData[1].LoadCount);

    bool checksFound = false;
    for (const auto& check : eventDetectorPtr->checkData)
    {
        if (check.second.type != LocationMission)
            continue;
        if (check.second.missionNumber == missionNumber && !check.second.checked)
        {
            eventDetectorPtr->randomizer.OnCheckFound(check.first);
            checksFound = true;
        }
    }
    if (checksFound)
        eventDetectorPtr->checkData = eventDetectorPtr->randomizer.GetCheckData();
});


int GetEnemyFromPosition(const NJS_VECTOR& position)
{
    for (const auto& enemy : eventDetectorPtr->enemies)
    {
        if (enemy.character != CurrentCharacter)
            continue;

        if (enemy.level != CurrentStageAndAct)
            continue;

        const float dx = position.x - enemy.x;
        const float dy = position.y - enemy.y;
        const float dz = position.z - enemy.z;
        const float distance = sqrt(dx * dx + dy * dy + dz * dz);

        if (distance <= 0.1)
            return enemy.locationId;
    }
    return ENEMY_INVALID_ID;
}

void DrawIndicator(const task* tp, const bool tallElement, const bool checked, const IndicatorType indicatorType,
                   const int locationId)
{
    if (!cameraready)
        return;

    if (Current_CharObj2 == nullptr || EntityData1Ptrs[0] == nullptr)
        return;


    if (!checked)
    {
        LocationType locationType;
        if (indicatorType == EnemyIndicator)
            locationType = LocationEnemy;
        else if (indicatorType == CapsuleIndicator)
            locationType = LocationCapsule;
        else
            locationType = LocationFish;
        eventDetectorPtr->possibleChecks.push_back({tp->twp->pos.x, tp->twp->pos.y, tp->twp->pos.z, locationType});
    }


    if (indicatorType == EnemyIndicator && !eventDetectorPtr->enemyIndicator)
        return;
    if (indicatorType == CapsuleIndicator && !eventDetectorPtr->capsuleIndicator)
        return;
    if (indicatorType == FishIndicator && !eventDetectorPtr->capsuleIndicator)
        return;

    const EntityData1* player = EntityData1Ptrs[0];
    const double dz = player->Position.z - tp->twp->pos.z;
    const double dy = player->Position.y - tp->twp->pos.y;
    const double dx = player->Position.x - tp->twp->pos.x;
    const double distance = sqrt(dx * dx + dy * dy + dz * dz);

    float extraPercentage;

    if (distance <= MIN_INDICATOR_DISTANCE || checked)
        extraPercentage = 0;
    else if (distance >= MAX_INDICATOR_DISTANCE)
        extraPercentage = 1;
    else
        extraPercentage = (distance - MIN_INDICATOR_DISTANCE) / (MAX_INDICATOR_DISTANCE - MIN_INDICATOR_DISTANCE);

    int verticalOffset = INDICATOR_HEIGHT + EXTRA_INDICATOR_HEIGHT * extraPercentage;
    const float arrowSize = HEIGHT_SIZE + EXTRA_HEIGHT_SIZE * extraPercentage;
    if (tallElement)
        if (indicatorType == EnemyIndicator)
            verticalOffset += 25;
        else
            verticalOffset += 15;

    NJS_VECTOR direction;
    direction.x = camera_twp->pos.x - tp->twp->pos.x;
    direction.y = camera_twp->pos.y - tp->twp->pos.y;
    direction.z = camera_twp->pos.z - tp->twp->pos.z;

    float length = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
    direction.x /= length;
    direction.y /= length;
    direction.z /= length;

    NJS_VECTOR up = {0.0f, 1.0f, 0.0f};
    NJS_VECTOR right;
    right.x = up.y * direction.z - up.z * direction.y;
    right.y = up.z * direction.x - up.x * direction.z;
    right.z = up.x * direction.y - up.y * direction.x;

    length = sqrt(right.x * right.x + right.y * right.y + right.z * right.z);
    right.x /= length;
    right.y /= length;
    right.z /= length;

    NJS_POINT3 point[] = {
        {tp->twp->pos.x, tp->twp->pos.y + verticalOffset, tp->twp->pos.z},
        {
            tp->twp->pos.x - right.x * arrowSize / 2, tp->twp->pos.y + verticalOffset + arrowSize,
            tp->twp->pos.z - right.z * arrowSize / 2
        },
        {
            tp->twp->pos.x + right.x * arrowSize / 2, tp->twp->pos.y + verticalOffset + arrowSize,
            tp->twp->pos.z + right.z * arrowSize / 2
        }
    };

    NJS_POINT3COL point3Col;
    point3Col.p = point;
    if (!checked)
        if (eventDetectorPtr->progressionIndicator && eventDetectorPtr->randomizer.GetOptions().
                                                                        LocationHasProgressiveItem(locationId))
            point3Col.col = eventDetectorPtr->progressionItemIndicatorColor;
        else if (indicatorType == EnemyIndicator)
            point3Col.col = eventDetectorPtr->enemyIndicatorColor;
        else if (indicatorType == CapsuleIndicator)
            point3Col.col = eventDetectorPtr->capsuleIndicatorColor;
        else
            point3Col.col = eventDetectorPtr->fishIndicatorColor;
    else
        point3Col.col = eventDetectorPtr->disabledIndicatorColor;

    njDrawTriangle3D(&point3Col, 3, 0x0);
}

bool GetCapsuleTypeOption(const Float type)
{
    switch (static_cast<int>(std::floor(type)))
    {
    case 6:
        return eventDetectorPtr->randomizer.GetOptions().lifeCapsuleSanity;
    case 5:
    case 8:
        return eventDetectorPtr->randomizer.GetOptions().shieldCapsuleSanity;
    case 2:
    case 3:
    case 4:
        return eventDetectorPtr->randomizer.GetOptions().ringCapsuleSanity;
    case 1:
    case 7:
    case 0:
    default:
        return eventDetectorPtr->randomizer.GetOptions().powerUpCapsuleSanity;
    }
}

FunctionHook<void, task*> OnItemBoxMain(0x4D6F10, [](task* tp)-> void
{
    OnItemBoxMain.Original(tp);
    if (!eventDetectorPtr->randomizer.GetOptions().capsuleSanity)
        return;
    if (!eventDetectorPtr->randomizer.GetOptions().GetCharacterCapsuleSanity(static_cast<Characters>(CurrentCharacter)))
        return;
    if (!GetCapsuleTypeOption(tp->twp->scl.x))
        return;
    if (!eventDetectorPtr->randomizer.GetOptions().includePinballCapsules && levelact(CurrentLevel, CurrentAct) ==
        LevelAndActIDs_Casinopolis3)
        return;

    const int locationId = GetCapsuleCapsuleFromPosition(tp->twp->pos);
    if (locationId > 0)
    {
        if (tp->twp->mode == 4)
            return;

        const auto test = eventDetectorPtr->checkData.find(locationId);
        DrawIndicator(tp, false, test->second.checked, CapsuleIndicator, test->first);
    }
});

FunctionHook<void, task*> OnAirItemBoxMain(0x4C07D0, [](task* tp)-> void
{
    OnAirItemBoxMain.Original(tp);
    if (!eventDetectorPtr->randomizer.GetOptions().capsuleSanity)
        return;
    if (!eventDetectorPtr->randomizer.GetOptions().GetCharacterCapsuleSanity(static_cast<Characters>(CurrentCharacter)))
        return;
    if (!GetCapsuleTypeOption(tp->twp->scl.x))
        return;
    if (!eventDetectorPtr->randomizer.GetOptions().includePinballCapsules && levelact(CurrentLevel, CurrentAct) ==
        LevelAndActIDs_Casinopolis3)
        return;

    const int locationId = GetCapsuleCapsuleFromPosition(tp->twp->pos);
    if (locationId > 0)
    {
        const auto test = eventDetectorPtr->checkData.find(locationId);
        DrawIndicator(tp, true, test->second.checked, CapsuleIndicator, test->first);
    }
});

void __cdecl EmptyTrackerFunction(task* obj)
{
}

int FindEnemyTrackerId(task* tp)
{
    int enemyId = ENEMY_SEARCHING_ID;
    const task* child = tp->ctp;
    while (child != nullptr)
    {
        if (child->awp != nullptr)
        {
            const int possibleId = child->awp->work.sl[0];
            if (possibleId == ENEMY_INVALID_ID || possibleId > ENEMY_STARTING_ID)
                enemyId = possibleId;
        }
        child = child->next;
    }
    return enemyId;
}

void CheckEnemy(task* tp)
{
    if (!eventDetectorPtr->randomizer.GetOptions().enemySanity)
        return;

    if (!eventDetectorPtr->randomizer.GetOptions().GetCharacterEnemySanity(static_cast<Characters>(CurrentCharacter)))
        return;

    int enemyId = FindEnemyTrackerId(tp);

    if (enemyId > ENEMY_STARTING_ID)
    {
        const auto check = eventDetectorPtr->checkData.find(enemyId);
        const bool isTallEnemy = check->second.enemyType == Buyon;
        DrawIndicator(tp, isTallEnemy, check->second.checked, EnemyIndicator, check->first);
    }
    else if (enemyId != ENEMY_INVALID_ID)
    {
        const task* childTask = CreateChildTask(LoadObj_UnknownB, EmptyTrackerFunction, tp);
        enemyId = GetEnemyFromPosition(tp->twp->pos);
        childTask->awp->work.sl[0] = enemyId;
    }
}

FunctionHook<void, task*> onRhinotankLoad(0x7A1380, [](task* tp)-> void
{
    CheckEnemy(tp);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_WindyValley3
        && tp->twp->pos.x > 1347 && tp->twp->pos.x < 1349
        && tp->twp->pos.y > -2662 && tp->twp->pos.y < -2660
        && tp->twp->pos.z > 1384 && tp->twp->pos.z < 1386)
    {
        tp->twp->pos.y = -2650.1;
    }
    onRhinotankLoad.Original(tp);
});

FunctionHook<void, task*> onKikiLoad(0x4AD140, [](task* tp)-> void
{
    CheckEnemy(tp);
    onKikiLoad.Original(tp);
});

FunctionHook<void, task*> onKikiMain(0x4ACF80, [](task* tp)-> void
{
    CheckEnemy(tp);
    onKikiMain.Original(tp);
});
FunctionHook<void, task*> onWaterSpiderLoad(0x7AA960, [](task* tp)-> void
{
    //We change the spider location for sadx
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_TwinklePark2
        && tp->twp->pos.x > -3 && tp->twp->pos.x < -2
        && tp->twp->pos.y > -9 && tp->twp->pos.y < -8
        && tp->twp->pos.z > 703 && tp->twp->pos.z < 704)
    {
        tp->twp->pos.x = -62.73f;
        tp->twp->pos.y = -8.43f;
        tp->twp->pos.z = 579.43f;
    }
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EmeraldCoast2
        && tp->twp->pos.x > 712 && tp->twp->pos.x < 714
        && tp->twp->pos.y > 540 && tp->twp->pos.y < 541
        && tp->twp->pos.z > -818 && tp->twp->pos.z < -816)
    {
        tp->twp->pos.z = -869.65f;
    }
    CheckEnemy(tp);
    onWaterSpiderLoad.Original(tp);
});

FunctionHook<void, task*> onWaterSpiderMain(0x7AA870, [](task* tp)-> void
{
    CheckEnemy(tp);
    onWaterSpiderMain.Original(tp);
});

FunctionHook<void, task*> onBuyonMain(0x7B2E00, [](task* tp)-> void
{
    CheckEnemy(tp);
    onBuyonMain.Original(tp);
});

FunctionHook<void, task*> onBoaBoaHeadLoad(0x7A00F0, [](task* tp)-> void
{
    onBoaBoaHeadLoad.Original(tp);
    if (!eventDetectorPtr->randomizer.GetOptions().enemySanity)
        return;
    if (!eventDetectorPtr->randomizer.GetOptions().
                           GetCharacterEnemySanity(static_cast<Characters>(CurrentCharacter)))
        return;

    int enemyId = FindEnemyTrackerId(tp);

    if (enemyId > ENEMY_STARTING_ID)
    {
        const auto check = eventDetectorPtr->checkData.find(enemyId);
        DrawIndicator(tp, false, check->second.checked, EnemyIndicator, check->first);
    }
    else if (enemyId != ENEMY_INVALID_ID)
    {
        const task* childTask = CreateChildTask(LoadObj_UnknownB, EmptyTrackerFunction, tp);
        enemyId = GetEnemyFromPosition(tp->ptp->twp->pos);
        childTask->awp->work.sl[0] = enemyId;
    }
});

FunctionHook<void, task*> onLeonLoad(0x4A85C0, [](task* tp)-> void
{
    CheckEnemy(tp);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_WindyValley3 and CurrentCharacter == Characters_Tails
        && tp->twp->pos.x > 408 && tp->twp->pos.x < 410
        && tp->twp->pos.y > -406 && tp->twp->pos.y < -403
        && tp->twp->pos.z > -1370 && tp->twp->pos.z < -1368)
    {
        tp->twp->pos.y = -401;
    }
    onLeonLoad.Original(tp);
});
FunctionHook<void, task*> onLeonMain(0x4A83D0, [](task* tp)-> void
{
    CheckEnemy(tp);
    onLeonMain.Original(tp);
});

FunctionHook<void, task*> onSpinnerAMain(0x4B0DF0, [](task* tp)-> void
{
    CheckEnemy(tp);
    onSpinnerAMain.Original(tp);
});
FunctionHook<void, task*> onSpinnerBMain(0x4B0F40, [](task* tp)-> void
{
    CheckEnemy(tp);
    onSpinnerBMain.Original(tp);
});
//Electric Spinner
FunctionHook<void, task*> onSpinnerCMain(0x4B1090, [](task* tp)-> void
{
    CheckEnemy(tp);
    onSpinnerCMain.Original(tp);
});
FunctionHook<void, task*> onPoliceLoad(0x4B3210, [](task* tp)-> void
{
    CheckEnemy(tp);
    onPoliceLoad.Original(tp);
});
FunctionHook<void, task*> onPoliceMain(0x4B30E0, [](task* tp)-> void
{
    CheckEnemy(tp);
    onPoliceMain.Original(tp);
});
FunctionHook<void, task*> onSpikeBallSpinnerALoad(0x4AF190, [](task* tp)-> void
{
    CheckEnemy(tp);
    onSpikeBallSpinnerALoad.Original(tp);
});
FunctionHook<void, task*> onSpikeBallSpinnerAMain(0x4AF030, [](task* tp)-> void
{
    CheckEnemy(tp);
    onSpikeBallSpinnerAMain.Original(tp);
});
FunctionHook<void, task*> onSpikeBallSpinnerBLoad(0x4AF500, [](task* tp)-> void
{
    CheckEnemy(tp);
    onSpikeBallSpinnerBLoad.Original(tp);
});
FunctionHook<void, task*> onSpikeBallSpinnerBMain(0x4AF3D0, [](task* tp)-> void
{
    CheckEnemy(tp);
    onSpikeBallSpinnerBMain.Original(tp);
});
//Gola (Fire)
FunctionHook<void, task*> onSpikeBallSpinnerCLoad(0x4AF860, [](task* tp)-> void
{
    CheckEnemy(tp);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_RedMountain1
        && tp->twp->pos.x > -3874 && tp->twp->pos.x < -3872
        && tp->twp->pos.y > 593 && tp->twp->pos.y < 595
        && tp->twp->pos.z > -1807 && tp->twp->pos.z < -1805)
    {
        tp->twp->pos.x = -4001.92f;
        tp->twp->pos.y = 581.37f;
        tp->twp->pos.z = -1831.20f;
    }
    onSpikeBallSpinnerCLoad.Original(tp);
});

FunctionHook<void, task*> onSpikeBallSpinnerCMain(0x4AF770, [](task* tp)-> void
{
    CheckEnemy(tp);
    onSpikeBallSpinnerCMain.Original(tp);
});

FunctionHook<void, task*> onIceBallLoad(0x4C8FB0, [](task* tp)-> void
{
    CheckEnemy(tp);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_IceCap1
        && tp->twp->pos.x > 509 && tp->twp->pos.x < 510
        && tp->twp->pos.y > 32 && tp->twp->pos.y < 34
        && tp->twp->pos.z > 960 && tp->twp->pos.z < 962)
    {
        tp->twp->pos.y = 42.28f;
    }
    onIceBallLoad.Original(tp);
});
FunctionHook<void, task*> onIceBallMainA(0x4C8AC0, [](task* tp)-> void
{
    CheckEnemy(tp);
    onIceBallMainA.Original(tp);
});
FunctionHook<void, task*> onIceBallMainB(0x4C8DD0, [](task* tp)-> void
{
    CheckEnemy(tp);
    onIceBallMainB.Original(tp);
});

FunctionHook<void, task*> onEggKeeperLoad(0x4A6700, [](task* tp)-> void
{
    CheckEnemy(tp);
    onEggKeeperLoad.Original(tp);
});
FunctionHook<void, task*> onEggKeeperMain(0x4A6420, [](task* tp)-> void
{
    CheckEnemy(tp);
    onEggKeeperMain.Original(tp);
});


void CheckDestroyedEnemy(task* tp)
{
    if (!eventDetectorPtr->randomizer.GetOptions().enemySanity)
        return;

    if (!eventDetectorPtr->randomizer.GetOptions().GetCharacterEnemySanity(static_cast<Characters>(CurrentCharacter)))
        return;

    const int enemyId = FindEnemyTrackerId(tp);

    if (enemyId > ENEMY_STARTING_ID)
    {
        const auto test = eventDetectorPtr->checkData.find(enemyId);
        if (!test->second.checked)
        {
            eventDetectorPtr->randomizer.OnCheckFound(enemyId);
            eventDetectorPtr->checkData = eventDetectorPtr->randomizer.GetCheckData();
        }
    }
}

FunctionHook<void, task*> onDeadOut(0x46C150, [](task* tp)-> void
{
    CheckDestroyedEnemy(tp);
    onDeadOut.Original(tp);
});

FunctionHook<void, task*> onBuyonDestroyChildren(0x7B1500, [](task* tp)-> void
{
    //We check the player actually destroyed the enemy, and it wasn't destroyed by a restart
    if (tp->twp->mode == 6)
        CheckDestroyedEnemy(tp);
    onBuyonDestroyChildren.Original(tp);
});

void HandleOnBoaBoaPartDestroyed(task* tp)
{
    OnBoaBoaPartDestroyed_t.Original(tp);
    CheckDestroyedEnemy(tp);
}


void EventDetector::OnTwinkleCircuitCompleted(const int character)
{
    if (!eventDetectorPtr->randomizer.GetOptions().twinkleCircuitCheck)
        return;

    if (eventDetectorPtr->randomizer.GetOptions().multipleTwinkleCircuitChecks)
    {
        switch (character)
        {
        case Characters_Sonic:
            eventDetectorPtr->randomizer.OnCheckFound(40);
            break;
        case Characters_Tails:
            eventDetectorPtr->randomizer.OnCheckFound(41);
            break;
        case Characters_Knuckles:
            eventDetectorPtr->randomizer.OnCheckFound(42);
            break;
        case Characters_Amy:
            eventDetectorPtr->randomizer.OnCheckFound(43);
            break;
        case Characters_Big:
            eventDetectorPtr->randomizer.OnCheckFound(44);
            break;
        case Characters_Gamma:
            eventDetectorPtr->randomizer.OnCheckFound(45);
            break;

        default:
            break;
        }
    }
    else
    {
        eventDetectorPtr->randomizer.OnCheckFound(15);
    }
}

FunctionHook<signed int> onSaveTwinkleCircuitRecord(0x4B5BC0, []()-> signed int
{
    eventDetectorPtr->OnTwinkleCircuitCompleted(CurrentCharacter);
    return onSaveTwinkleCircuitRecord.Original();
});

FunctionHook<void, task*> onFishMain(0x597010, [](task* tp)-> void
{
    onFishMain.Original(tp);
    if (!eventDetectorPtr->randomizer.GetOptions().fishSanity)
        return;
    if (CurrentCharacter != Characters_Big)
        return;


    const int fishType = tp->twp->value.w[1];

    for (const auto& check : eventDetectorPtr->checkData)
    {
        if (check.second.type != LocationFish)
            continue;

        if (check.second.level != CurrentLevel)
            continue;

        if (check.second.fishType == fishType)
        {
            DrawIndicator(tp, false, check.second.checked, FishIndicator, check.first);
            break;
        }
    }
});


FunctionHook<void, task*> onFishCaught(0x470160, [](task* tp)-> void
{
    onFishCaught.Original(tp);
    if (!eventDetectorPtr->randomizer.GetOptions().fishSanity)
        return;

    const auto* v1 = reinterpret_cast<int*>(tp->twp);
    const int fishType = v1[2];

    bool checksFound = false;
    for (const auto& check : eventDetectorPtr->checkData)
    {
        if (check.second.type != LocationFish)
            continue;

        if (check.second.level != CurrentLevel)
            continue;

        if (check.second.fishType == fishType && !check.second.checked)
        {
            eventDetectorPtr->randomizer.OnCheckFound(check.first);
            checksFound = true;
        }
    }
    if (checksFound)
        eventDetectorPtr->checkData = eventDetectorPtr->randomizer.GetCheckData();
});


FunctionHook<void> onCheckEggHold(0x7151A0, []()-> void
{
    const int holdingItem = GetHoldingItemIDP(0);
    if (holdingItem == 5)
        //Gold Egg
        eventDetectorPtr->randomizer.OnCheckFound(900);
    else if (holdingItem == 10)
        //Silver Egg
        eventDetectorPtr->randomizer.OnCheckFound(901);
    else if (holdingItem == 11)
        //Black Egg
        eventDetectorPtr->randomizer.OnCheckFound(902);

    onCheckEggHold.Original();
});

//Burger Man delete function, should prevent the crash.
FunctionHook<void, task*> onMissionStatueDelete(0x5934C0, [](task* tp)-> void
{
    FreeTask(tp);
});

//https://info.sonicretro.org/SCHG:Sonic_Adventure/Sound_Editing
FunctionHook<void, MusicIDs> onPlayMusic(0x425690, [](const MusicIDs songId)-> void
{
    int actualId = eventDetectorPtr->randomizer.songRandomizationMap[songId];
    onPlayMusic.Original(static_cast<MusicIDs>(actualId));
    eventDetectorPtr->randomizer.OnPlaySong(static_cast<MusicIDs>(actualId));
});


FunctionHook<void, MusicIDs> onPlayMusic2(0x425800, [](const MusicIDs songId)-> void
{
    int actualId = eventDetectorPtr->randomizer.songRandomizationMap[songId];
    onPlayMusic2.Original(static_cast<MusicIDs>(actualId));
    eventDetectorPtr->randomizer.OnPlaySong(static_cast<MusicIDs>(actualId));
});


