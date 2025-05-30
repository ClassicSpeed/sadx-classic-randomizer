#pragma once
#include <map>
#include "../../application/structs/ItemData.h"
#include "../../application/structs/UnlockStatus.h"



class ItemRepository
{
public:
    static ItemRepository& Init()
    {
        if (_instance == nullptr)
            _instance = new ItemRepository();
        return *_instance;
    }
    bool SetObtained(int64_t itemId);
    ItemData GetItem(int64_t itemId);
    std::map<int64_t, ItemData> GetItems();
    int AddEmblem();
    int GetEmblemCount();
    UnlockStatus GetUnlockStatus();
    void ResetItems();
    FillerType GetFillerFromName(const std::string& string);

private:
    ItemRepository();
    inline static ItemRepository* _instance = nullptr;
    
    int GetSavedItemReceived();
    void UpdateItemsReceived(int itemsReceived);
    std::map<int64_t, ItemData> _itemData;
    int _emblemCount = 0;

    int _itemsReceived = 0;
};
