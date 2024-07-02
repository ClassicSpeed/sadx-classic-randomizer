#pragma once
#include <string>
#include "SADXModLoader.h"
#include "../output/locationRepository/LocationRepository.h"
#include "../output/displayManager/DisplayManager.h"
#include "../output/itemRepository/ItemRepository.h"
#include "../output/upgradeManager/UpgradeManager.h"
#include "../output/characterSelectionManager/CharacterSelectionManager.h"
#include "../output/archipelagoMessenger/ArchipelagoMessenger.h"
#include "structs/LocationData.h"

class Randomizer
{
public:
    Randomizer(DisplayManager& displayManager, UpgradeManager& upgradeManager, CharacterSelectionManager& characterSelectionManager,ItemRepository& itemRepository, LocationRepository& checkRepository, ArchipelagoMessenger archipelagoMessenger)
        : _displayManager(displayManager),
          _upgradeManager(upgradeManager),
          _characterSelectionManager(characterSelectionManager),
          _itemRepository(itemRepository),
          _checkRepository(checkRepository),
          _archipelagoMessenger(archipelagoMessenger)
    
    {
    }

    void OnCheckFound(int checkId) const;
    void OnItemReceived(int64_t itemId) const;
    void OnCharacterLoaded() const;
    void OnCharacterSelectScreenLoaded() const;
    std::map<int, LocationData> GetCheckData() const;

private:
    DisplayManager& _displayManager;
    UpgradeManager& _upgradeManager;
    CharacterSelectionManager& _characterSelectionManager;
    ItemRepository& _itemRepository;
    LocationRepository& _checkRepository;
    ArchipelagoMessenger& _archipelagoMessenger;
};
