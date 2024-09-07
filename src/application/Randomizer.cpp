#include "Randomizer.h"

void Randomizer::OnCheckFound(const int checkId) const
{
    const LocationData check = _locationRepository.GetLocation(checkId);

    if (check.type == LocationUpgrade)
    {
        const ItemData item = _itemRepository.GetItem(check.originalItemId);
        if (!item.obtained)
            _characterManager.RemoveUpgrade(item.upgrade);
    }

    _locationRepository.SetLocationChecked(checkId);
    _archipelagoMessenger.CheckLocation(checkId);

    _displayManager.UpdateChecks(_locationRepository.GetLocations());
    if (check.type == LocationLevel && check.mission == MISSION_C
        && (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt))
    {
        const LevelStatus levelStatus = _locationRepository.GetLevelStatus(_options);
        _displayManager.UpdateLevelStatus(levelStatus);
        _displayManager.ShowGoalStatus();
        if (_options.levelGoal == levelStatus.levelsCompleted
            && AreLastStoryRequirementsCompleted())
            _displayManager.QueueMessage("You can now fight Perfect Chaos!");
    }
    if (check.type == LocationMission
        && (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt))
    {
        const MissionStatus missionStatus = _locationRepository.GetMissionStatus(_options);
        _displayManager.UpdateMissionStatus(missionStatus);
        _displayManager.ShowGoalStatus();
        if (_options.missionGoal == missionStatus.missionsCompleted
            && AreLastStoryRequirementsCompleted())
            _displayManager.QueueMessage("You can now fight Perfect Chaos!");
    }
}

void Randomizer::MarkCheckedLocation(const int64_t checkId) const
{
    _locationRepository.SetLocationChecked(checkId);
    const LevelStatus levelStatus = _locationRepository.GetLevelStatus(_options);
    _displayManager.UpdateLevelStatus(levelStatus);
    const MissionStatus missionStatus = _locationRepository.GetMissionStatus(_options);
    _displayManager.UpdateMissionStatus(missionStatus);
}


void Randomizer::OnItemReceived(const int64_t itemId) const
{
    const bool ignore = _itemRepository.SetObtained(itemId);
    if (ignore)
        return;

    const ItemData item = _itemRepository.GetItem(itemId);

    if (item.type == ItemUpgrade)
        _characterManager.GiveUpgrade(item.upgrade);
    else if (item.type == ItemCharacter || item.type == ItemKey)
        _worldStateManager.SetEventFlags(item.eventFlags);
    else if (item.type == ItemFiller)
        _characterManager.GiveFillerItem(item.fillerType);
    else if (item.type == ItemEmblem)
        _itemRepository.AddEmblem();

    const UnlockStatus unlockStatus = _itemRepository.GetUnlockStatus();
    _characterManager.UpdateUnlockStatus(unlockStatus);
    _displayManager.UpdateUnlockStatus(unlockStatus);
    _worldStateManager.UpdateUnlockStatus(unlockStatus);

    if (item.type == ItemChaosEmerald)
    {
        _displayManager.ShowGoalStatus();

        if (AreLastStoryRequirementsCompleted())
            _displayManager.QueueMessage("You can now fight Perfect Chaos!");
    }

    else if (item.type == ItemEmblem)
    {
        _displayManager.ShowGoalStatus();
        if (unlockStatus.currentEmblems == _options.emblemGoal && AreLastStoryRequirementsCompleted())
            _displayManager.QueueMessage("You can now fight Perfect Chaos!");
    }

    this->PlayRandomVoiceForItem(item);
}

void Randomizer::PlayRandomVoiceForItem(const ItemData& item) const
{
    WeightedRandomSelector selector;
    if (item.type == ItemCharacter)
    {
        if (_currentCharacterCommentOnCharacterUnlock)
        {
            if (CurrentCharacter == Characters_Amy)
            {
                selector.addNumber(498, 1); //Long time no see.
                selector.addNumber(860, 1); //Long time; no see!
            }
            else if (CurrentCharacter == Characters_Big)
            {
                selector.addNumber(364, 1); //Looking good; buddy!
            }
            else if (CurrentCharacter == Characters_Gamma)
            {
                selector.addNumber(363, 1); //Sensors detecting life.
            }
            else if (CurrentCharacter == Characters_Knuckles)
            {
                selector.addNumber(2013, 1); //Hmm... I wonder what those guys are doing?
            }
        }

        if (item.displayName == "Playable Amy")
        {
            if (_unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(277, 1); //I wanna go shopping!
                selector.addNumber(324, 1); //I'm going to do my best; Sonic.
                selector.addNumber(1730, 1); //It's my turn now!
            }
            if (_currentCharacterCommentOnCharacterUnlock)
            {
                if (CurrentCharacter == Characters_Sonic)
                {
                    selector.addNumber(499, 2); //Uhhh eh; Amy!
                    selector.addNumber(512, 2); //Aw; man! That girl is such a pain!
                    selector.addNumber(861, 2); //Y-ah-uhh... Amy!
                    selector.addNumber(1492, 2); //Amy!
                }
                else if (CurrentCharacter == Characters_Tails)
                {
                    selector.addNumber(959, 3); //Amy; come on; let's get going!
                }
            }
        }
        else if (item.displayName == "Playable Big")
        {
            if (_unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(367, 1); //I wanna go fishing!
                selector.addNumber(566, 1); //I must save Froggy!
                selector.addNumber(1335, 1); //Froggy?
                selector.addNumber(1342, 1); //Mm; smells like Froggy's around somewhere...
                selector.addNumber(1744, 1); //Hold on Froggy! I'm coming!
                selector.addNumber(1876, 1); //Okay! One more time!
                selector.addNumber(2012, 1); //Froggy? Where are you?
            }
            if (_currentCharacterCommentOnCharacterUnlock)
            {
                if (CurrentCharacter == Characters_Tails)
                {
                    selector.addNumber(2024, 3); //Hope you find Froggy soon!
                }
            }
        }
        else if (item.displayName == "Playable Gamma")
        {
            if (_unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(394, 1); //Combat system activated.
                selector.addNumber(543, 1); //What is your wish; master Robotnik?
                selector.addNumber(775, 1); //What is your wish; Master?
                selector.addNumber(932, 1); //At your service; sir.
                selector.addNumber(1276, 1); //How can I serve you; Dr. Robotnik?
                selector.addNumber(1767, 1); //Preperation complete.
            }
            if (_currentCharacterCommentOnCharacterUnlock)
            {
                if (CurrentCharacter == Characters_Amy)
                {
                    selector.addNumber(504, 2); //Look! One of Eggman's robots.
                    selector.addNumber(551, 2); //This robot is my friend. He helped me!
                    selector.addNumber(870, 2); //Aahh; look! Eggman's robot's on the loose!
                    selector.addNumber(911, 2); //You're different from the other robots.
                    selector.addNumber(943, 2); //This robot is different.
                    selector.addNumber(1292, 2); //And how are you; my metal friend?
                }
                else if (CurrentCharacter == Characters_Knuckles)
                {
                    selector.addNumber(1008, 3); //Huh? Who are you?
                    selector.addNumber(1121, 3); //Hey; isn't that one of Eggman's robots?
                }
                else if (CurrentCharacter == Characters_Sonic)
                {
                    selector.addNumber(265, 3); //I smell oil.
                }
                else if (CurrentCharacter == Characters_Tails)
                {
                    selector.addNumber(378, 3); //Something's different about this robot.
                }
            }
            if (_eggmanCommentOnCharacterUnlock)
            {
                selector.addNumber(542, 1); //GAMMA!!
                selector.addNumber(779, 1); //I'll leave it up to you; Gamma.
                selector.addNumber(931, 1); //Gamma!
                selector.addNumber(1174, 1); //E-102; Codename: Gamma!
                selector.addNumber(1179, 1); //Enter; Gamma!
                selector.addNumber(1186, 1); //Okay then; Gamma. Here's your test!
                selector.addNumber(1280, 1); //I'm counting on you Gamma!
            }
        }
        else if (item.displayName == "Playable Knuckles")
        {
            if (_unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(261, 1); //Okay now; where's the treasure?
                selector.addNumber(308, 1); //I've got to find the Master Emerald.
                selector.addNumber(709, 1); //I have some unfinished business to take care of.
                selector.addNumber(1123, 1); //Here I come; Eggman!
                selector.addNumber(1787, 1); //Okay! Let's go!
            }
            if (_currentCharacterCommentOnCharacterUnlock)
            {
                if (CurrentCharacter == Characters_Sonic)
                {
                    selector.addNumber(370, 2); //What's up; Knuckles?
                    selector.addNumber(579, 2);
                    //Hey there; Knuckles. Glad you finally made it! I thought you got lost or something.
                    selector.addNumber(604, 2); //What's up; Knuckles?
                    selector.addNumber(1148, 2); //There you are Knuckles! About time.
                    selector.addNumber(238, 2); //What's the smell? Smells like trash!
                }
                else if (CurrentCharacter == Characters_Tails)
                {
                    selector.addNumber(679, 3); //Hey Knuckles; what's up?
                }
            }
            if (_eggmanCommentOnCharacterUnlock)
            {
                selector.addNumber(1036, 1); //Kn- Knuckles!
            }
        }
        else if (item.displayName == "Playable Sonic")
        {
            if (_unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(206, 1); //Hey; hey; hey!
                selector.addNumber(242, 1); //Watch and learn!
                selector.addNumber(248, 3); //Time for some supersonic speed!
                selector.addNumber(349, 1); //Yo! Have you guys been good?
                selector.addNumber(374, 1); //You've had your fun. Now it's my turn!
                selector.addNumber(410, 1); //This could be fun!
                selector.addNumber(568, 1); //Just leave it to me!
            }
            if (_currentCharacterCommentOnCharacterUnlock)
            {
                if (CurrentCharacter == Characters_Amy)
                {
                    selector.addNumber(247, 1); //I wonder where Sonic went.
                    selector.addNumber(360, 1); //If only Sonic were here.
                    selector.addNumber(857, 1); //Oh; Sonic!
                    selector.addNumber(858, 1); //(dreamy sigh) My hero!
                    selector.addNumber(964, 1); //I wonder what Sonic is doing.
                    selector.addNumber(1491, 1); //Hey; Sonic!
                }
                else if (CurrentCharacter == Characters_Knuckles)
                {
                    selector.addNumber(1147, 1); //Hey Sonic!
                }
                else if (CurrentCharacter == Characters_Tails)
                {
                    selector.addNumber(417, 1); //Hey; Sonic! Long time no see; huh?
                    selector.addNumber(455, 1); //Sonic!
                    selector.addNumber(471, 1); //Come on; Sonic; we need to get busy!
                    selector.addNumber(525, 1); //Hey; Sonic!
                    selector.addNumber(760, 1); //There's Sonic!
                    selector.addNumber(1091, 1); //Hurry Sonic! What're we waiting for?
                    selector.addNumber(1408, 1); //Sonic!
                    selector.addNumber(1451, 1); //Sonic; wake up!
                    selector.addNumber(1512, 1); //Sonic?
                    selector.addNumber(235, 1); //I wonder where Sonic is.
                }
            }
            if (_eggmanCommentOnCharacterUnlock)
            {
                selector.addNumber(431, 1); //Ha ha ha ha! If it isn't Sonic!
                selector.addNumber(601, 1); //Well; if it isn't my pal; Sonic.
                selector.addNumber(1392, 1); //Ooh; I hate that Sonic!
                selector.addNumber(1713, 1); //Sonic! It's up to you now.
                selector.addNumber(1714, 1); //Be brave; blue hedgehog.
            }
        }
        else if (item.displayName == "Playable Tails")
        {
            if (_unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(243, 1); //Time to jam!
                selector.addNumber(275, 1); //Boy; I'm hungry.
                selector.addNumber(352, 1); //How's it goin' guys?
                selector.addNumber(375, 1); //C'mon Tails; you can do it!
                selector.addNumber(528, 1); //Roger!
                selector.addNumber(617, 1); //All systems go; full speed ahead!
                selector.addNumber(753, 1); //The time has come at last.
                selector.addNumber(757, 1); //Ready Sonic? Here I come!
                selector.addNumber(1800, 1); //Here I come; Sonic!
            }
            if (_currentCharacterCommentOnCharacterUnlock)
            {
                if (CurrentCharacter == Characters_Sonic)
                {
                    selector.addNumber(205, 1); //Come on; Tails!
                    selector.addNumber(207, 1); //All right; Tails!
                    selector.addNumber(208, 1); //Hey; Tails!
                    selector.addNumber(414, 1); //Wha? Tails?!
                    selector.addNumber(526, 1); //Tails! I'm glad you're okay.
                    selector.addNumber(527, 1); //Ready to roll; champ? Let's go!
                }
            }
            if (_eggmanCommentOnCharacterUnlock)
            {
                selector.addNumber(219, 2); //You little fox!
            }
        }
    }
    if (!selector.isEmpty())
    {
        const int voice = selector.getRandomNumber();
        PlayVoice(voice);
    }
}


void Randomizer::ResetItems()
{
    _itemRepository.ResetItems();
    const UnlockStatus unlockStatus = _itemRepository.GetUnlockStatus();
    _characterManager.UpdateUnlockStatus(unlockStatus);
    _displayManager.UpdateUnlockStatus(unlockStatus);
    _worldStateManager.UpdateUnlockStatus(unlockStatus);
}

void Randomizer::SetMissionMode(const int missionModeEnabled)
{
    _options.missionModeEnabled = missionModeEnabled;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::SetAutoStartMissions(const int autoStartMissions)
{
    if (autoStartMissions)
        _worldStateManager.StartAllMissions();
}

void Randomizer::OnCheckVersion(int serverVersion)
{
    if (serverVersion != SADX_AP_VERSION_MAJOR * 100 + SADX_AP_VERSION_MINOR * 10 + SADX_AP_VERSION_PATCH)
    {
        const std::string modVersionString = std::to_string(SADX_AP_VERSION_MAJOR) + "." +
            std::to_string(SADX_AP_VERSION_MINOR) + "." + std::to_string(SADX_AP_VERSION_PATCH);
        const std::string serverVersionString = std::to_string(serverVersion / 100) + "." +
            std::to_string((serverVersion / 10) % 10) + "." + std::to_string(serverVersion % 10);
        _displayManager.QueueMessage(
            "Warning: Version mismatch! Server: v" + serverVersionString + " Mod: v" + modVersionString);
    }
}

void Randomizer::SetStartingCharacter(const int startingCharacterIndex)
{
    _characterManager.SetStartingCharacter(startingCharacterIndex);
}

void Randomizer::UpdateLevelEntrances(LevelEntrances levelEntrances)
{
    _worldStateManager.UpdateLevelEntrances(levelEntrances);

    for (const auto& location : _locationRepository.GetLocations())
    {
        if (location.second.type == LocationLevel && location.second.checked && location.second.level >=
            LevelIDs_EmeraldCoast && location.second.level <= LevelIDs_HotShelter)
            _displayManager.UpdateVisitedLevels(_worldStateManager.GetVisitedLevels(location.second.level));
    }
}

void Randomizer::UpdateMissionBlacklist(const std::vector<int>& missionBlacklist)
{
    _options.missionBlacklist = missionBlacklist;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
    if (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt)
    {
        const MissionStatus missionStatus = _locationRepository.GetMissionStatus(_options);
        _displayManager.UpdateMissionStatus(missionStatus);
    }
}

void Randomizer::SetEntranceRandomizer(const bool enableEntranceRandomizer)
{
    _options.entranceRandomizer = enableEntranceRandomizer;
}

bool Randomizer::AreLastStoryRequirementsCompleted() const
{
    if (_options.goal == GoalLevels)
        return _locationRepository.GetLevelStatus(_options).levelsCompleted >= _options.levelGoal;

    if (_options.goal == GoalEmblems)
        return _itemRepository.GetEmblemCount() >= _options.emblemGoal;


    if (_options.goal == GoalMissions)
        return _locationRepository.GetMissionStatus(_options).missionsCompleted >= _options.missionGoal;

    if (_options.goal == GoalEmeraldHunt)
        return _itemRepository.GetUnlockStatus().GotAllChaosEmeralds();

    if (_options.goal == GoalLevelsAndEmeraldHunt)
        return _locationRepository.GetLevelStatus(_options).levelsCompleted >= _options.levelGoal &&
            _itemRepository.GetUnlockStatus().GotAllChaosEmeralds();

    if (_options.goal == GoalEmblemsAndEmeraldHunt)
        return _itemRepository.GetEmblemCount() >= _options.emblemGoal &&
            _itemRepository.GetUnlockStatus().GotAllChaosEmeralds();

    if (_options.goal == GoalMissionsAndEmeraldHunt)
        return _locationRepository.GetMissionStatus(_options).missionsCompleted >= _options.missionGoal &&
            _itemRepository.GetUnlockStatus().GotAllChaosEmeralds();
    return false;
}


void Randomizer::OnCharacterLoaded() const
{
    for (const auto& item : _itemRepository.GetItems())
    {
        if (item.second.type != ItemUpgrade)
            continue;

        if (item.second.obtained)
            _characterManager.GiveUpgrade(item.second.upgrade);
        else
            _characterManager.RemoveUpgrade(item.second.upgrade);
    }
    if (_options.entranceRandomizer && CurrentLevel >= LevelIDs_EmeraldCoast && CurrentLevel <= LevelIDs_HotShelter)
        _displayManager.UpdateVisitedLevels(_worldStateManager.GetVisitedLevels(CurrentLevel));
}


void Randomizer::OnCharacterSelectScreenLoaded() const
{
    for (const auto& item : _itemRepository.GetItems())
    {
        if (item.second.type == ItemEmblem)
        {
            if (AreLastStoryRequirementsCompleted())
                _worldStateManager.UnlockSuperSonic();
        }

        if (item.second.type == ItemCharacter && item.second.obtained)
            _worldStateManager.SetEventFlags(item.second.eventFlags);
    }
}


std::map<int, LocationData> Randomizer::GetCheckData() const
{
    return _locationRepository.GetLocations();
}

std::vector<LifeBoxLocationData> Randomizer::GetLifeCapsules()
{
    return _locationRepository.GetLifeCapsules();
}

void Randomizer::ProcessDeath(const std::string& deathCause)
{
    if (_ignoreNextDeathLink)
    {
        _ignoreNextDeathLink = false;
        return;
    }

    _pendingDeathCause = deathCause;
    _deathPending = true;
}

void Randomizer::OnPlayingFrame()
{
    if (!_options.deathLinkActive)
        return;
    if (!_deathPending)
        return;
    if (GameMode != GameModes_Mission)
        return;
    if (GameState != MD_GAME_MAIN)
        return;
    if (!IsControllerEnabled(0))
        return;

    _ignoreNextPlayerDeath = true;
    _characterManager.KillPlayer();
    _displayManager.QueueMessage(_pendingDeathCause);
    _pendingDeathCause.clear();
    _deathPending = false;
}

void Randomizer::OnSync()
{
    if (!_options.ringLinkActive)
        return;
    const int ringDifference = _characterManager.GetRingDifference();
    if (ringDifference == 0)
        return;
    _archipelagoMessenger.SendRingUpdate(ringDifference);
}

void Randomizer::OnDeath()
{
    if (!_options.deathLinkActive)
        return;
    if (_ignoreNextPlayerDeath)
    {
        _ignoreNextPlayerDeath = false;
        return;
    }

    _archipelagoMessenger.SendDeath(_options.playerName);
    _ignoreNextDeathLink = true;
    _displayManager.QueueMessage("Death Sent");
}

void Randomizer::ProcessRings(const Sint16 amount)
{
    _characterManager.ProcessRings(amount);
}

void Randomizer::OnConnected(std::string playerName)
{
    _options.playerName = playerName;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
    _displayManager.QueueMessage("Connected to Archipelago");
}

void Randomizer::OnGameCompleted()
{
    _displayManager.QueueMessage("Victory!");
    _archipelagoMessenger.GameCompleted();
}

void Randomizer::ShowStatusInformation(std::string information)
{
    _displayManager.ShowStatusInformation(information);
}

void Randomizer::QueueNewMessage(std::string information)
{
    _displayManager.QueueMessage(information);
}

void Randomizer::OnGoalSet(const Goal goal)
{
    _options.goal = goal;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
    if (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt)
    {
        const LevelStatus levelStatus = _locationRepository.GetLevelStatus(_options);
        _displayManager.UpdateLevelStatus(levelStatus);
    }
    else if (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt)
    {
        const MissionStatus missionStatus = _locationRepository.GetMissionStatus(_options);
        _displayManager.UpdateMissionStatus(missionStatus);
    }
}

void Randomizer::OnEmblemGoalSet(const int emblemGoal)
{
    _options.emblemGoal = max(1, emblemGoal);
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::OnLevelGoalSet(int levelGoal)
{
    _options.levelGoal = max(1, levelGoal);
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::OnMissionGoalSet(int missionGoal)
{
    _options.missionGoal = max(1, missionGoal);
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::OnLifeSanitySet(const bool lifeSanity)
{
    _options.lifeSanity = lifeSanity;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}


void Randomizer::OnPinballLifeCapsulesSet(const bool pinballLifeCapsules)
{
    _options.includePinballCapsules = pinballLifeCapsules;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::SetCharacterStatingArea(const Characters character, const StartingArea startingArea)
{
    _options.SetCharacterStatingArea(character, startingArea);
    _worldStateManager.UpdateOptions(_options);
    _worldStateManager.UpdateOptions(_options);
}

void Randomizer::SetPlayableCharacter(const Characters character, const bool playable)
{
    _options.SetPlayableCharacter(character, playable);
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::SetActionStageMissions(const Characters characters, const int missions)
{
    _options.SetActionStageMissions(characters, missions);
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
    if (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt)
    {
        const LevelStatus levelStatus = _locationRepository.GetLevelStatus(_options);
        _displayManager.UpdateLevelStatus(levelStatus);
    }
}

void Randomizer::SetCharacterLifeSanity(const Characters character, const bool characterLifeSanity)
{
    _options.SetCharacterLifeSanity(character, characterLifeSanity);
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::SetDeathLink(const bool deathLinkActive)
{
    _options.deathLinkActive = deathLinkActive;
    _archipelagoMessenger.UpdateTags(_options);
}

void Randomizer::SetRingLink(const bool ringLinkActive)
{
    _options.ringLinkActive = ringLinkActive;
    _archipelagoMessenger.UpdateTags(_options);
}

void Randomizer::SetCasinopolisRingLink(const bool casinopolisRingLink)
{
    _options.casinopolisRingLink = casinopolisRingLink;
}

void Randomizer::SetHardRingLink(const bool hardRingLinkActive)
{
    _options.hardRingLinkActive = hardRingLinkActive;
}

void Randomizer::SetRingLoss(const RingLoss ringLoss)
{
    _options.ringLoss = ringLoss;
    _worldStateManager.UpdateOptions(_options);
    _characterManager.UpdateOptions(_options);
}

void Randomizer::SetSkyChaseChecks(const bool skyChaseChecks)
{
    _options.skyChaseChecks = skyChaseChecks;
}

void Randomizer::SetBossChecks(const bool bossChecks)
{
    _options.bossChecks = bossChecks;
}

void Randomizer::SetUnifyChaos4(const bool unifyChaos4)
{
    _options.unifyChaos4 = unifyChaos4;
}

void Randomizer::SetUnifyChaos6(const bool unifyChaos6)
{
    _options.unifyChaos6 = unifyChaos6;
}

void Randomizer::SetUnifyEggHornet(const bool unifyEggHornet)
{
    _options.unifyEggHornet = unifyEggHornet;
}

Options Randomizer::GetOptions() const
{
    return _options;
}
