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
#include "../../configuration/options/Options.h"
#include "../../application/structs/LocationData.h"


struct LocationData;


class DisplayManager
{
public:
    static DisplayManager& Init(Options& options, Settings& settings)
    {
        if (_instance == nullptr)
            _instance = new DisplayManager(options, settings);
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
    void UpdateChecks(const std::map<int, LocationData>& checkData);
    void SetConnected();

private:
    explicit DisplayManager(Options& options, Settings& settings);
    inline static DisplayManager* _instance = nullptr;
    Options& _options;
    Settings& _settings;

    inline static FunctionHook<void, AdvaModeEnum> _charSelAdvaModeProcedureHook{0x505E60};
    static void OnCharSelAdvaModeProcedure(AdvaModeEnum adventureMode);
    
    inline static FunctionHook<void, AdvaModeEnum> _cmnAdvaModeProcedureHook{0x505B40};
    static void OnCmnAdvaModeProcedure(AdvaModeEnum adventureMode);
    
    inline static FunctionHook<Sint32> _finishedLevelMaybeHook{0x414090};
    static Sint32 OnFinishedLevelMaybe();
    
    inline static FunctionHook<SEQ_SECTIONTBL*, int> _storySelectedHook{0x44EAF0};
    static SEQ_SECTIONTBL* OnStorySelected(int playerNumber);
    
    inline static FunctionHook<BOOL> _loadMissionMenu{0x506410};
    inline static FunctionHook<BOOL> _loadTrialMenu{0x506780};

    
    void OnEnterCharacterSelectScreen();
    void OnExitCharacterSelectScreen();
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


    int _startLine = 2;
    size_t _displayCount = 5;
    int _displayStatusColor = 0xFF00FFFF; //Cyan
    int _displayEmblemColor = 0xFFF2C600; //Orange

    bool _inCharacterSelectScreen;
    bool _connected = false;

    std::queue<std::string> _itemMessagesQueue;
    std::deque<Message> _currentMessages;

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
