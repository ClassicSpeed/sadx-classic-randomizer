#include "UpgradeManager.h"

void UpgradeManager::GiveUpgrade(const Upgrades upgrade)
{
     if (Current_CharObj2 != nullptr)
         Current_CharObj2->Upgrades |= upgrade;
}


void UpgradeManager::RemoveUpgrade(const Upgrades upgrade)
{
    if (Current_CharObj2 != nullptr)
        Current_CharObj2->Upgrades &= ~upgrade;
}
