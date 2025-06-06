#include "Randomizer.h"


Randomizer::Randomizer(Options& options, Settings& settings, GameStatus& gameStatus, DisplayManager& displayManager,
                       CharacterManager& characterManager,
                       WorldStateManager& menuManager,
                       ItemRepository& itemRepository, LocationRepository& locationRepository,
                       ArchipelagoMessenger& archipelagoMessenger, SaveFileManager& saveFileManager,
                       MusicManager& musicManager, ReactionManager& reactionManager)
    : _options(options), _settings(settings), _gameStatus(gameStatus), _displayManager(displayManager),
      _characterManager(characterManager),
      _worldStateManager(menuManager),
      _itemRepository(itemRepository),
      _locationRepository(locationRepository),
      _archipelagoMessenger(archipelagoMessenger),
      _saveFileManager(saveFileManager), _musicManager(musicManager), _reactionManager(reactionManager)

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
        _displayManager.ShowGoalStatus();
        if (_options.levelGoal == _gameStatus.levels.levelsCompleted
            && AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }
    if (check.type == LocationMission && _options.goalRequiresMissions)
    {
        _displayManager.ShowGoalStatus();
        if (_options.missionGoal == _gameStatus.missions.missionsCompleted
            && AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }
    if (check.type == LocationBossFight && _options.goalRequiresBosses)
    {
        _displayManager.ShowGoalStatus();
        if (_options.bossesGoal == _gameStatus.bosses.bossesCompleted
            && AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }
    if (check.type == LocationChaoRace && _options.goalRequiresChaoRaces)
    {
        _displayManager.ShowGoalStatus();
        if (_gameStatus.chao.racesTotal >= _gameStatus.chao.racesCompleted && AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }
}

void Randomizer::MarkCheckedLocation(const int64_t checkId) const
{
    LocationData locationData = _locationRepository.SetLocationChecked(checkId);
    if (locationData.type == LocationMission)
        _saveFileManager.SetMissionCompleted(locationData.missionNumber);

    //TODO: Weird, check if we can move the data to status
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
    if (item.type == ItemChaosEmerald)
    {
        _displayManager.ShowGoalStatus();

        if (this->_settings._superSonicModRunning)
        {
            if (_gameStatus.unlock.GotAllChaosEmeralds())
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
        if (_gameStatus.unlock.currentEmblems == _options.emblemGoal && AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }

    _reactionManager.PlayRandomVoiceForItem(item, itemId);
}

void Randomizer::ResetItems() const
{
    _itemRepository.ResetItems();
}

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
            _worldStateManager.UpdateVisitedLevels(location.second.level);
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
        levelsCompleted = _gameStatus.levels.levelsCompleted >= _options.levelGoal;

    if (_options.goalRequiresEmblems)
        emblemsCompleted = _itemRepository.GetEmblemCount() >= _options.emblemGoal;

    if (_options.goalRequiresMissions)
        missionsCompleted = _gameStatus.missions.missionsCompleted >= _options.missionGoal;

    if (_options.goalRequiresChaosEmeralds)
        chaosEmeraldsCompleted = _gameStatus.unlock.GotAllChaosEmeralds();

    if (_options.goalRequiresBosses)
        bossesCompleted = _gameStatus.bosses.bossesCompleted >= _options.bossesGoal;

    if (_options.goalRequiresChaoRaces)
        chaoRacesCompleted = _gameStatus.chao.racesCompleted >= _gameStatus.chao.racesTotal;

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
        _worldStateManager.UpdateVisitedLevels(CurrentLevel);
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



void Randomizer::OnConnected()
{
    _locationRepository.ResetLocations();

    //Missions
    if (_options.autoStartMissions)
        _saveFileManager.StartAllMissions();


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
    const auto* song = _musicManager.FindSongById(songId);
    if (song != nullptr)
        _displayManager.ShowSongName("~ " + song->name + " ~");
}
