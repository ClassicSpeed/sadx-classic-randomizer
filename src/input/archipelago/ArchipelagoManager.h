﻿#pragma once
#include "../../application/Randomizer.h"

enum ConnectionStatus
{
    ReadyForConnection,
    SaveFileSelected,
    AttemptedConnection,
    Connected,

    BadSaveFile,
};

class ArchipelagoManager
{
public:
    explicit ArchipelagoManager(Randomizer& randomizer, int instanceId, int64_t baseId);

    void Connect();
    bool IsValidSaveFile();
    void OnFrame();
    bool IsWaitingForSaveFile();
    void OnSaveFileLoaded();
    void SetServerConfiguration(const std::string& serverIP, const std::string& playerName,
                                const std::string& serverPassword);

    std::string playerName;
    int instanceId = 0;
    int64_t baseId;

private:
    void ManageMessages();
    void EnqueueMessage(AP_Message* msg);

    Randomizer& _randomizer;
    mutable std::string _configPath;
    ConnectionStatus _status = ReadyForConnection;


    std::string _serverIP;
    std::string _serverPassword;
    std::string _seedName;

    const float _suggestChangingConfigWaitTime = 2.5f;
    std::clock_t _connectedAt = -1;

};
