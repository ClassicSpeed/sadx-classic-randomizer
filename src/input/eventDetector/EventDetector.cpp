#include "EventDetector.h"
EventDetector* eventDetector;

EventDetector::EventDetector(Randomizer& randomizer) : _randomizer(randomizer)
{
    _checkData = _randomizer.GetCheckData();
    eventDetector = this;
}


const std::unordered_map<int, int> sonic_target_times = {
    {LevelIDs_EmeraldCoast, 7200},
    {LevelIDs_WindyValley, 10800},
    {LevelIDs_Casinopolis, 18000},
    {LevelIDs_IceCap, 14400},
    {LevelIDs_TwinklePark, 10800},
    {LevelIDs_SpeedHighway, 9000},
    {LevelIDs_RedMountain, 10800},
    {LevelIDs_SkyDeck, 18000},
    {LevelIDs_LostWorld, 16200},
    {LevelIDs_FinalEgg, 16200}
};

const std::unordered_map<int, int> tails_target_times = {
    {LevelIDs_WindyValley, 5400}, //1 min 30 sec
    {LevelIDs_Casinopolis, 3600}, //1 min
    {LevelIDs_IceCap, 7200}, // 2 min
    {LevelIDs_SkyDeck, 3600}, //1 min
    {LevelIDs_SpeedHighway, 7200}, //2 min
};


const std::unordered_map<int, int> knuckles_target_times = {
    {LevelIDs_SpeedHighway, 3600},
    {LevelIDs_Casinopolis, 3600},
    {LevelIDs_RedMountain, 3600},
    {LevelIDs_LostWorld, 3600},
    {LevelIDs_SkyDeck, 7200},
};

const std::unordered_map<int, int> amy_target_times = {
    {LevelIDs_TwinklePark, 7200},
    {LevelIDs_HotShelter, 23400},
    {LevelIDs_FinalEgg, 9000},
};

const std::unordered_map<int, int> gamma_target_times = {
    {LevelIDs_FinalEgg, 9000},
    {LevelIDs_EmeraldCoast, 10800},
    {LevelIDs_WindyValley, 10800},
    {LevelIDs_RedMountain, 10800},
    {LevelIDs_HotShelter, 7200},
};


FunctionPointer(BOOL, ActualCheckMissionRequirements, (int mission, int character, int level), 0x426AA0);
FunctionPointer(BOOL, ActualCheckSublevelMissionRequirements, (int level, int character, int mission), 0x4282D0);


bool ManualMissionACheck(const int character, const int level)
{
    int time = TimeFrames + 60 * (TimeSeconds + 60 * TimeMinutes);
    switch (character)
    {
    case Characters_Sonic:
        if (sonic_target_times.find(level) != sonic_target_times.end())
            return time <= sonic_target_times.at(level);
        break;
    case Characters_Tails:
        if (tails_target_times.find(level) != tails_target_times.end())
            return time <= tails_target_times.at(level);
        break;
    case Characters_Knuckles:
        if (knuckles_target_times.find(level) != knuckles_target_times.end())
            return time <= knuckles_target_times.at(level);
        break;
    case Characters_Amy:
        if (amy_target_times.find(level) != amy_target_times.end())
            return time <= amy_target_times.at(level);
        break;
    case Characters_Gamma:
        if (gamma_target_times.find(level) != gamma_target_times.end())
            return time > gamma_target_times.at(level);
        break;
    case Characters_Big:
        return BigWeightRecord >= 2000;

    default: return false;
    }
    return false;
}

FunctionHook<void, SaveFileData*, int, signed int, int> OnLevelEmblemCollected(
    0x4B4640, [](SaveFileData* savefile, int character, signed int level, int mission)-> void
    {
        OnLevelEmblemCollected.Original(savefile, character, level, mission);
        eventDetector->OnLevelEmblem(character, level, mission);

        if(!eventDetector->completeMultipleLevelMissions)
            return;
        
        //We check all other missions that were completed
        if (level <= LevelIDs_HotShelter)
        {
            //level - mission B
            if (mission == MISSION_C)
            {
                if (ActualCheckMissionRequirements(MISSION_B, character, level))
                {
                    OnLevelEmblemCollected.Original(savefile, character, level, MISSION_B);
                    eventDetector->OnLevelEmblem(character, level, MISSION_B);
                }
            }

            //level - mission A
            if (mission == MISSION_C || mission == MISSION_B)
            {
                if (ManualMissionACheck(character, level))
                {
                    OnLevelEmblemCollected.Original(savefile, character, level, MISSION_A);
                    eventDetector->OnLevelEmblem(character, level, MISSION_A);
                }
            }
        }
        if (level == LevelIDs_TwinkleCircuit || level == LevelIDs_SandHill)
        {
            //sublevel - mission A
            if (mission == SUB_LEVEL_MISSION_B)
            {
                if (ActualCheckSublevelMissionRequirements(level, character, SUB_LEVEL_MISSION_A))
                {
                    OnLevelEmblemCollected.Original(savefile, character, level, MISSION_A);
                    eventDetector->OnLevelEmblem(character, level, MISSION_A);
                }
            }
        }
    });


//FunctionPointer(void, SetEmblemCollected, (SaveFileData *savefile, signed int index), 0x4B3F30);
FunctionHook<void, SaveFileData*, signed int> OnGenericEmblemCollected(
    0x4B3F30, [](SaveFileData* savefile, signed int index)-> void
    {
        OnGenericEmblemCollected.Original(savefile, index);
        eventDetector->OnGenericEmblem(index);
    });


void EventDetector::OnPlayingFrame() const
{
    if (DemoPlaying > 0)
        return;

    if (GameMode == GameModes_StartCredits && GetEventFlag(EventFlags_SuperSonicAdventureComplete))
        _randomizer.OnGameCompleted();

    //Ignore events given by the mod itself
    if (GameMode != GameModes_Adventure_Field)
        return;

    bool checksFound = false;
    for (const auto& check : _checkData)
    {
        if (check.second.type == LocationUpgrade && !check.second.checked
            && GetEventFlag(static_cast<EventFlags>(check.second.eventFlag)))
        {
            _randomizer.OnCheckFound(check.first);
            checksFound = true;
        }
    }
    if (checksFound)
        _checkData = _randomizer.GetCheckData();
}

void EventDetector::OnLevelEmblem(int character, int level, int mission)
{
    bool checksFound = false;
    for (const auto& check : _checkData)
    {
        if (check.second.type == LocationLevel && !check.second.checked
            && check.second.character == character
            && check.second.level == level
            && check.second.mission == mission)
        {
            _randomizer.OnCheckFound(check.first);
            checksFound = true;
        }
        if (check.second.type == LocationSubLevel && !check.second.checked
            && check.second.level == level
            && check.second.mission == mission)
        {
            _randomizer.OnCheckFound(check.first);
            checksFound = true;
        }
    }
    if (checksFound)
        _checkData = _randomizer.GetCheckData();
}

void EventDetector::OnGenericEmblem(signed int index)
{
    bool checksFound = false;
    for (const auto& check : _checkData)
    {
        if (check.second.type == LocationFieldEmblem && !check.second.checked
            && check.second.emblemId == index)
        {
            _randomizer.OnCheckFound(check.first);
            checksFound = true;
        }
    }
    if (checksFound)
        _checkData = _randomizer.GetCheckData();
}

void EventDetector::SetMultipleMissions(const bool completeMultipleMissions)
{
    this->completeMultipleLevelMissions = completeMultipleMissions;
}


FunctionHook<SEQ_SECTIONTBL*, int> SeqGetSectionListHook(0x44EAF0, [](int playerno)-> SEQ_SECTIONTBL* {
    SEQ_SECTIONTBL* ptr = SeqGetSectionListHook.Original(playerno);
    if (LastStoryFlag == 1 && eventDetector->lastStoryState == LastStoryNotStarted)
    {
        //Start Perfect Chaos fight as soon as we load the story
        ptr->stg = LevelIDs_PerfectChaos;
        ptr->act = 0;
        eventDetector->lastStoryState = LastStoryStarted;
    }
    return ptr;
});


FunctionHook<void, __int16> startLevelCutsceneHook(0x413C90, [](__int16 a1) -> void
{
    if (LastStoryFlag == 1 && eventDetector->lastStoryState == LastStoryStarted)
    {
        //We start the credits as soon as the fight is won
        startLevelCutsceneHook.Original(a1);
        EventFlagArray[EventFlags_SuperSonicAdventureComplete] = 1;
        WriteSaveFile();
        GameState = MD_GAME_FADEOUT_STAFFROLL;
        GameMode = GameModes_StartCredits;
        eventDetector->lastStoryState = LastStoryCompleted;
        return;
    }
    startLevelCutsceneHook.Original(a1);
});

FunctionHook<BOOL> onMissionMenuRenderHook(0x506410, []()-> BOOL
{
    eventDetector->lastStoryState = LastStoryNotStarted;
    return onMissionMenuRenderHook.Original();
});
