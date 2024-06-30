﻿#include "ItemRepository.h"
#include "SADXModLoader.h"

ItemRepository::ItemRepository() 
{
    _itemData[0] = ItemData(Upgrades_JetAnklet,"Tails's Jet Anklet");
    _itemData[1] = ItemData(Upgrades_RhythmBadge,"Tails's Rhythm Badge");
}


ItemData ItemRepository::SaveItem(int itemId)
{
    _itemData[itemId].obtained = true;
    return _itemData[itemId];
}

std::map<int, ItemData> ItemRepository::GetItems()
{
    return _itemData;
}
