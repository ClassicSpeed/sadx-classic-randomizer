#pragma once
#include <map>
#include "../../application/structs/ItemData.h"


class ItemRepository
{
public:
    ItemRepository();
    ItemData SetObtained(int itemId);
    ItemData GetItem(int itemId);
    std::map<int, ItemData> GetItems();

private:
    std::map<int, ItemData> _itemData;
};
