#pragma once
#include "../pch.h"
#include "../output/locationRepository/LocationRepository.h"
#include "../output/displayManager/DisplayManager.h"
#include "../output/itemRepository/ItemRepository.h"
#include "../output/characterManager/CharacterManager.h"
#include "../output/worldStateManager/WorldStateManager.h"
#include "../output/archipelagoMessenger/ArchipelagoMessenger.h"
#include "../output/saveFileManager/SaveFileManager.h"
#include "../output/musicManager/MusicManager.h"
#include "../output/reactionManager/ReactionManager.h"
#include "../configuration/Options.h"
#include "structs/LocationData.h"
#include "structs/Options.h"

class Randomizer
{
public:
    Randomizer(Options& options, DisplayManager& displayManager, CharacterManager& characterManager,
               WorldStateManager& menuManager,
               ItemRepository& itemRepository, LocationRepository& locationRepository,
               ArchipelagoMessenger& archipelagoMessenger, SaveFileManager& saveFileManager, MusicManager& musicManager, ReactionManager& reactionManager)
        : _options(options), _displayManager(displayManager),
          _characterManager(characterManager),
          _worldStateManager(menuManager),
          _itemRepository(itemRepository),
          _locationRepository(locationRepository),
          _archipelagoMessenger(archipelagoMessenger),
          _saveFileManager(saveFileManager), _musicManager(musicManager), _reactionManager(reactionManager),_deathPending(false)

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
    void QueueNewItemMessage(std::string information);
    void QueueNewChatMessage(std::string information);
    std::vector<CapsuleLocationData> GetCapsules();
    std::vector<EnemyLocationData> GetEnemies();
    void ProcessDeath(const std::string& deathCause);
    void OnPlayingFrame();
    void OnSync();
    void OnDeath();
    void ProcessRings(Sint16 amount);
    void ProcessTrapLink(std::string itemName, std::string message);
    void ResetItems();
    void SetAutoStartMissions(int autoStartMissions);
    void OnCheckVersion(int serverVersion);
    void SetStartingCharacter(int startingCharacterIndex);
    void UpdateLevelEntrances(LevelEntrances levelEntrances);

    void SetReverseControlTrapDuration(int reverseControlTrapDuration);
    void SetTrapsOnAdventureFields(bool trapsOnAdventureFields);
    void SetTrapsOnBossFights(bool trapsOnBossFights);
    void SetTrapsOnPerfectChaosFight(bool trapsOnPerfectChaosFight);
    void SetSuperSonicModRunning(bool isModRunning);
    void SetSendDeathLinkChance(int sendDeathLinkChance);
    void SetReceiveDeathLinkChance(int receiveDeathLinkChance);
    void DisplaySongName(int songId);
    int GetSongForId(int songId);
    int GetNewSongForId(int songId, int currentSongId);

private:
    Options& _options;
    DisplayManager& _displayManager;
    CharacterManager& _characterManager;
    WorldStateManager& _worldStateManager;
    ItemRepository& _itemRepository;
    LocationRepository& _locationRepository;
    ArchipelagoMessenger& _archipelagoMessenger;
    SaveFileManager& _saveFileManager;
    MusicManager& _musicManager;
    ReactionManager& _reactionManager;

    std::string _pendingDeathCause;
    bool _deathPending;

    float _deathLinkCooldown = 5.0f;
    std::clock_t _deathLinkCooldownTimer = -1;

    float _trapLinkCooldown = 5.0f;
    std::clock_t _trapLinkCooldownTimer = -1;

    int _sendDeathLinkChance = 100;
    int _receiveDeathLinkChance = 100;

    bool _superSonicModRunning = false;

    
    bool AreLastStoryRequirementsCompleted() const;

   
};
