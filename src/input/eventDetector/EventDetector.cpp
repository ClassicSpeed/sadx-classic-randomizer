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
    PrintDebug("Character: %d, Level: %d, Mission: %d\n", character, level, mission);
    bool checksFound = false;
    for (const auto& check : _checkData)
    {
        if (!check.second.checked && check.second.type == LocationLevel
            && check.second.address == Combine(character, level, mission))
        {
            PrintDebug("And we mark it as check");
            _randomizer.OnCheckFound(check.first);
            checksFound = true;
        }
    }
    if (checksFound)
        _checkData = _randomizer.GetCheckData();
}
