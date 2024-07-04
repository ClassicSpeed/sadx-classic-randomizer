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

private:
    void RemoveExpiredMessages();
    void AddNewMessages();
    void DisplayMessages() const;

    int _startLine = 1;
    size_t _displayCount = 5;
    int _displayColor = 0xFF33FF33;
    float _displayDuration = 6.0f;
    unsigned __int16 _debugFontSize = 20;
    std::queue<std::string> _messagesQueue;
    std::deque<Message> _currentMessages;
};
