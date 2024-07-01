#pragma once
#include <string>
#include "SADXModLoader.h"
#include "../output/checkRepository/CheckRepository.h"
#include "../output/displayManager/DisplayManager.h"
#include "../output/itemRepository/ItemRepository.h"
#include "../output/UpgradeManager/UpgradeManager.h"
#include "structs/CheckData.h"

class Randomizer
{
public:
    Randomizer(DisplayManager& displayManager, UpgradeManager& upgradeManager, ItemRepository& itemRepository, CheckRepository& checkRepository)
        : _displayManager(displayManager),
          _upgradeManager(upgradeManager),
          _itemRepository(itemRepository),
          _checkRepository(checkRepository)
    {
    }

    void OnUpgradeFound(int checkId) const;
    void OnItemReceived(int itemId) const;
    void OnCharacterLoaded() const;
    std::map<int, CheckData> GetCheckData() const;

private:
    DisplayManager& _displayManager;
    UpgradeManager& _upgradeManager;
    ItemRepository& _itemRepository;
    CheckRepository& _checkRepository;
};
