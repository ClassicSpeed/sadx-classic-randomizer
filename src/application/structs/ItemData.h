#pragma once
#include "../../pch.h"
#include <string>

enum ItemType
{
    ItemUpgrade,
    ItemCharacter,
    ItemEmblem,
    ItemUnknown
};

struct ItemData
{
    ItemData() : address(0), type(ItemUnknown), obtained(false),
                 displayName(std::string("Unknown"))
    {
    }

    ItemData(const int adress, ItemType type, std::string displayName) : address(adress), type(type), obtained(false),
                                                                         displayName(displayName)
    {
    }


    int address;
    ItemType type;
    bool obtained;
    std::string displayName;
};
