#include "EventDetector.h"

#include "SADXModLoader.h"


EventDetector::EventDetector(Randomizer& randomizer) : _randomizer(randomizer)
{
    _checkData = _randomizer.GetCheckData();
}


void EventDetector::OnPlayingFrame() const
{
    if(GameMode == GameModes_CharSel)
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
