#include "DisplayManager.h"


DisplayManager::DisplayManager(Options& options, Settings& settings, GameStatus& gameStatus, const char* path,
                               const HelperFunctions& helperFunctions) : _options(options), _settings(settings),
                                                                         _gameStatus(gameStatus)
{
    _charSelAdvaModeProcedureHook.Hook(OnCharSelAdvaModeProcedure);
    _cmnAdvaModeProcedureHook.Hook(OnCmnAdvaModeProcedure);
    _finishedLevelMaybeHook.Hook(OnFinishedLevelMaybe);
    _storySelectedHook.Hook(OnStorySelected);

    //Blocks mission/trail menu
    _loadMissionMenu.Hook([]() -> BOOL { return false; });
    _loadTrialMenu.Hook([]() -> BOOL { return false; });


    char pathbuf[MAX_PATH];
    ReplacePNG_Common("HYOJI_EMBLEM0");
    ReplacePNG_Common("HYOJI_EMBLEM1");
}

// On entering the character select screen while on the main menu
void DisplayManager::OnCharSelAdvaModeProcedure(const AdvaModeEnum adventureMode)
{
    if (adventureMode == ADVA_MODE_EXPLAIN)
        _instance->OnEnterCharacterSelectScreen();
    _charSelAdvaModeProcedureHook.Original(adventureMode);
}

// On exiting the character select screen 
void DisplayManager::OnCmnAdvaModeProcedure(const AdvaModeEnum adventureMode)
{
    if (adventureMode == ADVA_MODE_TITLE_MENU)
        _instance->OnExitCharacterSelectScreen();
    _cmnAdvaModeProcedureHook.Original(adventureMode);
}

//When leaving a level, check if we quiting the adventure game
Sint32 DisplayManager::OnFinishedLevelMaybe()
{
    if (GameState == MD_GAME_ABORT)
        _instance->OnEnterCharacterSelectScreen();
    return _finishedLevelMaybeHook.Original();
}

SEQ_SECTIONTBL* DisplayManager::OnStorySelected(const int playerNumber)
{
    _instance->OnExitCharacterSelectScreen();
    return _storySelectedHook.Original(playerNumber);
}

void DisplayManager::QueueItemMessage(const std::string& message)
{
    _itemMessagesQueue.push(message);
}

void DisplayManager::QueueChatMessage(const std::string& message)
{
    if (_chatMessagesQueue.size() >= this->_chatDisplayCount)
    {
        _chatMessagesQueue.erase(_chatMessagesQueue.begin());
    }
    _chatMessagesQueue.push_back(message);
    _lastMessageTime = std::clock();
}

void DisplayManager::ShowSongName(const std::string& songName)
{
    if (_settings.showSongName == ShowSongNameAlwaysOff)
        return;

    if (_settings.showSongName == ShowSongNameWithSongShuffle && _options.musicShuffle == MusicShuffleNone)
        return;

    if (_settings.showSongNameForType == ShowSongNameForTypeOnlyActionLevels)
        if (CurrentLevel < LevelIDs_EmeraldCoast || CurrentLevel > LevelIDs_HotShelter)
            return;

    if (_songName != songName)
    {
        _songName = songName;
        _songNameTime = std::clock();
    }
}

void DisplayManager::OnFrame()
{
    // for (const auto& button : PressedButtons)
    //
    //     if (button & WhistleButtons && Current_CharObj2 != nullptr)
    //     {
    //         _gameStatus.unlock.currentEmblems++;
    //     }
    MenuVoice = _settings.voiceMenuCharacter;
    RemoveExpiredMessages();

    AddNewMessages();

    DisplayItemMessages();
    DisplayChatMessages();
    DisplaySongName();

    DisplayGoalStatus();
    DisplayItemsUnlocked();
}

void DisplayManager::ShowStatusInformation(std::string information)
{
    SetDebugFontSize(_settings.debugFontSize);
    SetDebugFontColor(_displayStatusColor);
    DisplayDebugString(NJM_LOCATION(2, 1), ("> " + information).c_str());
}

void DisplayManager::ShowGoalStatus()
{
    _goalTimer = std::clock();
}


void DisplayManager::RemoveExpiredMessages()
{
    for (auto message = _currentMessages.begin(); message != _currentMessages.end();)
    {
        if (message->IsExpired(_settings.displayDuration))
            message = _currentMessages.erase(message);
        else
            ++message;
    }
}

void DisplayManager::AddNewMessages()
{
    while (!_itemMessagesQueue.empty() && _currentMessages.size() < this->_displayCount)
    {
        _currentMessages.emplace_front(_itemMessagesQueue.front());
        _itemMessagesQueue.pop();
    }
}

void DisplayManager::DisplayItemMessages() const
{
    for (size_t i = 0; i < this->_currentMessages.size(); i++)
    {
        const double timePassed = _currentMessages[i].TimePassed();
        const double timeRemaining = _settings.displayDuration - timePassed;
        if (timeRemaining < 1)
        {
            int alpha = static_cast<int>(timeRemaining * 255);
            //Fix for alpha value being too low and SADX showing it as solid color
            if (alpha < 15)
                continue;
            const int fadedColor = _settings.displayMessageColor & 0x00FFFFFF | alpha << 24;
            SetDebugFontColor(fadedColor);
        }
        else
            SetDebugFontColor(_settings.displayMessageColor);

        SetDebugFontSize(_settings.debugFontSize);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + i), _currentMessages[i].message.c_str());
    }
}

void DisplayManager::DisplayChatMessages()
{
    if (_lastMessageTime < 0)
        return;

    const double timePassed = (std::clock() - this->_lastMessageTime) / static_cast<double>(CLOCKS_PER_SEC);
    const double timeRemaining = _settings.displayDuration - timePassed;
    int alpha = 255;
    if (timeRemaining < 1)
    {
        alpha = static_cast<int>(timeRemaining * 255);
        //Fix for alpha value being too low and SADX showing it as solid color
        if (alpha < 15)
        {
            _lastMessageTime = -1;
            return;
        }
        const int fadedColor = _settings.chatMessageColor & 0x00FFFFFF | alpha << 24;
        SetDebugFontColor(fadedColor);
    }
    else
        SetDebugFontColor(_settings.chatMessageColor);

    const int rows = VerticalResolution / _settings.debugFontSize;
    SetDebugFontSize(_settings.debugFontSize);

    int longestMessageSize = 0;
    for (size_t i = 0; i < this->_chatMessagesQueue.size(); ++i)
    {
        int linesFromTop = rows - 2 - this->_chatMessagesQueue.size() + i + 1;
        DisplayDebugString(NJM_LOCATION(2, linesFromTop), _chatMessagesQueue[i].c_str());
        if (longestMessageSize < _chatMessagesQueue[i].size())
            longestMessageSize = _chatMessagesQueue[i].size();
    }

    njColorBlendingMode(0, NJD_COLOR_BLENDING_SRCALPHA);
    njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);

    int linesFromTop = rows - 1 - _chatDisplayCount;
    DrawRect_Queue(1.5f * _settings.debugFontSize,
                   (linesFromTop - 0.5f) * _settings.debugFontSize,
                   (2 + longestMessageSize + 0.5) * _settings.debugFontSize,
                   (linesFromTop + _chatDisplayCount + 0.5) * _settings.debugFontSize, 62041.496f,
                   0x5F0000FF & 0x00FFFFFF | alpha / 3 << 24,
                   QueuedModelFlagsB_EnableZWrite);


    njColorBlendingMode(0, NJD_COLOR_BLENDING_SRCALPHA);
    njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
}

void DisplayManager::DisplaySongName()
{
    if (_songNameTime < 0)
        return;

    const double timePassed = (std::clock() - this->_songNameTime) / static_cast<double>(CLOCKS_PER_SEC);
    const double timeRemaining = _settings.displayDuration - timePassed;
    int alpha = 255;
    if (timeRemaining < 1)
    {
        alpha = static_cast<int>(timeRemaining * 255);
        //Fix for alpha value being too low and SADX showing it as solid color
        if (alpha < 15)
        {
            _songNameTime = -1;
            return;
        }
        const int fadedColor = _settings.chatMessageColor & 0x00FFFFFF | alpha << 24;
        SetDebugFontColor(fadedColor);
    }
    else if (timePassed < 0.25)
    {
        alpha = static_cast<int>(timePassed * 4 * 255);
        //Fix for alpha value being too low and SADX showing it as solid color
        if (alpha < 15)
            return;

        const int fadedColor = _settings.chatMessageColor & 0x00FFFFFF | alpha << 24;
        SetDebugFontColor(fadedColor);
    }
    else
        SetDebugFontColor(_settings.chatMessageColor);

    const int columns = HorizontalResolution / _settings.debugFontSize;
    SetDebugFontSize(_settings.debugFontSize);

    DisplayDebugString(NJM_LOCATION(columns/2 - _songName.size() / 2, 4), _songName.c_str());

    njColorBlendingMode(0, NJD_COLOR_BLENDING_SRCALPHA);
    njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);

    DrawRect_Queue((columns / 2 - _songName.size() / 2 - 0.5f) * _settings.debugFontSize,
                   (4 - 0.5f) * _settings.debugFontSize,
                   (columns / 2 + _songName.size() / 2 + (_songName.size() % 2 != 0 ? 1 : 0) + 0.5f) * this->
                   _settings.debugFontSize,
                   (4 + 1 + 0.5) * _settings.debugFontSize, 62041.496f,
                   0x5F000000 & 0x00FFFFFF | alpha / 3 << 24,
                   QueuedModelFlagsB_EnableZWrite);


    njColorBlendingMode(0, NJD_COLOR_BLENDING_SRCALPHA);
    njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
}


void DisplayManager::DisplayGoalStatus()
{
    if (_goalTimer < 0)
        return;

    const double timePassed = (std::clock() - this->_goalTimer) / static_cast<double>(CLOCKS_PER_SEC);
    if (timePassed > _settings.displayDuration)
    {
        _goalTimer = -1;
        return;
    }

    SetDebugFontSize(_settings.debugFontSize);
    SetDebugFontColor(this->_displayEmblemColor);

    std::string buffer;
    if (_gameStatus.lastStoryRequirementsCompleted)
    {
        buffer.append("You can now fight Perfect Chaos!");
        DisplayDebugString(
            NJM_LOCATION(2, this->_startLine - 1), buffer.c_str());
        return;
    }


    if (_options.goalRequiresChaosEmeralds)
    {
        buffer.append("Emeralds:        ");
        SetDebugFontColor(
            _gameStatus.unlock.whiteEmerald ? _whiteEmeraldColor : _whiteEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine -1), "          W");
        SetDebugFontColor(_gameStatus.unlock.redEmerald
                              ? _redEmeraldColor
                              : _redEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine -1), "           R");
        SetDebugFontColor(_gameStatus.unlock.cyanEmerald
                              ? _cyanEmeraldColor
                              : _cyanEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine -1), "            C");
        SetDebugFontColor(_gameStatus.unlock.purpleEmerald
                              ? _purpleEmeraldColor
                              : _purpleEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine -1), "             P");
        SetDebugFontColor(
            _gameStatus.unlock.greenEmerald ? _greenEmeraldColor : _greenEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine -1), "              G");
        SetDebugFontColor(_gameStatus.unlock.yellowEmerald
                              ? _yellowEmeraldColor
                              : _yellowEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine -1), "               Y");
        SetDebugFontColor(_gameStatus.unlock.blueEmerald
                              ? _blueEmeraldColor
                              : _blueEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine -1), "                B");
    }

    SetDebugFontColor(this->_displayEmblemColor);

    if (_options.goalRequiresLevels)
        buffer.append(" Levels: " + std::to_string(_gameStatus.levels.levelsCompleted) + "/"
            + std::to_string(_options.levelGoal));

    if (_options.goalRequiresEmblems)
        buffer.append(" Emblems: " + std::to_string(_gameStatus.unlock.currentEmblems) + "/"
            + std::to_string(_options.emblemGoal));

    if (_options.goalRequiresMissions)
        buffer.append(" Missions: " + std::to_string(_gameStatus.missions.missionsCompleted) + "/"
            + std::to_string(_options.missionGoal));

    if (_options.goalRequiresBosses)
        buffer.append(" Bosses: " + std::to_string(_gameStatus.bosses.bossesCompleted) + "/"
            + std::to_string(_options.bossesGoal));

    if (_options.goalRequiresChaoRaces)
        buffer.append(" Races: " + std::to_string(_gameStatus.chao.racesCompleted) + "/"
            + std::to_string(_gameStatus.chao.racesTotal));

    DisplayDebugString(
        NJM_LOCATION(2, this->_startLine - 1), buffer.c_str());
}

std::string DisplayManager::GetMissionBTarget(const bool showTarget)
{
    switch (CurrentCharacter)
    {
    case Characters_Sonic:
    case Characters_Tails:
    case Characters_Amy:
    case Characters_Gamma:
        return showTarget ? " 50 Rings " : "(        )";
    case Characters_Knuckles:
        return showTarget ? " No Hints " : "(        )";
    case Characters_Big:
        return showTarget ? " 1000g " : "(     )";

    default: return "";
    }
}

std::string DisplayManager::GetMissionATarget(const bool showTarget)
{
    int targetTime;

    switch (CurrentCharacter)
    {
    case Characters_Sonic:
        targetTime = std::get<TIME_A_RANK>(SONIC_TARGET_TIMES.at(CurrentLevel));
        break;
    case Characters_Tails:
        targetTime = std::get<TIME_A_RANK>(TAILS_TARGET_TIMES.at(CurrentLevel));
        break;
    case Characters_Knuckles:
        targetTime = std::get<TIME_A_RANK>(KNUCKLES_TARGET_TIMES.at(CurrentLevel));
        break;
    case Characters_Amy:
        targetTime = std::get<TIME_A_RANK>(AMY_TARGET_TIMES.at(CurrentLevel));
        break;
    case Characters_Gamma:
        targetTime = std::get<TIME_A_RANK>(GAMMA_TARGET_TIMES.at(CurrentLevel));
        break;
    case Characters_Big:
        return showTarget ? " 2000g " : "(     )";

    default: return "";
    }
    const int minutes = targetTime / 60 / 60;
    const int seconds = targetTime / 60 % 60;
    const std::string formattedTime = " " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") +
        std::to_string(seconds) + " ";

    if (showTarget)
        return formattedTime;
    else
        return "(" + std::string(formattedTime.length() - 2, ' ') + ")";
}

std::string DisplayManager::GetMissionSTarget(const bool showTarget, const bool expertMode)
{
    int targetTime = 0;

    switch (CurrentCharacter)
    {
    case Characters_Sonic:
        if (expertMode)
            targetTime = std::get<TIME_S_RANK_EXPERT>(SONIC_TARGET_TIMES.at(CurrentLevel));
        else
            targetTime = std::get<TIME_S_RANK>(SONIC_TARGET_TIMES.at(CurrentLevel));
        break;
    case Characters_Tails:
        if (expertMode)
            targetTime = std::get<TIME_S_RANK_EXPERT>(TAILS_TARGET_TIMES.at(CurrentLevel));
        else
            targetTime = std::get<TIME_S_RANK>(TAILS_TARGET_TIMES.at(CurrentLevel));
        break;
    case Characters_Knuckles:
        if (expertMode)
            targetTime = std::get<TIME_S_RANK_EXPERT>(KNUCKLES_TARGET_TIMES.at(CurrentLevel));
        else
            targetTime = std::get<TIME_S_RANK>(KNUCKLES_TARGET_TIMES.at(CurrentLevel));
        break;
    case Characters_Amy:
        if (expertMode)
            targetTime = std::get<TIME_S_RANK_EXPERT>(AMY_TARGET_TIMES.at(CurrentLevel));
        else
            targetTime = std::get<TIME_S_RANK>(AMY_TARGET_TIMES.at(CurrentLevel));
        break;
    case Characters_Gamma:
        if (expertMode)
            targetTime = std::get<TIME_S_RANK_EXPERT>(GAMMA_TARGET_TIMES.at(CurrentLevel));
        else
            targetTime = std::get<TIME_S_RANK>(GAMMA_TARGET_TIMES.at(CurrentLevel));
        break;
    case Characters_Big:
        return showTarget ? " 2000g + 5000g " : "(             )";

    default: return "";
    }
    const int minutes = targetTime / 60 / 60;
    const int seconds = targetTime / 60 % 60;
    const std::string formattedTime = " " + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") +
        std::to_string(seconds) + " ";

    if (showTarget)
        return formattedTime;
    else
        return "(" + std::string(formattedTime.length() - 2, ' ') + ")";
}


void DisplayManager::OnEnterCharacterSelectScreen()
{
    this->_inCharacterSelectScreen = true;
    _unlockStatusTimer = std::clock();
}

void DisplayManager::OnExitCharacterSelectScreen()
{
    this->_inCharacterSelectScreen = false;
}

void DisplayManager::SetConnected()
{
    _connected = true;
}


void DisplayManager::DisplayItemsUnlocked()
{
    if (_settings.displayInGameTracker == DisplayTrackerAlwaysOff)
        return;

    if (!_connected)
        return;

    bool showMap = false;

    for (const auto& button : HeldButtons)
        if (button & WhistleButtons && Current_CharObj2 != nullptr)
            showMap = true;

    if (!showMap && _settings.displayInGameTracker == DisplayTrackerWhenPaused)
    {
        //Show Items Unlock on Pause menu or Character select screen
        if (!(GameState == MD_GAME_PAUSE || (GameMode == GameModes_Menu && this->_inCharacterSelectScreen)))
            return;
        // We don't show the tracker on the mission screen
        if (MissionScreenState > 0)
            return;

        if (this->_inCharacterSelectScreen)
        {
            //Added delay to show in sync with the character select screen
            const double timePassed = (std::clock() - this->_unlockStatusTimer) / static_cast<double>(CLOCKS_PER_SEC);
            if (timePassed < _unlockStatusDelay)
                return;
        }
    }

    SetDebugFontSize(_settings.debugFontSize);
    SetDebugFontColor(0x88FFFFFF);

    const int rows = VerticalResolution / _settings.debugFontSize;
    const int columns = HorizontalResolution / _settings.debugFontSize;
    const std::string modVersionString = "v" + std::to_string(SADX_AP_VERSION_MAJOR) + "." +
        std::to_string(SADX_AP_VERSION_MINOR) + "." + std::to_string(SADX_AP_VERSION_PATCH);
    DisplayDebugString(NJM_LOCATION(columns-7, rows-2), modVersionString.c_str());

    SetDebugFontColor(this->_displayEmblemColor);
    std::string buffer;

    int displayOffset = 0;

    if (_options.goalRequiresLevels)
    {
        displayOffset++;
        buffer.clear();
        buffer.append("Levels:   " + std::to_string(_gameStatus.levels.levelsCompleted) + "/"
            + std::to_string(_options.levelGoal));
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_options.goalRequiresMissions)
    {
        displayOffset++;
        buffer.clear();
        buffer.append("Missions: " + std::to_string(_gameStatus.missions.missionsCompleted) + "/"
            + std::to_string(_options.missionGoal));
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }
    if (_options.goalRequiresBosses)
    {
        displayOffset++;
        buffer.clear();
        buffer.append("Bosses:   " + std::to_string(_gameStatus.bosses.bossesCompleted) + "/"
            + std::to_string(_options.bossesGoal));
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }
    if (_options.goalRequiresChaoRaces)
    {
        displayOffset++;
        buffer.clear();
        buffer.append("Races:    " + std::to_string(_gameStatus.chao.racesCompleted) + "/"
            + std::to_string(_gameStatus.chao.racesTotal));
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_options.goalRequiresEmblems)
    {
        displayOffset++;
        buffer.clear();
        buffer.append("Emblems:  " + std::to_string(_gameStatus.unlock.currentEmblems) + "/"
            + std::to_string(_options.emblemGoal));
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_options.goalRequiresChaosEmeralds)
    {
        displayOffset++;
        buffer.clear();
        buffer.append("Emeralds: ");
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        SetDebugFontColor(
            _gameStatus.unlock.whiteEmerald ? _whiteEmeraldColor : _whiteEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "          W");
        SetDebugFontColor(_gameStatus.unlock.redEmerald
                              ? _redEmeraldColor
                              : _redEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "           R");
        SetDebugFontColor(_gameStatus.unlock.cyanEmerald
                              ? _cyanEmeraldColor
                              : _cyanEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "            C");
        SetDebugFontColor(_gameStatus.unlock.purpleEmerald
                              ? _purpleEmeraldColor
                              : _purpleEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "             P");
        SetDebugFontColor(
            _gameStatus.unlock.greenEmerald ? _greenEmeraldColor : _greenEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "              G");
        SetDebugFontColor(_gameStatus.unlock.yellowEmerald
                              ? _yellowEmeraldColor
                              : _yellowEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "               Y");
        SetDebugFontColor(_gameStatus.unlock.blueEmerald
                              ? _blueEmeraldColor
                              : _blueEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "                B");
    }

    //Show Level information
    if (CurrentLevel > LevelIDs_HedgehogHammer && CurrentLevel <= LevelIDs_HotShelter)
    {
        int missionsEnabled = -1;
        int currentColor = -1;
        switch (CurrentCharacter)
        {
        case Characters_Sonic: missionsEnabled = _options.sonicActionStageMissions;
            currentColor = _sonicColor;
            break;
        case Characters_Tails: missionsEnabled = _options.tailsActionStageMissions;
            currentColor = _tailsColor;
            break;
        case Characters_Knuckles: missionsEnabled = _options.knucklesActionStageMissions;
            currentColor = _knucklesColor;
            break;
        case Characters_Amy: missionsEnabled = _options.amyActionStageMissions;
            currentColor = _amyColor;
            break;
        case Characters_Big: missionsEnabled = _options.bigActionStageMissions;
            currentColor = _bigColor;
            break;
        case Characters_Gamma: missionsEnabled = _options.gammaActionStageMissions;
            currentColor = _gammaColor;
            break;
        default: break;
        }

        // Show current level name
        displayOffset++;
        const std::string levelName = LEVELS_MAP.at(CurrentLevel);
        // Show current character
        const std::string characterName = CHARACTERS_MAP.at(CurrentCharacter);
        // Show current mission

        std::string missionName;
        if (GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_C))
            if (GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_B))
                missionName = "A";
            else
                missionName = "B";
        else
            missionName = "C";

        const std::string levelInfo = levelName + " (" + characterName + ") - " + missionName;
        SetDebugFontColor(currentColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), levelInfo.c_str());

        if (missionsEnabled > 0)
        {
            // Show missions checked
            displayOffset++;
            buffer.clear();
            buffer.append(" ");
            if (missionsEnabled > 0)
                buffer.append(GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_C)
                                  ? "C"
                                  : " ");
            if (missionsEnabled > 1)
                buffer.append(GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_B)
                                  ? " B" + this->GetMissionBTarget(true)
                                  : "  " + this->GetMissionBTarget(true));
            if (missionsEnabled > 2)
                buffer.append(GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_A)
                                  ? " A" + this->GetMissionATarget(true)
                                  : "  " + this->GetMissionATarget(true));
            if (missionsEnabled > 3)
                buffer.append(GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_A)
                                  ? " S" + this->GetMissionSTarget(true, _options.expertMode)
                                  : "  " + this->GetMissionSTarget(true, _options.expertMode));

            DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());


            buffer.clear();
            buffer.append("[");
            if (missionsEnabled > 0)
                buffer.append(
                    !GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_C) ? "C" : " ");
            if (missionsEnabled > 1)
                buffer.append(!GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_B)
                                  ? "-B" + this->GetMissionBTarget(false)
                                  : "- " + this->GetMissionBTarget(false));
            if (missionsEnabled > 2)
                buffer.append(!GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_A)
                                  ? "-A" + this->GetMissionATarget(false)
                                  : "- " + this->GetMissionATarget(false));
            if (missionsEnabled > 3)
                buffer.append(!GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_A)
                                  ? "-S" + this->GetMissionSTarget(false, _options.expertMode)
                                  : "- " + this->GetMissionSTarget(false, _options.expertMode));
            buffer.append("]");

            SetDebugFontColor(currentColor & 0x00FFFFFF | 0x66000000);
            DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        }

        if (_options.enemySanity && _options.GetCharacterEnemySanity(static_cast<Characters>(CurrentCharacter)))
        {
            buffer.clear();
            buffer.append("Enemies:  ");


            int enemyCount = _gameStatus.enemySanity[CurrentLevel][CurrentCharacter].current;
            int enemyTotal = _gameStatus.enemySanity[CurrentLevel][CurrentCharacter].total;
            buffer.append(std::to_string(enemyCount) + "/" + std::to_string(enemyTotal));
            if (enemyTotal > 0)
            {
                displayOffset++;
                SetDebugFontColor(currentColor);
                DisplayDebugString(
                    NJM_LOCATION(2, this->_startLine + this->_displayCount + displayOffset), buffer.c_str());
            }
        }

        //TODO: improve
        if (_options.capsuleSanity && (
            _options.GetCapsuleSanityByType(static_cast<Characters>(CurrentCharacter), ExtraLifeCapsule) ||
            _options.GetCapsuleSanityByType(static_cast<Characters>(CurrentCharacter), ShieldCapsule) ||
            _options.GetCapsuleSanityByType(static_cast<Characters>(CurrentCharacter), SpeedUpCapsule) ||
            _options.GetCapsuleSanityByType(static_cast<Characters>(CurrentCharacter), FiveRingsCapsule)
        ))
        {
            buffer.clear();
            buffer.append("Capsules: ");

            int capsuleCount = _gameStatus.capsuleSanity[CurrentLevel][CurrentCharacter].current;
            int capsuleTotal = _gameStatus.capsuleSanity[CurrentLevel][CurrentCharacter].total;
            buffer.append(std::to_string(capsuleCount) + "/" + std::to_string(capsuleTotal));
            if (capsuleTotal > 0)
            {
                displayOffset++;
                SetDebugFontColor(currentColor);
                DisplayDebugString(
                    NJM_LOCATION(2, this->_startLine + this->_displayCount + displayOffset), buffer.c_str());
            }
        }

        if (_options.fishSanity)
        {
            buffer.clear();
            buffer.append("Fish:     ");


            int fishCount = _gameStatus.fishSanity[CurrentLevel].current;
            int fishTotal = _gameStatus.fishSanity[CurrentLevel].total;
            buffer.append(std::to_string(fishCount) + "/" + std::to_string(fishTotal));

            if (fishTotal > 0)
            {
                displayOffset++;
                SetDebugFontColor(currentColor);
                DisplayDebugString(
                    NJM_LOCATION(2, this->_startLine + this->_displayCount + displayOffset), buffer.c_str());
            }
        }
    }

    displayOffset++;

    if (_options.playableSonic)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_gameStatus.unlock.sonicUnlocked ? "S  " : "   ");
        buffer.append(_gameStatus.unlock.sonicLightShoesUnlocked ? "LS " : "   ");
        buffer.append(_gameStatus.unlock.sonicCrystalRingUnlocked ? "CR " : "   ");
        buffer.append(_gameStatus.unlock.sonicAncientLightUnlocked ? "AL" : "  ");
        if (_gameStatus.unlock.sonicUnlocked && _options.sonicActionStageMissions > 0 && _options.goalRequiresLevels)
        {
            buffer.append(" L:" + std::to_string(_gameStatus.levels.sonicLevelsCompleted)
                + "/" + std::to_string(_gameStatus.levels.sonicLevelsTotal));
        }
        if (_gameStatus.unlock.sonicUnlocked && _options.missionModeEnabled && _options.goalRequiresMissions)
        {
            buffer.append(" M:" + std::to_string(_gameStatus.missions.sonicMissionsCompleted)
                + "/" + std::to_string(_gameStatus.missions.sonicMissionsTotal));
        }
        if (_gameStatus.unlock.sonicUnlocked && _options.bossChecks && _options.goalRequiresBosses)
        {
            buffer.append(" B:" + std::to_string(_gameStatus.bosses.sonicBossesCompleted)
                + "/" + std::to_string(_gameStatus.bosses.sonicBossesTotal));
        }

        SetDebugFontColor(this->_sonicColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_gameStatus.unlock.sonicUnlocked ? "S: " : " : ");
        buffer.append(!_gameStatus.unlock.sonicLightShoesUnlocked ? "LS " : "   ");
        buffer.append(!_gameStatus.unlock.sonicCrystalRingUnlocked ? "CR " : "   ");
        buffer.append(!_gameStatus.unlock.sonicAncientLightUnlocked ? "AL" : "  ");
        if (!_gameStatus.unlock.sonicUnlocked && _options.sonicActionStageMissions > 0 && _options.goalRequiresLevels)
        {
            buffer.append(" L:" + std::to_string(_gameStatus.levels.sonicLevelsCompleted)
                + "/" + std::to_string(_gameStatus.levels.sonicLevelsTotal));
        }
        if (!_gameStatus.unlock.sonicUnlocked && _options.missionModeEnabled && _options.goalRequiresMissions)
        {
            buffer.append(" M:" + std::to_string(_gameStatus.missions.sonicMissionsCompleted)
                + "/" + std::to_string(_gameStatus.missions.sonicMissionsTotal));
        }
        if (!_gameStatus.unlock.sonicUnlocked && _options.bossChecks && _options.goalRequiresBosses)
        {
            buffer.append(" B:" + std::to_string(_gameStatus.bosses.sonicBossesCompleted)
                + "/" + std::to_string(_gameStatus.bosses.sonicBossesTotal));
        }

        SetDebugFontColor(this->_sonicColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_options.playableTails)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_gameStatus.unlock.tailsUnlocked ? "T  " : "   ");
        buffer.append(_gameStatus.unlock.tailsJetAnkletUnlocked ? "JA " : "   ");
        buffer.append(_gameStatus.unlock.tailsRhythmBadgeUnlocked ? "RB" : "  ");
        buffer.append("   ");
        if (_gameStatus.unlock.tailsUnlocked && _options.tailsActionStageMissions > 0 && _options.goalRequiresLevels)
        {
            buffer.append(" L:" + std::to_string(_gameStatus.levels.tailsLevelsCompleted)
                + "/" + std::to_string(_gameStatus.levels.tailsLevelsTotal) + " ");
        }
        if (_gameStatus.unlock.tailsUnlocked && _options.missionModeEnabled && _options.goalRequiresMissions)
        {
            buffer.append(" M:" + std::to_string(_gameStatus.missions.tailsMissionsCompleted)
                + "/" + std::to_string(_gameStatus.missions.tailsMissionsTotal) + " ");
        }
        if (_gameStatus.unlock.tailsUnlocked && _options.bossChecks && _options.goalRequiresBosses)
        {
            buffer.append(" B:" + std::to_string(_gameStatus.bosses.tailsBossesCompleted)
                + "/" + std::to_string(_gameStatus.bosses.tailsBossesTotal));
        }
        SetDebugFontColor(this->_tailsColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_gameStatus.unlock.tailsUnlocked ? "T: " : " : ");
        buffer.append(!_gameStatus.unlock.tailsJetAnkletUnlocked ? "JA " : "   ");
        buffer.append(!_gameStatus.unlock.tailsRhythmBadgeUnlocked ? "RB" : "  ");
        buffer.append("   ");
        if (!_gameStatus.unlock.tailsUnlocked && _options.tailsActionStageMissions > 0 && _options.goalRequiresLevels)
        {
            buffer.append(" L:" + std::to_string(_gameStatus.levels.tailsLevelsCompleted)
                + "/" + std::to_string(_gameStatus.levels.tailsLevelsTotal) + " ");
        }
        if (!_gameStatus.unlock.tailsUnlocked && _options.missionModeEnabled && _options.goalRequiresMissions)
        {
            buffer.append(" M:" + std::to_string(_gameStatus.missions.tailsMissionsCompleted)
                + "/" + std::to_string(_gameStatus.missions.tailsMissionsTotal) + " ");
        }
        if (!_gameStatus.unlock.tailsUnlocked && _options.bossChecks && _options.goalRequiresBosses)
        {
            buffer.append(" B:" + std::to_string(_gameStatus.bosses.tailsBossesCompleted)
                + "/" + std::to_string(_gameStatus.bosses.tailsBossesTotal));
        }
        SetDebugFontColor(this->_tailsColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_options.playableKnuckles)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_gameStatus.unlock.knucklesUnlocked ? "K  " : "   ");
        buffer.append(_gameStatus.unlock.knucklesShovelClawUnlocked ? "SC " : "   ");
        buffer.append(_gameStatus.unlock.knucklesFightingGlovesUnlocked ? "FG" : "  ");
        buffer.append("   ");
        if (_gameStatus.unlock.knucklesUnlocked && _options.knucklesActionStageMissions > 0 && _options.
            goalRequiresLevels)
        {
            buffer.append(" L:" + std::to_string(_gameStatus.levels.knucklesLevelsCompleted)
                + "/" + std::to_string(_gameStatus.levels.knucklesLevelsTotal) + " ");
        }
        if (_gameStatus.unlock.knucklesUnlocked && _options.missionModeEnabled && _options.goalRequiresMissions)
        {
            buffer.append(" M:" + std::to_string(_gameStatus.missions.knucklesMissionsCompleted)
                + "/" + std::to_string(_gameStatus.missions.knucklesMissionsTotal) + " ");
        }
        if (_gameStatus.unlock.knucklesUnlocked && _options.bossChecks && _options.goalRequiresBosses)
        {
            buffer.append(" B:" + std::to_string(_gameStatus.bosses.knucklesBossesCompleted)
                + "/" + std::to_string(_gameStatus.bosses.knucklesBossesTotal));
        }
        SetDebugFontColor(this->_knucklesColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_gameStatus.unlock.knucklesUnlocked ? "K: " : " : ");
        buffer.append(!_gameStatus.unlock.knucklesShovelClawUnlocked ? "SC " : "   ");
        buffer.append(!_gameStatus.unlock.knucklesFightingGlovesUnlocked ? "FG" : "  ");
        buffer.append("   ");
        if (!_gameStatus.unlock.knucklesUnlocked && _options.knucklesActionStageMissions > 0 && _options.
            goalRequiresLevels)
        {
            buffer.append(" L:" + std::to_string(_gameStatus.levels.knucklesLevelsCompleted)
                + "/" + std::to_string(_gameStatus.levels.knucklesLevelsTotal) + " ");
        }
        if (!_gameStatus.unlock.knucklesUnlocked && _options.missionModeEnabled && _options.goalRequiresMissions)
        {
            buffer.append(" M:" + std::to_string(_gameStatus.missions.knucklesMissionsCompleted)
                + "/" + std::to_string(_gameStatus.missions.knucklesMissionsTotal) + " ");
        }
        if (!_gameStatus.unlock.knucklesUnlocked && _options.bossChecks && _options.goalRequiresBosses)
        {
            buffer.append(" B:" + std::to_string(_gameStatus.bosses.knucklesBossesCompleted)
                + "/" + std::to_string(_gameStatus.bosses.knucklesBossesTotal));
        }
        SetDebugFontColor(this->_knucklesColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_options.playableAmy)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_gameStatus.unlock.amyUnlocked ? "A  " : "   ");
        buffer.append(_gameStatus.unlock.amyLongHammerUnlocked ? "LH " : "   ");
        buffer.append(_gameStatus.unlock.amyWarriorFeatherUnlocked ? "WF" : "  ");
        buffer.append("   ");
        if (_gameStatus.unlock.amyUnlocked && _options.amyActionStageMissions > 0 && _options.goalRequiresLevels)
        {
            buffer.append(" L:" + std::to_string(_gameStatus.levels.amyLevelsCompleted)
                + "/" + std::to_string(_gameStatus.levels.amyLevelsTotal) + " ");
        }
        if (_gameStatus.unlock.amyUnlocked && _options.missionModeEnabled && _options.goalRequiresMissions)
        {
            buffer.append(" M:" + std::to_string(_gameStatus.missions.amyMissionsCompleted)
                + "/" + std::to_string(_gameStatus.missions.amyMissionsTotal) + " ");
        }
        if (_gameStatus.unlock.amyUnlocked && _options.bossChecks && _options.goalRequiresBosses)
        {
            buffer.append(" B:" + std::to_string(_gameStatus.bosses.amyBossesCompleted)
                + "/" + std::to_string(_gameStatus.bosses.amyBossesTotal));
        }
        SetDebugFontColor(this->_amyColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_gameStatus.unlock.amyUnlocked ? "A: " : " : ");
        buffer.append(!_gameStatus.unlock.amyLongHammerUnlocked ? "LH " : "   ");
        buffer.append(!_gameStatus.unlock.amyWarriorFeatherUnlocked ? "WF" : "  ");
        buffer.append("   ");
        if (!_gameStatus.unlock.amyUnlocked && _options.amyActionStageMissions > 0 && _options.goalRequiresLevels)
        {
            buffer.append(" L:" + std::to_string(_gameStatus.levels.amyLevelsCompleted)
                + "/" + std::to_string(_gameStatus.levels.amyLevelsTotal) + " ");
        }
        if (!_gameStatus.unlock.amyUnlocked && _options.missionModeEnabled && _options.goalRequiresMissions)
        {
            buffer.append(" M:" + std::to_string(_gameStatus.missions.amyMissionsCompleted)
                + "/" + std::to_string(_gameStatus.missions.amyMissionsTotal) + " ");
        }
        if (!_gameStatus.unlock.amyUnlocked && _options.bossChecks && _options.goalRequiresBosses)
        {
            buffer.append(" B:" + std::to_string(_gameStatus.bosses.amyBossesCompleted)
                + "/" + std::to_string(_gameStatus.bosses.amyBossesTotal));
        }
        SetDebugFontColor(this->_amyColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_options.playableBig)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_gameStatus.unlock.bigUnlocked ? "B  " : "   ");
        buffer.append(_gameStatus.unlock.bigLifeBeltUnlocked ? "LB " : "   ");
        buffer.append(_gameStatus.unlock.bigPowerRodUnlocked ? "PR " : "   ");
        buffer.append(_gameStatus.unlock.bigLureQuantity > 0
                          ? "L" + std::to_string(_gameStatus.unlock.bigLureQuantity)
                          : "  ");
        if (_gameStatus.unlock.bigUnlocked && _options.bigActionStageMissions > 0 && _options.goalRequiresLevels)
        {
            buffer.append(" L:" + std::to_string(_gameStatus.levels.bigLevelsCompleted)
                + "/" + std::to_string(_gameStatus.levels.bigLevelsTotal) + " ");
        }
        if (_gameStatus.unlock.bigUnlocked && _options.missionModeEnabled && _options.goalRequiresMissions)
        {
            buffer.append(" M:" + std::to_string(_gameStatus.missions.bigMissionsCompleted)
                + "/" + std::to_string(_gameStatus.missions.bigMissionsTotal) + " ");
        }
        if (_gameStatus.unlock.bigUnlocked && _options.bossChecks && _options.goalRequiresBosses)
        {
            buffer.append(" B:" + std::to_string(_gameStatus.bosses.bigBossesCompleted)
                + "/" + std::to_string(_gameStatus.bosses.bigBossesTotal));
        }
        SetDebugFontColor(this->_bigColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_gameStatus.unlock.bigUnlocked ? "B: " : " : ");
        buffer.append(!_gameStatus.unlock.bigLifeBeltUnlocked ? "LB " : "   ");
        buffer.append(!_gameStatus.unlock.bigPowerRodUnlocked ? "PR " : "   ");
        buffer.append(_gameStatus.unlock.bigLureQuantity == 0 ? "L0" : "  ");
        if (!_gameStatus.unlock.bigUnlocked && _options.bigActionStageMissions > 0 && _options.goalRequiresLevels)
        {
            buffer.append(" L:" + std::to_string(_gameStatus.levels.bigLevelsCompleted)
                + "/" + std::to_string(_gameStatus.levels.bigLevelsTotal) + " ");
        }
        if (!_gameStatus.unlock.bigUnlocked && _options.missionModeEnabled && _options.goalRequiresMissions)
        {
            buffer.append(" M:" + std::to_string(_gameStatus.missions.bigMissionsCompleted)
                + "/" + std::to_string(_gameStatus.missions.bigMissionsTotal) + " ");
        }
        if (!_gameStatus.unlock.bigUnlocked && _options.bossChecks && _options.goalRequiresBosses)
        {
            buffer.append(" B:" + std::to_string(_gameStatus.bosses.bigBossesCompleted)
                + "/" + std::to_string(_gameStatus.bosses.bigBossesTotal));
        }
        SetDebugFontColor(this->_bigColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }
    if (_options.playableGamma)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_gameStatus.unlock.gammaUnlocked ? "G  " : "   ");
        buffer.append(_gameStatus.unlock.gammaJetBoosterUnlocked ? "JB " : "   ");
        buffer.append(_gameStatus.unlock.gammaLaserBlasterUnlocked ? "LB" : "  ");
        buffer.append("   ");
        if (_gameStatus.unlock.gammaUnlocked && _options.gammaActionStageMissions > 0 && _options.goalRequiresLevels)
        {
            buffer.append(" L:" + std::to_string(_gameStatus.levels.gammaLevelsCompleted)
                + "/" + std::to_string(_gameStatus.levels.gammaLevelsTotal) + " ");
        }
        if (_gameStatus.unlock.gammaUnlocked && _options.missionModeEnabled && _options.goalRequiresMissions)
        {
            buffer.append(" M:" + std::to_string(_gameStatus.missions.gammaMissionsCompleted)
                + "/" + std::to_string(_gameStatus.missions.gammaMissionsTotal) + " ");
        }
        if (_gameStatus.unlock.gammaUnlocked && _options.bossChecks && _options.goalRequiresBosses)
        {
            buffer.append(" B:" + std::to_string(_gameStatus.bosses.gammaBossesCompleted)
                + "/" + std::to_string(_gameStatus.bosses.gammaBossesTotal));
        }
        SetDebugFontColor(this->_gammaColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_gameStatus.unlock.gammaUnlocked ? "G: " : " : ");
        buffer.append(!_gameStatus.unlock.gammaJetBoosterUnlocked ? "JB " : "   ");
        buffer.append(!_gameStatus.unlock.gammaLaserBlasterUnlocked ? "LB" : "  ");
        buffer.append("   ");
        if (!_gameStatus.unlock.gammaUnlocked && _options.gammaActionStageMissions > 0 && _options.goalRequiresLevels)
        {
            buffer.append(" L:" + std::to_string(_gameStatus.levels.gammaLevelsCompleted)
                + "/" + std::to_string(_gameStatus.levels.gammaLevelsTotal) + " ");
        }
        if (!_gameStatus.unlock.gammaUnlocked && _options.missionModeEnabled && _options.goalRequiresMissions)
        {
            buffer.append(" M:" + std::to_string(_gameStatus.missions.gammaMissionsCompleted)
                + "/" + std::to_string(_gameStatus.missions.gammaMissionsTotal) + " ");
        }
        if (!_gameStatus.unlock.gammaUnlocked && _options.bossChecks && _options.goalRequiresBosses)
        {
            buffer.append(" B:" + std::to_string(_gameStatus.bosses.gammaBossesCompleted)
                + "/" + std::to_string(_gameStatus.bosses.gammaBossesTotal));
        }
        SetDebugFontColor(this->_gammaColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    const int disabledKeyItemColor = _keyItemColor & 0x00FFFFFF | 0x66000000;
    if (_options.gatingMode == KeyItemGating)
    {
        displayOffset++;
        buffer.clear();
        buffer.append("Travel  ");
        buffer.append(_gameStatus.unlock.keyTrain ? "Train " : "      ");
        buffer.append(_gameStatus.unlock.keyBoat ? "Boat " : "     ");
        buffer.append(_gameStatus.unlock.keyRaft ? "Raft" : "    ");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("      : ");
        buffer.append(!_gameStatus.unlock.keyTrain ? "Train|" : "     |");
        buffer.append(!_gameStatus.unlock.keyBoat ? "Boat|" : "    |");
        buffer.append(!_gameStatus.unlock.keyRaft ? "Raft" : "    ");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("Hotel   ");
        buffer.append(_gameStatus.unlock.keyHotelKey ? "Front " : "      ");
        buffer.append(_gameStatus.unlock.keyCasinoKey ? "Back" : "    ");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("     :  ");
        buffer.append(!_gameStatus.unlock.keyHotelKey ? "Front|" : "     |");
        buffer.append(!_gameStatus.unlock.keyCasinoKey ? "Back" : "    ");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("Station ");
        buffer.append(_gameStatus.unlock.keyStationKey ? "Front " : "      ");
        buffer.append(_gameStatus.unlock.keyShutterKey ? "Back" : "    ");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("       :");
        buffer.append(!_gameStatus.unlock.keyStationKey ? "Front|" : "     |");
        buffer.append(!_gameStatus.unlock.keyShutterKey ? "Back" : "    ");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("Stones  ");
        buffer.append(_gameStatus.unlock.keyWindStone ? " Wind " : "      ");
        buffer.append(_gameStatus.unlock.keyIceStone ? "Ice" : "   ");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("      : ");
        buffer.append(!_gameStatus.unlock.keyWindStone ? " Wind|" : "     |");
        buffer.append(!_gameStatus.unlock.keyIceStone ? "Ice" : "   ");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("SS  ");
        buffer.append(_gameStatus.unlock.keyTwinkleParkTicket ? "TP Ticket " : "          ");
        buffer.append(_gameStatus.unlock.keyEmployeeCard ? "Employee Card" : "             ");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("  : ");
        buffer.append(!_gameStatus.unlock.keyTwinkleParkTicket ? "TP Ticket|" : "         |");
        buffer.append(!_gameStatus.unlock.keyEmployeeCard ? "Employee Card" : "             ");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("MR  ");
        buffer.append(_gameStatus.unlock.keyDynamite ? " Dynamite " : "          ");
        buffer.append(_gameStatus.unlock.keyJungleCart ? "Jungle Cart" : "           ");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("  : ");
        buffer.append(!_gameStatus.unlock.keyDynamite ? " Dynamite|" : "         |");
        buffer.append(!_gameStatus.unlock.keyJungleCart ? "Jungle Cart" : "           ");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("EC  ");
        buffer.append(_gameStatus.unlock.keyEgglift ? "  Egglift " : "          ");
        buffer.append(_gameStatus.unlock.keyMonorail ? "Monorail" : "        ");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("  : ");
        buffer.append(!_gameStatus.unlock.keyEgglift ? "  Egglift|" : "         |");
        buffer.append(!_gameStatus.unlock.keyMonorail ? "Monorail" : "        ");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        displayOffset++;
    }

    if (_options.entranceRandomizer)
    {
        displayOffset++;
        buffer.clear();
        buffer.append("EC");
        if (_gameStatus.visitedLevels.emeraldCoastEntranceVisited)
            buffer.append("   ").append(_gameStatus.visitedLevels.emeraldCoastEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_gameStatus.visitedLevels.emeraldCoastEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("WV");
        if (_gameStatus.visitedLevels.windyValleyEntranceVisited)
            buffer.append("   ").append(_gameStatus.visitedLevels.windyValleyEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_gameStatus.visitedLevels.windyValleyEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("C ");
        if (_gameStatus.visitedLevels.casinopolisEntranceVisited)
            buffer.append("   ").append(_gameStatus.visitedLevels.casinopolisEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_gameStatus.visitedLevels.casinopolisEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("IC");
        if (_gameStatus.visitedLevels.iceCapEntranceVisited)
            buffer.append("   ").append(_gameStatus.visitedLevels.iceCapEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_gameStatus.visitedLevels.iceCapEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("TP");
        if (_gameStatus.visitedLevels.twinkleParkEntranceVisited)
            buffer.append("   ").append(_gameStatus.visitedLevels.twinkleParkEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_gameStatus.visitedLevels.twinkleParkEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());


        displayOffset++;
        buffer.clear();
        buffer.append("SH");
        if (_gameStatus.visitedLevels.speedHighwayEntranceVisited)
            buffer.append("   ").append(_gameStatus.visitedLevels.speedHighwayEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_gameStatus.visitedLevels.speedHighwayEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());


        displayOffset++;
        buffer.clear();
        buffer.append("RM");
        if (_gameStatus.visitedLevels.redMountainEntranceVisited)
            buffer.append("   ").append(_gameStatus.visitedLevels.redMountainEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_gameStatus.visitedLevels.redMountainEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("SD");
        if (_gameStatus.visitedLevels.skyDeckEntranceVisited)
            buffer.append("   ").append(_gameStatus.visitedLevels.skyDeckEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_gameStatus.visitedLevels.skyDeckEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("LW");
        if (_gameStatus.visitedLevels.lostWorldEntranceVisited)
            buffer.append("   ").append(_gameStatus.visitedLevels.lostWorldEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_gameStatus.visitedLevels.lostWorldEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("FE");
        if (_gameStatus.visitedLevels.finalEggEntranceVisited)
            buffer.append("   ").append(_gameStatus.visitedLevels.finalEggEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_gameStatus.visitedLevels.finalEggEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("HS");
        if (_gameStatus.visitedLevels.hotShelterEntranceVisited)
            buffer.append("   ").append(_gameStatus.visitedLevels.hotShelterEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_gameStatus.visitedLevels.hotShelterEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }
}
