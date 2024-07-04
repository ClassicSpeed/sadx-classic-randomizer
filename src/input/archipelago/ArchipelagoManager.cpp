#include "ArchipelagoManager.h"

constexpr int64_t BASE_ID = 5438000;
Randomizer* randomizerPtr = nullptr;
ArchipelagoManager* archipelagoManagerPtr = nullptr;

ArchipelagoManager::ArchipelagoManager(Randomizer& randomizer)
    : _randomizer(randomizer)
{
    randomizerPtr = &this->_randomizer;
    archipelagoManagerPtr = this;
}


BOOL OnFileSelect();
FunctionHook<BOOL> blockTrialMenu(0x506780, OnFileSelect);

BOOL OnFileSelect()
{
    if (GameMode == GameModes_Menu && archipelagoManagerPtr->IsWaitingForSaveFile())
        archipelagoManagerPtr->OnSaveFileLoaded();

    return false;
}


void ArchipelagoManager::OnFrame()
{
    if (_status == BadSaveFile)
        return _randomizer.ShowStatusInformation("Incorrect Save File. Relaunch game and load the correct save.");

    if (_status == ReadyForConnection)
        return _randomizer.ShowStatusInformation("Load a Save File to Connect");

    if (_status == SaveFileSelected)
        return this->Connect();

    if (_status == AttemptedConnection)
    {
        if (AP_GetConnectionStatus() != AP_ConnectionStatus::Authenticated)
            return _randomizer.ShowStatusInformation("Connecting...");

        const bool validSaveFile = this->IsValidSaveFile();
        if (!validSaveFile)
        {
            _status = BadSaveFile;
            return;
        }

        _status = Connected;
        _randomizer.OnConnected();
        return;
    }

    if (_status == Connected && AP_GetConnectionStatus() != AP_ConnectionStatus::Authenticated)
        return _randomizer.ShowStatusInformation("Connection to Archipelago lost. Reconnecting...");
}


void ArchipelagoManager::SetConfigPath(std::string configPath) const
{
    _configPath = configPath;
}

bool ArchipelagoManager::IsWaitingForSaveFile()
{
    return _status == ReadyForConnection;
}

void ArchipelagoManager::OnSaveFileLoaded()
{
    _status = SaveFileSelected;
}


void SADX_RecvItem(const int64_t itemId, bool notify)
{
    randomizerPtr->OnItemReceived(itemId - BASE_ID);
}

void SADX_ResetItems()
{
    //TODO: Do something?
    PrintDebug("Reset items\n");
}

void SADX_CheckLocation(int64_t loc_id)
{
    //TODO: Do something?
    PrintDebug("Checked location %d\n", loc_id);
}

void ArchipelagoManager::Connect()
{
    if (_configPath.empty())
        return _randomizer.ShowStatusInformation("Invalid Config Path");

    const IniFile* settingsINI = new IniFile(_configPath);

    if (!settingsINI)
        return _randomizer.ShowStatusInformation("Invalid Settings INI");

    //TODO: Improve configuration
    std::string serverIP = settingsINI->getString("AP", "IP");
    std::string playerName = settingsINI->getString("AP", "PlayerName");
    std::string serverPassword = settingsINI->getString("AP", "Password");
    AP_Init(serverIP.c_str(), "Sonic Adventure DX", playerName.c_str(), serverPassword.c_str());

    this->_playerName = playerName;

    AP_SetItemClearCallback(&SADX_ResetItems);
    AP_SetItemRecvCallback(&SADX_RecvItem);
    AP_SetLocationCheckedCallback(&SADX_CheckLocation);
    AP_Start();

    _status = AttemptedConnection;
}

char CalculateHash(const std::string& input)
{
    unsigned int hashValue = 0;

    for (char c : input)
    {
        hashValue += static_cast<unsigned char>(c);
    }

    return static_cast<char>(hashValue % 256);
}

bool ArchipelagoManager::IsValidSaveFile()
{
    AP_RoomInfo roomInfo;
    AP_GetRoomInfo(&roomInfo);
    if (this->_seedName.length() != 0)
        return true;
    if (roomInfo.seed_name.length() == 0)
        return true;
    this->_seedName = roomInfo.seed_name;

    char seedHash = CalculateHash(this->_seedName);
    if (SaveFile.gap_25b[0] == 0 && SaveFile.PlayTime < 10)
    {
        SaveFile.gap_25b[0] = seedHash;
        WriteSaveFile();
        return true;
    }

    if (SaveFile.gap_25b[0] == seedHash)
        return true;
    
    return false;
}
