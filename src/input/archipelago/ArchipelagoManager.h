#pragma once
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
    void ManageMessages();
    void EnqueueMessage(AP_Message* msg);
    
    Randomizer& _randomizer;
    mutable std::string _configPath;
    ConnectionStatus _status = ReadyForConnection;


    std::string _playerName;
    std::string _seedName;

    const float _suggestChangingConfigWaitTime = 2.5f;
    std::clock_t _connectedAt;
};
