#include "CharacterManager.h"
#include "sadx-mod-loader/SADXModLoader/include/UsercallFunctionHandler.h"

CharacterManager* characterManagerPtr;
DataPointer(int, TimerEnabled, 0x912DF0);

UsercallFuncVoid(HudDisplayRings_t, (signed int ringCount, unsigned __int8 digits, NJS_SPRITE* hud),
                 (ringCount, digits, hud), 0x425960, rEAX, rBL, rESI);
static void __cdecl HandleHudDisplayRings(signed int ringCount, unsigned __int8 digits, NJS_SPRITE* hud);
static void __cdecl HandleRingLoss();

void EmptyCall()
{
}

CharacterManager::CharacterManager(Options& options,  Settings& settings, ReactionManager& reactionManager): options(options), settings(settings),
    reactionManager(reactionManager)
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

    //Re-enable timer after finishing a mission
    WriteCall((void*)0x592057, EmptyCall);
    WriteCall((void*)0x592131, EmptyCall);
    WriteCall((void*)0x59219E, EmptyCall);

    //We override the Set0Rings call inside the HurtPlayer function;
    WriteCall(reinterpret_cast<void*>(0x45072D), &HandleRingLoss);

    HudDisplayRings_t.Hook(HandleHudDisplayRings);
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
    case OneHitKnockOutNoShields:
        Set0Rings();
        KillHimP(0);
        break;
    }
    characterManagerPtr->lastRingAmount = lastRingAmountBuffer;
}

FunctionHook<void, char> onGiveBarrier(0x441EA0, [](const char character)-> void
{
    if (characterManagerPtr->options.ringLoss == OneHitKnockOutNoShields)
        return;
    onGiveBarrier.Original(character);
});

FunctionHook<void, char> onGiveMagneticBarrier(0x441E30, [](const char character)-> void
{
    if (characterManagerPtr->options.ringLoss == OneHitKnockOutNoShields)
        return;
    onGiveMagneticBarrier.Original(character);
});

FunctionHook<void, char> onGiveInvincibility(0x441F10, [](const char character)-> void
{
    if (characterManagerPtr->options.ringLoss == OneHitKnockOutNoShields)
        return;
    onGiveInvincibility.Original(character);
});

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
    if (GameMode != GameModes_Mission && GameMode != GameModes_Adventure_Field)
        return;
    if (CurrentLevel == LevelIDs_PerfectChaos && !options.hardRingLinkActive)
        return;
    if (!options.casinopolisRingLink && CurrentLevel == LevelIDs_Casinopolis && CurrentCharacter == Characters_Sonic)
        return;
    if (GameState != MD_GAME_MAIN)
        return;
    if (amount == 0)
        return;
    if (Current_CharObj2 == nullptr || EntityData1Ptrs[0] == nullptr)
        return;

    if (amount < 0 && Rings > 0)
    {
        const Sint16 newRingAmount = max(Rings + amount, 0);
        PlaySound(RING_LOSS_SOUND_ID, nullptr, 0, nullptr);
        Rings = newRingAmount;
    }

    const int maxRings = settings.extendRingCapacity ? 99999 : 999;

    if (amount > 0 && Rings < maxRings)
    {
        AddRings(amount);
        PlaySound(RING_GAIN_SOUND_ID, nullptr, 0, nullptr);
    }

    lastRingAmount = Rings;
}

RingDifference CharacterManager::GetRingDifference()
{
    RingDifference ringDifference = {0, 0};
    if (GameMode != GameModes_Mission && GameMode != GameModes_Adventure_Field && GameMode !=
        GameModes_Adventure_ActionStg)
        return {0, 0};

    if (CurrentLevel == LevelIDs_PerfectChaos)
    {
        if (!options.hardRingLinkActive)
            return {0, 0};
        ringDifference.hardRingDifference = Rings - lastRingAmount;
        lastRingAmount = Rings;
        return ringDifference;
    }

    if (GameMode == GameModes_Mission && TimerEnabled == 0
        && CurrentLevel >= LevelIDs_EmeraldCoast && CurrentLevel <= LevelIDs_HotShelter)
    {
        if (!options.hardRingLinkActive)
        {
            lastRingAmount = Rings;
            return {0, 0};
        }
        ringDifference.hardRingDifference = Rings - lastRingAmount;
        lastRingAmount = Rings;
        return ringDifference;
    }

    if (!options.casinopolisRingLink && CurrentLevel == LevelIDs_Casinopolis && CurrentCharacter == Characters_Sonic)
        return {0, 0};


    ringDifference.ringDifference = Rings - lastRingAmount;
    lastRingAmount = Rings;
    return ringDifference;
}

void CharacterManager::GiveFillerItem(const FillerType filler, const bool priority)
{
    if (priority)
        _remainingFiller.push_front(filler);
    else
        _remainingFiller.push_back(filler);
}

void CharacterManager::OnFrame()
{
    
    if (Current_CharObj2 == nullptr || EntityData1Ptrs[0] == nullptr)
        return;
    if (_fillerTimer > 0)
    {
        const double timePassed = (std::clock() - this->_fillerTimer) / static_cast<double>(CLOCKS_PER_SEC);
        if (timePassed > _fillerDuration)
        {
            _fillerTimer = -1;
            EnablePause();
        }
    }

    if (options.lazyFishing && unlockStatus.bigPowerRodUnlocked)
        RodTension = 0;

    if (GameMode != GameModes_Mission && GameMode != GameModes_Adventure_Field)
        return;
    if (CurrentLevel == LevelIDs_TwinkleCircuit || CurrentLevel == LevelIDs_SkyChase1
        || CurrentLevel == LevelIDs_SkyChase2)
        return;

    if (CurrentLevel >= LevelIDs_Chaos0 && CurrentLevel <= LevelIDs_E101R && !options.trapsOnBossFights)
        return;

    if (CurrentLevel == LevelIDs_PerfectChaos && !options.trapsOnPerfectChaosFight)
        return;

    if (CurrentLevel >= LevelIDs_StationSquare && CurrentLevel <= LevelIDs_Past && !options.trapsOnAdventureFields)
        return;

    if (CurrentLevel >= LevelIDs_SSGarden && CurrentLevel <= LevelIDs_ChaoRace && !options.trapsOnAdventureFields)
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
    if (_gravityTimer > 0)
    {
        const double timePassed = (std::clock() - this->_gravityTimer) / static_cast<double>(CLOCKS_PER_SEC);
        if (timePassed > _gravityDuration)
        {
            Gravity.y = -1;
            _gravityTimer = -1;
        }
    }

    if (_reverseControlsTimer > 0 && options.reverseControlsDuration > 0)
    {
        const double timePassed = (std::clock() - this->_reverseControlsTimer) / static_cast<double>(CLOCKS_PER_SEC);
        if (timePassed > options.reverseControlsDuration)
        {
            reverseControlsEnabled = false;
            _reverseControlsTimer = -1;
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

    if (_remainingFiller.empty() || _fillerTimer > 0)
        return;


    ActivateFiller(_remainingFiller.front());
    _remainingFiller.pop_front();
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


void CharacterManager::RemoveStatusEffects()
{
    reverseControlsEnabled = false;
    _reverseControlsTimer = -1;
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
        GiveLives(1);
        if (GetCurrentCharacterID() == Characters_Gamma)
        {
            PlaySound(1306, 0, 0, 0);
        }
        PlaySound(11, 0, 0, 0);
        break;
    case IceTrap:
        this->FreezePlayer();
        DisablePause();
        reactionManager.PlayRandomTrapVoice(filler);
        break;
    case SpringTrap:
        this->SpawnSpring();
        DisablePause();
        reactionManager.PlayRandomTrapVoice(filler);
        break;
    case PoliceTrap:
        this->SpawnEnemies(EnemyPolice);
        DisablePause();
        reactionManager.PlayRandomTrapVoice(filler);
        break;
    case BuyonTrap:
        this->SpawnEnemies(EBuyon_Main);
        DisablePause();
        reactionManager.PlayRandomTrapVoice(filler);
        break;

    case ReverseTrap:
        this->ReverseControls();
        DisablePause();
        reactionManager.PlayRandomTrapVoice(filler);
        break;

    case GravityTrap:
        this->IncrementGravity();
        DisablePause();
        reactionManager.PlayRandomTrapVoice(filler);
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
    NullifyVelocity(EntityData2Ptrs[0], Current_CharObj2);
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
    if (CurrentLevel == LevelIDs_PerfectChaos)
    {
        AddRings(-5);
        return;
    }

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
    if (CurrentLevel != LevelIDs_PerfectChaos)
        if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Knuckles)
            return ForcePlayerAction(0, PL_OP_ICED);

    freezePLayer(EntityData1Ptrs[0]->CharIndex);
    Current_CharObj2->field_88.x = 300;
    NullifyVelocity(EntityData2Ptrs[0], Current_CharObj2);
    DisableController(0);
}

void CharacterManager::IncrementGravity()
{
    _gravityTimer = std::clock();
    Gravity.y = Gravity.y * 4;
}

void CharacterManager::ReverseControls()
{
    //If the player is already under the effect of reverse controls, set them back to normal
    if (reverseControlsEnabled)
    {
        reverseControlsEnabled = false;
        _reverseControlsTimer = -1;
    }

    if (options.reverseControlsDuration > 0)
        _reverseControlsTimer = std::clock();
    reverseControlsEnabled = true;
}


FunctionHook<void> onWriteAnalogs(0x40F170, []()-> void
{
    if (characterManagerPtr->reverseControlsEnabled)
    {
        ControllerPointers[0]->LeftStickX = -ControllerPointers[0]->LeftStickX;
        ControllerPointers[0]->LeftStickY = -ControllerPointers[0]->LeftStickY;
        ControllerPointers[0]->RightStickX = -ControllerPointers[0]->RightStickX;
        ControllerPointers[0]->RightStickY = -ControllerPointers[0]->RightStickY;
    }
    onWriteAnalogs.Original();
});


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

void HandleHudDisplayRings(const signed int ringCount, unsigned char digits, NJS_SPRITE* hud)
{
    if (characterManagerPtr->settings.extendRingCapacity)
        HudDisplayRings_t.Original(ringCount, 5, hud);
    else
        HudDisplayRings_t.Original(ringCount, digits, hud);
}

// For big, we extend the ring capacity to 99999 if enabled
FunctionHook<void, _SC_NUMBERS*> onDrawSNumbers(0x427BB0, [](_SC_NUMBERS* pscn)-> void
{
    if (characterManagerPtr->settings.extendRingCapacity && CurrentCharacter == Characters_Big && pscn->max == 999)
        pscn->max = 99999;
    onDrawSNumbers.Original(pscn);
});
