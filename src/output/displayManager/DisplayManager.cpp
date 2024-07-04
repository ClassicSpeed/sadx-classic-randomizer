#include "DisplayManager.h"


void DisplayManager::QueueMessage(const std::string& message)
{
    _messagesQueue.push(message);
}


void DisplayManager::OnFrame()
{
    RemoveExpiredMessages();

    AddNewMessages();

    DisplayMessages();
}

void DisplayManager::ShowStatusInformation(std::string information)
{
    SetDebugFontSize(this->_debugFontSize);
    SetDebugFontColor(0xFF00FFFF);
    DisplayDebugString(NJM_LOCATION(1, 1), ("> " + information).c_str());
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
        SetDebugFontColor(this->_displayColor);
        DisplayDebugString(NJM_LOCATION(1, this->_startLine + i), _currentMessages[i].message.c_str());
    }
}
