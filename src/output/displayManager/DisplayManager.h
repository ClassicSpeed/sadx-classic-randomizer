#pragma once
#include <queue>
#include <string>
#include "../../application/structs/ItemData.h"
#include "../../application/structs/Message.h"


class DisplayManager
{
public:
    void QueueMessage(const std::string& message);
    void OnFrame();
    void ShowStatusInformation(std::string information);
    void ShowEmblemCount(int emblemCount);

private:
    void RemoveExpiredMessages();
    void AddNewMessages();
    void DisplayMessages() const;
    void DisplayEmblemCount();

    int _startLine = 2;
    size_t _displayCount = 5;
    int _displayMessageColor = 0xFF33FF33;
    int _displayStatusColor = 0xFF00FFFF;
    int _displayEmblemColor = 0xFFF2C600;
    float _displayDuration = 6.0f;
    unsigned __int16 _debugFontSize = 20;
    std::queue<std::string> _messagesQueue;
    std::deque<Message> _currentMessages;
    
    int _emblemCount = -1;
    std::clock_t _emblemTimer;
};
