#include "Randomizer.h"
#include "SADXModLoader.h"

void Randomizer::OnUpgradeFound(std::string name) const
{
    _displayManager.FoundItem(name);
}

void Randomizer::OnItemReceived(const Upgrades upgrade, std::string name) const
{
    _displayManager.ReceiveItem(name);
    _upgradeManager.GiveUpgrade(upgrade);
}
