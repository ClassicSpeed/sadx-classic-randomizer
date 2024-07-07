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

    DisplayEmblemCount();
}

void DisplayManager::ShowStatusInformation(std::string information)
{
    SetDebugFontSize(this->_debugFontSize);
    SetDebugFontColor(_displayStatusColor);
    DisplayDebugString(NJM_LOCATION(1, 1), ("> " + information).c_str());
}

void DisplayManager::ShowEmblemCount(int emblemCount)
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
        DisplayDebugString(NJM_LOCATION(1, this->_startLine + i), _currentMessages[i].message.c_str());
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
        NJM_LOCATION(1, this->_startLine - 1), ("Emblems: " + std::to_string(_emblemCount)).c_str());
}
