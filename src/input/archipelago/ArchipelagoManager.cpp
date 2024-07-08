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


FunctionHook<BOOL> onTrialMenu(0x506780, []()-> BOOL
{
    if (GameMode == GameModes_Menu && archipelagoManagerPtr->IsWaitingForSaveFile())
        archipelagoManagerPtr->OnSaveFileLoaded();

    return onTrialMenu.Original();
});


void ArchipelagoManager::OnFrame()
{
    if (_status == BadSaveFile)
        return _randomizer.ShowStatusInformation("Incorrect Save File. Relaunch game and load the correct save.");

    if (_status == ReadyForConnection)
        return _randomizer.ShowStatusInformation("Load a Save File to Connect.");

    if (_status == SaveFileSelected)
        return this->Connect();

    if (_status == AttemptedConnection)
    {
        if (AP_GetConnectionStatus() != AP_ConnectionStatus::Authenticated)
        {
            const double timePassed = (std::clock() - this->_connectedAt) / static_cast<double>(CLOCKS_PER_SEC);
            if (timePassed > _suggestChangingConfigWaitTime)
                return _randomizer.ShowStatusInformation("Still connecting, check your configs...");
            return _randomizer.ShowStatusInformation("Connecting...");
        }

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

    this->ManageMessages();
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
    PrintDebug("Reset items\n");
}

void SADX_CheckLocation(int64_t loc_id)
{
    PrintDebug("Checked location %d\n", loc_id);
}

void SADX_EmblemsForPerfectChaos(const int emblemGoal)
{
    randomizerPtr->OnEmblemGoalSet(emblemGoal);
}

void SADX_SonicMissions(const int missions)
{
    randomizerPtr->SetMissions(Characters_Sonic, missions);
}

void SADX_TailsMissions(const int missions)
{
    randomizerPtr->SetMissions(Characters_Tails, missions);
}

void SADX_KnucklesMissions(const int missions)
{
    randomizerPtr->SetMissions(Characters_Knuckles, missions);
}

void SADX_AmyMissions(const int missions)
{
    randomizerPtr->SetMissions(Characters_Amy, missions);
}

void SADX_GammaMissions(const int missions)
{
    randomizerPtr->SetMissions(Characters_Gamma, missions);
}

void SADX_BigMissions(const int missions)
{
    randomizerPtr->SetMissions(Characters_Big, missions);
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
    AP_RegisterSlotDataIntCallback("EmblemsForPerfectChaos", &SADX_EmblemsForPerfectChaos);
    AP_RegisterSlotDataIntCallback("SonicMissions", &SADX_SonicMissions);
    AP_RegisterSlotDataIntCallback("TailsMissions", &SADX_TailsMissions);
    AP_RegisterSlotDataIntCallback("KnucklesMissions", &SADX_KnucklesMissions);
    AP_RegisterSlotDataIntCallback("AmyMissions", &SADX_AmyMissions);
    AP_RegisterSlotDataIntCallback("GammaMissions", &SADX_GammaMissions);
    AP_RegisterSlotDataIntCallback("BigMissions", &SADX_BigMissions);
    AP_Start();

    _connectedAt = std::clock();
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

    char seedHash = CalculateHash(this->_seedName + this->_playerName);
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


void ArchipelagoManager::ManageMessages()
{
    if (!AP_IsMessagePending())
        return;

    AP_Message* msg = AP_GetLatestMessage();

    EnqueueMessage(msg);
    AP_ClearLatestMessage();
}

void ArchipelagoManager::EnqueueMessage(AP_Message* msg)
{
    if (!msg)
        return;
    switch (msg->type)
    {
    case AP_MessageType::ItemSend:
        {
            AP_ItemSendMessage* sendMsg = static_cast<AP_ItemSendMessage*>(msg);
            if (!sendMsg)
                return;
            return _randomizer.QueueNewMessage("Sent " + sendMsg->item + " to " + sendMsg->recvPlayer);
        }
    case AP_MessageType::ItemRecv:
        {
            AP_ItemRecvMessage* recvMsg = static_cast<AP_ItemRecvMessage*>(msg);
            if (!recvMsg)
                return;
            return _randomizer.QueueNewMessage("Received " + recvMsg->item + " from " + recvMsg->sendPlayer);
        }
    case AP_MessageType::Hint:
        {
            AP_HintMessage* hintMsg = static_cast<AP_HintMessage*>(msg);

            if (!hintMsg)
                return;
            std::string foundText = hintMsg->checked ? " (found)" : " (not found)";

            _randomizer.QueueNewMessage(hintMsg->recvPlayer + "'s " + hintMsg->item + " can be found at");
            _randomizer.QueueNewMessage("  " + hintMsg->location + " in " + hintMsg->sendPlayer + "'s world." +
                foundText);
            return;
        }
    case AP_MessageType::Plaintext:
    case AP_MessageType::Countdown:
    default:
        {
            // Do nothing, avoid spam
        }
    }
}
