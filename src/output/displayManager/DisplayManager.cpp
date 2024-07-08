#include "DisplayManager.h"

DisplayManager* displayManagerPtr;

DisplayManager::DisplayManager()
{
    displayManagerPtr = this;
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
        SetDebugFontSize(this->_debugFontSize);
        SetDebugFontColor(this->_displayMessageColor);
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
    //TODO: Remove when story is selected
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
    if (_sonicMissions > 0)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.sonicUnlocked ? "S  " : "   ");
        buffer.append(_unlockStatus.sonicLightShoesUnlocked ? "LS " : "   ");
        buffer.append(_unlockStatus.sonicCrystalRingUnlocked ? "CR " : "   ");
        buffer.append(_unlockStatus.sonicAncientLightUnlocked ? "AL" : "  ");
        SetDebugFontColor(this->_SonicColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.sonicUnlocked ? "S: " : " : ");
        buffer.append(!_unlockStatus.sonicLightShoesUnlocked ? "LS " : "   ");
        buffer.append(!_unlockStatus.sonicCrystalRingUnlocked ? "CR " : "   ");
        buffer.append(!_unlockStatus.sonicAncientLightUnlocked ? "AL" : "  ");
        SetDebugFontColor(this->_SonicColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_tailsMissions > 0)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.tailsUnlocked ? "T  " : "   ");
        buffer.append(_unlockStatus.tailsJetAnkletUnlocked ? "JA " : "   ");
        buffer.append(_unlockStatus.tailsRhythmBadgeUnlocked ? "RB" : "  ");
        SetDebugFontColor(this->_TailsColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.tailsUnlocked ? "T: " : " : ");
        buffer.append(!_unlockStatus.tailsJetAnkletUnlocked ? "JA " : "   ");
        buffer.append(!_unlockStatus.tailsRhythmBadgeUnlocked ? "RB" : "  ");
        SetDebugFontColor(this->_TailsColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_knucklesMissions > 0)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.knucklesUnlocked ? "K  " : "   ");
        buffer.append(_unlockStatus.knucklesShovelClawUnlocked ? "SC " : "   ");
        buffer.append(_unlockStatus.knucklesFightingGlovesUnlocked ? "FG" : "  ");
        SetDebugFontColor(this->_KnucklesColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.knucklesUnlocked ? "K: " : " : ");
        buffer.append(!_unlockStatus.knucklesShovelClawUnlocked ? "SC " : "   ");
        buffer.append(!_unlockStatus.knucklesFightingGlovesUnlocked ? "FG" : "  ");
        SetDebugFontColor(this->_KnucklesColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_amyMissions > 0)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.amyUnlocked ? "A  " : "   ");
        buffer.append(_unlockStatus.amyLongHammerUnlocked ? "LH " : "   ");
        buffer.append(_unlockStatus.amyWarriorFeatherUnlocked ? "WF" : "  ");
        SetDebugFontColor(this->_AmyColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.amyUnlocked ? "A: " : " : ");
        buffer.append(!_unlockStatus.amyLongHammerUnlocked ? "LH " : "   ");
        buffer.append(!_unlockStatus.amyWarriorFeatherUnlocked ? "WF" : "  ");
        SetDebugFontColor(this->_AmyColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }

    if (_bigMissions > 0)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.bigUnlocked ? "B  " : "   ");
        buffer.append(_unlockStatus.bigLifeRingUnlocked ? "LR " : "   ");
        buffer.append(_unlockStatus.bigPowerRodUnlocked ? "PR" : "  ");
        SetDebugFontColor(this->_BigColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.bigUnlocked ? "B: " : " : ");
        buffer.append(!_unlockStatus.bigLifeRingUnlocked ? "LR " : "   ");
        buffer.append(!_unlockStatus.bigPowerRodUnlocked ? "PR" : "  ");
        SetDebugFontColor(this->_BigColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }
    if (_gammaMissions > 0)
    {
        displayOffset++;
        buffer.clear();
        buffer.append(_unlockStatus.gammaUnlocked ? "G  " : "   ");
        buffer.append(_unlockStatus.gammaJetBoosterUnlocked ? "JB " : "   ");
        buffer.append(_unlockStatus.gammaLaserBlasterUnlocked ? "LB" : "  ");
        SetDebugFontColor(this->_GamnmaColor);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
        buffer.clear();
        buffer.append(!_unlockStatus.gammaUnlocked ? "G: " : " : ");
        buffer.append(!_unlockStatus.gammaJetBoosterUnlocked ? "JB " : "   ");
        buffer.append(!_unlockStatus.gammaLaserBlasterUnlocked ? "LB" : "  ");
        SetDebugFontColor(this->_GamnmaColor & 0x00FFFFFF | 0x66000000);
        DisplayDebugString(NJM_LOCATION(2, this->_startLine + this->_displayCount+displayOffset), buffer.c_str());
    }
}
