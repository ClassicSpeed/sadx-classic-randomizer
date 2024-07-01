#pragma once
#include <string>
#include "SADXModLoader.h"
#include "../output/checkRepository/CheckRepository.h"
#include "../output/displayManager/DisplayManager.h"
#include "../output/itemRepository/ItemRepository.h"
#include "../output/upgradeManager/UpgradeManager.h"
#include "../output/characterSelectionManager/CharacterSelectionManager.h"
#include "structs/CheckData.h"

class Randomizer
{
public:
    Randomizer(DisplayManager& displayManager, UpgradeManager& upgradeManager, CharacterSelectionManager& characterSelectionManager,ItemRepository& itemRepository, CheckRepository& checkRepository)
        : _displayManager(displayManager),
          _upgradeManager(upgradeManager),
          _characterSelectionManager(characterSelectionManager),
          _itemRepository(itemRepository),
          _checkRepository(checkRepository)
    {
    }

    void OnUpgradeFound(int checkId) const;
    void OnItemReceived(int itemId) const;
    void OnCharacterLoaded() const;
    void OnCharacterSelectScreenLoaded() const;
    std::map<int, CheckData> GetCheckData() const;

private:
    DisplayManager& _displayManager;
    UpgradeManager& _upgradeManager;
    CharacterSelectionManager& _characterSelectionManager;
    ItemRepository& _itemRepository;
    CheckRepository& _checkRepository;
};
