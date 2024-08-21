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
          _archipelagoMessenger(archipelagoMessenger), _deathPending(false)

    {
        _displayManager.UpdateChecks(locationRepository.GetLocations());
    }

    void OnCheckFound(int checkId) const;
    void OnItemReceived(int64_t itemId) const;
    void MarkCheckedLocation(int64_t checkId) const;
    void OnCharacterLoaded() const;
    void OnCharacterSelectScreenLoaded() const;
    std::map<int, LocationData> GetCheckData() const;
    void OnConnected(std::string playerName);
    void OnGameCompleted();
    void ShowStatusInformation(std::string information);
    void QueueNewMessage(std::string information);
    void OnGoalSet(Goal goal);
    void OnEmblemGoalSet(int emblemGoal);
    void SetCharacterStatingArea(Characters characters, StartingArea startingArea);
    void SetPlayableCharacter(Characters character, bool playable);
    void SetActionStageMissions(Characters characters, int missions);
    void SetCharacterLifeSanity(Characters character, bool characterLifeSanity);
    void SetDeathLink(bool deathLinkActive);
    void SetRingLink(bool ringLinkActive);
    void SetHardRingLink(bool hardRingLinkActive);
    void SetRingLoss(RingLoss ringLoss);
    void SetSublevelChecks(bool sublevelChecks);
    void SetBossChecks(bool bossChecks);
    void SetUnifyChaos4(bool unifyChaos4);
    void SetUnifyChaos6(bool unifyChaos6);
    void SetUnifyEggHornet(bool unifyEggHornet);
    Options GetOptions() const;
    std::vector<LifeBoxLocationData> GetLifeCapsules();
    void ProcessDeath(const std::string& deathCause);
    void OnPlayingFrame();
    void OnSync();
    void OnDeath();
    void ProcessRings(Sint16 amount);
    void OnLifeSanitySet(bool lifeSanity);
    void OnPinballLifeCapsulesSet(bool pinballLifeCapsules);
    void ResetItems();

private:
    bool AreLastStoryRequirementsCompleted() const;
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
