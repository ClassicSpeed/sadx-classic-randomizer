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
    std::map<int, ItemData> items = _itemRepository.GetItems();
    for (auto item : items)
    {
        if (item.second.obtained)
        {
            //TODO: Remove upgrades that has the check but not the item
            _upgradeManager.GiveUpgrade(item.second.upgrade);
        }
    }
}
