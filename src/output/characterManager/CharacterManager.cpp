#include "CharacterManager.h"
#include "sadx-mod-loader/SADXModLoader/include/UsercallFunctionHandler.h"

CharacterManager* characterManagerPtr;
DataPointer(int, TimerEnabled, 0x912DF0);
const char* subtitleTrapBuffer[] = {NULL, NULL};

UsercallFuncVoid(HudDisplayRings_t, (signed int ringCount, unsigned __int8 digits, NJS_SPRITE* hud),
                 (ringCount, digits, hud), 0x425960, rEAX, rBL, rESI);
static void __cdecl HandleHudDisplayRings(signed int ringCount, unsigned __int8 digits, NJS_SPRITE* hud);
static void __cdecl HandleRingLoss();

CharacterManager::CharacterManager(const Options& options): options(options)
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
    WriteCall((void*)0x592057, WakeTimer);
    
    //We override the Set0Rings call inside the HurtPlayer function;
    WriteCall(reinterpret_cast<void*>(0x45072D), &HandleRingLoss);

    HudDisplayRings_t.Hook(HandleHudDisplayRings);
}


void CharacterManager::SetExtendRingCapacity(const bool extendRingCapacity)
{
    this->extendRingCapacity = extendRingCapacity;
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

    const int maxRings = this->extendRingCapacity ? 99999 : 999;

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

void CharacterManager::OnPlayingFrame()
{
    if (_fillerTimer > 0)
    {
        const double timePassed = (std::clock() - this->_fillerTimer) / static_cast<double>(CLOCKS_PER_SEC);
        if (timePassed > _fillerDuration)
        {
            _fillerTimer = -1;
            EnablePause();
        }
    }

    if (GameMode != GameModes_Mission && GameMode != GameModes_Adventure_Field)
        return;
    if (CurrentLevel == LevelIDs_TwinkleCircuit || CurrentLevel == LevelIDs_SkyChase1
        || CurrentLevel == LevelIDs_SkyChase2)
        return;

    if (CurrentLevel >= LevelIDs_Chaos0 && CurrentLevel <= LevelIDs_E101R && !_trapsOnBossFights)
        return;

    if (CurrentLevel == LevelIDs_PerfectChaos && !_trapsOnPerfectChaosFight)
        return;

    if (CurrentLevel >= LevelIDs_StationSquare && CurrentLevel <= LevelIDs_Past && !_trapsOnAdventureFields)
        return;

    if (CurrentLevel >= LevelIDs_SSGarden && CurrentLevel <= LevelIDs_ChaoRace && !_trapsOnAdventureFields)
        return;

    if (GameState != MD_GAME_MAIN || !EntityData1Ptrs[0])
        return;

    if (options.lazyFishing && unlockStatus.bigPowerRodUnlocked)
        RodTension = 0;

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

    if (_reverseControlsTimer > 0 && _reverseControlsDuration > 0)
    {
        const double timePassed = (std::clock() - this->_reverseControlsTimer) / static_cast<double>(CLOCKS_PER_SEC);
        if (timePassed > _reverseControlsDuration)
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

void CharacterManager::SetCharacterVoiceReactions(const bool eggmanCommentOnTrap,
                                                  const bool otherCharactersCommentOnTrap,
                                                  const bool currentCharacterReactToTrap,
                                                  const bool showCommentsSubtitles)
{
    _eggmanCommentOnTrap = eggmanCommentOnTrap;
    _otherCharactersCommentOnTrap = otherCharactersCommentOnTrap;
    _currentCharacterReactToTrap = currentCharacterReactToTrap;
    _showCommentsSubtitles = showCommentsSubtitles;
}

void CharacterManager::SetReverseControlTrapDuration(const int reverseControlTrapDuration)
{
    _reverseControlsDuration = static_cast<float>(reverseControlTrapDuration);
}

void CharacterManager::SetTrapsOnAdventureFields(const bool trapsOnAdventureFields)
{
    this->_trapsOnAdventureFields = trapsOnAdventureFields;
}

void CharacterManager::SetTrapsOnBossFights(const bool trapsOnBossFights)
{
    this->_trapsOnBossFights = trapsOnBossFights;
}

void CharacterManager::SetTrapsOnPerfectChaosFight(const bool trapsOnPerfectChaosFight)
{
    this->_trapsOnPerfectChaosFight = trapsOnPerfectChaosFight;
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
        PlayRandomTrapVoice(filler);
        break;
    case SpringTrap:
        this->SpawnSpring();
        DisablePause();
        PlayRandomTrapVoice(filler);
        break;
    case PoliceTrap:
        this->SpawnEnemies(EnemyPolice);
        DisablePause();
        PlayRandomTrapVoice(filler);
        break;
    case BuyonTrap:
        this->SpawnEnemies(EBuyon_Main);
        DisablePause();
        PlayRandomTrapVoice(filler);
        break;

    case ReverseTrap:
        this->ReverseControls();
        DisablePause();
        PlayRandomTrapVoice(filler);
        break;

    case GravityTrap:
        this->IncrementGravity();
        DisablePause();
        PlayRandomTrapVoice(filler);
        break;

    case NoFiller:
        break;
    default: ;
    }
}


void CharacterManager::PlayRandomTrapVoice(const FillerType filler)
{
    WeightedRandomSelector selector;
    selector.addNumber(174, 1); //Get a load of this!
    if (_eggmanCommentOnTrap)
    {
        selector.addNumber(171, 2); //All systems; full power!
        selector.addNumber(173, 3); //Ah-ha!
        selector.addNumber(178, 1); //Ho ho! It's no use. Give up!
        selector.addNumber(221, 1); //Wha ha ha ha ha ha ha ha ha!
        selector.addNumber(413, 1); //Ha ha ha ha ha ha ha ha ha ha ha!
        selector.addNumber(443, 1); //Aha!
        selector.addNumber(449, 1); //Ha ha ha ha ha!		
        selector.addNumber(463, 5); //Oh no; you don't!
        selector.addNumber(465, 1); //Ha ha ha ha ha ha ha ha ha!
        selector.addNumber(474, 1); //Ha ha ha ha ha ha!
        selector.addNumber(562, 1); //Ha ha ha ha ha!
        selector.addNumber(569, 1); //Ha ha ha ha ha!
        selector.addNumber(650, 3); //Gotcha!
        selector.addNumber(924, 1); //You can't get away this easily!
        selector.addNumber(926, 1); //Too late; buddy!
        selector.addNumber(1059, 1); //Ah ha hahahaha!
        selector.addNumber(1072, 1); //Mwuahahahahahahahahaha!
        selector.addNumber(1376, 1); //Ha ha ha ha ha ha!
        selector.addNumber(1518, 10); //Get a load of this!
        selector.addNumber(1522, 3); //Hahahahaha! I bet you wern't expecting this!
        selector.addNumber(1525, 1); //Haha hahahahaha!
        selector.addNumber(1542, 1); //I guess you wern't expecting that; were you?
        selector.addNumber(1680, 1); //You're not going to get away that easily. Huhahahaha.
        selector.addNumber(1903, 5); //Take this!
        selector.addNumber(1986, 1); //Huhaha! Why don't you give up?
        selector.addNumber(1987, 1); //Ha ha! It's no use! Give up!
        if (CurrentCharacter == Characters_Tails)
        {
            selector.addNumber(222, 3); //Goodbye; Tails!
            selector.addNumber(226, 3); //Give up now; Tails!
            selector.addNumber(217, 3); //I've got you now; Tails.
        }
        else if (CurrentCharacter == Characters_Sonic)
        {
            selector.addNumber(563, 3); //Oh yes! Attack Sonic now!
        }
        else if (CurrentCharacter == Characters_Amy)
        {
            selector.addNumber(922, 3); //Where do you think you're going; Amy?
        }
        if (filler == PoliceTrap)
        {
            selector.addNumber(1436, 3); //Ready men? Charge!
            selector.addNumber(404, 3); //You are completely surrounded!
            selector.addNumber(405, 3); //Surrender yourself!
            selector.addNumber(407, 3); //Lock on target men. Ready? Fire!
        }
    }
    if (_otherCharactersCommentOnTrap)
    {
        if (CurrentCharacter != Characters_Amy)
        {
            selector.addNumber(384, 1); //You're gonna pay for what you've done!
            selector.addNumber(849, 1); //Hey; are you alright? You look kind of hurt.
            selector.addNumber(885, 1); //Now; now; calm down.
            selector.addNumber(902, 1); //I pity you.
            selector.addNumber(952, 1); //Uh; you okay?
            selector.addNumber(988, 1); //Oh no! Are you okay?
            selector.addNumber(990, 1); //Now you're gonna get it!
            selector.addNumber(1258, 1); //I feel sorry for you.
            selector.addNumber(1493, 1); //Here; take this!
            if (filler == IceTrap || filler == SpringTrap)
            {
                selector.addNumber(888, 3); //Nope!
            }
        }
        if (CurrentCharacter != Characters_Big)
        {
            selector.addNumber(365, 1); //Are you guys okay?
            selector.addNumber(1336, 1); //Uh oh...
            if (filler == IceTrap)
            {
                selector.addNumber(241, 3); //The ice looks kinda tasty!
            }
        }
        if (CurrentCharacter != Characters_Gamma)
        {
            selector.addNumber(169, 1); //Resistance is futile.
            selector.addNumber(385, 1); //Target confirmed.
            selector.addNumber(1777, 1); //Running impossible.
            selector.addNumber(1779, 1); //Ha. Ha. Ha.
            if (CurrentCharacter == Characters_Sonic)
            {
                selector.addNumber(269, 3); //Blue hedgehog: enemy.
                selector.addNumber(386, 3); //Blue hedgehog: enemy.
            }
        }

        if (CurrentCharacter != Characters_Knuckles)
        {
            selector.addNumber(382, 1); //When will you ever learn?
            selector.addNumber(383, 1); //This time; you're finished!
            selector.addNumber(1159, 1); //Yeah! You're finished!
            selector.addNumber(1981, 1); //What's the matter? What're you waiting for?
        }
        if (CurrentCharacter != Characters_Sonic)
        {
            selector.addNumber(496, 1); //Ah; I wonder if he's okay.
            selector.addNumber(605, 1); //Something buggin' you?
            if (CurrentCharacter == Characters_Tails)
            {
                selector.addNumber(211, 3); //See you later; Tails!
            }
            if (filler == IceTrap)
            {
                selector.addNumber(229, 3); //What a nice breeze!
                selector.addNumber(240, 3); //Man; everything's frozen!
            }
        }
        if (CurrentCharacter != Characters_Tails)
        {
            selector.addNumber(618, 1); //Uh oh; what's this?
            selector.addNumber(731, 1); //Oops!
            selector.addNumber(828, 1); //Oops!
            selector.addNumber(1333, 1); //Oops!
            selector.addNumber(1511, 1); //All's well that ends well; right?
        }
    }
    if (_currentCharacterReactToTrap)
    {
        if (CurrentCharacter == Characters_Amy)
        {
            selector.addNumber(347, 1); //Hey; come on!
            selector.addNumber(506, 1); //Whoa!!
            selector.addNumber(517, 1); //Ahh! Sonic! Help!
            selector.addNumber(524, 1); //Sonic; help me!
            selector.addNumber(847, 1); //Aahh!! Watch it; watch it!
            selector.addNumber(851, 1); //Ah! Uh oh!
            selector.addNumber(872, 1); //*shouts*
            selector.addNumber(881, 1); //*scream*
            selector.addNumber(916, 1); //*gasp*
            selector.addNumber(923, 1); //Eggman; no!
            selector.addNumber(987, 1); //*gasp*
            selector.addNumber(1739, 1); //Oo-oo-ooh!
            selector.addNumber(1740, 1); //Oh no!
            selector.addNumber(1741, 1); //Whoa!
            selector.addNumber(1743, 1); //Wah!
            if (filler == IceTrap)
            {
                selector.addNumber(1742, 3); //Bbrrr!
            }
        }
        else if (CurrentCharacter == Characters_Big)
        {
            selector.addNumber(747, 1); //Wwhooa!
            selector.addNumber(1330, 1); //Whoaaaa!!
            selector.addNumber(1331, 1); //Ouh!
            selector.addNumber(1752, 1); //*inhales*
            selector.addNumber(1753, 1); //Oh no.
            selector.addNumber(1755, 1); //Oof!
            selector.addNumber(1756, 1); //Oh no!
            selector.addNumber(1757, 1); //Wah!!
            selector.addNumber(1764, 1); //Whooaa!!
        }
        else if (CurrentCharacter == Characters_Knuckles)
        {
            selector.addNumber(164, 1); //Oh no!
            selector.addNumber(332, 1); //Why?
            selector.addNumber(380, 1); //That's it. I've had enough!
            selector.addNumber(475, 1); //Ahh; Eggman!
            selector.addNumber(1004, 1); //What the!?
            selector.addNumber(1006, 1); //Oh no!
            selector.addNumber(1010, 1); //Ooph!
            selector.addNumber(1011, 1); //Auh! Euh! Hey; no fair!
            selector.addNumber(1789, 1); //Whoa!
            selector.addNumber(1795, 1); //Ohh!
            selector.addNumber(1796, 1); //I'm a goner.
            selector.addNumber(1799, 1); //Whooa!
        }
        else if (CurrentCharacter == Characters_Sonic)
        {
            selector.addNumber(165, 1); //Oh no!
            selector.addNumber(167, 1); //I've had enough!
            selector.addNumber(170, 1); //Oh no!
            selector.addNumber(402, 1); //Huh?
            selector.addNumber(444, 1); //Oh no!
            selector.addNumber(460, 1); //Hyyeeh!
            selector.addNumber(464, 1); //Aw; geesh!
            selector.addNumber(476, 1); //Uh oh!
            selector.addNumber(502, 1); //You must be kidding!
            selector.addNumber(523, 1); //Stop!
            selector.addNumber(561, 1); //Oh no! Not again!
            selector.addNumber(582, 1); //Agh; I hate Eggman!
            selector.addNumber(1461, 1); //What?!
            selector.addNumber(1854, 1); //Wwhoa!
            selector.addNumber(1855, 1); //Whoa!
            if (filler == IceTrap)
            {
                selector.addNumber(239, 3); //It's getting cold!
            }
        }
        else if (CurrentCharacter == Characters_Tails)
        {
            selector.addNumber(376, 1); //H-hey; wait a minute!
            selector.addNumber(619, 1); //Noooo!
            selector.addNumber(620, 1); //Ahhhh!
            selector.addNumber(623, 1); //Ahhhh!
            selector.addNumber(671, 1); //Ahhhhh!
            selector.addNumber(728, 1); //Sstop!
            selector.addNumber(748, 1); //Yikes!!
            selector.addNumber(802, 1); //Oh no!
            selector.addNumber(1801, 1); //Whoo!
            selector.addNumber(1814, 1); //Augh!
        }
    }
    if (!selector.isEmpty())
    {
        const int voice = selector.getRandomNumber();
        PlayVoice(voice);
        if (_showCommentsSubtitles)
        {
            auto it = _trapCommentMap.find(voice);
            if (it != _trapCommentMap.end() && GameMode != GameModes_Menu)
            {
                subtitleTrapBuffer[0] = it->second.c_str();
                DisplayHintText(subtitleTrapBuffer, 60 + 5 * it->second.length());
            }
        }
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

    if (_reverseControlsDuration > 0)
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
    if (characterManagerPtr->extendRingCapacity)
        HudDisplayRings_t.Original(ringCount, 5, hud);
    else
        HudDisplayRings_t.Original(ringCount, digits, hud);
}

// For big, we extend the ring capacity to 99999 if enabled
FunctionHook<void, _SC_NUMBERS*> onDrawSNumbers(0x427BB0, [](_SC_NUMBERS* pscn)-> void
{
    if (characterManagerPtr->extendRingCapacity && CurrentCharacter == Characters_Big && pscn->max == 999)
        pscn->max = 99999;
    onDrawSNumbers.Original(pscn);
});
