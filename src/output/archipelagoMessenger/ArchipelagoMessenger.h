#pragma once
#include "../../pch.h"
#include "../../configuration/options/Options.h"
#include "../../configuration/gameStatus/GameStatus.h"

class ArchipelagoMessenger
{
public:
    static ArchipelagoMessenger& Init(Options& options, GameStatus& gameStatus)
    {
        if (_instance == nullptr)
            _instance = new ArchipelagoMessenger(options, gameStatus);
        return *_instance;
    }

    void CheckLocation(int locationId);
    void GameCompleted();
    void SendDeath(std::string playerName);
    void UpdateTags();
    void SendRingUpdate(int ringDifference);
    void SendHardRingUpdate(int ringDifference);
    void SendTrapLink(std::string trapName, std::string playerName);
    void SetMapStatus();

private:
    explicit ArchipelagoMessenger(Options& options, GameStatus& gameStatus);
    inline static ArchipelagoMessenger* _instance = nullptr;
    Options& _options;
    GameStatus& _gameStatus;
    void SendRingPacket(int ringDifference, const std::string& tagName);
};
