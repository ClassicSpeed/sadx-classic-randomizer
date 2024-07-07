#include "Randomizer.h"

void Randomizer::OnCheckFound(const int checkId) const
{
    const LocationData check = _locationRepository.GetLocation(checkId);

    //TODO: improve this, maybe separate locations from upgrades/levels/etc
    if (LocationUpgrade == check.type)
    {
        const ItemData item = _itemRepository.GetItem(check.originalItemId);
        if (!item.obtained)
            _upgradeManager.RemoveUpgrade(item.address);
    }

    _locationRepository.SetLocationChecked(checkId);
    _archipelagoMessenger.CheckLocation(checkId);
}


void Randomizer::OnItemReceived(const int64_t itemId) const
{
    const ItemData item = _itemRepository.SetObtained(itemId);
    if (item.type == ItemUpgrade)
        _upgradeManager.GiveUpgrade(item.address);
    else if (item.type == ItemCharacter)
        _menuManager.UnlockCharacterSelection(item.address);
    else if (item.type == ItemEmblem)
    {
        const int emblemCount = _itemRepository.AddEmblem();
        _displayManager.ShowEmblemCount(emblemCount);
        if (emblemCount == _emblemGoal)
            _displayManager.QueueMessage("You can now fight Perfect Chaos!");
    }
}

void Randomizer::OnCharacterLoaded() const
{
    for (const auto& item : _itemRepository.GetItems())
    {
        if (item.second.type != ItemUpgrade)
            continue;

        if (item.second.obtained)
            _upgradeManager.GiveUpgrade(item.second.address);
        else
            _upgradeManager.RemoveUpgrade(item.second.address);
    }
}


void Randomizer::OnCharacterSelectScreenLoaded() const
{
    for (const auto& item : _itemRepository.GetItems())
    {
        if (item.second.type == ItemEmblem)
        {
            if (_itemRepository.GetEmblemCount() >= _emblemGoal)
                _menuManager.UnlockCharacterSelection(EventFlags_SuperSonicUnlockedAdventure);
            else
                _menuManager.LockCharacterSelection(EventFlags_SuperSonicUnlockedAdventure);
        }

        if (item.second.type == ItemCharacter)
        {
            if (item.second.obtained)
                _menuManager.UnlockCharacterSelection(item.second.address);
            else
                _menuManager.LockCharacterSelection(item.second.address);
        }
    }
}


std::map<int, LocationData> Randomizer::GetCheckData() const
{
    return _locationRepository.GetLocations();
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
    _emblemGoal = emblemGoal;
}
