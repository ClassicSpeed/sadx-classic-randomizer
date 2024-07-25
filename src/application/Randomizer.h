#pragma once
#include "../pch.h"
#include "../output/locationRepository/LocationRepository.h"
#include "../output/displayManager/DisplayManager.h"
#include "../output/itemRepository/ItemRepository.h"
#include "../output/upgradeManager/UpgradeManager.h"
#include "../output/worldStateManager/WorldStateManager.h"
#include "../output/archipelagoMessenger/ArchipelagoMessenger.h"
#include "structs/LocationData.h"
#include "structs/Options.h"

class Randomizer
{
public:
    Randomizer(DisplayManager& displayManager, UpgradeManager& upgradeManager, WorldStateManager& menuManager,
               ItemRepository& itemRepository, LocationRepository& locationRepository,
               ArchipelagoMessenger archipelagoMessenger)
        : _displayManager(displayManager),
          _upgradeManager(upgradeManager),
          _worldStateManager(menuManager),
          _itemRepository(itemRepository),
          _locationRepository(locationRepository),
          _archipelagoMessenger(archipelagoMessenger)

    {
    }

    void OnCheckFound(int checkId) const;
    void OnItemReceived(int64_t itemId) const;
    void OnCharacterLoaded() const;
    void OnCharacterSelectScreenLoaded() const;
    std::map<int, LocationData> GetCheckData() const;
    void OnConnected();
    void OnGameCompleted();
    void ShowStatusInformation(std::string information);
    void QueueNewMessage(std::string information);
    void OnEmblemGoalSet(int emblemGoal);
    void SetMissions(Characters characters, int missions);
    std::vector<LifeBoxLocationData> GetLifeCapsules();

private:
    DisplayManager& _displayManager;
    UpgradeManager& _upgradeManager;
    WorldStateManager& _worldStateManager;
    ItemRepository& _itemRepository;
    LocationRepository& _locationRepository;
    ArchipelagoMessenger& _archipelagoMessenger;

    Options _options;
};
