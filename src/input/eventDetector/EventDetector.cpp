#include "EventDetector.h"


EventDetector::EventDetector(Randomizer& randomizer) : _randomizer(randomizer)
{
    _checkData = _randomizer.GetCheckData();
}


void EventDetector::OnPlayingFrame() const
{
    if (GameMode == GameModes_StartCredits && GetEventFlag(EventFlags_SuperSonicAdventureComplete))
    {
        _randomizer.OnGameCompleted();
    }
    //Ignore events given by the mod itself
    if (GameMode != GameModes_Adventure_Field)
        return;


    bool checksFound = false;
    for (const auto& check : _checkData)
    {
        if (!check.second.checked && GetEventFlag(check.second.eventFlag))
        {
            _randomizer.OnCheckFound(check.first);
            checksFound = true;
        }
    }
    if (checksFound)
        _checkData = _randomizer.GetCheckData();
}
