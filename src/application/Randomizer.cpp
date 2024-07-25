#include "Randomizer.h"

void Randomizer::OnCheckFound(const int checkId) const
{
    const LocationData check = _locationRepository.GetLocation(checkId);

    if (LocationUpgrade == check.type)
    {
        const ItemData item = _itemRepository.GetItem(check.originalItemId);
        if (!item.obtained)
            _upgradeManager.RemoveUpgrade(item.upgrade);
    }

    _locationRepository.SetLocationChecked(checkId);
    _archipelagoMessenger.CheckLocation(checkId);
}


void Randomizer::OnItemReceived(const int64_t itemId) const
{
    const ItemData item = _itemRepository.SetObtained(itemId);
    if (item.type == ItemUpgrade)
        _upgradeManager.GiveUpgrade(item.upgrade);
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
    _displayManager.UpdateUnlockStatus(unlockStatus);
}

void Randomizer::OnCharacterLoaded() const
{
    for (const auto& item : _itemRepository.GetItems())
    {
        if (item.second.type != ItemUpgrade)
            continue;

        if (item.second.obtained)
            _upgradeManager.GiveUpgrade(item.second.upgrade);
        else
            _upgradeManager.RemoveUpgrade(item.second.upgrade);
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

void Randomizer::SetMissions(Characters characters, int missions)
{
    _options.SetMissions(characters, missions);
    _displayManager.UpdateOptions(_options);
}
