#include "Randomizer.h"

#include <random>

Randomizer::Randomizer(Options& options, Settings& settings, DisplayManager& displayManager,
                       CharacterManager& characterManager,
                       WorldStateManager& menuManager,
                       ItemRepository& itemRepository, LocationRepository& locationRepository,
                       ArchipelagoMessenger& archipelagoMessenger, SaveFileManager& saveFileManager,
                       MusicManager& musicManager, ReactionManager& reactionManager)
    : _options(options), _settings(settings), _displayManager(displayManager),
      _characterManager(characterManager),
      _worldStateManager(menuManager),
      _itemRepository(itemRepository),
      _locationRepository(locationRepository),
      _archipelagoMessenger(archipelagoMessenger),
      _saveFileManager(saveFileManager), _musicManager(musicManager), _reactionManager(reactionManager),
      _deathPending(false)

{
    _displayManager.UpdateChecks(locationRepository.GetLocations());
}

void Randomizer::OnCheckFound(const int checkId) const
{
    const LocationData check = _locationRepository.GetLocation(checkId);

    if (check.type == LocationUpgrade)
    {
        const ItemData item = _itemRepository.GetItem(check.originalItemId);
        if (!item.obtained)
            _characterManager.RemoveUpgrade(item.upgrade);
    }

    _locationRepository.SetLocationChecked(checkId);
    _archipelagoMessenger.CheckLocation(checkId);

    _displayManager.UpdateChecks(_locationRepository.GetLocations());
    _worldStateManager.UpdateChecks(_locationRepository.GetLocations());
    if (check.type == LocationLevel && check.levelMission == MISSION_C && _options.goalRequiresLevels)
    {
        const LevelStatus levelStatus = _locationRepository.GetLevelStatus(_options);
        _displayManager.UpdateLevelStatus(levelStatus);
        _displayManager.ShowGoalStatus();
        if (_options.levelGoal == levelStatus.levelsCompleted
            && AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }
    if (check.type == LocationMission && _options.goalRequiresMissions)
    {
        const MissionStatus missionStatus = _locationRepository.GetMissionStatus(_options);
        _displayManager.UpdateMissionStatus(missionStatus);
        _displayManager.ShowGoalStatus();
        if (_options.missionGoal == missionStatus.missionsCompleted
            && AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }
    if (check.type == LocationBossFight && _options.goalRequiresBosses)
    {
        const BossesStatus bossesStatus = _locationRepository.GetBossesStatus(_options);
        _displayManager.UpdateBossesStatus(bossesStatus);
        _displayManager.ShowGoalStatus();
        if (_options.bossesGoal == bossesStatus.bossesCompleted
            && AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }
    if (check.type == LocationChaoRace && _options.goalRequiresChaoRaces)
    {
        const ChaoStatus chaoStatus = _locationRepository.GetChaoStatus();
        _displayManager.UpdateChaoStatus(chaoStatus);
        _displayManager.ShowGoalStatus();
        if (chaoStatus.racesTotal >= chaoStatus.racesCompleted && AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }
}

void Randomizer::MarkCheckedLocation(const int64_t checkId) const
{
    LocationData locationData = _locationRepository.SetLocationChecked(checkId);
    if (locationData.type == LocationMission)
        _saveFileManager.SetMissionCompleted(locationData.missionNumber);


    //TODO: Unify?
    const LevelStatus levelStatus = _locationRepository.GetLevelStatus(_options);
    _displayManager.UpdateLevelStatus(levelStatus);
    const MissionStatus missionStatus = _locationRepository.GetMissionStatus(_options);
    _displayManager.UpdateMissionStatus(missionStatus);
    const BossesStatus bossesStatus = _locationRepository.GetBossesStatus(_options);
    _displayManager.UpdateBossesStatus(bossesStatus);
    const ChaoStatus chaoStatus = _locationRepository.GetChaoStatus();
    _displayManager.UpdateChaoStatus(chaoStatus);
    _displayManager.UpdateChecks(_locationRepository.GetLocations());
    _worldStateManager.UpdateChecks(_locationRepository.GetLocations());
}


void Randomizer::OnItemReceived(const int64_t itemId) const
{
    const bool ignore = _itemRepository.SetObtained(itemId);
    if (ignore)
        return;

    const ItemData item = _itemRepository.GetItem(itemId);

    if (item.type == ItemUpgrade)
        _characterManager.GiveUpgrade(item.upgrade);
    else if (item.type == ItemCharacter || item.type == ItemKey)
        _worldStateManager.SetEventFlags(item.eventFlags);
    else if (item.type == ItemEmblem)
        _itemRepository.AddEmblem();
    else if (item.type == ItemFiller)
    {
        _characterManager.GiveFillerItem(item.fillerType, false);
        if (_options.trapLinkActive && !IsJunkFiller(item.fillerType))
        {
            _archipelagoMessenger.SendTrapLink(item.displayName, _settings.playerName);
            _displayManager.QueueItemMessage("Linked " + item.displayName + " sent");
        }
    }

    const UnlockStatus unlockStatus = _itemRepository.GetUnlockStatus();
    _characterManager.UpdateUnlockStatus(unlockStatus);
    _displayManager.UpdateUnlockStatus(unlockStatus);
    _worldStateManager.UpdateUnlockStatus(unlockStatus);
    _reactionManager.UpdateUnlockStatus(unlockStatus);

    if (item.type == ItemChaosEmerald)
    {
        _displayManager.ShowGoalStatus();

        if (this->_settings._superSonicModRunning)
        {
            if (_itemRepository.GetUnlockStatus().GotAllChaosEmeralds())
            {
                SetEventFlag(static_cast<EventFlags>(FLAG_SUPERSONIC_COMPLETE));
                _displayManager.QueueItemMessage("You can now transform into Super Sonic!");
            }
        }

        if (AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }

    else if (item.type == ItemEmblem)
    {
        _displayManager.ShowGoalStatus();
        if (unlockStatus.currentEmblems == _options.emblemGoal && AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }

    _reactionManager.PlayRandomVoiceForItem(item, itemId);
}

void Randomizer::ResetItems()
{
    _itemRepository.ResetItems();
    const UnlockStatus unlockStatus = _itemRepository.GetUnlockStatus();
    _characterManager.UpdateUnlockStatus(unlockStatus);
    _displayManager.UpdateUnlockStatus(unlockStatus);
    _worldStateManager.UpdateUnlockStatus(unlockStatus);
}


void Randomizer::OnCheckVersion(int serverVersion)
{
    const int serverMajor = serverVersion / 100;
    const int serverMinor = (serverVersion / 10) % 10;
    const int serverPatch = serverVersion % 10;

    const std::string modVer = std::to_string(SADX_AP_VERSION_MAJOR)
        + "." + std::to_string(SADX_AP_VERSION_MINOR)
        + "." + std::to_string(SADX_AP_VERSION_PATCH);
    const std::string serverVer = std::to_string(serverMajor)
        + "." + std::to_string(serverMinor)
        + "." + std::to_string(serverPatch);
    if (serverMajor != SADX_AP_VERSION_MAJOR || serverMinor != SADX_AP_VERSION_MINOR)
    {
        std::string errorMessage = "Error: Major version mismatch!\n\nServer: v" + serverVer + "\nMod: v" + modVer;
        MessageBox(WindowHandle, std::wstring(errorMessage.begin(), errorMessage.end()).c_str(),
                   L"SADX Archipelago Error: Version mismatch", MB_OK | MB_ICONERROR);
        exit(0);
    }
    if (serverPatch != SADX_AP_VERSION_PATCH)
    {
        _displayManager.QueueItemMessage("Warning: version mismatch! Server: v" + serverVer + " Mod: v" + modVer);
    }
}


//TODO: Move to OnConnect
void Randomizer::SetStartingCharacter(const int startingCharacterIndex)
{
    _characterManager.SetStartingCharacter(startingCharacterIndex);
}

//TODO: Move to OnConnect
void Randomizer::UpdateLevelEntrances()
{
    if (_options.levelEntrancesMap.empty())
        return;

    LevelEntrances levelEntrances;

    for (const auto& [first, second] : _options.levelEntrancesMap)
    {
        const auto levelEntrance = static_cast<Levels>(first);
        const auto actualLevel = static_cast<Levels>(second);
        levelEntrances.addRelationship(levelEntrance, actualLevel);
    }

    _worldStateManager.UpdateLevelEntrances(levelEntrances);

    for (const auto& location : _locationRepository.GetLocations())
    {
        if (location.second.type == LocationLevel && location.second.checked && location.second.level >=
            LevelIDs_EmeraldCoast && location.second.level <= LevelIDs_HotShelter)
            _displayManager.UpdateVisitedLevels(_worldStateManager.GetVisitedLevels(location.second.level));
    }
}

//TODO: Later, Move to Goal/Status Manager?
bool Randomizer::AreLastStoryRequirementsCompleted() const
{
    bool levelsCompleted = true;
    bool emblemsCompleted = true;
    bool chaosEmeraldsCompleted = true;
    bool missionsCompleted = true;
    bool bossesCompleted = true;
    bool chaoRacesCompleted = true;

    if (_options.goalRequiresLevels)
        levelsCompleted = _locationRepository.GetLevelStatus(_options).levelsCompleted >= _options.levelGoal;

    if (_options.goalRequiresEmblems)
        emblemsCompleted = _itemRepository.GetEmblemCount() >= _options.emblemGoal;

    if (_options.goalRequiresMissions)
        missionsCompleted = _locationRepository.GetMissionStatus(_options).missionsCompleted >= _options.missionGoal;

    if (_options.goalRequiresChaosEmeralds)
        chaosEmeraldsCompleted = _itemRepository.GetUnlockStatus().GotAllChaosEmeralds();

    if (_options.goalRequiresBosses)
        bossesCompleted = _locationRepository.GetBossesStatus(_options).bossesCompleted >= _options.bossesGoal;

    if (_options.goalRequiresChaoRaces)
        chaoRacesCompleted = _locationRepository.GetChaoStatus().racesCompleted >= _locationRepository.GetChaoStatus().
            racesTotal;

    return levelsCompleted && emblemsCompleted && chaosEmeraldsCompleted && missionsCompleted && bossesCompleted &&
        chaoRacesCompleted;
}


void Randomizer::OnCharacterLoaded() const
{
    _characterManager.RemoveStatusEffects();
    for (const auto& item : _itemRepository.GetItems())
    {
        if (item.second.type != ItemUpgrade)
            continue;

        if (item.second.obtained)
            _characterManager.GiveUpgrade(item.second.upgrade);
        else
            _characterManager.RemoveUpgrade(item.second.upgrade);
    }
    if (CurrentLevel >= LevelIDs_EmeraldCoast && CurrentLevel <= LevelIDs_HotShelter)
        _displayManager.UpdateVisitedLevels(_worldStateManager.GetVisitedLevels(CurrentLevel));
}


void Randomizer::OnCharacterSelectScreenLoaded() const
{
    for (const auto& item : _itemRepository.GetItems())
    {
        if (item.second.type == ItemEmblem)
        {
            if (AreLastStoryRequirementsCompleted())
                _worldStateManager.UnlockSuperSonic();
        }

        if (item.second.type == ItemCharacter && item.second.obtained)
            _worldStateManager.SetEventFlags(item.second.eventFlags);
    }
}

//TODO: Later, maybe we can remove these calls/move to status
std::map<int, LocationData> Randomizer::GetCheckData() const
{
    return _locationRepository.GetLocations();
}

std::vector<CapsuleLocationData> Randomizer::GetCapsules()
{
    return _locationRepository.GetCapsuleLocations();
}

std::vector<EnemyLocationData> Randomizer::GetEnemies()
{
    return _locationRepository.GetEnemyLocations();
}


//TODO: Move to helper, make generic name
bool CheckDeathLinkChance(const int chance)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    return dis(gen) <= chance;
}

void Randomizer::ProcessDeath(const std::string& deathCause)
{
    const double timePassed = (std::clock() - _deathLinkCooldownTimer) / static_cast<double>(CLOCKS_PER_SEC);
    if (_deathLinkCooldownTimer < 0 || timePassed > _deathLinkCooldown)
    {
        if (!CheckDeathLinkChance(_options.receiveDeathLinkChance))
        {
            _displayManager.QueueItemMessage("You survived a Death Link!");
            return;
        }

        //Processing a death won't restart the cooldown timer
        _pendingDeathCause = deathCause;
        _deathPending = true;
    }
}

//Move to Own Manager
void Randomizer::OnFrame()
{
    if (_syncTimer == 0)
        this->OnSync();
    else
        _syncTimer--;

    if (Current_CharObj2 == nullptr || EntityData1Ptrs[0] == nullptr)
        return;
    if (!_options.deathLinkActive)
        return;
    if (!_deathPending)
        return;
    if (GameMode != GameModes_Mission)
        return;
    if (GameState != MD_GAME_MAIN)
        return;
    if (!IsControllerEnabled(0))
        return;


    const double timePassed = (std::clock() - _deathLinkCooldownTimer) / static_cast<double>(CLOCKS_PER_SEC);

    if (_deathLinkCooldownTimer < 0 || timePassed > _deathLinkCooldown)
    {
        _deathLinkCooldownTimer = std::clock();
        _characterManager.KillPlayer();
        _displayManager.QueueItemMessage(_pendingDeathCause);
        _pendingDeathCause.clear();
        _deathPending = false;
    }
}

void Randomizer::OnSync()
{
    _syncTimer = SYNC_RATE;
    if (!_options.ringLinkActive)
        return;
    const RingDifference ringDifference = _characterManager.GetRingDifference();

    _archipelagoMessenger.SendRingUpdate(ringDifference.ringDifference);
    _archipelagoMessenger.SendHardRingUpdate(ringDifference.hardRingDifference);
}


//TODO: Move to Own Manager
void Randomizer::OnDeath()
{
    if (!_options.deathLinkActive)
        return;
    if (DemoPlaying > 0)
        return;

    const double timePassed = (std::clock() - _deathLinkCooldownTimer) / static_cast<double>(CLOCKS_PER_SEC);

    if (_deathLinkCooldownTimer < 0 || timePassed > _deathLinkCooldown)
    {
        _deathLinkCooldownTimer = std::clock();

        if (!CheckDeathLinkChance(_options.sendDeathLinkChance))
        {
            _displayManager.QueueItemMessage("Death Link not sent!");
            return;
        }
        _archipelagoMessenger.SendDeath(_settings.playerName);
        _displayManager.QueueItemMessage("Death Sent");
    }
}

void Randomizer::ProcessRings(const Sint16 amount)
{
    _characterManager.ProcessRings(amount);
}

void Randomizer::ProcessTrapLink(std::string itemName, std::string message)
{
    FillerType filler = _itemRepository.GetFillerFromName(itemName);

    if (!_options.IsTrapEnabled(filler))
        return;

    const double timePassed = (std::clock() - _trapLinkCooldownTimer) / static_cast<double>(CLOCKS_PER_SEC);
    if (_trapLinkCooldownTimer >= 0 && timePassed <= _trapLinkCooldown)
        return;

    _trapLinkCooldownTimer = std::clock();
    _displayManager.QueueItemMessage(message);
    _characterManager.GiveFillerItem(filler, true);
}

void Randomizer::OnConnected()
{
    //Levels
    const LevelStatus levelStatus = _locationRepository.GetLevelStatus(_options);
    _displayManager.UpdateLevelStatus(levelStatus);

    //Missions
    const MissionStatus missionStatus = _locationRepository.GetMissionStatus(_options);
    _displayManager.UpdateMissionStatus(missionStatus);
    if (_options.autoStartMissions)
        _saveFileManager.StartAllMissions();

    // Bosses
    const BossesStatus bossesStatus = _locationRepository.GetBossesStatus(_options);
    _displayManager.UpdateBossesStatus(bossesStatus);

    //Chao
    const ChaoStatus chaoStatus = _locationRepository.GetChaoStatus();
    _displayManager.UpdateChaoStatus(chaoStatus);

    if (!_options.goalRequiresChaosEmeralds)
        SetEventFlag(static_cast<EventFlags>(FLAG_SUPERSONIC_COMPLETE));

    // Music
    _worldStateManager.MarkBlacklistedMissionsAsCompleted(_options.missionBlacklist);
    _musicManager.RandomizeMusic();

    //Starting Character
    _characterManager.SetStartingCharacter(_options.startingCharacterIndex);

    // Update Level Entrances

    UpdateLevelEntrances();

    _archipelagoMessenger.UpdateTags(_options);
    _displayManager.SetConnected();
    _displayManager.QueueItemMessage("Connected to Archipelago");
}

void Randomizer::OnGameCompleted()
{
    _displayManager.QueueItemMessage("Victory!");
    _archipelagoMessenger.GameCompleted();
}

void Randomizer::ShowStatusInformation(std::string information)
{
    _displayManager.ShowStatusInformation(information);
}

void Randomizer::QueueNewItemMessage(std::string information)
{
    _displayManager.QueueItemMessage(information);
}

void Randomizer::QueueNewChatMessage(std::string information)
{
    _displayManager.QueueChatMessage(information);
}

int Randomizer::GetSongForId(const int songId)
{
    return _musicManager.GetSongForId(songId);
}

int Randomizer::GetNewSongForId(const int songId, const int currentSongId)
{
    return _musicManager.GetNewSongForId(songId, currentSongId);
}

void Randomizer::MinorVersionMismatch(const std::string& serverVer, const std::string& modVer)
{
    _displayManager.QueueItemMessage("Warning: version mismatch! Server: v" + serverVer + " Mod: v" + modVer);
}

void Randomizer::OnSaveFileLoaded()
{
    _saveFileManager.OnSaveFileLoaded();
}

void Randomizer::DisplaySongName(const int songId)
{
    //TODO: Move logic to displayManager
    if (_settings.showSongName == ShowSongNameAlwaysOff)
        return;

    if (_settings.showSongName == ShowSongNameWithSongShuffle && _options.musicShuffle == MusicShuffleNone)
        return;

    if (_settings.showSongNameForType == ShowSongNameForTypeOnlyActionLevels)
        if (CurrentLevel < LevelIDs_EmeraldCoast || CurrentLevel > LevelIDs_HotShelter)
            return;

    const auto* song = _musicManager.FindSongById(songId);
    if (song != nullptr)
        _displayManager.ShowSongName("~ " + song->name + " ~");
}
