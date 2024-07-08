#include "EventDetector.h"
EventDetector* eventDetector;

EventDetector::EventDetector(Randomizer& randomizer) : _randomizer(randomizer)
{
    _checkData = _randomizer.GetCheckData();
    eventDetector = this;
}

static int Combine(const int character, const int level, const int mission)
{
    return (character << 16) | (level << 8) | mission;
}

FunctionHook<void, SaveFileData*, int, signed int, int> OnLevelEmblemCollected(
    0x4B4640, [](SaveFileData* savefile, int character, signed int level, int mission)-> void
    {
        OnLevelEmblemCollected.Original(savefile, character, level, mission);
        eventDetector->OnLevelEmblem(character, level, mission);
    });


void EventDetector::OnPlayingFrame() const
{
    if(DemoPlaying>0)
        return;
    
    if (GameMode == GameModes_StartCredits && GetEventFlag(EventFlags_SuperSonicAdventureComplete))
        _randomizer.OnGameCompleted();

    //Ignore events given by the mod itself
    if (GameMode != GameModes_Adventure_Field)
        return;

    bool checksFound = false;
    for (const auto& check : _checkData)
    {
        if (!check.second.checked && GetEventFlag(static_cast<EventFlags>(check.second.address))
            && (check.second.type == LocationUpgrade || check.second.type == LocationCharacter))
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
        if (!check.second.checked && check.second.type == LocationLevel
            && check.second.address == Combine(character, level, mission))
        {
            _randomizer.OnCheckFound(check.first);
            checksFound = true;
        }
    }
    if (checksFound)
        _checkData = _randomizer.GetCheckData();
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
        GameState = 14;
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
