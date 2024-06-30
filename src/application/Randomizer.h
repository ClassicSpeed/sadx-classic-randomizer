#pragma once
#include <string>
#include "SADXModLoader.h"
#include "../output/displayManager/DisplayManager.h"
#include "../output/itemRepository/ItemRepository.h"
#include "../output/UpgradeManager/UpgradeManager.h"

class Randomizer
{
public:
    Randomizer(DisplayManager& displayManager, UpgradeManager& upgradeManager, ItemRepository& itemRepository)
        : _displayManager(displayManager),
          _upgradeManager(upgradeManager),
          _itemRepository(itemRepository)
    {
    }

    void OnUpgradeFound(std::string name) const;
    void OnItemReceived(int itemId) const;
    void OnCharacterLoaded() const;

private:
    DisplayManager& _displayManager;
    UpgradeManager& _upgradeManager;
    ItemRepository& _itemRepository;
};
