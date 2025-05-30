#pragma once
#include <queue>
#include <string>
#include "../../application/structs/ItemData.h"
#include "../../application/structs/Message.h"
#include "../../application/structs/UnlockStatus.h"
#include "../../application/structs/LevelStatus.h"
#include "../../application/structs/MissionStatus.h"
#include "../../application/structs/BossesStatus.h"
#include "../../application/structs/ChaoStatus.h"
#include "../../application/structs/VisitedLevels.h"
#include "../../configuration/Options.h"
#include "../../application/structs/LocationData.h"
#include "../../configuration/Options.h"


struct LocationData;


enum DisplayInGameTracker
{
    DisplayTrackerWhenPaused = 0,
    DisplayTrackerAlwaysOn = 1,
    DisplayTrackerAlwaysOff = 2,
};

class DisplayManager
{
public:
    static DisplayManager& Init(Options& options)
    {
        if (_instance == nullptr)
            _instance = new DisplayManager(options);
        return *_instance;
    }

    void QueueItemMessage(const std::string& message);
    void QueueChatMessage(const std::string& message);
    void ShowSongName(const std::string& songName);
    void UpdateUnlockStatus(UnlockStatus unlockStatus);
    void UpdateLevelStatus(LevelStatus levelStatus);
    void UpdateMissionStatus(MissionStatus missionStatus);
    void UpdateBossesStatus(BossesStatus bossesStatus);
    void UpdateChaoStatus(ChaoStatus chaoStatus);
    void UpdateVisitedLevels(VisitedLevels visitedLevels);
    void OnFrame();
    void ShowStatusInformation(std::string information);
    void ShowGoalStatus();
    void OnEnterCharacterSelectScreen();
    void OnExitCharacterSelectScreen();
    void UpdateChecks(const std::map<int, LocationData>& checkData);
    void SetMessageConfiguration(float messageDisplayDuration, int messageFontSize,
                                 DisplayInGameTracker displayInGameTracker, int itemMessageColor, int chatMessageColor);
    void UpdateVoiceMenuCharacter(int characterVoiceIndex);
    void SetConnected();

    static void OnCharSelAdvaModeProcedure(AdvaModeEnum adventureMode);
    static void OnCmnAdvaModeProcedure(AdvaModeEnum adventureMode);
    static Sint32 OnFinishedLevelMaybe();
    static SEQ_SECTIONTBL* OnStorySelected(int playerNumber);

private:
    explicit DisplayManager(Options& options);
    static DisplayManager* _instance;


    void RemoveExpiredMessages();
    void AddNewMessages();
    void DisplayItemMessages() const;
    void DisplayChatMessages();
    void DisplaySongName();
    void DisplayGoalStatus();
    std::string GetMissionBTarget(bool showTarget);
    std::string GetMissionATarget(bool showTarget);
    std::string GetMissionSTarget(bool showTarget, bool expertMode);
    void DisplayItemsUnlocked();

    int _voiceMenuCharacter = 0;

    int _startLine = 2;
    size_t _displayCount = 5;
    int _displayMessageColor = 0xFF33FF33; //Green
    int _displayStatusColor = 0xFF00FFFF; //Cyan
    int _displayEmblemColor = 0xFFF2C600; //Orange

    bool _inCharacterSelectScreen;
    bool _connected = false;

    float _displayDuration = 6.0f;
    unsigned __int16 _debugFontSize = 21;
    DisplayInGameTracker _displayInGameTracker = DisplayTrackerWhenPaused;
    std::queue<std::string> _itemMessagesQueue;
    std::deque<Message> _currentMessages;

    int _chatMessageColor = 0xFFFFFFFF;
    int _chatDisplayCount = 5;
    std::vector<std::string> _chatMessagesQueue;
    std::clock_t _lastMessageTime = -1;

    std::string _songName = "Unknown";
    std::clock_t _songNameTime = -1;

    std::clock_t _goalTimer = -1;

    std::clock_t _unlockStatusTimer;
    float _unlockStatusDelay = 0.3f;

    UnlockStatus _unlockStatus;
    LevelStatus _levelStatus;
    MissionStatus _missionStatus;
    BossesStatus _bossesStatus;
    ChaoStatus _chaoStatus;
    VisitedLevels _visitedLevels;
    Options& _options;


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
