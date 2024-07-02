#include "Randomizer.h"

void Randomizer::OnCheckFound(const int checkId) const
{
    const LocationData check = _checkRepository.GetCheck(checkId);

    // _displayManager.QueueMessage("Checked: " +check.displayName);

    const ItemData item = _itemRepository.GetItem(check.originalItemId);
    if (!item.obtained)
        _upgradeManager.RemoveUpgrade(item.adress);

    _checkRepository.SetChecked(checkId);
    _archipelagoMessenger.CheckLocation(checkId);
}

void Randomizer::OnItemReceived(const int64_t itemId) const
{
    const ItemData item = _itemRepository.SetObtained(itemId);
    _displayManager.QueueMessage("Got: " + item.displayName);
    if (item.type == ItemUpgrade)
        _upgradeManager.GiveUpgrade(item.adress);
    else if (item.type == ItemCharacter)
        _characterSelectionManager.Unlock(item.adress);
}

void Randomizer::OnCharacterLoaded() const
{
    for (const auto& item : _itemRepository.GetItems())
    {
        if (item.second.type != ItemUpgrade)
            continue;

        if (item.second.obtained)
            _upgradeManager.GiveUpgrade(item.second.adress);
        else
            _upgradeManager.RemoveUpgrade(item.second.adress);
    }
}


void Randomizer::OnCharacterSelectScreenLoaded() const
{
    for (const auto& item : _itemRepository.GetItems())
    {
        if (item.second.type != ItemCharacter)
            continue;
        
        if (item.second.obtained)
            _characterSelectionManager.Unlock(item.second.adress);
        else
            _characterSelectionManager.Lock(item.second.adress);
    }
}


std::map<int, LocationData> Randomizer::GetCheckData() const
{
    return _checkRepository.GetChecks();
}

void Randomizer::OnConnected()
{
    _displayManager.QueueMessage("Connected to Archipelago");
}
