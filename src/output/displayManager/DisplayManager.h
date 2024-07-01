#pragma once
#include <map>
#include <queue>
#include <string>
#include "../../application/structs/ItemData.h"
#include "../../application/structs/Message.h"


class DisplayManager
{
public:
    void FoundItem(std::string displayName);
    void ReceiveItem(std::string displayName);
    void OnFrame();

private:
    void RemoveExpiredMessages();
    void AddNewMessages();
    void DisplayMessages() const;

    int _startLine = 15;
    size_t _displayCount = 5;
    int _displayColor = 0xFFF542C8;
    float _displayDuration = 6.0f;
    unsigned __int16 _debugFontSize = 16;
    std::queue<std::string> _messagesQueue;
    std::deque<Message> _currentMessages;
};
