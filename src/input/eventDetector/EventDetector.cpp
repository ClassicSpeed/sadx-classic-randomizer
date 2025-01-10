#include "EventDetector.h"
#include "sadx-mod-loader/SADXModLoader/include/UsercallFunctionHandler.h"
EventDetector* eventDetectorPtr;

UsercallFuncVoid(PlayCharacterDeathSound_t, (task * tp, int pid), (tp, pid), 0x446AF0, rEAX, stack4);
static void __cdecl HandlePlayCharacterDeathSound(task* tp, int pid);


UsercallFunc(bool, CheckMissionRequirements_t, (int mission, int character, int level), (mission, character, level),
             0x426AA0, rAL, rEAX, rEDX, rECX);
static bool __cdecl HandleCheckMissionRequirements(int mission, int character, int level);


UsercallFuncVoid(OnBoaBoaPartDestroyed_t, (task * tp), (tp), 0x79F8F0, rEAX);
static void __cdecl HandleOnBoaBoaPartDestroyed(task* tp);


EventDetector::EventDetector(Randomizer& randomizer) : randomizer(randomizer)
{
    PlayCharacterDeathSound_t.Hook(HandlePlayCharacterDeathSound);
    CheckMissionRequirements_t.Hook(HandleCheckMissionRequirements);
    OnBoaBoaPartDestroyed_t.Hook(HandleOnBoaBoaPartDestroyed);
    checkData = randomizer.GetCheckData();
    capsules = randomizer.GetCapsules();
    enemies = randomizer.GetEnemies();
    eventDetectorPtr = this;
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
        if (SONIC_TARGET_TIMES.find(level) != SONIC_TARGET_TIMES.end())
            return time <= SONIC_TARGET_TIMES.at(level);
        break;
    case Characters_Tails:
        if (TAILS_TARGET_TIMES.find(level) != TAILS_TARGET_TIMES.end())
            return time <= TAILS_TARGET_TIMES.at(level);
        break;
    case Characters_Knuckles:
        if (KNUCKLES_TARGET_TIMES.find(level) != KNUCKLES_TARGET_TIMES.end())
            return time <= KNUCKLES_TARGET_TIMES.at(level);
        break;
    case Characters_Amy:
        if (AMY_TARGET_TIMES.find(level) != AMY_TARGET_TIMES.end())
            return time <= AMY_TARGET_TIMES.at(level);
        break;
    case Characters_Gamma:
        if (GAMMA_TARGET_TIMES.find(level) != GAMMA_TARGET_TIMES.end())
            return time > GAMMA_TARGET_TIMES.at(level);
        break;
    case Characters_Big:
        return BigWeightRecord >= 2000;

    default: return false;
    }
    return false;
}


bool ManualSubLevelMissionACheck(const int level)
{
    //You can't fail the Twinkle Circuit mission A 
    if (level == LevelIDs_TwinkleCircuit)
        return true;

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
        if (mission == MISSION_C)
        {
            if (ManualMissionBCheck(character))
            {
                SetLevelEmblemCollected(&SaveFile, character, level, MISSION_B);
                eventDetectorPtr->OnLevelEmblem(character, level, MISSION_B);
            }
        }

        //level - mission A
        if (mission == MISSION_C || mission == MISSION_B)
        {
            if (ManualMissionACheck(character, level))
            {
                SetLevelEmblemCollected(&SaveFile, character, level, MISSION_A);
                eventDetectorPtr->OnLevelEmblem(character, level, MISSION_A);
            }
        }
    }
    return CheckMissionRequirements_t.Original(mission, character, level);
}

FunctionHook<void, SaveFileData*, int, signed int, int> onLevelEmblemCollected(
    0x4B4640, [](SaveFileData* saveFile, const int character, const signed int level, const int mission)-> void
    {
        onLevelEmblemCollected.Original(saveFile, character, level, mission);
        if (DemoPlaying > 0)
            return;
        eventDetectorPtr->OnLevelEmblem(character, level, mission);

        if (!eventDetectorPtr->completeMultipleLevelMissions)
            return;

        if (level >= LevelIDs_TwinkleCircuit && level <= LevelIDs_SandHill)
        {
            //sublevel - mission A
            if (mission == SUB_LEVEL_MISSION_B)
            {
                if (ManualSubLevelMissionACheck(level))
                {
                    onLevelEmblemCollected.Original(saveFile, character, level, SUB_LEVEL_MISSION_A);
                    eventDetectorPtr->OnLevelEmblem(character, level, SUB_LEVEL_MISSION_A);
                }
            }
        }
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
        NJS_VECTOR playerPosition = EntityData1Ptrs[0]->Position;
        if (CurrentCharacter == Characters_Gamma || CurrentCharacter == Characters_Big)
            playerPosition.y += 25.0f;
        else
            playerPosition.y += 15.0f;
        float closestDistance = 1000000.0f;
        LocationData* closestLocation = nullptr;

        for (auto& check : checkData)
        {
            const LocationData& location = check.second;
            if ((location.type == LocationEnemy || location.type == LocationCapsule) &&
                location.character == CurrentCharacter &&
                location.level == CurrentStageAndAct &&
                !location.checked)
            {
                float dx = playerPosition.x - location.x;
                float dy = playerPosition.y - location.y;
                float dz = playerPosition.z - location.z;
                float distance = sqrt(dx * dx + dy * dy + dz * dz);

                if (distance < closestDistance)
                {
                    closestDistance = distance;
                    closestLocation = &check.second;
                }
            }
        }

        if (closestLocation != nullptr)
        {
            // Calculate direction vector from player to enemy
            NJS_VECTOR direction;
            direction.x = closestLocation->x - playerPosition.x;
            direction.y = closestLocation->y - playerPosition.y;
            direction.z = closestLocation->z - playerPosition.z;

            // Normalize the direction vector
            float length = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
            direction.x /= length;
            direction.y /= length;
            direction.z /= length;

            float height = 5.0f; // Distance from player to triangle tip
            float baseWidth = 2.5f; // Width of the base of the triangle

            NJS_POINT3 tip;
            tip.x = playerPosition.x + direction.x * height;
            tip.y = playerPosition.y + direction.y * height;
            tip.z = playerPosition.z + direction.z * height;


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
            leftBase.x = playerPosition.x - right.x * baseWidth / 2;
            leftBase.y = playerPosition.y - right.y * baseWidth / 2;
            leftBase.z = playerPosition.z - right.z * baseWidth / 2;

            // Right base point
            rightBase.x = playerPosition.x + right.x * baseWidth / 2;
            rightBase.y = playerPosition.y + right.y * baseWidth / 2;
            rightBase.z = playerPosition.z + right.z * baseWidth / 2;

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
            frontBase.x = playerPosition.x - forward.x * baseWidth / 2;
            frontBase.y = playerPosition.y - forward.y * baseWidth / 2;
            frontBase.z = playerPosition.z - forward.z * baseWidth / 2;

            // Back base point
            backBase.x = playerPosition.x + forward.x * baseWidth / 2;
            backBase.y = playerPosition.y + forward.y * baseWidth / 2;
            backBase.z = playerPosition.z + forward.z * baseWidth / 2;

            // Calculate the arrow points
            NJS_POINT3 point[] = {
                {tip.x, tip.y, tip.z}, // Tip of the triangle (pointing towards the enemy)
                {leftBase.x, leftBase.y, leftBase.z}, // Left base point
                {rightBase.x, rightBase.y, rightBase.z}, // Right base point
                {tip.x, tip.y, tip.z}, // Tip of the second triangle
                {frontBase.x, frontBase.y, frontBase.z}, // Front base point
                {backBase.x, backBase.y, backBase.z} // Back base point
            };


            NJS_COLOR colors[] = {
                {0xAA00FF00},
                {0xAA00FF00},
                {0xAA00FF00},
                {0xAA00FF00},
                {0xAA00FF00},
                {0xAA00FF00},
            };
            NJS_POINT3COL point3Col;
            point3Col.p = point;
            point3Col.col = colors;
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
            && check.second.mission == mission)
        {
            randomizer.OnCheckFound(check.first);
            checksFound = true;
        }
        if (check.second.type == LocationSubLevel && !check.second.checked
            && check.second.level == level
            && check.second.mission == mission)
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

        if (distance <= 4.0)
            return capsule.locationId;
    }
    return -1;
}

void CheckCapsule(EntityData1* entity, bool specificCapsule)
{
    if (DemoPlaying > 0)
        return;
    if (!eventDetectorPtr->randomizer.GetOptions().capsuleSanity)
        return;
    if (!specificCapsule)
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

        if (distance <= 4.0)
            return enemy.locationId;
    }
    return -1;
}
void DrawIndicator(const task* tp, const bool tallElement)
{
    if (!cameraready)
        return;

    const EntityData1* player = EntityData1Ptrs[0];
    const double dz = player->Position.z - tp->twp->pos.z;
    const double dy = player->Position.y - tp->twp->pos.y;
    const double dx = player->Position.x - tp->twp->pos.x;
    const double distance = sqrt(dx * dx + dy * dy + dz * dz);

    float extraPercentage;

    if (distance <= MIN_INDICATOR_DISTANCE)
        extraPercentage = 0;
    else if (distance >= MAX_INDICATOR_DISTANCE)
        extraPercentage = 1;
    else
        extraPercentage = (distance - MIN_INDICATOR_DISTANCE) / (MAX_INDICATOR_DISTANCE - MIN_INDICATOR_DISTANCE);

    int verticalOffset = INDICATOR_HEIGHT + EXTRA_INDICATOR_HEIGHT * extraPercentage;
    const float arrowSize = HEIGHT_SIZE + EXTRA_HEIGHT_SIZE * extraPercentage;
    if (tallElement)
        verticalOffset += 10;

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

    NJS_COLOR colors[] = {
        {0xFFFF1400},
        {0xFFFF1400},
        {0xFFFF1400},
    };
    NJS_POINT3COL point3Col;
    point3Col.p = point;
    point3Col.col = colors;
    njDrawTriangle3D(&point3Col, 3, 0x0);
}

FunctionHook<void, task*> OnItemBoxMain(0x4D6F10, [](task* tp)-> void
{
    OnItemBoxMain.Original(tp);
    if (!eventDetectorPtr->randomizer.GetOptions().capsuleSanity)
        return;

    if (!eventDetectorPtr->randomizer.GetOptions().GetCharacterCapsuleSanity(static_cast<Characters>(CurrentCharacter)))
        return;

    const int locationId = GetCapsuleCapsuleFromPosition(tp->twp->pos);
    if (locationId > 0)
    {
        const auto test = eventDetectorPtr->checkData.find(locationId);
        if (!test->second.checked)
            DrawIndicator(tp, false);
    }
});

FunctionHook<void, task*> OnAirItemBoxMain(0x4C07D0, [](task* tp)-> void
{
    OnAirItemBoxMain.Original(tp);
    if (!eventDetectorPtr->randomizer.GetOptions().capsuleSanity)
        return;
    if (!eventDetectorPtr->randomizer.GetOptions().GetCharacterCapsuleSanity(static_cast<Characters>(CurrentCharacter)))
        return;

    //TODO: check capsule type

    const int locationId = GetCapsuleCapsuleFromPosition(tp->twp->pos);
    if (locationId > 0)
    {
        const auto test = eventDetectorPtr->checkData.find(locationId);
        if (!test->second.checked)
            DrawIndicator(tp, true);
    }
});

void CheckEnemy(task* tp)
{
    if (!eventDetectorPtr->randomizer.GetOptions().enemySanity)
        return;

    if (!eventDetectorPtr->randomizer.GetOptions().GetCharacterEnemySanity(static_cast<Characters>(CurrentCharacter)))
        return;

    const auto it = eventDetectorPtr->enemyTaskMap.find(tp->twp);
    if (it == eventDetectorPtr->enemyTaskMap.end())
    {
        const int enemyId = GetEnemyFromPosition(tp->twp->pos);
        if (enemyId > 0)
            eventDetectorPtr->enemyTaskMap[tp->twp] = enemyId;
    }
    else
    {
        const auto test = eventDetectorPtr->checkData.find(it->second);
        if (!test->second.checked)
        {
            DrawIndicator(tp, false);
        }
    }
}


FunctionHook<void, task*> onRhinotankLoad(0x7A1380, [](task* tp)-> void
{
    CheckEnemy(tp);
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
    CheckEnemy(tp);
    onBoaBoaHeadLoad.Original(tp);
});

FunctionHook<void, task*> onLeonLoad(0x4A85C0, [](task* tp)-> void
{
    CheckEnemy(tp);
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


void CheckDestroyedEnemy(taskwk* twp)
{
    if (!eventDetectorPtr->randomizer.GetOptions().enemySanity)
        return;

    if (!eventDetectorPtr->randomizer.GetOptions().GetCharacterEnemySanity(static_cast<Characters>(CurrentCharacter)))
        return;

    const auto it = eventDetectorPtr->enemyTaskMap.find(twp);
    if (it != eventDetectorPtr->enemyTaskMap.end())
    {
        int enemyLocationId = it->second;
        const auto test = eventDetectorPtr->checkData.find(enemyLocationId);
        if (!test->second.checked)
        {
            eventDetectorPtr->randomizer.OnCheckFound(enemyLocationId);
            eventDetectorPtr->checkData = eventDetectorPtr->randomizer.GetCheckData();
        }
    }
}

FunctionHook<void, task*> onDeadOut(0x46C150, [](task* tp)-> void
{
    CheckDestroyedEnemy(tp->twp);
    onDeadOut.Original(tp);
});

void HandleOnBoaBoaPartDestroyed(task* tp)
{
    OnBoaBoaPartDestroyed_t.Original(tp);
    CheckDestroyedEnemy(tp->twp);
}
