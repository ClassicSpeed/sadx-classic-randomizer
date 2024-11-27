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
    void PlayRandomVoiceForItem(const ItemData& item, const int64_t itemId) const;
    void OnItemReceived(int64_t itemId) const;
    void MarkCheckedLocation(int64_t checkId) const;
    void OnCharacterLoaded() const;
    void OnCharacterSelectScreenLoaded() const;
    std::map<int, LocationData> GetCheckData() const;
    void OnConnected(std::string playerName);
    void OnGameCompleted();
    void ShowStatusInformation(std::string information);
    void QueueNewMessage(std::string information);
    void OnEmblemGoalSet(int emblemGoal);
    void OnLevelGoalSet(int levelGoal);
    void OnMissionGoalSet(int missionGoal);
    void OnBossesGoalSet(int bossesGoal);
    void SetCharacterStatingArea(Characters characters, StartingArea startingArea);
    void SetPlayableCharacter(Characters character, bool playable);
    void SetActionStageMissions(Characters characters, int missions);
    void SetCharacterLifeSanity(Characters character, bool characterLifeSanity);
    void SetDeathLink(bool deathLinkActive);
    void SetRingLink(bool ringLinkActive);
    void SetCasinopolisRingLink(bool casinopolisRingLink);
    void SetHardRingLink(bool hardRingLinkActive);
    void SetRingLoss(RingLoss ringLoss);
    void SetSkyChaseChecks(bool skyChaseChecks);
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
    void SetMissionMode(int missionModeEnabled);
    void SetAutoStartMissions(int autoStartMissions);
    void OnCheckVersion(int serverVersion);
    void SetStartingCharacter(int startingCharacterIndex);
    void UpdateLevelEntrances(LevelEntrances levelEntrances);
    void UpdateMissionBlacklist(const std::vector<int>& missionBlacklist);
    void SetEntranceRandomizer(bool enableEntranceRandomizer);
    void SetCharacterVoiceReactions(bool eggmanCommentOnCharacterUnlock, bool currentCharacterCommentOnCharacterUnlock,
                                    bool unlockedCharacterCommentOnCharacterUnlock, bool eggmanCommentOnKeyItems,
                                    bool tikalCommentOnKeyItems,
                                    bool currentCharacterCommentOnKeyItems);
    void SetReverseControlTrapDuration(int reverseControlTrapDuration);
    void SetTrapsOnAdventureFields(bool trapsOnAdventureFields);
    void SetTrapsOnBossFights(bool trapsOnBossFights);
    void SetTrapsOnPerfectChaosFight(bool trapsOnPerfectChaosFight);
    void SetSuperSonicModRunning(bool isModRunning);
    void SetSendDeathLinkChance(int sendDeathLinkChance);
    void SetReceiveDeathLinkChance(int receiveDeathLinkChance);
    void OnGoalRequiresLevelsSet(bool goalRequiresLevels);
    void OnGoalRequiresChaosEmeraldsSet(bool goalRequiresChaosEmeralds);
    void OnGoalRequiresEmblems(bool goalRequiresEmblems);
    void OnGoalRequiresMissionsSet(bool goalRequiresMissions);
    void OnGoalRequiresBossesSet(bool goalRequiresBosses);

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

    float _deathLinkCooldown = 5.0f;
    std::clock_t _deathLinkCooldownTimer = -1;
    
    int _sendDeathLinkChance = 100;
    int _receiveDeathLinkChance = 100;


    bool _eggmanCommentOnCharacterUnlock = true;
    bool _currentCharacterCommentOnCharacterUnlock = true;
    bool _unlockedCharacterCommentOnCharacterUnlock = true;

    bool _eggmanCommentOnKeyItems = true;
    bool _tikalCommentOnKeyItems = true;
    bool _currentCharacterCommentOnKeyItems = true;
    bool _superSonicModRunning = false;
};
