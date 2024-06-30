#pragma once
#include <map>
#include <string>
#include "SADXModLoader.h"


struct ItemData
{
    ItemData() : upgrade(static_cast<Upgrades>(0x00)), obtained(false),
                 displayName(std::string("Unknown"))
    {
    }

    ItemData(const Upgrades upgrade, std::string displayName) : upgrade(upgrade), obtained(false),
                                                                displayName(displayName)
    {
    }

    Upgrades upgrade;
    bool obtained;
    std::string displayName;
};


class ItemRepository
{
public:
    ItemRepository();
    ItemData SaveItem(int itemId);
    std::map<int, ItemData> GetItems();

private:
    std::map<int, ItemData> _itemData;
};
