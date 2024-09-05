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
        //We prevent entering the main menu when we are still connecting
        TldFlg = false;
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
        TldFlg = true;
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

            //We don't ignore deaths from our own slot

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

            //Ignore our own ring link    
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

void SADX_CompareModVersion(const int version)
{
    randomizerPtr->OnCheckVersion(version);
}

void SADX_EmblemsForPerfectChaos(const int emblemGoal)
{
    randomizerPtr->OnEmblemGoalSet(emblemGoal);
}

void SADX_LevelForPerfectChaos(const int levelGoal)
{
    randomizerPtr->OnLevelGoalSet(levelGoal);
}

void SADX_MissionForPerfectChaos(const int missionGoal)
{
    randomizerPtr->OnMissionGoalSet(missionGoal);
}

void SADX_MissionModeChecks(const int missionModeEnabled)
{
    randomizerPtr->SetMissionMode(missionModeEnabled);
}

void SADX_MissionBlackList(const std::map<int, int> missionBlacklist)
{
    if (missionBlacklist.empty())
        return;
    std::vector<int> blacklistedMissions;

    for (const auto& mission : missionBlacklist)
        blacklistedMissions.push_back(mission.first);

    randomizerPtr->UpdateMissionBlacklist(blacklistedMissions);
}

void SADX_AutoStartMissions(const int autoStartMissions)
{
    randomizerPtr->SetAutoStartMissions(autoStartMissions);
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


void SADX_StartingCharacter(const int startingCharacterIndex)
{
    randomizerPtr->SetStartingCharacter(startingCharacterIndex);
}

void SADX_SonicStartingArea(const int startingArea)
{
    randomizerPtr->SetCharacterStatingArea(Characters_Sonic, static_cast<StartingArea>(startingArea));
}

void SADX_TailsStartingArea(const int startingArea)
{
    randomizerPtr->SetCharacterStatingArea(Characters_Tails, static_cast<StartingArea>(startingArea));
}

void SADX_KnucklesStartingArea(const int startingArea)
{
    randomizerPtr->SetCharacterStatingArea(Characters_Knuckles, static_cast<StartingArea>(startingArea));
}

void SADX_AmyStartingArea(const int startingArea)
{
    randomizerPtr->SetCharacterStatingArea(Characters_Amy, static_cast<StartingArea>(startingArea));
}

void SADX_GammaStartingArea(const int startingArea)
{
    randomizerPtr->SetCharacterStatingArea(Characters_Gamma, static_cast<StartingArea>(startingArea));
}

void SADX_BigStartingArea(const int startingArea)
{
    randomizerPtr->SetCharacterStatingArea(Characters_Big, static_cast<StartingArea>(startingArea));
}

void SADX_LevelEntranceMap(const std::map<int, int> levelEntrancesValues)
{
    if (levelEntrancesValues.empty())
        return;

    LevelEntrances levelEntrances = {};

    for (const auto& entrance : levelEntrancesValues)
    {
        const auto levelEntrance = static_cast<Levels>(entrance.first);
        const auto actualLevel = static_cast<Levels>(entrance.second);
        levelEntrances.addRelationship(levelEntrance, actualLevel);
    }
    randomizerPtr->UpdateLevelEntrances(levelEntrances);
}

void SADX_SetDeathLink(const int deathLinkActive)
{
    randomizerPtr->SetDeathLink(deathLinkActive);
}

void SADX_SetRingLink(const int ringLinkActive)
{
    randomizerPtr->SetRingLink(ringLinkActive);
}

void SADX_SetCasinopolisRingLink(const int casinopolisRingLink)
{
    randomizerPtr->SetCasinopolisRingLink(casinopolisRingLink);
}

void SADX_SetHardRingLink(const int hardRingLinkActive)
{
    randomizerPtr->SetHardRingLink(hardRingLinkActive);
}

void SADX_RingLoss(const int ringLoss)
{
    randomizerPtr->SetRingLoss(static_cast<RingLoss>(ringLoss));
}

void SADX_SkyChaseChecks(const int skyChaseChecks)
{
    randomizerPtr->SetSkyChaseChecks(skyChaseChecks);
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

void SADX_PlayableSonic(const int playable)
{
    randomizerPtr->SetPlayableCharacter(Characters_Sonic, playable);
}

void SADX_PlayableTails(const int playable)
{
    randomizerPtr->SetPlayableCharacter(Characters_Tails, playable);
}

void SADX_PlayableKnuckles(const int playable)
{
    randomizerPtr->SetPlayableCharacter(Characters_Knuckles, playable);
}

void SADX_PlayableAmy(const int playable)
{
    randomizerPtr->SetPlayableCharacter(Characters_Amy, playable);
}

void SADX_PlayableGamma(const int playable)
{
    randomizerPtr->SetPlayableCharacter(Characters_Gamma, playable);
}

void SADX_PlayableBig(const int playable)
{
    randomizerPtr->SetPlayableCharacter(Characters_Big, playable);
}

void SADX_SonicActionStageMissions(const int missions)
{
    randomizerPtr->SetActionStageMissions(Characters_Sonic, missions);
}

void SADX_TailsActionStageMissions(const int missions)
{
    randomizerPtr->SetActionStageMissions(Characters_Tails, missions);
}

void SADX_KnucklesActionStageMissions(const int missions)
{
    randomizerPtr->SetActionStageMissions(Characters_Knuckles, missions);
}

void SADX_AmyActionStageMissions(const int missions)
{
    randomizerPtr->SetActionStageMissions(Characters_Amy, missions);
}

void SADX_GammaActionStageMissions(const int missions)
{
    randomizerPtr->SetActionStageMissions(Characters_Gamma, missions);
}

void SADX_BigActionStageMissions(const int missions)
{
    randomizerPtr->SetActionStageMissions(Characters_Big, missions);
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
    AP_RegisterSlotDataIntCallback("ModVersion", &SADX_CompareModVersion);
    AP_RegisterSlotDataIntCallback("EmblemsForPerfectChaos", &SADX_EmblemsForPerfectChaos);
    AP_RegisterSlotDataIntCallback("LevelForPerfectChaos", &SADX_LevelForPerfectChaos);
    AP_RegisterSlotDataIntCallback("MissionForPerfectChaos", &SADX_MissionForPerfectChaos);
    AP_RegisterSlotDataIntCallback("MissionModeChecks", &SADX_MissionModeChecks);
    AP_RegisterSlotDataMapIntIntCallback("MissionBlackList", &SADX_MissionBlackList);

    AP_RegisterSlotDataIntCallback("AutoStartMissions", &SADX_AutoStartMissions);

    AP_RegisterSlotDataIntCallback("LifeSanity", &SADX_LifeSanity);
    AP_RegisterSlotDataIntCallback("PinballLifeCapsules", &SADX_PinballLifeCapsules);
    AP_RegisterSlotDataIntCallback("SonicLifeSanity", &SADX_SonicLifeSanity);
    AP_RegisterSlotDataIntCallback("TailsLifeSanity", &SADX_TailsLifeSanity);
    AP_RegisterSlotDataIntCallback("KnucklesLifeSanity", &SADX_KnucklesLifeSanity);
    AP_RegisterSlotDataIntCallback("AmyLifeSanity", &SADX_AmyLifeSanity);
    AP_RegisterSlotDataIntCallback("BigLifeSanity", &SADX_BigLifeSanity);
    AP_RegisterSlotDataIntCallback("GammaLifeSanity", &SADX_GammaLifeSanity);

    AP_RegisterSlotDataIntCallback("StartingCharacter", &SADX_StartingCharacter);
    AP_RegisterSlotDataIntCallback("SonicStartingArea", &SADX_SonicStartingArea);
    AP_RegisterSlotDataIntCallback("TailsStartingArea", &SADX_TailsStartingArea);
    AP_RegisterSlotDataIntCallback("KnucklesStartingArea", &SADX_KnucklesStartingArea);
    AP_RegisterSlotDataIntCallback("AmyStartingArea", &SADX_AmyStartingArea);
    AP_RegisterSlotDataIntCallback("GammaStartingArea", &SADX_GammaStartingArea);
    AP_RegisterSlotDataIntCallback("BigStartingArea", &SADX_BigStartingArea);

    AP_RegisterSlotDataMapIntIntCallback("LevelEntranceMap", &SADX_LevelEntranceMap);

    AP_RegisterSlotDataIntCallback("DeathLink", &SADX_SetDeathLink);
    AP_RegisterSlotDataIntCallback("RingLink", &SADX_SetRingLink);
    AP_RegisterSlotDataIntCallback("CasinopolisRingLink", &SADX_SetCasinopolisRingLink);
    AP_RegisterSlotDataIntCallback("HardRingLink", &SADX_SetHardRingLink);
    AP_RegisterSlotDataIntCallback("RingLoss", &SADX_RingLoss);

    AP_RegisterSlotDataIntCallback("SkyChaseChecks", &SADX_SkyChaseChecks);

    AP_RegisterSlotDataIntCallback("BossChecks", &SADX_BossChecks);
    AP_RegisterSlotDataIntCallback("UnifyChaos4", &SADX_UnifyChaos4);
    AP_RegisterSlotDataIntCallback("UnifyChaos6", &SADX_UnifyChaos6);
    AP_RegisterSlotDataIntCallback("UnifyEggHornet", &SADX_UnifyEggHornet);


    AP_RegisterSlotDataIntCallback("PlayableSonic", &SADX_PlayableSonic);
    AP_RegisterSlotDataIntCallback("PlayableTails", &SADX_PlayableTails);
    AP_RegisterSlotDataIntCallback("PlayableKnuckles", &SADX_PlayableKnuckles);
    AP_RegisterSlotDataIntCallback("PlayableAmy", &SADX_PlayableAmy);
    AP_RegisterSlotDataIntCallback("PlayableBig", &SADX_PlayableBig);
    AP_RegisterSlotDataIntCallback("PlayableGamma", &SADX_PlayableGamma);

    AP_RegisterSlotDataIntCallback("SonicActionStageMissions", &SADX_SonicActionStageMissions);
    AP_RegisterSlotDataIntCallback("TailsActionStageMissions", &SADX_TailsActionStageMissions);
    AP_RegisterSlotDataIntCallback("KnucklesActionStageMissions", &SADX_KnucklesActionStageMissions);
    AP_RegisterSlotDataIntCallback("AmyActionStageMissions", &SADX_AmyActionStageMissions);
    AP_RegisterSlotDataIntCallback("GammaActionStageMissions", &SADX_GammaActionStageMissions);
    AP_RegisterSlotDataIntCallback("BigActionStageMissions", &SADX_BigActionStageMissions);
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
            const AP_HintMessage* hintMsg = static_cast<AP_HintMessage*>(msg);

            if (!hintMsg)
                return;
            if (hintMsg->checked)
                return;

            _randomizer.QueueNewMessage(
                "  " + hintMsg->location + " in " + hintMsg->sendPlayer + "'s world. (not found)");
            _randomizer.QueueNewMessage(hintMsg->recvPlayer + "'s " + hintMsg->item + " can be found at");
            return;
        }
    case AP_MessageType::Plaintext:
    case AP_MessageType::Countdown:
        {
            // Do nothing, avoid spam
        }
    }
}
