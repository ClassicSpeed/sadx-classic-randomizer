#pragma once
#include <map>
#include "../../application/structs/ItemData.h"


class ItemRepository
{
public:
    ItemRepository();
    ItemData SetObtained(int64_t itemId);
    ItemData GetItem(int itemId);
    std::map<int64_t, ItemData> GetItems();
    int AddEmblem();
    int GetEmblemCount();

private:
    std::map<int64_t, ItemData> _itemData;
    int _emblemCount = 0;
};
