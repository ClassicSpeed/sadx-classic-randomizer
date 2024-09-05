#include "DisplayManager.h"

DisplayManager* displayManagerPtr;

DisplayManager::DisplayManager()
{
    displayManagerPtr = this;
}

// On entering the character select screen while on the main menu
FunctionHook<void, AdvaModeEnum> CharSelAdvaModeProcedureHook(0x505E60, [](AdvaModeEnum mode)-> void
{
    if (mode == ADVA_MODE_EXPLAIN)
        displayManagerPtr->OnEnterCharacterSelectScreen();
    CharSelAdvaModeProcedureHook.Original(mode);
});

// On exiting the character select screen 
FunctionHook<void, AdvaModeEnum> CmnAdvaModeProcedureHook(0x505B40, [](AdvaModeEnum mode)-> void
{
    if (mode == ADVA_MODE_TITLE_MENU)
        displayManagerPtr->OnExitCharacterSelectScreen();
    CmnAdvaModeProcedureHook.Original(mode);
});

//When leaving a level, check if we quiting the adventure game
FunctionHook<Sint32> onFinishedLevelMaybe2(0x414090, []()-> Sint32
{
    if (GameState == MD_GAME_ABORT)
    {
        displayManagerPtr->OnEnterCharacterSelectScreen();
    }
    return onFinishedLevelMaybe2.Original();
});

FunctionHook<SEQ_SECTIONTBL*, int> storySelectedHook(0x44EAF0, [](int playerno)-> SEQ_SECTIONTBL* {
    SEQ_SECTIONTBL* ptr = storySelectedHook.Original(playerno);
    displayManagerPtr->OnExitCharacterSelectScreen();
    return ptr;
});

void DisplayManager::QueueMessage(const std::string& message)
{
    _messagesQueue.push(message);
}

void DisplayManager::UpdateUnlockStatus(const UnlockStatus unlockStatus)
{
    this->_unlockStatus = unlockStatus;
}

void DisplayManager::UpdateLevelStatus(LevelStatus levelStatus)
{
    this->_levelStatus = levelStatus;
}

void DisplayManager::UpdateMissionStatus(MissionStatus missionStatus)
{
    this->_missionStatus = missionStatus;
}

void DisplayManager::UpdateVisitedLevels(VisitedLevels visitedLevels)
{
    this->_visitedLevels = visitedLevels;
}

void DisplayManager::UpdateOptions(const Options options)
{
    this->_options = options;
}


void DisplayManager::OnFrame()
{
    RemoveExpiredMessages();

    AddNewMessages();

    DisplayMessages();

    DisplayGoalStatus();
    DisplayItemsUnlocked();
}

void DisplayManager::ShowStatusInformation(std::string information)
{
    SetDebugFontSize(this->_debugFontSize);
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
        if (message->IsExpired(_displayDuration))
            message = _currentMessages.erase(message);
        else
            ++message;
    }
}

void DisplayManager::AddNewMessages()
{
    while (!_messagesQueue.empty() && _currentMessages.size() < this->_displayCount)
    {
        _currentMessages.emplace_front(_messagesQueue.front());
        _messagesQueue.pop();
    }
}

void DisplayManager::DisplayMessages() const
{
    for (size_t i = 0; i < this->_currentMessages.size(); i++)
    {
        const double timePassed = _currentMessages[i].TimePassed();
        const double timeRemaining = _displayDuration - timePassed;
        if (timeRemaining < 1)
        {
            int alpha = static_cast<int>(timeRemaining * 255);
            //Fix for alpha value being too low and SADX showing it as solid color
            if (alpha < 15)
                continue;
            const int fadedColor = _displayMessageColor & 0x00FFFFFF | alpha << 24;
            SetDebugFontColor(fadedColor);
        }
        else
            SetDebugFontColor(this->_displayMessageColor);

        SetDebugFontSize(this->_debugFontSize);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + i), _currentMessages[i].message.c_str());
    }
}

void DisplayManager::DisplayGoalStatus()
{
    if (_goalTimer < 0)
        return;

    const double timePassed = (std::clock() - this->_goalTimer) / static_cast<double>(CLOCKS_PER_SEC);
    if (timePassed > _displayDuration)
    {
        _goalTimer = -1;
        return;
    }

    SetDebugFontSize(this->_debugFontSize);
    SetDebugFontColor(this->_displayEmblemColor);

    std::string buffer;

    if (_options.goal == GoalEmeraldHunt || _options.goal == GoalEmblemsAndEmeraldHunt || _options.goal ==
        GoalLevelsAndEmeraldHunt || _options.goal == GoalMissionsAndEmeraldHunt)
    {
        buffer.append("Emeralds:        ");
        SetDebugFontColor(
            _unlockStatus.whiteEmerald ? _whiteEmeraldColor : _whiteEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine -1), "          W");
        SetDebugFontColor(_unlockStatus.redEmerald ? _redEmeraldColor : _redEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine -1), "           R");
        SetDebugFontColor(_unlockStatus.cyanEmerald ? _cyanEmeraldColor : _cyanEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine -1), "            C");
        SetDebugFontColor(_unlockStatus.purpleEmerald
                              ? _purpleEmeraldColor
                              : _purpleEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine -1), "             P");
        SetDebugFontColor(
            _unlockStatus.greenEmerald ? _greenEmeraldColor : _greenEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine -1), "              G");
        SetDebugFontColor(_unlockStatus.yellowEmerald
                              ? _yellowEmeraldColor
                              : _yellowEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine -1), "               Y");
        SetDebugFontColor(_unlockStatus.blueEmerald ? _blueEmeraldColor : _blueEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine -1), "                B");
    }

    SetDebugFontColor(this->_displayEmblemColor);
    if (_options.goal == GoalEmblemsAndEmeraldHunt || _options.goal == GoalLevelsAndEmeraldHunt || _options.goal ==
        GoalMissionsAndEmeraldHunt)
        buffer.append(" ");

    if (_options.goal == GoalEmblems || _options.goal == GoalEmblemsAndEmeraldHunt)
        buffer.append("Emblems: " + std::to_string(_unlockStatus.currentEmblems) + "/"
            + std::to_string(_options.emblemGoal));

    if (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt)
        buffer.append("Levels: " + std::to_string(_levelStatus.levelsCompleted) + "/"
            + std::to_string(_options.levelGoal));

    if (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt)
        buffer.append("Missions: " + std::to_string(_missionStatus.missionsCompleted) + "/"
            + std::to_string(_options.missionGoal));


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
    int targetTime = 0;

    switch (CurrentCharacter)
    {
    case Characters_Sonic:
        if (SONIC_TARGET_TIMES.find(CurrentLevel) != SONIC_TARGET_TIMES.end())
            targetTime = SONIC_TARGET_TIMES.at(CurrentLevel);
        break;
    case Characters_Tails:
        if (TAILS_TARGET_TIMES.find(CurrentLevel) != TAILS_TARGET_TIMES.end())
            targetTime = TAILS_TARGET_TIMES.at(CurrentLevel);
        break;
    case Characters_Knuckles:
        if (KNUCKLES_TARGET_TIMES.find(CurrentLevel) != KNUCKLES_TARGET_TIMES.end())
            targetTime = KNUCKLES_TARGET_TIMES.at(CurrentLevel);
        break;
    case Characters_Amy:
        if (AMY_TARGET_TIMES.find(CurrentLevel) != AMY_TARGET_TIMES.end())
            targetTime = AMY_TARGET_TIMES.at(CurrentLevel);
        break;
    case Characters_Gamma:
        if (GAMMA_TARGET_TIMES.find(CurrentLevel) != GAMMA_TARGET_TIMES.end())
            targetTime = GAMMA_TARGET_TIMES.at(CurrentLevel);
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


void DisplayManager::OnEnterCharacterSelectScreen()
{
    this->_inCharacterSelectScreen = true;
    _unlockStatusTimer = std::clock();
}

void DisplayManager::OnExitCharacterSelectScreen()
{
    this->_inCharacterSelectScreen = false;
}

void DisplayManager::UpdateChecks(const std::map<int, LocationData>& checkData)
{
    this->_checkData = checkData;
}

void DisplayManager::SetMessageConfiguration(const float messageDisplayDuration, const int messageFontSize,
                                             const int messageColor)
{
    this->_displayDuration = messageDisplayDuration;
    this->_debugFontSize = messageFontSize;
    this->_displayMessageColor = messageColor;
}


void DisplayManager::DisplayItemsUnlocked()
{
    //Show Items Unlock on Pause menu or Character select screen
    if (!(GameState == MD_GAME_PAUSE || (GameMode == GameModes_Menu && this->_inCharacterSelectScreen)))
        return;

    if (this->_inCharacterSelectScreen)
    {
        //Added delay to show in sync with the character select screen
        const double timePassed = (std::clock() - this->_unlockStatusTimer) / static_cast<double>(CLOCKS_PER_SEC);
        if (timePassed < _unlockStatusDelay)
            return;
    }
    SetDebugFontSize(this->_debugFontSize);
    SetDebugFontColor(this->_displayEmblemColor);
    std::string buffer;

    int displayOffset = 0;
    if (_options.goal == GoalEmblems || _options.goal == GoalEmblemsAndEmeraldHunt)
    {
        displayOffset++;
        buffer.clear();
        buffer.append("Emblems: " + std::to_string(_unlockStatus.currentEmblems) + "/"
            + std::to_string(_options.emblemGoal));
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt)
    {
        displayOffset++;
        buffer.clear();
        buffer.append("Levels: " + std::to_string(_levelStatus.levelsCompleted) + "/"
            + std::to_string(_options.levelGoal));
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt)
    {
        displayOffset++;
        buffer.clear();
        buffer.append("Missions: " + std::to_string(_missionStatus.missionsCompleted) + "/"
            + std::to_string(_options.missionGoal));
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_options.goal == GoalEmeraldHunt || _options.goal == GoalEmblemsAndEmeraldHunt || _options.goal ==
        GoalLevelsAndEmeraldHunt || _options.goal == GoalMissionsAndEmeraldHunt)
    {
        displayOffset++;
        buffer.clear();
        buffer.append("Emeralds: ");
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        SetDebugFontColor(
            _unlockStatus.whiteEmerald ? _whiteEmeraldColor : _whiteEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "          W");
        SetDebugFontColor(_unlockStatus.redEmerald ? _redEmeraldColor : _redEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "           R");
        SetDebugFontColor(_unlockStatus.cyanEmerald ? _cyanEmeraldColor : _cyanEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "            C");
        SetDebugFontColor(_unlockStatus.purpleEmerald
                              ? _purpleEmeraldColor
                              : _purpleEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "             P");
        SetDebugFontColor(
            _unlockStatus.greenEmerald ? _greenEmeraldColor : _greenEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "              G");
        SetDebugFontColor(_unlockStatus.yellowEmerald
                              ? _yellowEmeraldColor
                              : _yellowEmeraldColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "               Y");
        SetDebugFontColor(_unlockStatus.blueEmerald ? _blueEmeraldColor : _blueEmeraldColor & 0x00FFFFFF | 0x66000000);
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

        const std::string levelInfo = levelName + " (" + characterName + " - " + missionName + ")";
        SetDebugFontColor(currentColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), levelInfo.c_str());

        // Show missions checked
        displayOffset++;
        buffer.clear();
        buffer.append(" ");
        if (missionsEnabled > 0)
            buffer.append(GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_C) ? "C" : " ");
        if (missionsEnabled > 1)
            buffer.append(GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_B)
                              ? " B" + this->GetMissionBTarget(true)
                              : "  " + this->GetMissionBTarget(true));
        if (missionsEnabled > 2)
            buffer.append(GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_A)
                              ? " A" + this->GetMissionATarget(true)
                              : "  " + this->GetMissionATarget(true));
        buffer.append(" ");

        if (_options.lifeSanity && _options.GetCharacterLifeSanity(static_cast<Characters>(CurrentCharacter)))
        {
            buffer.append(" Lives: ");
            for (const auto& check : _checkData)
            {
                if (check.second.character == CurrentCharacter && check.second.type == LocationLifeCapsule &&
                    GET_LEVEL(check.second.level) == CurrentLevel)
                {
                    if (!_options.includePinballCapsules && (check.first == 1211 || check.first == 1212))
                        continue;
                    buffer.append(check.second.checked ? "X" : "-");
                }
            }
            SetDebugFontColor(currentColor);
            DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        }

        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        buffer.clear();
        buffer.append("[");
        if (missionsEnabled > 0)
            buffer.append(!GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_C) ? "C" : " ");
        if (missionsEnabled > 1)
            buffer.append(!GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_B)
                              ? "-B" + this->GetMissionBTarget(false)
                              : "- " + this->GetMissionBTarget(false));
        if (missionsEnabled > 2)
            buffer.append(!GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_A)
                              ? "-A" + this->GetMissionATarget(false)
                              : "- " + this->GetMissionATarget(false));
        buffer.append("]");

        SetDebugFontColor(currentColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());


        displayOffset++;
    }


    if (_options.playableSonic)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.sonicUnlocked ? "S  " : "   ");
        buffer.append(_unlockStatus.sonicLightShoesUnlocked ? "LS " : "   ");
        buffer.append(_unlockStatus.sonicCrystalRingUnlocked ? "CR " : "   ");
        buffer.append(_unlockStatus.sonicAncientLightUnlocked ? "AL" : "  ");
        if (_unlockStatus.sonicUnlocked && _options.sonicActionStageMissions > 0
            && (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_levelStatus.sonicLevelsCompleted)
                + "/" + std::to_string(_levelStatus.sonicLevelsTotal));
        }
        if (_unlockStatus.sonicUnlocked && _options.missionModeEnabled
            && (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_missionStatus.sonicMissionsCompleted)
                + "/" + std::to_string(_missionStatus.sonicMissionsTotal));
        }

        SetDebugFontColor(this->_sonicColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.sonicUnlocked ? "S: " : " : ");
        buffer.append(!_unlockStatus.sonicLightShoesUnlocked ? "LS " : "   ");
        buffer.append(!_unlockStatus.sonicCrystalRingUnlocked ? "CR " : "   ");
        buffer.append(!_unlockStatus.sonicAncientLightUnlocked ? "AL" : "  ");
        if (!_unlockStatus.sonicUnlocked && _options.sonicActionStageMissions > 0
            && (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_levelStatus.sonicLevelsCompleted)
                + "/" + std::to_string(_levelStatus.sonicLevelsTotal));
        }
        if (!_unlockStatus.sonicUnlocked && _options.missionModeEnabled
            && (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_missionStatus.sonicMissionsCompleted)
                + "/" + std::to_string(_missionStatus.sonicMissionsTotal));
        }

        SetDebugFontColor(this->_sonicColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_options.playableTails)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.tailsUnlocked ? "T  " : "   ");
        buffer.append(_unlockStatus.tailsJetAnkletUnlocked ? "JA " : "   ");
        buffer.append(_unlockStatus.tailsRhythmBadgeUnlocked ? "RB" : "  ");
        if (_unlockStatus.tailsUnlocked && _options.tailsActionStageMissions > 0
            && (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_levelStatus.tailsLevelsCompleted)
                + "/" + std::to_string(_levelStatus.tailsLevelsTotal));
        }
        if (_unlockStatus.tailsUnlocked && _options.missionModeEnabled
            && (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_missionStatus.tailsMissionsCompleted)
                + "/" + std::to_string(_missionStatus.tailsMissionsTotal));
        }
        SetDebugFontColor(this->_tailsColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.tailsUnlocked ? "T: " : " : ");
        buffer.append(!_unlockStatus.tailsJetAnkletUnlocked ? "JA " : "   ");
        buffer.append(!_unlockStatus.tailsRhythmBadgeUnlocked ? "RB" : "  ");
        if (!_unlockStatus.tailsUnlocked && _options.tailsActionStageMissions > 0
            && (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_levelStatus.tailsLevelsCompleted)
                + "/" + std::to_string(_levelStatus.tailsLevelsTotal));
        }
        if (!_unlockStatus.tailsUnlocked && _options.missionModeEnabled
            && (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_missionStatus.tailsMissionsCompleted)
                + "/" + std::to_string(_missionStatus.tailsMissionsTotal));
        }
        SetDebugFontColor(this->_tailsColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_options.playableKnuckles)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.knucklesUnlocked ? "K  " : "   ");
        buffer.append(_unlockStatus.knucklesShovelClawUnlocked ? "SC " : "   ");
        buffer.append(_unlockStatus.knucklesFightingGlovesUnlocked ? "FG" : "  ");
        if (_unlockStatus.knucklesUnlocked && _options.knucklesActionStageMissions > 0
            && (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_levelStatus.knucklesLevelsCompleted)
                + "/" + std::to_string(_levelStatus.knucklesLevelsTotal));
        }
        if (_unlockStatus.knucklesUnlocked && _options.missionModeEnabled
            && (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_missionStatus.knucklesMissionsCompleted)
                + "/" + std::to_string(_missionStatus.knucklesMissionsTotal));
        }
        SetDebugFontColor(this->_knucklesColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.knucklesUnlocked ? "K: " : " : ");
        buffer.append(!_unlockStatus.knucklesShovelClawUnlocked ? "SC " : "   ");
        buffer.append(!_unlockStatus.knucklesFightingGlovesUnlocked ? "FG" : "  ");
        if (!_unlockStatus.knucklesUnlocked && _options.knucklesActionStageMissions > 0
            && (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_levelStatus.knucklesLevelsCompleted)
                + "/" + std::to_string(_levelStatus.knucklesLevelsTotal));
        }
        if (!_unlockStatus.knucklesUnlocked && _options.missionModeEnabled
            && (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_missionStatus.knucklesMissionsCompleted)
                + "/" + std::to_string(_missionStatus.knucklesMissionsTotal));
        }
        SetDebugFontColor(this->_knucklesColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_options.playableAmy)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.amyUnlocked ? "A  " : "   ");
        buffer.append(_unlockStatus.amyLongHammerUnlocked ? "LH " : "   ");
        buffer.append(_unlockStatus.amyWarriorFeatherUnlocked ? "WF" : "  ");
        if (_unlockStatus.amyUnlocked && _options.amyActionStageMissions > 0
            && (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_levelStatus.amyLevelsCompleted)
                + "/" + std::to_string(_levelStatus.amyLevelsTotal));
        }
        if (_unlockStatus.amyUnlocked && _options.missionModeEnabled
            && (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_missionStatus.amyMissionsCompleted)
                + "/" + std::to_string(_missionStatus.amyMissionsTotal));
        }
        SetDebugFontColor(this->_amyColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.amyUnlocked ? "A: " : " : ");
        buffer.append(!_unlockStatus.amyLongHammerUnlocked ? "LH " : "   ");
        buffer.append(!_unlockStatus.amyWarriorFeatherUnlocked ? "WF" : "  ");
        if (!_unlockStatus.amyUnlocked && _options.amyActionStageMissions > 0
            && (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_levelStatus.amyLevelsCompleted)
                + "/" + std::to_string(_levelStatus.amyLevelsTotal));
        }
        if (!_unlockStatus.amyUnlocked && _options.missionModeEnabled
            && (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_missionStatus.amyMissionsCompleted)
                + "/" + std::to_string(_missionStatus.amyMissionsTotal));
        }
        SetDebugFontColor(this->_amyColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_options.playableBig)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.bigUnlocked ? "B  " : "   ");
        buffer.append(_unlockStatus.bigLifeBeltUnlocked ? "LB " : "   ");
        buffer.append(_unlockStatus.bigPowerRodUnlocked ? "PR " : "   ");
        buffer.append(_unlockStatus.bigLureQuantity > 0 ? "L" + std::to_string(_unlockStatus.bigLureQuantity) : "  ");
        if (_unlockStatus.bigUnlocked && _options.bigActionStageMissions > 0
            && (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_levelStatus.bigLevelsCompleted)
                + "/" + std::to_string(_levelStatus.bigLevelsTotal));
        }
        if (_unlockStatus.bigUnlocked && _options.missionModeEnabled
            && (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_missionStatus.bigMissionsCompleted)
                + "/" + std::to_string(_missionStatus.bigMissionsTotal));
        }
        SetDebugFontColor(this->_bigColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.bigUnlocked ? "B: " : " : ");
        buffer.append(!_unlockStatus.bigLifeBeltUnlocked ? "LB " : "   ");
        buffer.append(!_unlockStatus.bigPowerRodUnlocked ? "PR " : "   ");
        buffer.append(_unlockStatus.bigLureQuantity == 0 ? "L0" : "  ");
        if (!_unlockStatus.bigUnlocked && _options.bigActionStageMissions > 0
            && (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_levelStatus.bigLevelsCompleted)
                + "/" + std::to_string(_levelStatus.bigLevelsTotal));
        }
        if (!_unlockStatus.bigUnlocked && _options.missionModeEnabled
            && (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_missionStatus.bigMissionsCompleted)
                + "/" + std::to_string(_missionStatus.bigMissionsTotal));
        }
        SetDebugFontColor(this->_bigColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }
    if (_options.playableGamma)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.gammaUnlocked ? "G  " : "   ");
        buffer.append(_unlockStatus.gammaJetBoosterUnlocked ? "JB " : "   ");
        buffer.append(_unlockStatus.gammaLaserBlasterUnlocked ? "LB" : "  ");
        if (_unlockStatus.gammaUnlocked && _options.gammaActionStageMissions > 0
            && (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_levelStatus.gammaLevelsCompleted)
                + "/" + std::to_string(_levelStatus.gammaLevelsTotal));
        }
        if (_unlockStatus.gammaUnlocked && _options.missionModeEnabled
            && (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_missionStatus.gammaMissionsCompleted)
                + "/" + std::to_string(_missionStatus.gammaMissionsTotal));
        }
        SetDebugFontColor(this->_gammaColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.gammaUnlocked ? "G: " : " : ");
        buffer.append(!_unlockStatus.gammaJetBoosterUnlocked ? "JB " : "   ");
        buffer.append(!_unlockStatus.gammaLaserBlasterUnlocked ? "LB" : "  ");
        if (!_unlockStatus.gammaUnlocked && _options.gammaActionStageMissions > 0
            && (_options.goal == GoalLevels || _options.goal == GoalLevelsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_levelStatus.gammaLevelsCompleted)
                + "/" + std::to_string(_levelStatus.gammaLevelsTotal));
        }
        if (!_unlockStatus.gammaUnlocked && _options.missionModeEnabled
            && (_options.goal == GoalMissions || _options.goal == GoalMissionsAndEmeraldHunt))
        {
            buffer.append(" " + std::to_string(_missionStatus.gammaMissionsCompleted)
                + "/" + std::to_string(_missionStatus.gammaMissionsTotal));
        }
        SetDebugFontColor(this->_gammaColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }


    const int disabledKeyItemColor = _keyItemColor & 0x00FFFFFF | 0x66000000;

    displayOffset++;
    buffer.clear();
    buffer.append("Travel  ");
    buffer.append(_unlockStatus.keyTrain ? "Train " : "      ");
    buffer.append(_unlockStatus.keyBoat ? "Boat " : "     ");
    buffer.append(_unlockStatus.keyRaft ? "Raft" : "    ");
    SetDebugFontColor(_keyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    buffer.clear();
    buffer.append("      : ");
    buffer.append(!_unlockStatus.keyTrain ? "Train|" : "     |");
    buffer.append(!_unlockStatus.keyBoat ? "Boat|" : "    |");
    buffer.append(!_unlockStatus.keyRaft ? "Raft" : "    ");
    SetDebugFontColor(disabledKeyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

    displayOffset++;
    buffer.clear();
    buffer.append("Keys  ");
    buffer.append(_unlockStatus.keyStationKeys ? "Station " : "        ");
    buffer.append(_unlockStatus.keyHotelKeys ? "Hotel " : "      ");
    buffer.append(_unlockStatus.keyCasinoKeys ? "Casino" : "      ");
    SetDebugFontColor(_keyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    buffer.clear();
    buffer.append("    : ");
    buffer.append(!_unlockStatus.keyStationKeys ? "Station|" : "       |");
    buffer.append(!_unlockStatus.keyHotelKeys ? "Hotel|" : "     |");
    buffer.append(!_unlockStatus.keyCasinoKeys ? "Casino" : "      ");
    SetDebugFontColor(disabledKeyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

    displayOffset++;
    buffer.clear();
    buffer.append("Stones  ");
    buffer.append(_unlockStatus.keyWindStone ? "Wind " : "     ");
    buffer.append(_unlockStatus.keyIceStone ? "Ice" : "   ");
    SetDebugFontColor(_keyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    buffer.clear();
    buffer.append("      : ");
    buffer.append(!_unlockStatus.keyWindStone ? "Wind|" : "    |");
    buffer.append(!_unlockStatus.keyIceStone ? "Ice" : "   ");
    SetDebugFontColor(disabledKeyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

    displayOffset++;
    buffer.clear();
    buffer.append("SS  ");
    buffer.append(_unlockStatus.keyTwinkleParkTicket ? "TP Ticket " : "          ");
    buffer.append(_unlockStatus.keyEmployeeCard ? "Employee Card" : "             ");
    SetDebugFontColor(_keyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    buffer.clear();
    buffer.append("  : ");
    buffer.append(!_unlockStatus.keyTwinkleParkTicket ? "TP Ticket|" : "         |");
    buffer.append(!_unlockStatus.keyEmployeeCard ? "Employee Card" : "             ");
    SetDebugFontColor(disabledKeyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

    displayOffset++;
    buffer.clear();
    buffer.append("MR  ");
    buffer.append(_unlockStatus.keyDynamite ? "Dynamite " : "         ");
    buffer.append(_unlockStatus.jungleCart ? "Jungle Cart" : "           ");
    SetDebugFontColor(_keyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    buffer.clear();
    buffer.append("  : ");
    buffer.append(!_unlockStatus.keyDynamite ? "Dynamite|" : "        |");
    buffer.append(!_unlockStatus.jungleCart ? "Jungle Cart" : "           ");
    SetDebugFontColor(disabledKeyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    displayOffset++;

    if (_options.entranceRandomizer)
    {
        displayOffset++;
        buffer.clear();
        buffer.append("EC");
        if (_visitedLevels.emeraldCoastEntranceVisited)
            buffer.append("   ").append(_visitedLevels.emeraldCoastEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_visitedLevels.emeraldCoastEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("WV");
        if (_visitedLevels.windyValleyEntranceVisited)
            buffer.append("   ").append(_visitedLevels.windyValleyEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_visitedLevels.windyValleyEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("C ");
        if (_visitedLevels.casinopolisEntranceVisited)
            buffer.append("   ").append(_visitedLevels.casinopolisEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_visitedLevels.casinopolisEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("IC");
        if (_visitedLevels.iceCapEntranceVisited)
            buffer.append("   ").append(_visitedLevels.iceCapEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_visitedLevels.iceCapEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("TP");
        if (_visitedLevels.twinkleParkEntranceVisited)
            buffer.append("   ").append(_visitedLevels.twinkleParkEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_visitedLevels.twinkleParkEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());


        displayOffset++;
        buffer.clear();
        buffer.append("SH");
        if (_visitedLevels.speedHighwayEntranceVisited)
            buffer.append("   ").append(_visitedLevels.speedHighwayEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_visitedLevels.speedHighwayEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());


        displayOffset++;
        buffer.clear();
        buffer.append("RM");
        if (_visitedLevels.redMountainEntranceVisited)
            buffer.append("   ").append(_visitedLevels.redMountainEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_visitedLevels.redMountainEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("SD");
        if (_visitedLevels.skyDeckEntranceVisited)
            buffer.append("   ").append(_visitedLevels.skyDeckEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_visitedLevels.skyDeckEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("LW");
        if (_visitedLevels.lostWorldEntranceVisited)
            buffer.append("   ").append(_visitedLevels.lostWorldEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_visitedLevels.lostWorldEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("FE");
        if (_visitedLevels.finalEggEntranceVisited)
            buffer.append("   ").append(_visitedLevels.finalEggEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_visitedLevels.finalEggEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        displayOffset++;
        buffer.clear();
        buffer.append("HS");
        if (_visitedLevels.hotShelterEntranceVisited)
            buffer.append("   ").append(_visitedLevels.hotShelterEntranceActualLevel);
        else
            buffer.append("");
        SetDebugFontColor(_keyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append("   >");
        if (!_visitedLevels.hotShelterEntranceVisited)
            buffer.append(" ??");
        SetDebugFontColor(disabledKeyItemColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }
}
