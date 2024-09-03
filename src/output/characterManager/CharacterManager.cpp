#include "CharacterManager.h"

CharacterManager* characterManagerPtr;


CharacterManager::CharacterManager()
{
    characterManagerPtr = this;
    //Re-enable control after graving an emblem
    WriteCall((void*)0x4B4891, EnableControl);
    WriteCall((void*)0x4B46C5, EnableControl);


    //Re-enable control after graving a mission card
    WriteCall((void*)0x595BFD, EnableControl);
    WriteCall((void*)0x595C53, EnableControl);
    WriteCall((void*)0x595C5D, EnableControl);

    //Re-enable control after finishing a mission
    WriteCall((void*)0x592094, EnableControl);
    WriteCall((void*)0x5920CA, EnableControl);

    //Re-enable pause after finishing a mission
    WriteCall((void*)0x592048, EnablePause);
    WriteCall((void*)0x5920AF, EnablePause);
}

void CharacterManager::GiveUpgrade(const Upgrades upgrade)
{
    if (GameMode != GameModes_Mission && GameMode != GameModes_Menu)
        return;
    if (CurrentLevel == LevelIDs_SkyChase1 || CurrentLevel == LevelIDs_SkyChase2)
        return;
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
    if (GameMode != GameModes_Mission && GameMode != GameModes_Menu)
        return;
    if (CurrentLevel == LevelIDs_SkyChase1 || CurrentLevel == LevelIDs_SkyChase2)
        return;
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
    if (GameMode != GameModes_Mission)
        return;
    if (CurrentLevel == LevelIDs_PerfectChaos && !options.hardRingLinkActive)
        return;
    if (!options.casinopolisRingLink && CurrentLevel == LevelIDs_Casinopolis && CurrentCharacter == Characters_Sonic)
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
    if (GameMode != GameModes_Mission)
        return lastRingAmount = 0;
    if (CurrentLevel == LevelIDs_PerfectChaos && !options.hardRingLinkActive)
        return lastRingAmount = 0;
    if (GameMode == GameModes_Mission && TimeThing == 0 && !options.hardRingLinkActive)
        return lastRingAmount = 0;
    if (!options.casinopolisRingLink && CurrentLevel == LevelIDs_Casinopolis && CurrentCharacter == Characters_Sonic)
        return lastRingAmount = 0;

    const int ringDifference = Rings - lastRingAmount;
    lastRingAmount = Rings;
    return ringDifference;
}

void CharacterManager::GiveFillerItem(const FillerType filler)
{
    _remainingFiller.push(filler);
}

void CharacterManager::OnPlayingFrame()
{
    if (GameMode != GameModes_Mission)
        return;
    if (CurrentLevel == LevelIDs_PerfectChaos || CurrentLevel == LevelIDs_TwinkleCircuit
        || CurrentLevel == LevelIDs_SkyChase1 || CurrentLevel == LevelIDs_SkyChase2)
        return;
    if (GameState != MD_GAME_MAIN || !EntityData1Ptrs[0])
        return;
    if (PauseEnabled == 0)
        return;

    if (_freezeTimer > 0)
    {
        const double timePassed = (std::clock() - this->_freezeTimer) / static_cast<double>(CLOCKS_PER_SEC);
        if (timePassed > _freezeDuration)
        {
            EnableController(0);
            _freezeTimer = -1;
        }
    }


    if (_springTimer > 0)
    {
        const double timePassed = (std::clock() - this->_springTimer) / static_cast<double>(CLOCKS_PER_SEC);
        if (timePassed > _springDuration)
        {
            FreeTask(_springTask);
            _springTask = nullptr;
            _springTimer = -1;
        }
    }

    if (_fillerTimer > 0)
    {
        const double timePassed = (std::clock() - this->_fillerTimer) / static_cast<double>(CLOCKS_PER_SEC);
        if (timePassed > _fillerDuration)
        {
            _fillerTimer = -1;
        }
    }

    if (_remainingFiller.empty() || _fillerTimer > 0)
        return;


    ActivateFiller(_remainingFiller.front());
    _remainingFiller.pop();
    _fillerTimer = std::clock();
}

void CharacterManager::SetStartingCharacter(int startingCharacterIndex)
{
    if (GameMode != GameModes_Menu)
        return;
    if (startingCharacterIndex == 1)
    {
        BYTE1(CharacterSelection) = 0;
        CurrentCharacter = Characters_Sonic;
    }
    else if (startingCharacterIndex == 2)
    {
        BYTE1(CharacterSelection) = 1;
        CurrentCharacter = Characters_Tails;
    }
    else if (startingCharacterIndex == 3)
    {
        BYTE1(CharacterSelection) = 2;
        CurrentCharacter = Characters_Knuckles;
    }
    else if (startingCharacterIndex == 4)
    {
        BYTE1(CharacterSelection) = 3;
        CurrentCharacter = Characters_Amy;
    }
    else if (startingCharacterIndex == 5)
    {
        BYTE1(CharacterSelection) = 4;
        CurrentCharacter = Characters_Big;
    }
    else if (startingCharacterIndex == 6)
    {
        BYTE1(CharacterSelection) = 5;
        CurrentCharacter = Characters_Gamma;
    }
}

TaskFunc(EBuyon_Main, 0x7B2E00);

void CharacterManager::ActivateFiller(const FillerType filler)
{
    switch (filler)
    {
    case Invincibility:
        InvincibilityPowerup(EntityData1Ptrs[0]);
        break;
    case FiveRings:
        FiveRingsPowerup(EntityData1Ptrs[0]);
        break;
    case TenRings:
        TenRingsPowerup(EntityData1Ptrs[0]);
        break;
    case Shield:
        BarrierPowerup(EntityData1Ptrs[0]);
        break;
    case MagneticShield:
        MagneticBarrierPowerup(EntityData1Ptrs[0]);
        break;
    case ExtraLife:
        ExtraLifePowerup(EntityData1Ptrs[0]);
        break;
    case IceTrap:
        this->FreezePlayer();
        PlayVoice(174);
        break;
    case SpringTrap:
        this->SpawnSpring();
        PlayVoice(174);
        break;
    case PoliceTrap:
        this->SpawnEnemies(EnemyPolice);
        PlayVoice(174);
        break;
    case BuyonTrap:
        this->SpawnEnemies(EBuyon_Main);
        PlayVoice(174);
        break;

    case NoFiller:
        break;
    default: ;
    }
}


FunctionHook<int> getLureQuantity(0x46C870, []()-> int
{
    return characterManagerPtr->unlockStatus.bigLureQuantity;
});

void CharacterManager::SpawnSpring()
{
    _springTimer = std::clock();
    _springTask = CreateElementalTask(LoadObj_Data1, 3, ObjectSpringB);
    _springTask->twp->pos.x = EntityData1Ptrs[0]->Position.x;
    _springTask->twp->pos.y = EntityData1Ptrs[0]->Position.y + 5;
    _springTask->twp->pos.z = EntityData1Ptrs[0]->Position.z;

    _springTask->twp->ang.x = 0x10000 - EntityData1Ptrs[0]->Rotation.y;
    _springTask->twp->ang.z = 0x5000;

    _springTask->twp->scl.x = 5;
    _springTask->twp->scl.y = 6;
    _springTask->twp->scl.z = 1;
}


void CharacterManager::SpawnEnemies(void (*enemyFunc)(task* tp))
{
    const auto enemy = CreateElementalTask(LoadObj_Data1, 3, enemyFunc);
    enemy->twp->pos.x = EntityData1Ptrs[0]->Position.x + 30;
    enemy->twp->pos.y = EntityData1Ptrs[0]->Position.y;
    enemy->twp->pos.z = EntityData1Ptrs[0]->Position.z + 30;
    enemy->thp = 0;
    enemy->ocp = new OBJ_CONDITION;

    const auto enemy2 = CreateElementalTask(LoadObj_Data1, 3, enemyFunc);
    enemy2->twp->pos.x = EntityData1Ptrs[0]->Position.x + 30;
    enemy2->twp->pos.y = EntityData1Ptrs[0]->Position.y;
    enemy2->twp->pos.z = EntityData1Ptrs[0]->Position.z - 30;
    enemy2->thp = 0;
    enemy2->ocp = new OBJ_CONDITION;


    const auto enemy3 = CreateElementalTask(LoadObj_Data1, 3, enemyFunc);
    enemy3->twp->pos.x = EntityData1Ptrs[0]->Position.x - 30;
    enemy3->twp->pos.y = EntityData1Ptrs[0]->Position.y;
    enemy3->twp->pos.z = EntityData1Ptrs[0]->Position.z + 30;
    enemy3->thp = 0;
    enemy3->ocp = new OBJ_CONDITION;


    const auto enemy4 = CreateElementalTask(LoadObj_Data1, 3, enemyFunc);
    enemy4->twp->pos.x = EntityData1Ptrs[0]->Position.x - 30;
    enemy4->twp->pos.y = EntityData1Ptrs[0]->Position.y;
    enemy4->twp->pos.z = EntityData1Ptrs[0]->Position.z - 30;
    enemy4->thp = 0;
    enemy4->ocp = new OBJ_CONDITION;


    const auto enemy5 = CreateElementalTask(LoadObj_Data1, 3, enemyFunc);
    enemy5->twp->pos.x = EntityData1Ptrs[0]->Position.x + 30;
    enemy5->twp->pos.y = EntityData1Ptrs[0]->Position.y;
    enemy5->twp->pos.z = EntityData1Ptrs[0]->Position.z;
    enemy5->thp = 0;
    enemy5->ocp = new OBJ_CONDITION;


    const auto enemy6 = CreateElementalTask(LoadObj_Data1, 3, enemyFunc);
    enemy6->twp->pos.x = EntityData1Ptrs[0]->Position.x;
    enemy6->twp->pos.y = EntityData1Ptrs[0]->Position.y;
    enemy6->twp->pos.z = EntityData1Ptrs[0]->Position.z + 30;
    enemy6->thp = 0;
    enemy6->ocp = new OBJ_CONDITION;


    const auto enemy7 = CreateElementalTask(LoadObj_Data1, 3, enemyFunc);
    enemy7->twp->pos.x = EntityData1Ptrs[0]->Position.x - 30;
    enemy7->twp->pos.y = EntityData1Ptrs[0]->Position.y;
    enemy7->twp->pos.z = EntityData1Ptrs[0]->Position.z;
    enemy7->thp = 0;
    enemy7->ocp = new OBJ_CONDITION;


    const auto enemy8 = CreateElementalTask(LoadObj_Data1, 3, enemyFunc);
    enemy8->twp->pos.x = EntityData1Ptrs[0]->Position.x;
    enemy8->twp->pos.y = EntityData1Ptrs[0]->Position.y;
    enemy8->twp->pos.z = EntityData1Ptrs[0]->Position.z - 30;
    enemy8->thp = 0;

    enemy8->ocp = new OBJ_CONDITION;
}

FunctionPointer(ObjectMaster *, freezePLayer, (char a1), 0x4A2550);

void CharacterManager::FreezePlayer()
{
    _freezeTimer = std::clock();
    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Knuckles)
        return ForcePlayerAction(0, PL_OP_ICED);

    freezePLayer(EntityData1Ptrs[0]->CharIndex);
    Current_CharObj2->field_88.x = 300;
    NullifyVelocity(EntityData2Ptrs[0], Current_CharObj2);
    DisableController(0);
}


//We scale up the freeze trap for Big and Gamma
FunctionHook<void, task*> freezeTrapDisplay(0x4A2240, [](task* tp)-> void
{
    if (CurrentCharacter == Characters_Big || CurrentCharacter == Characters_Gamma)
    {
        tp->twp->scl.x = 3;
        tp->twp->scl.y = 3;
        tp->twp->scl.z = 3;
    }
    freezeTrapDisplay.Original(tp);
});

// We temporally set the game mode to trick the result screen into showing its full version
FunctionHook<void, task*> onScoreDisplay_Main(0x42BCC0, [](task* tp)-> void
{
    //If Tails just lost, we don't do anything
    if (CurrentCharacter == Characters_Tails && RaceWinnerPlayer == 2)
        return onScoreDisplay_Main.Original(tp);

    const GameModes bufferGameMode = GameMode;
    GameMode = GameModes_Adventure_ActionStg;
    onScoreDisplay_Main.Original(tp);
    GameMode = bufferGameMode;
});
