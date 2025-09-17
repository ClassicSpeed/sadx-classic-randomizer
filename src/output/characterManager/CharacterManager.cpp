#include "CharacterManager.h"

DataPointer(int, TimerEnabled, 0x912DF0);

CharacterManager::__hudDisplayRingsHook_t CharacterManager::_hudDisplayRingsHook;

CharacterManager::CharacterManager(Options& options, Settings& settings, GameStatus& gameStatus,
                                   ReactionManager& reactionManager) : _options(options), _settings(settings),
                                                                       _gameStatus(gameStatus),
                                                                       _reactionManager(reactionManager)
{
    _set0RingsHook.Hook(OnSet0Rings);
    _giveBarrierHook.Hook(OnGiveBarrier);
    _giveMagneticBarrierHook.Hook(OnGiveMagneticBarrier);
    _giveInvincibilityHook.Hook(OnGiveInvincibility);
    _getLureQuantityHook.Hook(OnGetLureQuantity);
    _writeAnalogsHook.Hook(OnWriteAnalogs);
    _freezeTrapDisplayHook.Hook(OnFreezeTrapDisplay);
    _scoreDisplayMainHook.Hook(OnScoreDisplayMain);
    _drawSNumbersHook.Hook(OnDrawSNumbers);
    _hudDisplayRingsHook.Hook(HandleHudDisplayRings);
    _createAnimalHook.Hook(OnCreateAnimal);

    //We override the Set0Rings call inside the HurtPlayer function;
    WriteCall(reinterpret_cast<void*>(0x45072D), (void*)HandleRingLoss);


    //Re-enable control after graving an emblem
    WriteCall((void*)0x4B4891, (void*)EnableControl);
    WriteCall((void*)0x4B46C5, (void*)EnableControl);


    //Re-enable control after graving a mission card
    WriteCall((void*)0x595BFD, (void*)EnableControl);
    WriteCall((void*)0x595C53, (void*)EnableControl);
    WriteCall((void*)0x595C5D, (void*)EnableControl);

    //Re-enable control after finishing a mission
    WriteCall((void*)0x592094, (void*)EnableControl);
    WriteCall((void*)0x5920CA, (void*)EnableControl);

    //Re-enable pause after finishing a mission
    WriteCall((void*)0x592048, (void*)EnablePause);
    WriteCall((void*)0x5920AF, (void*)EnablePause);

    //Re-enable timer after finishing a mission
    WriteCall((void*)0x592057, (void*)EmptyCall);
    WriteCall((void*)0x592131, (void*)EmptyCall);
    WriteCall((void*)0x59219E, (void*)EmptyCall);


    //Re-enable control inside of Sky Deck Cannon
    WriteCall((void*)0x5FC81B, (void*)EnablePause);
    WriteCall((void*)0x5FC8B0, (void*)EnablePause);
    WriteCall((void*)0x5FC8FE, (void*)EnablePause);
    WriteCall((void*)0x5FC9A2, (void*)EnablePause);
    WriteCall((void*)0x5FCA36, (void*)EnablePause);


    _hudDisplayRingsHook.Hook(HandleHudDisplayRings);
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
void CharacterManager::OnSet0Rings()
{
    _set0RingsHook.Original();
    _instance->_lastRingAmount = Rings;
}


void CharacterManager::HandleRingLoss()
{
    //We preserve the last ring amount when the player is hurt
    //In practice, every set0ring call won't be synced except for this one
    const int lastRingAmountBuffer = _instance->_lastRingAmount;
    switch (_instance->_options.ringLoss)
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
    _instance->_lastRingAmount = lastRingAmountBuffer;
}


void CharacterManager::OnGiveBarrier(const char character)
{
    if (_instance->_options.ringLoss == OneHitKnockOutNoShields)
        return;
    _giveBarrierHook.Original(character);
}

void CharacterManager::OnGiveMagneticBarrier(const char character)
{
    if (_instance->_options.ringLoss == OneHitKnockOutNoShields)
        return;
    _giveMagneticBarrierHook.Original(character);
}

void CharacterManager::OnGiveInvincibility(const char character)
{
    if (_instance->_options.ringLoss == OneHitKnockOutNoShields)
        return;
    _giveInvincibilityHook.Original(character);
}


void CharacterManager::KillPlayer()
{
    KillHimP(0);
}

void CharacterManager::ProcessRings(const Sint16 amount)
{
    if (GameMode != GameModes_Mission && GameMode != GameModes_Adventure_Field)
        return;
    if (CurrentLevel == LevelIDs_PerfectChaos && !_options.hardRingLinkActive)
        return;
    if (!_options.casinopolisRingLink && CurrentLevel == LevelIDs_Casinopolis && CurrentCharacter == Characters_Sonic)
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

    const int maxRings = _settings.extendRingCapacity ? 99999 : 999;

    if (amount > 0 && Rings < maxRings)
    {
        AddRings(amount);
        PlaySound(RING_GAIN_SOUND_ID, nullptr, 0, nullptr);
    }

    _lastRingAmount = Rings;
}

RingDifference CharacterManager::GetRingDifference()
{
    RingDifference ringDifference = {0, 0};
    if (GameMode != GameModes_Mission && GameMode != GameModes_Adventure_Field && GameMode !=
        GameModes_Adventure_ActionStg)
        return {0, 0};

    if (CurrentLevel == LevelIDs_PerfectChaos)
    {
        if (!_options.hardRingLinkActive)
            return {0, 0};
        ringDifference.hardRingDifference = Rings - _lastRingAmount;
        _lastRingAmount = Rings;
        return ringDifference;
    }

    if (GameMode == GameModes_Mission && TimerEnabled == 0
        && CurrentLevel >= LevelIDs_EmeraldCoast && CurrentLevel <= LevelIDs_E101R)
    {
        if (!_options.hardRingLinkActive)
        {
            _lastRingAmount = Rings;
            return {0, 0};
        }
        ringDifference.hardRingDifference = Rings - _lastRingAmount;
        _lastRingAmount = Rings;
        return ringDifference;
    }

    if (!_options.casinopolisRingLink && CurrentLevel == LevelIDs_Casinopolis && CurrentCharacter == Characters_Sonic)
        return {0, 0};


    ringDifference.ringDifference = Rings - _lastRingAmount;
    _lastRingAmount = Rings;
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

    if (_options.lazyFishing && _gameStatus.unlock.bigPowerRodUnlocked)
        RodTension = 0;

    if (GameMode != GameModes_Mission && GameMode != GameModes_Adventure_Field)
        return;
    if (CurrentLevel == LevelIDs_TwinkleCircuit || CurrentLevel == LevelIDs_SkyChase1
        || CurrentLevel == LevelIDs_SkyChase2)
        return;

    if (CurrentLevel >= LevelIDs_Chaos0 && CurrentLevel <= LevelIDs_E101R && !_options.trapsOnBossFights)
        return;

    if (CurrentLevel == LevelIDs_PerfectChaos && !_options.trapsOnPerfectChaosFight)
        return;

    if (CurrentLevel >= LevelIDs_StationSquare && CurrentLevel <= LevelIDs_Past && !_options.trapsOnAdventureFields)
        return;

    if (CurrentLevel >= LevelIDs_SSGarden && CurrentLevel <= LevelIDs_ChaoRace && !_options.trapsOnAdventureFields)
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

    if (_reverseControlsTimer > 0 && _options.reverseControlsDuration > 0)
    {
        const double timePassed = (std::clock() - this->_reverseControlsTimer) / static_cast<double>(CLOCKS_PER_SEC);
        if (timePassed > _options.reverseControlsDuration)
        {
            _reverseControlsEnabled = false;
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
    _reverseControlsEnabled = false;
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
        _reactionManager.PlayRandomTrapVoice(filler);
        break;
    case SpringTrap:
        this->SpawnSpring();
        DisablePause();
        _reactionManager.PlayRandomTrapVoice(filler);
        break;
    case PoliceTrap:
        this->SpawnEnemies(EnemyPolice);
        DisablePause();
        _reactionManager.PlayRandomTrapVoice(filler);
        break;
    case BuyonTrap:
        this->SpawnEnemies(EBuyon_Main);
        DisablePause();
        _reactionManager.PlayRandomTrapVoice(filler);
        break;

    case ReverseTrap:
        this->ReverseControls();
        DisablePause();
        _reactionManager.PlayRandomTrapVoice(filler);
        break;

    case GravityTrap:
        this->IncrementGravity();
        DisablePause();
        _reactionManager.PlayRandomTrapVoice(filler);
        break;

    case NoFiller:
        break;
    default: ;
    }
}

int CharacterManager::OnGetLureQuantity()
{
    return _instance->_gameStatus.unlock.bigLureQuantity;
}

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
    if (_reverseControlsEnabled)
    {
        _reverseControlsEnabled = false;
        _reverseControlsTimer = -1;
    }

    if (_options.reverseControlsDuration > 0)
        _reverseControlsTimer = std::clock();
    _reverseControlsEnabled = true;
}


void CharacterManager::OnWriteAnalogs()
{
    if (_instance->_reverseControlsEnabled)
    {
        ControllerPointers[0]->LeftStickX = -ControllerPointers[0]->LeftStickX;
        ControllerPointers[0]->LeftStickY = -ControllerPointers[0]->LeftStickY;
        ControllerPointers[0]->RightStickX = -ControllerPointers[0]->RightStickX;
        ControllerPointers[0]->RightStickY = -ControllerPointers[0]->RightStickY;
    }
    _writeAnalogsHook.Original();
}

void CharacterManager::OnFreezeTrapDisplay(task* tp)
{
    if (CurrentCharacter == Characters_Big || CurrentCharacter == Characters_Gamma)
    {
        tp->twp->scl.x = 3;
        tp->twp->scl.y = 3;
        tp->twp->scl.z = 3;
    }
    _freezeTrapDisplayHook.Original(tp);
}

// We temporally set the game mode to trick the result screen into showing its full version
void CharacterManager::OnScoreDisplayMain(task* tp)
{
    //If Tails just lost, we don't do anything
    if (CurrentCharacter == Characters_Tails && RaceWinnerPlayer == 2)
        return _scoreDisplayMainHook.Original(tp);

    const GameModes bufferGameMode = GameMode;
    GameMode = GameModes_Adventure_ActionStg;
    _scoreDisplayMainHook.Original(tp);
    GameMode = bufferGameMode;
}

void CharacterManager::HandleHudDisplayRings(const signed int ringCount, const unsigned char digits, NJS_SPRITE* hud)
{
    if (_instance->_settings.extendRingCapacity)
        _hudDisplayRingsHook.Original(ringCount, 5, hud);
    else
        _hudDisplayRingsHook.Original(ringCount, digits, hud);
}

// For big, we extend the ring capacity to 99999 if enabled
void CharacterManager::OnDrawSNumbers(_SC_NUMBERS* pscn)
{
    if (_instance->_settings.extendRingCapacity && CurrentCharacter == Characters_Big && pscn->max == 999)
        pscn->max = 99999;
    _drawSNumbersHook.Original(pscn);
}

//We don't create animals outside levels
//Allow us to spawn enemies in the adventure fields
void CharacterManager::OnCreateAnimal(int e_num, float x, float y, float z)
{
    if (CurrentLevel > LevelIDs_HedgehogHammer && CurrentLevel <= LevelIDs_HotShelter)
        _createAnimalHook.Original(e_num, x, y, z);
}
