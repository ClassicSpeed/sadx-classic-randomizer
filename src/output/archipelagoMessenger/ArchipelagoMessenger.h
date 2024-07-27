#pragma once
#include "../../pch.h"
#include "../../application/structs/Options.h"

class ArchipelagoMessenger
{
public:
    explicit ArchipelagoMessenger(int instanceId, int64_t baseId);
    void CheckLocation(int locationId);
    void GameCompleted();
    void SendDeath();
    void UpdateTags(Options options);
    void SendRingUpdate(int ringDifference);
private:
    int _instanceId = 0;
    int64_t _baseId;
};
