#include "DisplayManager.h"

DisplayManager* displayManagerPtr;

DisplayManager::DisplayManager()
{
    displayManagerPtr = this;
    _charactersMap = {
        {Characters_Sonic, "Sonic"},
        {Characters_Tails, "Tails"},
        {Characters_Knuckles, "Knuckles"},
        {Characters_Amy, "Amy"},
        {Characters_Gamma, "Gamma"},
        {Characters_Big, "Big"}
    };


    _levelsMap = {
        {LevelIDs_EmeraldCoast, "Emerald Coast"},
        {LevelIDs_WindyValley, "Windy Valley"},
        {LevelIDs_TwinklePark, "Twinkle Park"},
        {LevelIDs_SpeedHighway, "Speed Highway"},
        {LevelIDs_RedMountain, "Red Mountain"},
        {LevelIDs_SkyDeck, "Sky Deck"},
        {LevelIDs_LostWorld, "Lost World"},
        {LevelIDs_IceCap, "Ice Cap"},
        {LevelIDs_Casinopolis, "Casinopolis"},
        {LevelIDs_FinalEgg, "Final Egg"},
        {LevelIDs_HotShelter, "Hot Shelter"},
        {LevelIDs_TwinkleCircuit, "Twinkle Circuit"},
        {LevelIDs_SandHill, "Sand Hill"},
    };
}


FunctionHook<void, AdvaModeEnum> CharSelAdvaModeProcedureHook(0x505E60, [](AdvaModeEnum mode)-> void
{
    if (mode == ADVA_MODE_EXPLAIN)
        displayManagerPtr->OnEnterCharacterSelectScreen();
    CharSelAdvaModeProcedureHook.Original(mode);
});

FunctionHook<void, AdvaModeEnum> CmnAdvaModeProcedureHook(0x505B40, [](AdvaModeEnum mode)-> void
{
    if (mode == ADVA_MODE_TITLE_MENU)
        displayManagerPtr->OnExitCharacterSelectScreen();
    CmnAdvaModeProcedureHook.Original(mode);
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


void DisplayManager::OnFrame()
{
    RemoveExpiredMessages();

    AddNewMessages();

    DisplayMessages();

    DisplayEmblemCount();
    DisplayItemsUnlocked();
}

void DisplayManager::ShowStatusInformation(std::string information)
{
    SetDebugFontSize(this->_debugFontSize);
    SetDebugFontColor(_displayStatusColor);
    DisplayDebugString(NJM_LOCATION(2, 1), ("> " + information).c_str());
}

void DisplayManager::ShowEmblemCount(const int emblemCount)
{
    _emblemCount = emblemCount;
    _emblemTimer = std::clock();
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

void DisplayManager::DisplayEmblemCount()
{
    if (_emblemCount < 0)
        return;

    const double timePassed = (std::clock() - this->_emblemTimer) / static_cast<double>(CLOCKS_PER_SEC);
    if (timePassed > _displayDuration)
    {
        _emblemCount = -1;
        return;
    }

    SetDebugFontSize(this->_debugFontSize);
    SetDebugFontColor(this->_displayEmblemColor);
    DisplayDebugString(
        NJM_LOCATION(2, this->_startLine - 1), ("Emblems: " + std::to_string(_emblemCount)).c_str());
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

void DisplayManager::SetMissions(Characters characters, int missions)
{
    switch (characters)
    {
    case Characters_Sonic:
        _sonicMissions = missions;
        break;
    case Characters_Tails:
        _tailsMissions = missions;
        break;
    case Characters_Knuckles:
        _knucklesMissions = missions;
        break;
    case Characters_Amy:
        _amyMissions = missions;
        break;
    case Characters_Big:
        _bigMissions = missions;
        break;
    case Characters_Gamma:
        _gammaMissions = missions;
        break;
    default:
        break;
    }
}

void DisplayManager::SetLifeSanity(bool lifeSanity)
{
    _lifeSanity = lifeSanity;
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
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+1),
                       ("Emblems: " + std::to_string(_unlockStatus.currentEmblems) + "/"
                           + std::to_string(_unlockStatus.emblemGoal)).c_str());

    int displayOffset = 1;

    std::string buffer;
    //Show Level information
    if (CurrentLevel > LevelIDs_HedgehogHammer && CurrentLevel <= LevelIDs_HotShelter)
    {
        int missionsEnabled = -1;
        int currentColor = -1;
        if (CurrentCharacter == Characters_Sonic)
        {
            missionsEnabled = _sonicMissions;
            currentColor = _sonicColor;
        }
        else if (CurrentCharacter == Characters_Tails)
        {
            missionsEnabled = _tailsMissions;
            currentColor = _tailsColor;
        }
        else if (CurrentCharacter == Characters_Knuckles)
        {
            missionsEnabled = _knucklesMissions;
            currentColor = _knucklesColor;
        }
        else if (CurrentCharacter == Characters_Amy)
        {
            missionsEnabled = _amyMissions;
            currentColor = _amyColor;
        }
        else if (CurrentCharacter == Characters_Big)
        {
            missionsEnabled = _bigMissions;
            currentColor = _bigColor;
        }
        else if (CurrentCharacter == Characters_Gamma)
        {
            missionsEnabled = _gammaMissions;
            currentColor = _gammaColor;
        }

        // Show current level name
        displayOffset++;
        const std::string levelName = _levelsMap.at(CurrentLevel);
        // Show current character
        const std::string characterName = _charactersMap.at(CurrentCharacter);
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
            buffer.append(GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_B) ? " B" : "  ");
        if (missionsEnabled > 2)
            buffer.append(GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_A) ? " A" : "  ");
        buffer.append(" ");

        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());

        buffer.clear();
        buffer.append("[");
        if (missionsEnabled > 0)
            buffer.append(!GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_C) ? "C" : " ");
        if (missionsEnabled > 1)
            buffer.append(!GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_B) ? "-B" : "- ");
        if (missionsEnabled > 2)
            buffer.append(!GetLevelEmblemCollected(&SaveFile, CurrentCharacter, CurrentLevel, MISSION_A) ? "-A" : "- ");
        buffer.append("]");

        SetDebugFontColor(currentColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());


        displayOffset++;
    }

    if (_sonicMissions > 0)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.sonicUnlocked ? "S  " : "   ");
        buffer.append(_unlockStatus.sonicLightShoesUnlocked ? "LS " : "   ");
        buffer.append(_unlockStatus.sonicCrystalRingUnlocked ? "CR " : "   ");
        buffer.append(_unlockStatus.sonicAncientLightUnlocked ? "AL" : "  ");
        SetDebugFontColor(this->_sonicColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.sonicUnlocked ? "S: " : " : ");
        buffer.append(!_unlockStatus.sonicLightShoesUnlocked ? "LS " : "   ");
        buffer.append(!_unlockStatus.sonicCrystalRingUnlocked ? "CR " : "   ");
        buffer.append(!_unlockStatus.sonicAncientLightUnlocked ? "AL" : "  ");
        SetDebugFontColor(this->_sonicColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_tailsMissions > 0)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.tailsUnlocked ? "T  " : "   ");
        buffer.append(_unlockStatus.tailsJetAnkletUnlocked ? "JA " : "   ");
        buffer.append(_unlockStatus.tailsRhythmBadgeUnlocked ? "RB" : "  ");
        SetDebugFontColor(this->_tailsColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.tailsUnlocked ? "T: " : " : ");
        buffer.append(!_unlockStatus.tailsJetAnkletUnlocked ? "JA " : "   ");
        buffer.append(!_unlockStatus.tailsRhythmBadgeUnlocked ? "RB" : "  ");
        SetDebugFontColor(this->_tailsColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_knucklesMissions > 0)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.knucklesUnlocked ? "K  " : "   ");
        buffer.append(_unlockStatus.knucklesShovelClawUnlocked ? "SC " : "   ");
        buffer.append(_unlockStatus.knucklesFightingGlovesUnlocked ? "FG" : "  ");
        SetDebugFontColor(this->_knucklesColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.knucklesUnlocked ? "K: " : " : ");
        buffer.append(!_unlockStatus.knucklesShovelClawUnlocked ? "SC " : "   ");
        buffer.append(!_unlockStatus.knucklesFightingGlovesUnlocked ? "FG" : "  ");
        SetDebugFontColor(this->_knucklesColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_amyMissions > 0)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.amyUnlocked ? "A  " : "   ");
        buffer.append(_unlockStatus.amyLongHammerUnlocked ? "LH " : "   ");
        buffer.append(_unlockStatus.amyWarriorFeatherUnlocked ? "WF" : "  ");
        SetDebugFontColor(this->_amyColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.amyUnlocked ? "A: " : " : ");
        buffer.append(!_unlockStatus.amyLongHammerUnlocked ? "LH " : "   ");
        buffer.append(!_unlockStatus.amyWarriorFeatherUnlocked ? "WF" : "  ");
        SetDebugFontColor(this->_amyColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_bigMissions > 0)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.bigUnlocked ? "B  " : "   ");
        buffer.append(_unlockStatus.bigLifeRingUnlocked ? "LR " : "   ");
        buffer.append(_unlockStatus.bigPowerRodUnlocked ? "PR" : "  ");
        SetDebugFontColor(this->_bigColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.bigUnlocked ? "B: " : " : ");
        buffer.append(!_unlockStatus.bigLifeRingUnlocked ? "LR " : "   ");
        buffer.append(!_unlockStatus.bigPowerRodUnlocked ? "PR" : "  ");
        SetDebugFontColor(this->_bigColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }
    if (_gammaMissions > 0)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.gammaUnlocked ? "G  " : "   ");
        buffer.append(_unlockStatus.gammaJetBoosterUnlocked ? "JB " : "   ");
        buffer.append(_unlockStatus.gammaLaserBlasterUnlocked ? "LB" : "  ");
        SetDebugFontColor(this->_gammaColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.gammaUnlocked ? "G: " : " : ");
        buffer.append(!_unlockStatus.gammaJetBoosterUnlocked ? "JB " : "   ");
        buffer.append(!_unlockStatus.gammaLaserBlasterUnlocked ? "LB" : "  ");
        SetDebugFontColor(this->_gammaColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }


    const int disabledKeyItemColor = _keyItemColor & 0x00FFFFFF | 0x66000000;

    displayOffset++;
    SetDebugFontColor(_unlockStatus.keyTrain ? _keyItemColor : disabledKeyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "Train");

    displayOffset++;
    SetDebugFontColor(_unlockStatus.keyBoat ? _keyItemColor : disabledKeyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "Boat");

    displayOffset++;
    SetDebugFontColor(_unlockStatus.keyRaft ? _keyItemColor : disabledKeyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "Raft");

    displayOffset++;
    SetDebugFontColor(_unlockStatus.keyHotelKeys ? _keyItemColor : disabledKeyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "Hotel Keys");

    displayOffset++;
    SetDebugFontColor(_unlockStatus.keyCasinoKeys ? _keyItemColor : disabledKeyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "Casino District Keys");

    displayOffset++;
    SetDebugFontColor(_unlockStatus.keyTwinkleParkTicket ? _keyItemColor : disabledKeyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "Twinkle Park Ticket");

    displayOffset++;
    SetDebugFontColor(_unlockStatus.keyEmployeeCard ? _keyItemColor : disabledKeyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "Employee card");

    displayOffset++;
    SetDebugFontColor(_unlockStatus.keyDynamite ? _keyItemColor : disabledKeyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "Dynamite");

    displayOffset++;
    SetDebugFontColor(_unlockStatus.keyIceStone ? _keyItemColor : disabledKeyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "Ice Stone");

    displayOffset++;
    SetDebugFontColor(_unlockStatus.jungleKart ? _keyItemColor : disabledKeyItemColor);
    DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), "Jungle Kart");
}
