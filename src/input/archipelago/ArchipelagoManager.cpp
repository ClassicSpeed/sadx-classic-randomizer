#include "ArchipelagoManager.h"

Randomizer* randomizerPtr = nullptr;
ArchipelagoManager* archipelagoManagerPtr = nullptr;

ArchipelagoManager::ArchipelagoManager(Randomizer& randomizer, Options& options)
    : options(options), _randomizer(randomizer)
{
    randomizerPtr = &this->_randomizer;
    archipelagoManagerPtr = this;
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

// TODO: Move to helpers
static std::string LeftTrim(std::string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
    {
        return !std::isspace(ch);
    }));
    return s;
}

static std::string RightTrim(std::string s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
    {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

static std::string Trim(std::string s)
{
    return LeftTrim(RightTrim(std::move(s)));
}

void ArchipelagoManager::SetServerConfiguration(const std::string& serverIp, const std::string& newPlayerName,
                                                const std::string& serverPassword,
                                                const bool showChatMessages, const bool showGoalReached,
                                                const bool showCountdowns, const bool showPlayerConnections)
{
    this->_serverIP = Trim(serverIp);
    this->playerName = Trim(newPlayerName);
    this->_serverPassword = serverPassword;
    this->_showChatMessages = showChatMessages;
    this->_showGoalReached = showGoalReached;
    this->_showCountdowns = showCountdowns;
    this->_showPlayerConnections = showPlayerConnections;
}


bool ArchipelagoManager::IsWaitingForSaveFile()
{
    return _status == ReadyForConnection;
}

void ArchipelagoManager::OnSaveFileLoaded()
{
    _status = SaveFileSelected;
}

void ArchipelagoManager::ReceiveItem(const int64_t itemId, const bool notify)
{
    PrintDebug(" --- Item received: %d\n", itemId);
    randomizerPtr->OnItemReceived(itemId - options.baseId);
}

void ArchipelagoManager::ResetItems()
{
    PrintDebug(" --- Reset items\n");
    randomizerPtr->ResetItems();
}

void ArchipelagoManager::CheckLocation(const int64_t locationId)
{
    PrintDebug(" --- Checked location %d\n", locationId);
    randomizerPtr->MarkCheckedLocation(locationId - options.baseId);
}

void ArchipelagoManager::HandleBouncedPacket(AP_Bounce bouncePacket)
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
            if (!options.deathLinkActive)
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
            if (!options.ringLinkActive)
                return;

            //Ignore our own ring link    
            if (bounceData["source"].asInt() == options.instanceId)
                break;

            const int amount = bounceData["amount"].asInt();

            randomizerPtr->ProcessRings(amount);
            break;
        }
        if (!strcmp(tag.c_str(), "HardRingLink"))
        {
            if (!options.ringLinkActive || !options.hardRingLinkActive)
                return;

            //Ignore our own ring link    
            if (bounceData["source"].asInt() == options.instanceId)
                break;

            const int amount = bounceData["amount"].asInt();

            randomizerPtr->ProcessRings(amount);
            break;
        }


        if (!strcmp(tag.c_str(), "TrapLink"))
        {
            if (!options.trapLinkActive)
                return;

            //Ignore our own trap link
            if (bounceData["source"] == archipelagoManagerPtr->playerName)
                break;

            std::string trapName = bounceData["trap_name"].asCString();
            std::string message = "Received Linked " + trapName + " from " + bounceData["source"].asCString();

            randomizerPtr->ProcessTrapLink(trapName, message);
            break;
        }
    }
}

void ArchipelagoManager::CompareModVersion(const int serverVersion)
{
    const int serverMajor = serverVersion / 100;
    const int serverMinor = (serverVersion / 10) % 10;
    const int serverPatch = serverVersion % 10;

    const std::string modVer = std::to_string(SADX_AP_VERSION_MAJOR)
        + "." + std::to_string(SADX_AP_VERSION_MINOR)
        + "." + std::to_string(SADX_AP_VERSION_PATCH);
    const std::string serverVer = std::to_string(serverMajor)
        + "." + std::to_string(serverMinor)
        + "." + std::to_string(serverPatch);
    if (serverMajor != SADX_AP_VERSION_MAJOR || serverMinor != SADX_AP_VERSION_MINOR)
    {
        std::string errorMessage = "Error: Major version mismatch!\n\nServer: v" + serverVer + "\nMod: v" + modVer;
        MessageBox(WindowHandle, std::wstring(errorMessage.begin(), errorMessage.end()).c_str(),
                   L"SADX Archipelago Error: Version mismatch", MB_OK | MB_ICONERROR);
        exit(0);
    }
    if (serverPatch != SADX_AP_VERSION_PATCH)
    {
        randomizerPtr->MinorVersionMismatch(serverVer, modVer);
    }
}

void ArchipelagoManager::Connect()
{
    AP_Init(_serverIP.c_str(), "Sonic Adventure DX", playerName.c_str(), _serverPassword.c_str());

    AP_SetDeathLinkSupported(false);
    AP_SetItemClearCallback([this]() { ResetItems(); });
    AP_SetItemRecvCallback([this](const int64_t itemId, const bool notify) { ReceiveItem(itemId, notify); });
    AP_SetLocationCheckedCallback([this](const int64_t locationId) { CheckLocation(locationId); });
    AP_RegisterBouncedCallback([this](const AP_Bounce bouncePacket) { HandleBouncedPacket(bouncePacket); });
    AP_REGISTER_INT_CALLBACK("ModVersion", CompareModVersion);
    
    AP_REGISTER_INT_CALLBACK("GoalRequiresLevels", options.GoalRequiresLevels);
    AP_REGISTER_INT_CALLBACK("GoalRequiresChaosEmeralds", options.GoalRequiresChaosEmeralds);
    AP_REGISTER_INT_CALLBACK("GoalRequiresEmblems", options.GoalRequiresEmblems);
    AP_REGISTER_INT_CALLBACK("GoalRequiresMissions", options.GoalRequiresMissions);
    AP_REGISTER_INT_CALLBACK("GoalRequiresBosses", options.GoalRequiresBosses);
    AP_REGISTER_INT_CALLBACK("GoalRequiresChaoRaces", options.GoalRequiresChaoRaces);
    AP_REGISTER_INT_CALLBACK("LogicLevel", options.LogicLevel);
    AP_REGISTER_INT_CALLBACK("EmblemsForPerfectChaos", options.EmblemsForPerfectChaos);
    AP_REGISTER_INT_CALLBACK("LevelForPerfectChaos", options.LevelForPerfectChaos);
    AP_REGISTER_INT_CALLBACK("MissionForPerfectChaos", options.MissionForPerfectChaos);
    AP_REGISTER_INT_CALLBACK("BossesForPerfectChaos", options.BossesForPerfectChaos);
    AP_REGISTER_INT_CALLBACK("MissionModeChecks", options.MissionModeChecks);
    AP_REGISTER_MAP_CALLBACK("MissionBlackList", options.MissionBlackList);

    AP_REGISTER_INT_CALLBACK("AutoStartMissions", options.AutoStartMissions);

    AP_REGISTER_INT_CALLBACK("EnemySanity", options.EnemySanity);

    AP_REGISTER_INT_CALLBACK_CHARACTER("SonicEnemySanity", options.SetCharacterEnemySanity, Characters_Sonic);
    AP_REGISTER_INT_CALLBACK_CHARACTER("TailsEnemySanity", options.SetCharacterEnemySanity, Characters_Tails);
    AP_REGISTER_INT_CALLBACK_CHARACTER("KnucklesEnemySanity", options.SetCharacterEnemySanity, Characters_Knuckles);
    AP_REGISTER_INT_CALLBACK_CHARACTER("AmyEnemySanity", options.SetCharacterEnemySanity, Characters_Amy);
    AP_REGISTER_INT_CALLBACK_CHARACTER("GammaEnemySanity", options.SetCharacterEnemySanity, Characters_Gamma);
    AP_REGISTER_INT_CALLBACK_CHARACTER("BigEnemySanity", options.SetCharacterEnemySanity, Characters_Big);

    AP_REGISTER_INT_CALLBACK("CapsuleSanity", options.CapsuleSanity);
    AP_REGISTER_INT_CALLBACK("PinballCapsules", options.PinballCapsules);

    AP_REGISTER_INT_CALLBACK_CHARACTER("SonicCapsuleSanity", options.SetCharacterCapsuleSanity, Characters_Sonic);
    AP_REGISTER_INT_CALLBACK_CHARACTER("TailsCapsuleSanity", options.SetCharacterCapsuleSanity, Characters_Tails);
    AP_REGISTER_INT_CALLBACK_CHARACTER("KnucklesCapsuleSanity", options.SetCharacterCapsuleSanity, Characters_Knuckles);
    AP_REGISTER_INT_CALLBACK_CHARACTER("AmyCapsuleSanity", options.SetCharacterCapsuleSanity, Characters_Amy);
    AP_REGISTER_INT_CALLBACK_CHARACTER("GammaCapsuleSanity", options.SetCharacterCapsuleSanity, Characters_Gamma);
    AP_REGISTER_INT_CALLBACK_CHARACTER("BigCapsuleSanity", options.SetCharacterCapsuleSanity, Characters_Big);

    AP_REGISTER_INT_CALLBACK("LifeCapsuleSanity", options.LifeCapsuleSanity);
    AP_REGISTER_INT_CALLBACK("ShieldCapsuleSanity", options.ShieldCapsuleSanity);
    AP_REGISTER_INT_CALLBACK("PowerUpCapsuleSanity", options.PowerUpCapsuleSanity);
    AP_REGISTER_INT_CALLBACK("RingCapsuleSanity", options.RingCapsuleSanity);

    AP_REGISTER_INT_CALLBACK("FishSanity", options.FishSanity);
    AP_REGISTER_INT_CALLBACK("LazyFishing", options.LazyFishing);

    AP_REGISTER_MAP_CALLBACK("ProgressionItems", options.ProgressionItems);

    AP_REGISTER_INT_CALLBACK("StartingCharacter", options.StartingCharacter);
    AP_REGISTER_INT_CALLBACK_CHARACTER("SonicStartingArea", options.SetCharacterStatingArea, Characters_Sonic);
    AP_REGISTER_INT_CALLBACK_CHARACTER("TailsStartingArea", options.SetCharacterStatingArea, Characters_Tails);
    AP_REGISTER_INT_CALLBACK_CHARACTER("KnucklesStartingArea", options.SetCharacterStatingArea, Characters_Knuckles);
    AP_REGISTER_INT_CALLBACK_CHARACTER("AmyStartingArea", options.SetCharacterStatingArea, Characters_Amy);
    AP_REGISTER_INT_CALLBACK_CHARACTER("GammaStartingArea", options.SetCharacterStatingArea, Characters_Gamma);
    AP_REGISTER_INT_CALLBACK_CHARACTER("BigStartingArea", options.SetCharacterStatingArea, Characters_Big);

    AP_REGISTER_MAP_CALLBACK("LevelEntranceMap", options.LevelEntranceMap);
    AP_REGISTER_INT_CALLBACK("EntranceRandomizer", options.SetEntranceRandomizer);

    AP_REGISTER_INT_CALLBACK("DeathLink", options.SetDeathLink);
    AP_REGISTER_INT_CALLBACK("SendDeathLinkChance", options.SendDeathLinkChance);
    AP_REGISTER_INT_CALLBACK("ReceiveDeathLinkChance", options.ReceiveDeathLinkChance);

    AP_REGISTER_INT_CALLBACK("RingLink", options.SetRingLink);
    AP_REGISTER_INT_CALLBACK("CasinopolisRingLink", options.SetCasinopolisRingLink);
    AP_REGISTER_INT_CALLBACK("HardRingLink", options.SetHardRingLink);
    AP_REGISTER_INT_CALLBACK("RingLoss", options.SetRingLoss);

    AP_REGISTER_INT_CALLBACK("TrapLink", options.SetTrapLink);

    AP_REGISTER_INT_CALLBACK("TwinkleCircuitCheck", options.TwinkleCircuitCheck);
    AP_REGISTER_INT_CALLBACK("MultipleTwinkleCircuitChecks", options.MultipleTwinkleCircuitChecks);
    AP_REGISTER_INT_CALLBACK("SkyChaseChecks", options.SkyChaseChecks);
    AP_REGISTER_INT_CALLBACK("SkyChaseChecksHard", options.SkyChaseChecksHard);

    AP_REGISTER_INT_CALLBACK("BossChecks", options.BossChecks);
    AP_REGISTER_INT_CALLBACK("UnifyChaos4", options.UnifyChaos4);
    AP_REGISTER_INT_CALLBACK("UnifyChaos6", options.UnifyChaos6);
    AP_REGISTER_INT_CALLBACK("UnifyEggHornet", options.UnifyEggHornet);

    AP_REGISTER_INT_CALLBACK_CHARACTER("PlayableSonic", options.SetPlayableCharacter, Characters_Sonic);
    AP_REGISTER_INT_CALLBACK_CHARACTER("PlayableTails", options.SetPlayableCharacter, Characters_Tails);
    AP_REGISTER_INT_CALLBACK_CHARACTER("PlayableKnuckles", options.SetPlayableCharacter, Characters_Knuckles);
    AP_REGISTER_INT_CALLBACK_CHARACTER("PlayableAmy", options.SetPlayableCharacter,Characters_Amy);
    AP_REGISTER_INT_CALLBACK_CHARACTER("PlayableGamma", options.SetPlayableCharacter, Characters_Gamma);
    AP_REGISTER_INT_CALLBACK_CHARACTER("PlayableBig", options.SetPlayableCharacter, Characters_Big);

    AP_REGISTER_INT_CALLBACK_CHARACTER("SonicActionStageMissions", options.SetActionStageMissions, Characters_Sonic);
    AP_REGISTER_INT_CALLBACK_CHARACTER("TailsActionStageMissions", options.SetActionStageMissions, Characters_Tails);
    AP_REGISTER_INT_CALLBACK_CHARACTER("KnucklesActionStageMissions", options.SetActionStageMissions, Characters_Knuckles);
    AP_REGISTER_INT_CALLBACK_CHARACTER("AmyActionStageMissions", options.SetActionStageMissions,Characters_Amy);
    AP_REGISTER_INT_CALLBACK_CHARACTER("GammaActionStageMissions", options.SetActionStageMissions, Characters_Gamma);
    AP_REGISTER_INT_CALLBACK_CHARACTER("BigActionStageMissions", options.SetActionStageMissions, Characters_Big);

    AP_REGISTER_INT_CALLBACK("MusicSource", options.SetMusicSource);
    AP_REGISTER_INT_CALLBACK("MusicShuffle", options.SetMusicShuffle);
    AP_REGISTER_INT_CALLBACK("MusicShuffleConsistency", options.SetMusicShuffleConsistency);
    AP_REGISTER_INT_CALLBACK("MusicShuffleSeed", options.SetMusicShuffleSeed);
    AP_REGISTER_INT_CALLBACK("LifeCapsulesChangeSongs", options.SetLifeCapsulesChangeSongs);

    AP_REGISTER_INT_CALLBACK("IceTrapWeight", options.SetIceTrapWeight);
    AP_REGISTER_INT_CALLBACK("SpringTrapWeight", options.SetSpringTrapWeight);
    AP_REGISTER_INT_CALLBACK("PoliceTrapWeight", options.SetPoliceTrapWeight);
    AP_REGISTER_INT_CALLBACK("BuyonTrapWeight", options.SetBuyonTrapWeight);
    AP_REGISTER_INT_CALLBACK("ReverseTrapWeight", options.SetReverseTrapWeight);
    AP_REGISTER_INT_CALLBACK("GravityTrapWeight", options.SetGravityTrapWeight);

    AP_REGISTER_INT_CALLBACK("ReverseControlTrapDuration", options.SetReverseControlTrapDuration);
    AP_REGISTER_INT_CALLBACK("TrapsOnAdventureFields", options.SetTrapsOnAdventureFields);
    AP_REGISTER_INT_CALLBACK("TrapsOnBossFights", options.SetTrapsOnBossFights);
    AP_REGISTER_INT_CALLBACK("TrapsOnPerfectChaosFight", options.SetTrapsOnPerfectChaosFight);


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
            return _randomizer.QueueNewItemMessage("Sent " + sendMsg->item + " to " + sendMsg->recvPlayer);
        }
    case AP_MessageType::ItemRecv:
        {
            AP_ItemRecvMessage* recvMsg = static_cast<AP_ItemRecvMessage*>(msg);
            if (!recvMsg)
                return;
            return _randomizer.QueueNewItemMessage("Received " + recvMsg->item + " from " + recvMsg->sendPlayer);
        }
    case AP_MessageType::Hint:
        {
            const AP_HintMessage* hintMsg = static_cast<AP_HintMessage*>(msg);

            if (!hintMsg)
                return;
            if (hintMsg->checked)
                return;

            _randomizer.QueueNewItemMessage(
                "  " + hintMsg->location + " in " + hintMsg->sendPlayer + "'s world. (not found)");
            _randomizer.QueueNewItemMessage(hintMsg->recvPlayer + "'s " + hintMsg->item + " can be found at");
            return;
        }
    case AP_MessageType::Chat:
        {
            if (this->_showChatMessages)
                _randomizer.QueueNewChatMessage(msg->text);
            return;
        }
    case AP_MessageType::Countdown:
        {
            if (this->_showCountdowns)
                _randomizer.QueueNewChatMessage(msg->text);
            return;
        }
    case AP_MessageType::PlayerConnection:
        {
            if (this->_showPlayerConnections)
                _randomizer.QueueNewChatMessage(msg->text);
            return;
        }
    case AP_MessageType::GoalReached:
        {
            if (this->_showGoalReached)
                _randomizer.QueueNewChatMessage(msg->text);
            return;
        }
    case AP_MessageType::Plaintext:
        {
        }
    }
}
