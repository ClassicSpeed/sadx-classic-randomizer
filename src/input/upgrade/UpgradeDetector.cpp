#include "UpgradeDetector.h"

#include "SADXModLoader.h"


UpgradeDetector::UpgradeDetector(Randomizer& randomizer) : _randomizer(randomizer)
{
    _checkData = _randomizer.GetCheckData();
}


void UpgradeDetector::OnPlayingFrame() const
{
    bool checksFound = false;
    for (const auto& check : _checkData)
    {
        if (!check.second.checked && GetEventFlag(check.second.eventFlag))
        {
            _randomizer.OnUpgradeFound(check.first);
            checksFound = true;
        }
    }
    if (checksFound)
        _checkData = _randomizer.GetCheckData();
}
