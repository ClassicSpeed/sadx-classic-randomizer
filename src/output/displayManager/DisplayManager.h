#pragma once
#include <queue>
#include <string>
#include "../../application/structs/ItemData.h"
#include "../../application/structs/Message.h"
#include "../../application/structs/UnlockStatus.h"


class DisplayManager
{
public:
    DisplayManager();

    void QueueMessage(const std::string& message);
    void UpdateUnlockStatus(UnlockStatus unlockStatus);
    void OnFrame();
    void ShowStatusInformation(std::string information);
    void ShowEmblemCount(int emblemCount);
    void OnEnterCharacterSelectScreen();
    void OnExitCharacterSelectScreen();
    void SetMissions(Characters characters, int missions);

private:
    void RemoveExpiredMessages();
    void AddNewMessages();
    void DisplayMessages() const;
    void DisplayEmblemCount();
    void DisplayItemsUnlocked();

    int _startLine = 2;
    size_t _displayCount = 5;
    int _displayMessageColor = 0xFF33FF33; //Green
    int _displayStatusColor = 0xFF00FFFF; //Cyan
    int _displayEmblemColor = 0xFFF2C600; //Orange

    bool _inCharacterSelectScreen;

    
    int _SonicColor = 0xFF1A50BC;
    int _TailsColor = 0xFFF1B000; 
    int _KnucklesColor = 0xFFFF1400; 
    int _AmyColor = 0xFFFD95C6; 
    int _BigColor = 0xFF7505f5; 
    int _GamnmaColor = 0xFF827f80; 
    float _displayDuration = 6.0f;
    unsigned __int16 _debugFontSize = 21;
    std::queue<std::string> _messagesQueue;
    std::deque<Message> _currentMessages;
    
    int _emblemCount = -1;
    std::clock_t _emblemTimer;
    
    std::clock_t _unlockStatusTimer;
    float _unlockStatusDelay = 0.3f;

    UnlockStatus _unlockStatus;

    int _sonicMissions;
    int _tailsMissions;
    int _knucklesMissions;
    int _amyMissions;
    int _bigMissions;
    int _gammaMissions;
};
