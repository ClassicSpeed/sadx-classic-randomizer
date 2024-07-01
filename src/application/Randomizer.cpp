#include "Randomizer.h"
#include "SADXModLoader.h"

void Randomizer::OnUpgradeFound(std::string name) const
{
    _displayManager.FoundItem(name);
    //save check state
}

void Randomizer::OnItemReceived(const int itemId) const
{
    const ItemData item = _itemRepository.SaveItem(itemId);
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
