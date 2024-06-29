#pragma once
#include <string>
#include "SADXModLoader.h"
#include "../output/game/displayManager/DisplayManager.h"
#include "../output/game/UpgradeManager/UpgradeManager.h"

class Randomizer
{
public:
    Randomizer(DisplayManager& displayManager, UpgradeManager& upgradeManager)
        : _displayManager(displayManager),
          _upgradeManager(upgradeManager)
    {
    }

    void OnUpgradeFound(std::string name) const;
    void OnItemReceived(Upgrades upgrade, std::string name) const;

private:
    DisplayManager& _displayManager;
    UpgradeManager& _upgradeManager;
};
