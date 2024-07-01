#include "UpgradeManager.h"

void UpgradeManager::GiveUpgrade(const Upgrades upgrade)
{
    Current_CharObj2->Upgrades |= upgrade;
}


void UpgradeManager::RemoveUpgrade(const Upgrades upgrade)
{
    Current_CharObj2->Upgrades &= ~upgrade;
}