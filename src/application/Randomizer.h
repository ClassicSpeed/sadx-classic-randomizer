#pragma once
#include "../pch.h"
#include "../output/locationRepository/LocationRepository.h"
#include "../output/displayManager/DisplayManager.h"
#include "../output/itemRepository/ItemRepository.h"
#include "../output/characterManager/CharacterManager.h"
#include "../output/worldStateManager/WorldStateManager.h"
#include "../output/archipelagoMessenger/ArchipelagoMessenger.h"
#include "structs/LocationData.h"
#include "structs/Options.h"

class Randomizer
{
public:
    Randomizer(DisplayManager& displayManager, CharacterManager& characterManager, WorldStateManager& menuManager,
               ItemRepository& itemRepository, LocationRepository& locationRepository,
               ArchipelagoMessenger& archipelagoMessenger)
        : _displayManager(displayManager),
          _characterManager(characterManager),
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
    void SetStatingArea(StartingArea startingArea);
    void SetMissions(Characters characters, int missions);
    void SetDeathLink(bool deathLinkActive);
    void SetRingLink(bool ringLinkActive);
    void SetRingLoss(RingLoss ringLoss);
    Options GetOptions() const;
    std::vector<LifeBoxLocationData> GetLifeCapsules();
    void ProcessDeath(const std::string& deathCause);
    void OnPlayingFrame();
    void OnSync();
    void OnDeath();
    void ProcessRings(Sint16 amount);

private:
    DisplayManager& _displayManager;
    CharacterManager& _characterManager;
    WorldStateManager& _worldStateManager;
    ItemRepository& _itemRepository;
    LocationRepository& _locationRepository;
    ArchipelagoMessenger& _archipelagoMessenger;

    Options _options;
    std::string _pendingDeathCause;
    bool _deathPending;
    bool _ignoreNextDeath = false;
};
