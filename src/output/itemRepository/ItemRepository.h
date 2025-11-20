#pragma once
#include <map>
#include "../../configuration/gameStatus/GameStatus.h"
#include "../../application/structs/ItemData.h"


class ItemRepository
{
public:
    static ItemRepository& Init(GameStatus& gameStatus)
    {
        if (_instance == nullptr)
            _instance = new ItemRepository(gameStatus);
        return *_instance;
    }

    bool SetObtained(int64_t itemId);
    ItemData GetItem(int64_t itemId);
    std::map<int64_t, ItemData> GetItems();
    int AddEmblem();
    int GetEmblemCount();
    void UpdateUnlockStatus();
    void ResetItems();
    FillerType GetFillerFromName(const std::string& trapName);

private:
    explicit ItemRepository(GameStatus& gameStatus);
    inline static ItemRepository* _instance = nullptr;
    GameStatus& _gameStatus;

    int GetSavedItemReceived();
    void UpdateItemsReceived(int itemsReceived);
    std::map<int64_t, ItemData> _itemData;

    int _itemsReceived = 0;
};
