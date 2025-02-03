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

enum DeathLinkOverride
{
    DeathLinkDefault = 0,
    DeathLinkForceEnabled = 1,
    DeathLinkForceDisabled = 2,
};

enum RingLinkOverride
{
    RingLinkDefault = 0,
    RingLinkForceEnabled = 1,
    RingLinkForceEnabledHard = 2,
    RingLinkForceDisabled = 3,
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
    void SetServerConfiguration(const std::string& serverIp, const std::string& newPlayerName,
                                const std::string& serverPassword, DeathLinkOverride newDeathLinkOverride,
                                RingLinkOverride newRingLinkOverride,
                                bool showChatMessages, bool showGoalReached,
                                bool showCountdowns, bool showPlayerConnections);

    std::string playerName;
    int instanceId = 0;
    int64_t baseId;
    DeathLinkOverride deathLinkOverride;
    RingLinkOverride ringLinkOverride;

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

    bool _showChatMessages = true;
    bool _showGoalReached = true;
    bool _showCountdowns = true;
    bool _showPlayerConnections = false;
};
