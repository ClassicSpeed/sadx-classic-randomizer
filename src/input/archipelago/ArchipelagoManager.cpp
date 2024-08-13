#include "ArchipelagoManager.h"

Randomizer* randomizerPtr = nullptr;
ArchipelagoManager* archipelagoManagerPtr = nullptr;

ArchipelagoManager::ArchipelagoManager(Randomizer& randomizer, const int instanceId, const int64_t baseId)
    : _randomizer(randomizer)
{
    randomizerPtr = &this->_randomizer;
    archipelagoManagerPtr = this;
    this->instanceId = instanceId;
    this->baseId = baseId;
}


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
        _randomizer.OnConnected(playerName);
        return;
    }

    if (_status == Connected && AP_GetConnectionStatus() != AP_ConnectionStatus::Authenticated)
        return _randomizer.ShowStatusInformation("Connection to Archipelago lost. Reconnecting...");

    this->ManageMessages();
}


void ArchipelagoManager::SetServerConfiguration(const std::string& serverIP, const std::string& playerNameConfig,
                                                const std::string& serverPassword)
{
    this->_serverIP = serverIP;
    this->playerName = playerNameConfig;
    this->_serverPassword = serverPassword;
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
    PrintDebug(" --- Item received: %d\n", itemId);
    randomizerPtr->OnItemReceived(itemId - archipelagoManagerPtr->baseId);
}

void SADX_ResetItems()
{
    PrintDebug(" --- Reset items\n");
    randomizerPtr->ResetItems();
}

void SADX_CheckLocation(int64_t loc_id)
{
    PrintDebug(" --- Checked location %d\n", loc_id);
    randomizerPtr->MarkCheckedLocation(loc_id - archipelagoManagerPtr->baseId);
}

void SADX_HandleBouncedPacket(AP_Bounce bouncePacket)
{
    Json::Value bounceData;
    Json::Reader reader;
    reader.parse(bouncePacket.data, bounceData);

    if (bouncePacket.tags == nullptr)
        return;

    for (const auto& tag : *bouncePacket.tags)
    {
        if (tag.length() == 0)
            return;

        if (!strcmp(tag.c_str(), "DeathLink"))
        {
            if (!randomizerPtr->GetOptions().deathLinkActive)
                return;

            //Ignore our own death link    
            if (!strcmp(bounceData["source"].asCString(), archipelagoManagerPtr->playerName.c_str()))
                break;

            std::string deathCause;
            if (!bounceData["cause"].isNull())
                deathCause = std::string(bounceData["cause"].asCString());
            else
                deathCause = std::string("You were killed by ") + bounceData["source"].asCString();
            randomizerPtr->ProcessDeath(deathCause);
            break;
        }
        if (!strcmp(tag.c_str(), "RingLink"))
        {
            if (!randomizerPtr->GetOptions().ringLinkActive)
                return;

            //Ignore our own death link    
            if (bounceData["source"].asInt() == archipelagoManagerPtr->instanceId)
                break;

            const int amount = bounceData["amount"].asInt();

            randomizerPtr->ProcessRings(amount);
            break;
        }
    }
}

void SADX_Goal(const int goal)
{
    randomizerPtr->OnGoalSet(static_cast<Goal>(goal));
}

void SADX_EmblemsForPerfectChaos(const int emblemGoal)
{
    randomizerPtr->OnEmblemGoalSet(emblemGoal);
}

void SADX_LifeSanity(const int lifeSanity)
{
    randomizerPtr->OnLifeSanitySet(lifeSanity);
}

void SADX_PinballLifeCapsules(const int pinballLifeCapsules)
{
    randomizerPtr->OnPinballLifeCapsulesSet(pinballLifeCapsules);
}

void SADX_SonicLifeSanity(const int lifeSanity)
{
    randomizerPtr->SetCharacterLifeSanity(Characters_Sonic, lifeSanity);
}

void SADX_TailsLifeSanity(const int lifeSanity)
{
    randomizerPtr->SetCharacterLifeSanity(Characters_Tails, lifeSanity);
}

void SADX_KnucklesLifeSanity(const int lifeSanity)
{
    randomizerPtr->SetCharacterLifeSanity(Characters_Knuckles, lifeSanity);
}

void SADX_AmyLifeSanity(const int lifeSanity)
{
    randomizerPtr->SetCharacterLifeSanity(Characters_Amy, lifeSanity);
}

void SADX_GammaLifeSanity(const int lifeSanity)
{
    randomizerPtr->SetCharacterLifeSanity(Characters_Gamma, lifeSanity);
}

void SADX_BigLifeSanity(const int lifeSanity)
{
    randomizerPtr->SetCharacterLifeSanity(Characters_Big, lifeSanity);
}


void SADX_StartingArea(const int startingArea)
{
    randomizerPtr->SetStatingArea(static_cast<StartingArea>(startingArea));
}

void SADX_SetDeathLink(const int deathLinkActive)
{
    randomizerPtr->SetDeathLink(deathLinkActive);
}

void SADX_SetRingLink(const int ringLinkActive)
{
    randomizerPtr->SetRingLink(ringLinkActive);
}

void SADX_SetHardRingLink(const int hardRingLinkActive)
{
    randomizerPtr->SetHardRingLink(hardRingLinkActive);
}

void SADX_RingLoss(const int ringLoss)
{
    randomizerPtr->SetRingLoss(static_cast<RingLoss>(ringLoss));
}

void SADX_BossChecks(const int bossChecks)
{
    randomizerPtr->SetBossChecks(bossChecks);
}

void SADX_UnifyChaos4(const int unifiyChaos4)
{
    randomizerPtr->SetUnifyChaos4(unifiyChaos4);
}

void SADX_UnifyChaos6(const int unifiyChaos6)
{
    randomizerPtr->SetUnifyChaos6(unifiyChaos6);
}

void SADX_UnifyEggHornet(const int unifyEggHornet)
{
    randomizerPtr->SetUnifyEggHornet(unifyEggHornet);
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
    AP_Init(_serverIP.c_str(), "Sonic Adventure DX", playerName.c_str(), _serverPassword.c_str());

    AP_SetDeathLinkSupported(false);
    AP_SetItemClearCallback(&SADX_ResetItems);
    AP_SetItemRecvCallback(&SADX_RecvItem);
    AP_SetLocationCheckedCallback(&SADX_CheckLocation);
    AP_RegisterBouncedCallback(&SADX_HandleBouncedPacket);
    AP_RegisterSlotDataIntCallback("Goal", &SADX_Goal);
    AP_RegisterSlotDataIntCallback("EmblemsForPerfectChaos", &SADX_EmblemsForPerfectChaos);
    AP_RegisterSlotDataIntCallback("LifeSanity", &SADX_LifeSanity);
    AP_RegisterSlotDataIntCallback("PinballLifeCapsules", &SADX_PinballLifeCapsules);
    AP_RegisterSlotDataIntCallback("SonicLifeSanity", &SADX_SonicLifeSanity);
    AP_RegisterSlotDataIntCallback("TailsLifeSanity", &SADX_TailsLifeSanity);
    AP_RegisterSlotDataIntCallback("KnucklesLifeSanity", &SADX_KnucklesLifeSanity);
    AP_RegisterSlotDataIntCallback("AmyLifeSanity", &SADX_AmyLifeSanity);
    AP_RegisterSlotDataIntCallback("BigLifeSanity", &SADX_BigLifeSanity);
    AP_RegisterSlotDataIntCallback("GammaLifeSanity", &SADX_GammaLifeSanity);

    AP_RegisterSlotDataIntCallback("StartingArea", &SADX_StartingArea);
    AP_RegisterSlotDataIntCallback("DeathLink", &SADX_SetDeathLink);
    AP_RegisterSlotDataIntCallback("RingLink", &SADX_SetRingLink);
    AP_RegisterSlotDataIntCallback("HardRingLink", &SADX_SetHardRingLink);
    AP_RegisterSlotDataIntCallback("RingLoss", &SADX_RingLoss);

    AP_RegisterSlotDataIntCallback("BossChecks", &SADX_BossChecks);
    AP_RegisterSlotDataIntCallback("UnifyChaos4", &SADX_UnifyChaos4);
    AP_RegisterSlotDataIntCallback("UnifyChaos6", &SADX_UnifyChaos6);
    AP_RegisterSlotDataIntCallback("UnifyEggHornet", &SADX_UnifyEggHornet);
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

    char seedHash = CalculateHash(this->_seedName + this->playerName);
    if (SaveFile.gap_25b[0] == 0)
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

            _randomizer.QueueNewMessage("  " + hintMsg->location + " in " + hintMsg->sendPlayer + "'s world."
                + foundText);
            _randomizer.QueueNewMessage(hintMsg->recvPlayer + "'s " + hintMsg->item + " can be found at");
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
