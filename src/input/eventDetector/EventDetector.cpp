#include "EventDetector.h"
EventDetector* eventDetectorPtr;

EventDetector::EventDetector(Randomizer& randomizer) : randomizer(randomizer)
{
    checkData = randomizer.GetCheckData();
    lifeCapsules = randomizer.GetLifeCapsules();
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
        if (check.second.type == LocationUpgrade && !check.second.checked
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


void EventDetector::OnLevelCompleted(const short character, const short level)
{
    int mission = MISSION_C;
    if (GetLevelEmblemCollected(&SaveFile, character, level, MISSION_C))
        mission = MISSION_B;
    if (GetLevelEmblemCollected(&SaveFile, character, level, MISSION_B))
        mission = MISSION_A;

    if (mission == MISSION_C)
    {
        SetLevelEmblemCollected(&SaveFile, character, level, MISSION_C);
        eventDetectorPtr->OnLevelEmblem(character, level, mission);
    }

    //We check all other missions that were completed
    //level - mission B
    if (mission == MISSION_B || (mission == MISSION_C && eventDetectorPtr->completeMultipleLevelMissions))
    {
        if (ManualMissionBCheck(character))
        {
            SetLevelEmblemCollected(&SaveFile, character, level, MISSION_B);
            eventDetectorPtr->OnLevelEmblem(character, level, MISSION_B);
        }
    }

    //level - mission A
    if (mission == MISSION_A || ((mission == MISSION_C || mission == MISSION_B) && eventDetectorPtr->
        completeMultipleLevelMissions))
    {
        if (ManualMissionACheck(character, level))
        {
            SetLevelEmblemCollected(&SaveFile, character, level, MISSION_A);
            eventDetectorPtr->OnLevelEmblem(character, level, MISSION_A);
        }
    }
}

void EventDetector::OnSublevelCompleted(const short character, const short level, const int mission)
{
    if (mission == SUB_LEVEL_MISSION_B)
    {
        eventDetectorPtr->OnLevelEmblem(character, level, mission);
    }

    if (!eventDetectorPtr->completeMultipleLevelMissions)
        return;

    //sublevel - mission A
    if (mission == SUB_LEVEL_MISSION_A || (mission == SUB_LEVEL_MISSION_B && eventDetectorPtr->
        completeMultipleLevelMissions))
    {
        if (ManualSubLevelMissionACheck(level))
        {
            SetLevelEmblemCollected(&SaveFile, character, level, SUB_LEVEL_MISSION_A);
            eventDetectorPtr->OnLevelEmblem(character, level, SUB_LEVEL_MISSION_A);
        }
    }
}

void EventDetector::OnBossCompleted(int character, int level)
{
    if (!this->randomizer.GetOptions().bossChecks)
        return;
    bool checksFound = false;
    for (const auto& check : this->checkData)
    {
        if (check.second.type != LocationBossFight)
            continue;

        if (this->randomizer.GetOptions().unifyEggHornet && CurrentLevel == LevelIDs_EggHornet)
        {
            if (check.second.character == -1 && check.second.level == LevelIDs_EggHornet && !check.second.checked)
            {
                this->randomizer.OnCheckFound(check.first);
                checksFound = true;
            }
        }
        else if (this->randomizer.GetOptions().unifyChaos4 && CurrentLevel == LevelIDs_Chaos4)
        {
            if (check.second.character == -1 && check.second.level == LevelIDs_Chaos4 && !check.second.checked)
            {
                this->randomizer.OnCheckFound(check.first);
                checksFound = true;
            }
        }
        else if (this->randomizer.GetOptions().unifyChaos6 && CurrentLevel == LevelIDs_Chaos6)
        {
            if (check.second.character == -1 && check.second.level == LevelIDs_Chaos6 && !check.second.checked)
            {
                this->randomizer.OnCheckFound(check.first);
                checksFound = true;
            }
        }
        else if (check.second.character == CurrentCharacter && check.second.level == CurrentLevel && !check.second.
            checked)
        {
            this->randomizer.OnCheckFound(check.first);
            checksFound = true;
        }
    }
    if (checksFound)
        this->checkData = this->randomizer.GetCheckData();
}

void EventDetector::OnGenericEmblem(signed int index)
{
    bool checksFound = false;
    for (const auto& check : checkData)
    {
        if (check.second.type == LocationFieldEmblem && !check.second.checked
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


int GetLifeCapsuleFromPosition(const NJS_VECTOR& position)
{
    for (const auto& lifeCapsule : eventDetectorPtr->lifeCapsules)
    {
        if (lifeCapsule.character != CurrentCharacter)
            continue;

        if (lifeCapsule.level != CurrentStageAndAct)
            continue;

        const float dx = position.x - lifeCapsule.x;
        const float dy = position.y - lifeCapsule.y;
        const float dz = position.z - lifeCapsule.z;
        const float distance = sqrt(dx * dx + dy * dy + dz * dz);

        if (distance <= 5.0)
            return lifeCapsule.locationId;
    }
    return -1;
}

FunctionHook<void, EntityData1*> onBrokenGenericLifeCapsule(0x4D6D40, [](EntityData1* entity)-> void
{
    onBrokenGenericLifeCapsule.Original(entity);
    if (DemoPlaying > 0)
        return;
    if (!eventDetectorPtr->randomizer.GetOptions().lifeSanity)
        return;

    const int locationId = GetLifeCapsuleFromPosition(entity->Position);
    if (locationId > 0)
    {
        eventDetectorPtr->randomizer.OnCheckFound(locationId);
        eventDetectorPtr->checkData = eventDetectorPtr->randomizer.GetCheckData();
    }
});


FunctionHook<void, task*> onBrokenGroundLifeCapsule(0x4D6F10, [](task* tp)-> void
{
    onBrokenGroundLifeCapsule.Original(tp);
    if (!eventDetectorPtr->randomizer.GetOptions().lifeSanity)
        return;

    const int locationId = GetLifeCapsuleFromPosition(tp->twp->pos);
    if (locationId > 0)
    {
        const auto test = eventDetectorPtr->checkData.find(locationId);
        if (test->second.checked)
            FreeTask(tp);
    }
});

FunctionHook<void, task*> onBrokenAirLifeCapsule(0x4C07D0, [](task* tp)-> void
{
    onBrokenAirLifeCapsule.Original(tp);
    if (!eventDetectorPtr->randomizer.GetOptions().lifeSanity)
        return;

    const int locationId = GetLifeCapsuleFromPosition(tp->twp->pos);
    if (locationId > 0)
    {
        const auto test = eventDetectorPtr->checkData.find(locationId);
        if (test->second.checked)
            FreeTask(tp);
    }
});


FunctionHook<void, int> onGiveLives(0x425B60, [](const int lives)-> void
{
    //The game gives a negative live to represent a death
    if (lives == -1 && GameState == MD_GAME_FADEOUT_MISS)
        eventDetectorPtr->randomizer.OnDeath();
    onGiveLives.Original(lives);
});

FunctionHook<void, SaveFileData*, int, signed int, int> onLevelEmblemCollected(
    0x4B4640, [](SaveFileData* saveFile, const int character, const signed int level, const int mission)-> void
    {
        onLevelEmblemCollected.Original(saveFile, character, level, mission);
        if (DemoPlaying > 0)
            return;
        if (CurrentLevel >= LevelIDs_TwinkleCircuit && CurrentLevel <= LevelIDs_SandHill)
            eventDetectorPtr->OnSublevelCompleted(CurrentCharacter, CurrentLevel, mission);
    });

FunctionHook<void> onLoadLevelResults(0x415540, []()-> void
{
    onLoadLevelResults.Original();
    if (DemoPlaying > 0)
        return;

    if (CurrentLevel >= LevelIDs_Chaos0 && CurrentLevel <= LevelIDs_E101R)
        eventDetectorPtr->OnBossCompleted(CurrentCharacter, CurrentLevel);
    else if (CurrentLevel <= LevelIDs_HotShelter)
        eventDetectorPtr->OnLevelCompleted(CurrentCharacter, CurrentLevel);
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
