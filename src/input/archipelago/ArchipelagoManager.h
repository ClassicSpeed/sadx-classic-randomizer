#pragma once
#include "../../application/randomizer/Randomizer.h"
#include "../../application/link/Link.h"
#include "../../configuration/options/Options.h"

#define AP_REGISTER_INT_CALLBACK(key, method) \
AP_RegisterSlotDataIntCallback(key, [this](const int value) { method(value); })
#define AP_REGISTER_INT_CALLBACK_CHARACTER(key, method, character) \
AP_RegisterSlotDataIntCallback(key, [this](const int value) { method(character, value); })
#define AP_REGISTER_MAP_CALLBACK(key, method) \
AP_RegisterSlotDataMapIntIntCallback(key, [this](const std::map<int, int>& value) { method(value); })


enum ConnectionStatus
{
    ReadyForConnection,
    SaveFileSelected,
    AttemptedConnection,
    Connected,

    BadSaveFile,
};

class ArchipelagoManager: public IOnFrame
{
public:
    static ArchipelagoManager& Init(Options& options, Settings& settings, Randomizer& randomizer, Link& link)
    {
        if (_instance == nullptr)
            _instance = new ArchipelagoManager(options, settings, randomizer, link);
        return *_instance;
    }
    void OnFrame() override;

    void Connect();
    bool IsValidSaveFile();
    bool IsWaitingForSaveFile();
    void ReceiveItem(int64_t itemId, bool notify);
    void ResetItems();
    void CheckLocation(int64_t locationId);
    void HandleBouncedPacket(AP_Bounce bouncePacket);
    void CompareModVersion(int serverVersion);

private:
    explicit ArchipelagoManager(Options& options, Settings& settings, Randomizer& randomizer, Link& link);
    inline static ArchipelagoManager* _instance = nullptr;
    Options& _options;
    Settings& _settings;
    Randomizer& _randomizer;
    Link& _link;

    inline static FunctionHook<BOOL> _loadTrialMenuHook{0x506780};
    static BOOL OnLoadTrialMenu();

    void ManageMessages();
    void EnqueueMessage(AP_Message* msg);

    mutable std::string _configPath;
    ConnectionStatus _status = ReadyForConnection;
    std::string _seedName;

    const float _suggestChangingConfigWaitTime = 2.5f;
    std::clock_t _connectedAt = -1;
};
