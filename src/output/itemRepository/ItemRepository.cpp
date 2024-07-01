#include "ItemRepository.h"
#include "SADXModLoader.h"

ItemRepository::ItemRepository()
{
    _itemData[0] = ItemData(Upgrades_JetAnklet, ItemUpgrade, "Tails's Jet Anklet");
    _itemData[1] = ItemData(Upgrades_RhythmBadge, ItemUpgrade, "Tails's Rhythm Badge");
    _itemData[2] = ItemData(EventFlags_SonicUnlockedAdventure, ItemCharacter, "Sonic's Story");
    _itemData[3] = ItemData(EventFlags_GammaUnlockedAdventure, ItemCharacter, "Gamma's Story");
    _itemData[4] = ItemData(EventFlags_BigUnlockedAdventure, ItemCharacter, "Big's Story");
    _itemData[5] = ItemData(EventFlags_TailsUnlockedAdventure, ItemCharacter, "Tails's Story");

    _itemData[2].obtained = true;
    _itemData[4].obtained = true;
}


ItemData ItemRepository::SetObtained(const int itemId)
{
    _itemData[itemId].obtained = true;
    return _itemData[itemId];
}

ItemData ItemRepository::GetItem(const int itemId)
{
    return _itemData[itemId];
}


std::map<int, ItemData> ItemRepository::GetItems()
{
    return _itemData;
}
