#include "UpgradeManager.h"

void UpgradeManager::GiveUpgrade(const Upgrades upgrade)
{
    Current_CharObj2->Upgrades |= upgrade;
}
