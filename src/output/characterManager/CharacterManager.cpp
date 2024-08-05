#include "CharacterManager.h"

CharacterManager* characterManagerPtr;


CharacterManager::CharacterManager()
{
    characterManagerPtr = this;
    //Re-enable control after graving an emblem
    WriteCall((void*)0x4B4891, EnableControl);
    WriteCall((void*)0x4B46C5, EnableControl);
}

void CharacterManager::GiveUpgrade(const Upgrades upgrade)
{
    if (Current_CharObj2 != nullptr)
        Current_CharObj2->Upgrades |= upgrade;
    if (CharObj2Ptrs != nullptr)
    {
        for (const auto& character : CharObj2Ptrs)
        {
            if (character != nullptr)
                character->Upgrades |= upgrade;
        }
    }
}


void CharacterManager::RemoveUpgrade(const Upgrades upgrade)
{
    if (Current_CharObj2 != nullptr)
        Current_CharObj2->Upgrades &= ~upgrade;

    for (const auto& character : CharObj2Ptrs)
    {
        if (character != nullptr)
            character->Upgrades &= ~upgrade;
    }
}

//We don't send ring updates when set to zero
FunctionHook<void> onSet0Rings(0x425AB0, []()-> void
{
    onSet0Rings.Original();
    characterManagerPtr->lastRingAmount = Rings;
});


static void __cdecl HandleRingLoss()
{
    //We preserve the last ring amount when the player is hurt
    //In practice, every set0ring call won't be synced except for this one
    const int lastRingAmountBuffer = characterManagerPtr->lastRingAmount;
    switch (characterManagerPtr->options.ringLoss)
    {
    case Classic:
        Set0Rings();
        break;
    case Modern:
        if (Rings > 20)
            Rings -= 20;
        else
            Set0Rings();
        break;
    case OneHitKnockOut:
        Set0Rings();
        KillHimP(0);
        break;
    }
    characterManagerPtr->lastRingAmount = lastRingAmountBuffer;
}

void CharacterManager::UpdateOptions(const Options newOptions)
{
    this->options = newOptions;
    //We override the Set0Rings call inside the HurtPlayer function;
    WriteCall(reinterpret_cast<void*>(0x45072D), &HandleRingLoss);
}

void CharacterManager::UpdateUnlockStatus(const UnlockStatus newUnlockStatus)
{
    this->unlockStatus = newUnlockStatus;
}

void CharacterManager::KillPlayer()
{
    KillHimP(0);
}

void CharacterManager::ProcessRings(const Sint16 amount)
{
    if (GameMode != GameModes_Adventure_Field && GameMode != GameModes_Adventure_ActionStg)
        return;
    if (CurrentLevel == LevelIDs_PerfectChaos && !options.hardRingLinkActive)
        return;
    if (GameState != MD_GAME_MAIN)
        return;
    if (amount == 0)
        return;

    if (amount < 0 && Rings > 0)
    {
        const Sint16 newRingAmount = max(Rings + amount, 0);
        PlaySound(RING_LOSS_SOUND_ID, nullptr, 0, nullptr);
        Rings = newRingAmount;
    }

    if (amount > 0 && Rings < 999)
    {
        AddRings(amount);
        PlaySound(RING_GAIN_SOUND_ID, nullptr, 0, nullptr);
    }

    lastRingAmount = Rings;
}

int CharacterManager::GetRingDifference()
{
    if (GameMode != GameModes_Adventure_Field && GameMode != GameModes_Adventure_ActionStg)
        return lastRingAmount = 0;
    if (CurrentLevel == LevelIDs_PerfectChaos && !options.hardRingLinkActive)
        return lastRingAmount = 0;
    if (GameMode == GameModes_Adventure_ActionStg && TimeThing == 0 && !options.hardRingLinkActive)
        return lastRingAmount = 0;


    const int ringDifference = Rings - lastRingAmount;
    lastRingAmount = Rings;
    return ringDifference;
}


FunctionHook<int> getLureQuantity(0x46C870, []()-> int
{
    return characterManagerPtr->unlockStatus.bigLureQuantity;
});
