#include "Randomizer.h"

void Randomizer::OnUpgradeFound(const int checkId) const
{
    const CheckData check = _checkRepository.GetCheck(checkId);

    _displayManager.FoundItem(check.displayName);

    const ItemData item = _itemRepository.GetItem(check.originalItemId);
    if (!item.obtained)
        _upgradeManager.RemoveUpgrade(item.upgrade);

    _checkRepository.SetChecked(checkId);
}

void Randomizer::OnItemReceived(const int itemId) const
{
    const ItemData item = _itemRepository.SetObtained(itemId);
    _displayManager.ReceiveItem(item.displayName);
    _upgradeManager.GiveUpgrade(item.upgrade);
}

void Randomizer::OnCharacterLoaded() const
{
    for (const auto& item : _itemRepository.GetItems())
    {
        if (item.second.obtained)
            _upgradeManager.GiveUpgrade(item.second.upgrade);
        else
            _upgradeManager.RemoveUpgrade(item.second.upgrade);
    }
}

std::map<int, CheckData> Randomizer::GetCheckData() const
{
    return _checkRepository.GetChecks();
}
