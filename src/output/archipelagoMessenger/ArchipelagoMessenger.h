#pragma once
#include "../../pch.h"
#include "../../configuration/Options.h"

class ArchipelagoMessenger
{
public:
    explicit ArchipelagoMessenger(Options& options);
    void CheckLocation(int locationId);
    void GameCompleted();
    void SendDeath(std::string playerName);
    void UpdateTags(Options options);
    void SendRingUpdate(int ringDifference);
    void SendHardRingUpdate(int ringDifference);
    void SendTrapLink(std::string trapName, std::string playerName);

private:
    Options& _options;
    void SendRingPacket(int ringDifference, const std::string& tagName);
};
