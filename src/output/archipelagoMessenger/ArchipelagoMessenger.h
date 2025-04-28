#pragma once
#include "../../pch.h"
#include "../../application/structs/Options.h"

class ArchipelagoMessenger
{
public:
    explicit ArchipelagoMessenger(int instanceId, int64_t baseId);
    void CheckLocation(int locationId);
    void GameCompleted();
    void SendDeath(std::string playerName);
    void UpdateTags(Options options);
    void SendRingUpdate(int ringDifference);
    void SendHardRingUpdate(int ringDifference);
    void SendTrapLink(std::string trapName, std::string playerName);

private:
    void SendRingPacket(int ringDifference, const std::string& tagName);
    int _instanceId = 0;
    int64_t _baseId;
};
