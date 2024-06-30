#include "UpgradeDetector.h"

#include <iostream>
#include <vector>

#include "SADXModLoader.h"


UpgradeDetector::UpgradeDetector(Randomizer& randomizer) : _randomizer(randomizer)
{
    _upgrades = {
        {"Tails's Jet Anklet", EventFlags_Tails_JetAnklet, Upgrades_JetAnklet, false, false},
        {"Tails's Rhythm Badge", EventFlags_Tails_RhythmBadge, Upgrades_RhythmBadge, false, false},
    };
}


void UpgradeDetector::OnPlayingFrame() const
{
    for (const auto& upgrade : _upgrades)
    {
        if (!upgrade.gotCheck && GetEventFlag(upgrade.eventFlag))
        {
            upgrade.gotCheck = true;
            if (!upgrade.gotUpgrade)
            {
                Current_CharObj2->Upgrades &= ~upgrade.upgradeFlag;
            }

            _randomizer.OnUpgradeFound(upgrade.displayName);
        }
    }
}
