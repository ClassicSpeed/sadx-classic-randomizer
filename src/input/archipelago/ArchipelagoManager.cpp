#include "ArchipelagoManager.h"
#include "../../pch.h"

constexpr int64_t BASE_ID = 5438000;
Randomizer* randomizerPtr = nullptr;


ArchipelagoManager::ArchipelagoManager(Randomizer& randomizer)
    : _randomizer(randomizer), _connected(false)
{
    randomizerPtr = &this->_randomizer;
}

void ArchipelagoManager::OnFrame()
{
    //TODO: Check savefile

    //TODO: Check mod version

    //TODO: Check connection lost

    if (!_connected)
    {
        this->Connect();
    }
}

void ArchipelagoManager::SetConfigPath(std::string configPath) const
{
    _configPath = configPath;
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
    //TODO: Get settings from configuration
    if (_configPath.empty())
        return;

    const IniFile* settingsINI = new IniFile(_configPath);
    std::string serverIP = settingsINI->getString("AP", "IP");
    std::string playerName = settingsINI->getString("AP", "PlayerName");
    std::string serverPassword = settingsINI->getString("AP", "Password");
    AP_Init(serverIP.c_str(), "Sonic Adventure DX", playerName.c_str(), serverPassword.c_str());
    AP_SetItemClearCallback(&SADX_ResetItems);
    AP_SetItemRecvCallback(&SADX_RecvItem);
    AP_SetLocationCheckedCallback(&SADX_CheckLocation);
    AP_Start();
    _randomizer.OnConnected();
    _connected = true;
}
