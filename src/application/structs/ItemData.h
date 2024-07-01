#pragma once
#include <string>
#include "SADXModLoader.h"

enum ItemType
{
    ItemUpgrade,
    ItemCharacter,
    ItemEmblem,
    ItemUnknown
};

struct ItemData
{
    ItemData() : adress(0), obtained(false), type(ItemUnknown),
                 displayName(std::string("Unknown"))
    {
    }

    ItemData(const int adress, ItemType type, std::string displayName) : adress(adress), type(type), obtained(false),
                                                                displayName(displayName)
    {
    }

    
    int adress;
    ItemType type;
    bool obtained;
    std::string displayName;
};
