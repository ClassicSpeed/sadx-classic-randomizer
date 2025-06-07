#include "Randomizer.h"


Randomizer::Randomizer(Options& options, Settings& settings, GameStatus& gameStatus, DisplayManager& displayManager,
                       CharacterManager& characterManager, WorldStateManager& menuManager,
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

    _gameStatus.CheckGoalRequirements();
    if (check.type == LocationLevel && check.levelMission == MISSION_C && _options.goalRequiresLevels)
        _displayManager.ShowGoalStatus();

    if (check.type == LocationMission && _options.goalRequiresMissions)
        _displayManager.ShowGoalStatus();

    if (check.type == LocationBossFight && _options.goalRequiresBosses)
        _displayManager.ShowGoalStatus();

    if (check.type == LocationChaoRace && _options.goalRequiresChaoRaces)
        _displayManager.ShowGoalStatus();
}

void Randomizer::MarkCheckedLocation(const int64_t checkId) const
{
    LocationData locationData = _locationRepository.SetLocationChecked(checkId);
    if (locationData.type == LocationMission)
        _saveFileManager.SetMissionCompleted(locationData.missionNumber);
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
        _saveFileManager.SetEventFlags(item.eventFlags);
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

    _gameStatus.CheckGoalRequirements();
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
    }
    else if (item.type == ItemEmblem)
        _displayManager.ShowGoalStatus();


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

    _worldStateManager.UpdateLevelEntrances();

    for (const auto& location : _locationRepository.GetLocations())
    {
        if (location.second.type == LocationLevel && location.second.checked && location.second.level >=
            LevelIDs_EmeraldCoast && location.second.level <= LevelIDs_HotShelter)
            _worldStateManager.UpdateVisitedLevels(location.second.level);
    }
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
            if (_gameStatus.lastStoryRequirementsCompleted)
                _saveFileManager.UnlockSuperSonic();
        }
        if (item.second.type == ItemCharacter && item.second.obtained)
            _saveFileManager.SetEventFlags(item.second.eventFlags);
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
    _locationRepository.UpdateStatus();

    //Missions
    if (_options.autoStartMissions)
        _saveFileManager.StartAllMissions();


    if (!_options.goalRequiresChaosEmeralds)
        SetEventFlag(static_cast<EventFlags>(FLAG_SUPERSONIC_COMPLETE));

    // Music
    _saveFileManager.MarkBlacklistedMissionsAsCompleted(_options.missionBlacklist);
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
