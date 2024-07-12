#pragma once
#include "../../pch.h"
#include <string>

enum ItemType
{
    ItemUpgrade,
    ItemCharacter,
    ItemEmblem,
    ItemKey,
    ItemUnknown
};

struct ItemData
{
    ItemData() : upgrade(static_cast<Upgrades>(0)), eventFlags({}), type(ItemUnknown), obtained(false),
                 displayName(std::string("Unknown"))
    {
    }

    ItemData(const Upgrades upgrade, const std::vector<StoryFlags>& eventFlags, const ItemType type,
             const bool obtained, const std::string& displayName)
        : upgrade(upgrade),
          eventFlags(eventFlags),
          type(type),
          obtained(obtained),
          displayName(displayName)
    {
    }

    static ItemData CharacterItem(const StoryFlags unlockFlag, const std::string& displayName)
    {
        return ItemData(static_cast<Upgrades>(0), {unlockFlag}, ItemCharacter, false, displayName);
    }

    static ItemData UpgradeItem(const Upgrades upgrade, const std::string& displayName)
    {
        return ItemData(upgrade, {}, ItemUpgrade, false, displayName);
    }

    static ItemData KeyItem(const std::vector<StoryFlags>& eventFlags, const std::string& displayName)
    {
        return ItemData(static_cast<Upgrades>(0), {eventFlags}, ItemKey, false, displayName);
    }

    static ItemData EmblemItem(const std::string& displayName)
    {
        return ItemData(static_cast<Upgrades>(0), {}, ItemEmblem, false, displayName);
    }


    Upgrades upgrade;
    std::vector<StoryFlags> eventFlags;
    ItemType type;
    bool obtained;
    std::string displayName;
};
