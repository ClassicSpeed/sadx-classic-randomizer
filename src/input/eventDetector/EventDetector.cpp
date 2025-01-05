#include "EventDetector.h"
#include "sadx-mod-loader/SADXModLoader/include/UsercallFunctionHandler.h"
EventDetector* eventDetectorPtr;

UsercallFuncVoid(PlayCharacterDeathSound_t, (task * tp, int pid), (tp, pid), 0x446AF0, rEAX, stack4);
static void __cdecl HandlePlayCharacterDeathSound(task* tp, int pid);


UsercallFunc(bool, CheckMissionRequirements_t, (int mission, int character, int level), (mission, character, level),
             0x426AA0, rAL, rEAX, rEDX, rECX);
static bool __cdecl HandleCheckMissionRequirements(int mission, int character, int level);


EventDetector::EventDetector(Randomizer& randomizer) : randomizer(randomizer)
{
    PlayCharacterDeathSound_t.Hook(HandlePlayCharacterDeathSound);
    CheckMissionRequirements_t.Hook(HandleCheckMissionRequirements);
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

        if (distance <= 5.0)
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

        if (distance <= 5.0)
            return enemy.locationId;
    }
    return -1;
}

void CheckEnemy(task* tp)
{
    const auto it = eventDetectorPtr->enemyTaskMap.find(tp->twp);
    if (it == eventDetectorPtr->enemyTaskMap.end())
    {
        const int enemyId = GetEnemyFromPosition(tp->twp->pos);
        eventDetectorPtr->enemyTaskMap[tp->twp] = enemyId;
    }
    else
    {
        const auto test = eventDetectorPtr->checkData.find(it->second);
        if (!test->second.checked)
        {
            const EntityData1* player = EntityData1Ptrs[0];
            const double dz = player->Position.z - tp->twp->pos.z;
            const double dy = player->Position.y - tp->twp->pos.y;
            const double dx = player->Position.x - tp->twp->pos.x;
            const double distance = sqrt(dx * dx + dy * dy + dz * dz);

            constexpr double MIN_DISTANCE = 110.0;
            constexpr double MAX_DISTANCE = 150.0;
            constexpr int OFFSET_WHEN_FAR = 20;

            int verticalOffset = OFFSET_WHEN_FAR;
            if (distance <= MIN_DISTANCE)
            {
                verticalOffset = 0;
            }
            else if (distance >= MAX_DISTANCE)
            {
                verticalOffset = OFFSET_WHEN_FAR;
            }
            else
            {
                verticalOffset = static_cast<int>((distance - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE) *
                    OFFSET_WHEN_FAR);
            }

            NJS_POINT3 point[] = {
                {tp->twp->pos.x, tp->twp->pos.y + verticalOffset + 16, tp->twp->pos.z},
                {tp->twp->pos.x, tp->twp->pos.y + verticalOffset + 22, tp->twp->pos.z + 3},
                {tp->twp->pos.x, tp->twp->pos.y + verticalOffset + 22, tp->twp->pos.z - 3},
                {tp->twp->pos.x, tp->twp->pos.y + verticalOffset + 16, tp->twp->pos.z},
                {tp->twp->pos.x + 3, tp->twp->pos.y + verticalOffset + 22, tp->twp->pos.z},
                {tp->twp->pos.x - 3, tp->twp->pos.y + verticalOffset + 22, tp->twp->pos.z}
            };
            NJS_COLOR color;
            color.argb = {0, 0, 0, 255};
            NJS_POINT3COL point3Col;
            point3Col.p = point;
            point3Col.num = 6;
            point3Col.col = &color;
            NJS_TEX tex = {1, 1};
            point3Col.tex = &tex;
            late_DrawTriangle3D(&point3Col, 6, 0xF0000000, LATE_MAT);
        }
    }
}

FunctionHook<BOOL, taskwk*, enemywk*> onEnemyCheckDamage(0x4CE030, [](taskwk* twp, enemywk* ewp)-> BOOL
{
    const BOOL result = onEnemyCheckDamage.Original(twp, ewp);
    if (result)
    {
        // PrintDebug("Enemy check damage in position: %f %f %f\n", twp->pos.x, twp->pos.y, twp->pos.z);
        const auto it = eventDetectorPtr->enemyTaskMap.find(twp);
        // PrintDebug("---AAA\n");
        if (it != eventDetectorPtr->enemyTaskMap.end())
        {
            // PrintDebug("---BBB\n");
            int enemyLocationId = it->second;
            const auto test = eventDetectorPtr->checkData.find(enemyLocationId);
            if (!test->second.checked)
            {
                // PrintDebug("---CCC\n");
                PrintDebug("Enemy check damage in position: %f %f %f\n", twp->pos.x, twp->pos.y, twp->pos.z);
                eventDetectorPtr->randomizer.OnCheckFound(enemyLocationId);
                eventDetectorPtr->checkData = eventDetectorPtr->randomizer.GetCheckData();
            }
        }
    }

    return result;
});

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

FunctionHook<void, task*> onBoaBoaLoad(0x7A0330, [](task* tp)-> void
{
    CheckEnemy(tp);
    onBoaBoaLoad.Original(tp);
});

FunctionHook<void, task*> onLeonLoad(0x4A85C0, [](task* tp)-> void
{
    CheckEnemy(tp);
    onLeonLoad.Original(tp);
});
