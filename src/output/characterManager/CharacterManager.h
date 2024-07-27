#pragma once
#include "../../pch.h"
#include "../../application/structs/Options.h"
#include "../../application/structs/UnlockStatus.h"

class CharacterManager
{
public:
    CharacterManager();

    void GiveUpgrade(Upgrades upgrade);
    void RemoveUpgrade(Upgrades upgrade);
    void UpdateOptions(Options newOptions);
    void UpdateUnlockStatus(UnlockStatus unlockStatus);
    Options options;
    UnlockStatus unlockStatus;
};
