#pragma once
#include "../../application/Randomizer.h"

constexpr int MOD_VERSION = 003;

enum ConnectionStatus
{
    ReadyForConnection,
    SaveFileSelected,
    AttemptedConnection,
    Connected,

    BadSaveFile,
    BadVersion
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
    
    // bool _authFailed = false;
    // bool _badSaveFile = false;
    // bool _badSaveName = false;
    // bool _badModVersion = false;


    //Own state
    // bool _sadxFileSelected = false;
    // bool _sadxAttemptedConnected = false;
    // bool _sadxAlreadyConnected = false;
    
    int _serverModVersion = 0;

    
    std::string ap_player_name;
    std::string _seedName;
};
