#pragma once
#include <map>
#include "../../application/structs/ItemData.h"
#include "../../application/structs/UnlockStatus.h"



class ItemRepository
{
public:
    ItemRepository();
    ItemData SetObtained(int64_t itemId);
    ItemData GetItem(int itemId);
    std::map<int64_t, ItemData> GetItems();
    int AddEmblem();
    int GetEmblemGoal() const;
    void SetEmblemGoal(int emblemGoal);
    int GetEmblemCount();
    UnlockStatus GetUnlockStatus();

private:
    std::map<int64_t, ItemData> _itemData;
    int _emblemCount = 0;
    int _emblemGoal = -1; 
};
