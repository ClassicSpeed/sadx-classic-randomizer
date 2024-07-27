#pragma once
#include "../../pch.h"
#include "../../application/structs/Options.h"
#include "../../application/structs/UnlockStatus.h"

#define RING_LOSS_SOUND_ID 0
#define RING_GAIN_SOUND_ID 7
class CharacterManager
{
public:
    CharacterManager();

    void GiveUpgrade(Upgrades upgrade);
    void RemoveUpgrade(Upgrades upgrade);
    void UpdateOptions(Options newOptions);
    void UpdateUnlockStatus(UnlockStatus unlockStatus);
    void KillPlayer();
    void ProcessRings(Sint16 amount);
    int GetRingDifference();
    Options options;
    UnlockStatus unlockStatus;
    int lastRingAmount;
};
