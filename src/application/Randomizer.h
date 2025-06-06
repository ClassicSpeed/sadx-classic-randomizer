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
#include "../configuration/options/Options.h"
#include "structs/LocationData.h"
constexpr int SYNC_RATE = 10;

class Randomizer : public IOnFrame
{
public:
    static Randomizer& Init(Options& options, Settings& settings, GameStatus& gameStatus,
                            DisplayManager& displayManager,
                            CharacterManager& characterManager, WorldStateManager& menuManager,
                            ItemRepository& itemRepository, LocationRepository& locationRepository,
                            ArchipelagoMessenger& archipelagoMessenger, SaveFileManager& saveFileManager,
                            MusicManager& musicManager, ReactionManager& reactionManager)
    {
        if (_instance == nullptr)
            _instance = new Randomizer(options, settings, gameStatus, displayManager, characterManager, menuManager,
                                       itemRepository, locationRepository, archipelagoMessenger,
                                       saveFileManager, musicManager, reactionManager);
        return *_instance;
    }

    void OnFrame() override;

    void OnCheckFound(int checkId) const;
    void OnItemReceived(int64_t itemId) const;
    void MarkCheckedLocation(int64_t checkId) const;
    void OnCharacterLoaded() const;
    void OnCharacterSelectScreenLoaded() const;
    std::map<int, LocationData> GetCheckData() const;
    void OnConnected();
    void OnGameCompleted();
    void ShowStatusInformation(std::string information);
    void QueueNewItemMessage(std::string information);
    void QueueNewChatMessage(std::string information);
    std::vector<CapsuleLocationData> GetCapsules();
    std::vector<EnemyLocationData> GetEnemies();
    void ProcessDeath(const std::string& deathCause);
    void OnSync();
    void OnDeath();
    void ProcessRings(Sint16 amount);
    void ProcessTrapLink(std::string itemName, std::string message);
    void ResetItems();
    void OnCheckVersion(int serverVersion);
    void UpdateLevelEntrances();
    void DisplaySongName(int songId);
    int GetSongForId(int songId);
    int GetNewSongForId(int songId, int currentSongId);
    void MinorVersionMismatch(const std::string& serverVer, const std::string& modVer);
    void OnSaveFileLoaded();

private:
    Randomizer(Options& options, Settings& settings, GameStatus& gameStatus, DisplayManager& displayManager,
               CharacterManager& characterManager,
               WorldStateManager& menuManager,
               ItemRepository& itemRepository, LocationRepository& locationRepository,
               ArchipelagoMessenger& archipelagoMessenger, SaveFileManager& saveFileManager, MusicManager& musicManager,
               ReactionManager& reactionManager);
    inline static Randomizer* _instance = nullptr;
    Options& _options;
    Settings& _settings;
    GameStatus& _gameStatus;
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

    bool AreLastStoryRequirementsCompleted() const;

    int _syncTimer = 0;
};
