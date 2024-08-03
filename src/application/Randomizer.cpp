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
}

void Randomizer::MarkCheckedLocation(const int64_t checkId) const
{
    _locationRepository.SetLocationChecked(checkId);
}


void Randomizer::OnItemReceived(const int64_t itemId) const
{
    const ItemData item = _itemRepository.SetObtained(itemId);
    if (item.type == ItemUpgrade)
        _characterManager.GiveUpgrade(item.upgrade);
    else if (item.type == ItemCharacter || item.type == ItemKey)
        _worldStateManager.SetEventFlags(item.eventFlags);
    else if (item.type == ItemEmblem)
    {
        const int emblemCount = _itemRepository.AddEmblem();
        _displayManager.ShowEmblemCount(emblemCount);
        if (emblemCount == _options.emblemGoal)
            _displayManager.QueueMessage("You can now fight Perfect Chaos!");
    }
    const UnlockStatus unlockStatus = _itemRepository.GetUnlockStatus();
    _characterManager.UpdateUnlockStatus(unlockStatus);
    _displayManager.UpdateUnlockStatus(unlockStatus);
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
            if (_options.emblemGoal >= 0 &&
                _itemRepository.GetEmblemCount() >= _options.emblemGoal)
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
    _pendingDeathCause = deathCause;
    _deathPending = true;
}

void Randomizer::OnPlayingFrame()
{
    if (!_options.deathLinkActive)
        return;
    if (!_deathPending)
        return;
    if (GameMode != GameModes_Adventure_Field && GameMode != GameModes_Adventure_ActionStg)
        return;

    _characterManager.KillPlayer();
    _displayManager.QueueMessage(_pendingDeathCause);
    _pendingDeathCause.clear();
    _deathPending = false;
    _ignoreNextDeath = true;
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
    if (_ignoreNextDeath)
    {
        _ignoreNextDeath = false;
        return;
    }

    _displayManager.QueueMessage("Death Sent");
    _archipelagoMessenger.SendDeath();
}

void Randomizer::ProcessRings(const Sint16 amount)
{
    _characterManager.ProcessRings(amount);
}

void Randomizer::OnConnected()
{
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

void Randomizer::OnEmblemGoalSet(const int emblemGoal)
{
    _options.emblemGoal = max(1, emblemGoal);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::OnLifeSanitySet(const bool lifeSanity)
{
    _options.lifeSanity = lifeSanity;
    _displayManager.UpdateOptions(_options);
}


void Randomizer::OnPinballLifeCapsulesSet(const bool pinballLifeCapsules)
{
    _options.pinballCapsules = pinballLifeCapsules;
    _displayManager.UpdateOptions(_options);
}
void Randomizer::SetStatingArea(const StartingArea startingArea)
{
    _options.startingArea = startingArea;
    _worldStateManager.UpdateOptions(_options);
}

void Randomizer::SetMissions(Characters characters, int missions)
{
    _options.SetMissions(characters, missions);
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

void Randomizer::SetRingLoss(const RingLoss ringLoss)
{
    _options.ringLoss = ringLoss;
    _characterManager.UpdateOptions(_options);
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
