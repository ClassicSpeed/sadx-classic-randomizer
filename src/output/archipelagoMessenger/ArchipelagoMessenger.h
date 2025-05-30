#pragma once
#include "../../pch.h"
#include "../../configuration/Options.h"

class ArchipelagoMessenger
{
public:
    static ArchipelagoMessenger& Init(Options& options)
    {
        if (_instance == nullptr)
            _instance = new ArchipelagoMessenger(options);
        return *_instance;
    }

    void CheckLocation(int locationId);
    void GameCompleted();
    void SendDeath(std::string playerName);
    void UpdateTags(Options options);
    void SendRingUpdate(int ringDifference);
    void SendHardRingUpdate(int ringDifference);
    void SendTrapLink(std::string trapName, std::string playerName);

private:
    explicit ArchipelagoMessenger(Options& options);
    inline static ArchipelagoMessenger* _instance = nullptr;
    Options& _options;
    void SendRingPacket(int ringDifference, const std::string& tagName);
};
