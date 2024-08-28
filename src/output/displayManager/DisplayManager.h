#pragma once
#include <queue>
#include <string>
#include "../../application/structs/ItemData.h"
#include "../../application/structs/Message.h"
#include "../../application/structs/UnlockStatus.h"
#include "../../application/structs/LevelStatus.h"
#include "../../application/structs/Options.h"
#include "../../application/structs/LocationData.h"


struct LocationData;

class DisplayManager
{
public:
    DisplayManager();

    void QueueMessage(const std::string& message);
    void UpdateUnlockStatus(UnlockStatus unlockStatus);
    void UpdateLevelStatus(LevelStatus levelStatus);
    void UpdateOptions(Options options);
    void OnFrame();
    void ShowStatusInformation(std::string information);
    void ShowGoalStatus();
    void OnEnterCharacterSelectScreen();
    void OnExitCharacterSelectScreen();
    void UpdateChecks(const std::map<int, LocationData>& checkData);
    void SetMessageConfiguration(float messageDisplayDuration, int messageFontSize, int messageColor);

private:
    void RemoveExpiredMessages();
    void AddNewMessages();
    void DisplayMessages() const;
    void DisplayGoalStatus();
    std::string GetMissionBTarget(bool showTarget);
    std::string GetMissionATarget(bool showTarget);
    void DisplayItemsUnlocked();

    int _startLine = 2;
    size_t _displayCount = 5;
    int _displayMessageColor = 0xFF33FF33; //Green
    int _displayStatusColor = 0xFF00FFFF; //Cyan
    int _displayEmblemColor = 0xFFF2C600; //Orange

    bool _inCharacterSelectScreen;


    float _displayDuration = 6.0f;
    unsigned __int16 _debugFontSize = 21;
    std::queue<std::string> _messagesQueue;
    std::deque<Message> _currentMessages;

    std::clock_t _goalTimer = -1;

    std::clock_t _unlockStatusTimer;
    float _unlockStatusDelay = 0.3f;

    UnlockStatus _unlockStatus;
    LevelStatus _levelStatus;
    Options _options;


    int _keyItemColor = 0xFFF2C600;

    int _sonicColor = 0xFF0D7ADF;
    int _tailsColor = 0xFFF1B000;
    int _knucklesColor = 0xFFFF1400;
    int _amyColor = 0xFFFD95C6;
    int _bigColor = 0xFF7505f5;
    int _gammaColor = 0xFF827f80;

    
    int _whiteEmeraldColor = 0xDDFFFFFF;
    int _redEmeraldColor = 0xDDFF0000;
    int _cyanEmeraldColor = 0xDD00FFFF;
    int _purpleEmeraldColor = 0xDD800080;
    int _greenEmeraldColor = 0xDD00FF00;
    int _yellowEmeraldColor = 0xDDFFFF00;
    int _blueEmeraldColor = 0xDD0000FF;


    mutable std::map<int, LocationData> _checkData;
};
