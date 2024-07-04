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
    explicit ArchipelagoManager(Randomizer& randomizer);

    void Connect();
    bool IsValidSaveFile();
    void OnFrame();
    void SetConfigPath(std::string configPath) const;
    bool IsWaitingForSaveFile();
    void OnSaveFileLoaded();

private:
    Randomizer& _randomizer;
    mutable std::string _configPath;
    ConnectionStatus _status = ReadyForConnection;


    std::string _playerName;
    std::string _seedName;
};
