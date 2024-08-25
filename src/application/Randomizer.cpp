#include "Randomizer.h"

void Randomizer::OnCheckFound(const int checkId) const
{
    const LocationData check = _locationRepository.GetLocation(checkId);

    if (LocationUpgrade == check.type)
    {
        const ItemData item = _itemRepository.GetItem(check.originalItemId);
        if (!item.obtained)
            _characterManager.RemoveUpgrade(item.upgrade);
    }

    _locationRepository.SetLocationChecked(checkId);
    _archipelagoMessenger.CheckLocation(checkId);
    if (check.character == Characters_Big && check.level == LevelIDs_TwinklePark && check.mission == MISSION_C)
        _worldStateManager.SetEventFlags({FLAG_BIG_SS_TPARK_ELEVATOR});

    _displayManager.UpdateChecks(_locationRepository.GetLocations());
    if (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt)
    {
        const LevelStatus levelStatus = _locationRepository.GetLevelStatus(_options);
        _displayManager.UpdateLevelStatus(levelStatus);
        _displayManager.ShowGoalStatus();
        if (levelStatus.levelsTotal == levelStatus.levelsCompleted && check.mission == MISSION_C
            && AreLastStoryRequirementsCompleted())
            _displayManager.QueueMessage("You can now fight Perfect Chaos!");
    }
}

void Randomizer::MarkCheckedLocation(const int64_t checkId) const
{
    _locationRepository.SetLocationChecked(checkId);
    const LevelStatus levelStatus = _locationRepository.GetLevelStatus(_options);
    _displayManager.UpdateLevelStatus(levelStatus);
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

bool Randomizer::AreLastStoryRequirementsCompleted() const
{
    if (_options.goal == GoalLevels)
        return _locationRepository.CompletedAllLevels(_options);

    if (_options.goal == GoalEmblems)
        return _itemRepository.GetEmblemCount() >= _options.emblemGoal;

    if (_options.goal == GoalEmeraldHunt)
        return _itemRepository.GetUnlockStatus().GotAllChaosEmeralds();

    if (_options.goal == GoalLevelsAndEmeraldHunt)
        return _locationRepository.CompletedAllLevels(_options) &&
            _itemRepository.GetUnlockStatus().GotAllChaosEmeralds();

    if (_options.goal == GoalEmblemsAndEmeraldHunt)
        return _itemRepository.GetEmblemCount() >= _options.emblemGoal &&
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

    _characterManager.KillPlayer();
    _displayManager.QueueMessage(_pendingDeathCause);
    _pendingDeathCause.clear();
    _deathPending = false;
    _ignoreNextPlayerDeath = true;
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
}

void Randomizer::OnEmblemGoalSet(const int emblemGoal)
{
    _options.emblemGoal = max(1, emblemGoal);
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
    _options.pinballCapsules = pinballLifeCapsules;
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

void Randomizer::SetSublevelChecks(const bool sublevelChecks)
{
    _options.sublevelsChecks = sublevelChecks;
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
