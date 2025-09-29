#include "ArchipelagoManager.h"


ArchipelagoManager::ArchipelagoManager(Options& options, Settings& settings, Randomizer& randomizer, Link& link)
    : _options(options), _settings(settings), _randomizer(randomizer), _link(link)
{
    _loadTrialMenuHook.Hook(OnLoadTrialMenu);
}

BOOL ArchipelagoManager::OnLoadTrialMenu()
{
    if (GameMode == GameModes_Menu && _instance->_status == ReadyForConnection)
    {
        _instance->_status = SaveFileSelected;
        _instance->_randomizer.OnSaveFileLoaded();
    }
    return _loadTrialMenuHook.Original();
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
        _randomizer.OnConnected();
        return;
    }

    if (_status == Connected && AP_GetConnectionStatus() != AP_ConnectionStatus::Authenticated)
        return _randomizer.ShowStatusInformation("Connection to Archipelago lost. Reconnecting...");

    this->ManageMessages();
}


bool ArchipelagoManager::IsWaitingForSaveFile()
{
    return _status == ReadyForConnection;
}


void ArchipelagoManager::ReceiveItem(const int64_t itemId, const bool notify)
{
    PrintDebug(" --- Item received: %d\n", itemId);
    _instance->_randomizer.OnItemReceived(itemId - _options.baseId);
}

void ArchipelagoManager::ResetItems()
{
    PrintDebug(" --- Reset items\n");
    _instance->_randomizer.ResetItems();
}

void ArchipelagoManager::CheckLocation(const int64_t locationId)
{
    PrintDebug(" --- Checked location %d\n", locationId);
    _instance->_randomizer.MarkCheckedLocation(locationId - _options.baseId);
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
            if (!_options.deathLinkActive)
                return;

            //We don't ignore deaths from our own slot

            std::string deathCause;
            if (!bounceData["cause"].isNull())
                deathCause = std::string(bounceData["cause"].asCString());
            else
                deathCause = std::string("You were killed by ") + bounceData["source"].asCString();
            _instance->_link.ProcessDeath(deathCause);
            break;
        }
        if (!strcmp(tag.c_str(), "RingLink"))
        {
            if (!_options.ringLinkActive)
                return;

            //Ignore our own ring link    
            if (bounceData["source"].asInt() == _options.instanceId)
                break;

            const int amount = bounceData["amount"].asInt();

            _instance->_link.ProcessRings(amount);
            break;
        }
        if (!strcmp(tag.c_str(), "HardRingLink"))
        {
            if (!_options.ringLinkActive || !_options.hardRingLinkActive)
                return;

            //Ignore our own ring link    
            if (bounceData["source"].asInt() == _options.instanceId)
                break;

            const int amount = bounceData["amount"].asInt();

            _instance->_link.ProcessRings(amount);
            break;
        }


        if (!strcmp(tag.c_str(), "TrapLink"))
        {
            if (!_options.trapLinkActive)
                return;

            //Ignore our own trap link
            if (bounceData["source"] == _settings.playerName)
                break;

            std::string trapName = bounceData["trap_name"].asCString();
            std::string message = "Received Linked " + trapName + " from " + bounceData["source"].asCString();

            _instance->_link.ProcessTrapLink(trapName, message);
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
        _instance->_randomizer.MinorVersionMismatch(serverVer, modVer);
    }
}

void ArchipelagoManager::Connect()
{
    AP_Init(_settings.serverIp.c_str(), "Sonic Adventure DX", _settings.playerName.c_str(),
            _settings.serverPassword.c_str());

    AP_SetDeathLinkSupported(false);
    AP_SetItemClearCallback([this]() { ResetItems(); });
    AP_SetItemRecvCallback([this](const int64_t itemId, const bool notify) { ReceiveItem(itemId, notify); });
    AP_SetLocationCheckedCallback([this](const int64_t locationId) { CheckLocation(locationId); });
    AP_RegisterBouncedCallback([this](const AP_Bounce bouncePacket) { HandleBouncedPacket(bouncePacket); });
    AP_REGISTER_INT_CALLBACK("ModVersion", CompareModVersion);

    AP_REGISTER_INT_CALLBACK("GoalRequiresLevels", _options.GoalRequiresLevels);
    AP_REGISTER_INT_CALLBACK("GoalRequiresChaosEmeralds", _options.GoalRequiresChaosEmeralds);
    AP_REGISTER_INT_CALLBACK("GoalRequiresEmblems", _options.GoalRequiresEmblems);
    AP_REGISTER_INT_CALLBACK("GoalRequiresMissions", _options.GoalRequiresMissions);
    AP_REGISTER_INT_CALLBACK("GoalRequiresBosses", _options.GoalRequiresBosses);
    AP_REGISTER_INT_CALLBACK("GoalRequiresChaoRaces", _options.GoalRequiresChaoRaces);
    AP_REGISTER_INT_CALLBACK("LogicLevel", _options.LogicLevel);
    AP_REGISTER_INT_CALLBACK("EmblemsForPerfectChaos", _options.EmblemsForPerfectChaos);
    AP_REGISTER_INT_CALLBACK("LevelForPerfectChaos", _options.LevelForPerfectChaos);
    AP_REGISTER_INT_CALLBACK("MissionForPerfectChaos", _options.MissionForPerfectChaos);
    AP_REGISTER_INT_CALLBACK("BossesForPerfectChaos", _options.BossesForPerfectChaos);
    AP_REGISTER_INT_CALLBACK("MissionModeChecks", _options.MissionModeChecks);
    AP_REGISTER_MAP_CALLBACK("MissionBlackList", _options.MissionBlackList);

    AP_REGISTER_INT_CALLBACK("AutoStartMissions", _options.AutoStartMissions);

    AP_REGISTER_INT_CALLBACK("EnemySanity", _options.EnemySanity);

    AP_REGISTER_INT_CALLBACK_CHARACTER("SonicEnemySanity", _options.SetCharacterEnemySanity, Characters_Sonic);
    AP_REGISTER_INT_CALLBACK_CHARACTER("TailsEnemySanity", _options.SetCharacterEnemySanity, Characters_Tails);
    AP_REGISTER_INT_CALLBACK_CHARACTER("KnucklesEnemySanity", _options.SetCharacterEnemySanity, Characters_Knuckles);
    AP_REGISTER_INT_CALLBACK_CHARACTER("AmyEnemySanity", _options.SetCharacterEnemySanity, Characters_Amy);
    AP_REGISTER_INT_CALLBACK_CHARACTER("GammaEnemySanity", _options.SetCharacterEnemySanity, Characters_Gamma);
    AP_REGISTER_INT_CALLBACK_CHARACTER("BigEnemySanity", _options.SetCharacterEnemySanity, Characters_Big);

    AP_REGISTER_INT_CALLBACK("CapsuleSanity", _options.CapsuleSanity);
    AP_REGISTER_INT_CALLBACK("PinballCapsules", _options.PinballCapsules);

    AP_REGISTER_INT_CALLBACK_CHARACTER("SonicCapsuleSanity", _options.SetCharacterCapsuleSanity, Characters_Sonic);
    AP_REGISTER_INT_CALLBACK_CHARACTER("TailsCapsuleSanity", _options.SetCharacterCapsuleSanity, Characters_Tails);
    AP_REGISTER_INT_CALLBACK_CHARACTER("KnucklesCapsuleSanity", _options.SetCharacterCapsuleSanity,
                                       Characters_Knuckles);
    AP_REGISTER_INT_CALLBACK_CHARACTER("AmyCapsuleSanity", _options.SetCharacterCapsuleSanity, Characters_Amy);
    AP_REGISTER_INT_CALLBACK_CHARACTER("GammaCapsuleSanity", _options.SetCharacterCapsuleSanity, Characters_Gamma);
    AP_REGISTER_INT_CALLBACK_CHARACTER("BigCapsuleSanity", _options.SetCharacterCapsuleSanity, Characters_Big);

    AP_REGISTER_INT_CALLBACK("LifeCapsuleSanity", _options.LifeCapsuleSanity);
    AP_REGISTER_INT_CALLBACK("ShieldCapsuleSanity", _options.ShieldCapsuleSanity);
    AP_REGISTER_INT_CALLBACK("PowerUpCapsuleSanity", _options.PowerUpCapsuleSanity);
    AP_REGISTER_INT_CALLBACK("RingCapsuleSanity", _options.RingCapsuleSanity);

    AP_REGISTER_INT_CALLBACK("FishSanity", _options.FishSanity);
    AP_REGISTER_INT_CALLBACK("LazyFishing", _options.LazyFishing);

    AP_REGISTER_MAP_CALLBACK("ProgressionItems", _options.ProgressionItems);

    AP_REGISTER_INT_CALLBACK("StartingCharacter", _options.StartingCharacter);
    AP_REGISTER_INT_CALLBACK_CHARACTER("SonicStartingArea", _options.SetCharacterStatingArea, Characters_Sonic);
    AP_REGISTER_INT_CALLBACK_CHARACTER("TailsStartingArea", _options.SetCharacterStatingArea, Characters_Tails);
    AP_REGISTER_INT_CALLBACK_CHARACTER("KnucklesStartingArea", _options.SetCharacterStatingArea, Characters_Knuckles);
    AP_REGISTER_INT_CALLBACK_CHARACTER("AmyStartingArea", _options.SetCharacterStatingArea, Characters_Amy);
    AP_REGISTER_INT_CALLBACK_CHARACTER("GammaStartingArea", _options.SetCharacterStatingArea, Characters_Gamma);
    AP_REGISTER_INT_CALLBACK_CHARACTER("BigStartingArea", _options.SetCharacterStatingArea, Characters_Big);

    AP_REGISTER_MAP_CALLBACK("LevelEntranceMap", _options.LevelEntranceMap);
    AP_REGISTER_INT_CALLBACK("EntranceRandomizer", _options.SetEntranceRandomizer);
    AP_REGISTER_MAP_CALLBACK("EntranceEmblemValueMap", _options.SetEntranceEmblemValueMap);

    AP_REGISTER_INT_CALLBACK("DeathLink", _options.SetDeathLink);
    AP_REGISTER_INT_CALLBACK("SendDeathLinkChance", _options.SendDeathLinkChance);
    AP_REGISTER_INT_CALLBACK("ReceiveDeathLinkChance", _options.ReceiveDeathLinkChance);

    AP_REGISTER_INT_CALLBACK("RingLink", _options.SetRingLink);
    AP_REGISTER_INT_CALLBACK("CasinopolisRingLink", _options.SetCasinopolisRingLink);
    AP_REGISTER_INT_CALLBACK("HardRingLink", _options.SetHardRingLink);
    AP_REGISTER_INT_CALLBACK("RingLoss", _options.SetRingLoss);

    AP_REGISTER_INT_CALLBACK("TrapLink", _options.SetTrapLink);

    AP_REGISTER_INT_CALLBACK("TwinkleCircuitCheck", _options.TwinkleCircuitCheck);
    AP_REGISTER_INT_CALLBACK("MultipleTwinkleCircuitChecks", _options.MultipleTwinkleCircuitChecks);
    AP_REGISTER_INT_CALLBACK("SkyChaseChecks", _options.SkyChaseChecks);
    AP_REGISTER_INT_CALLBACK("SkyChaseChecksHard", _options.SkyChaseChecksHard);

    AP_REGISTER_INT_CALLBACK("BossChecks", _options.BossChecks);
    AP_REGISTER_INT_CALLBACK("UnifyChaos4", _options.UnifyChaos4);
    AP_REGISTER_INT_CALLBACK("UnifyChaos6", _options.UnifyChaos6);
    AP_REGISTER_INT_CALLBACK("UnifyEggHornet", _options.UnifyEggHornet);

    AP_REGISTER_INT_CALLBACK_CHARACTER("PlayableSonic", _options.SetPlayableCharacter, Characters_Sonic);
    AP_REGISTER_INT_CALLBACK_CHARACTER("PlayableTails", _options.SetPlayableCharacter, Characters_Tails);
    AP_REGISTER_INT_CALLBACK_CHARACTER("PlayableKnuckles", _options.SetPlayableCharacter, Characters_Knuckles);
    AP_REGISTER_INT_CALLBACK_CHARACTER("PlayableAmy", _options.SetPlayableCharacter, Characters_Amy);
    AP_REGISTER_INT_CALLBACK_CHARACTER("PlayableGamma", _options.SetPlayableCharacter, Characters_Gamma);
    AP_REGISTER_INT_CALLBACK_CHARACTER("PlayableBig", _options.SetPlayableCharacter, Characters_Big);

    AP_REGISTER_INT_CALLBACK_CHARACTER("SonicActionStageMissions", _options.SetActionStageMissions, Characters_Sonic);
    AP_REGISTER_INT_CALLBACK_CHARACTER("TailsActionStageMissions", _options.SetActionStageMissions, Characters_Tails);
    AP_REGISTER_INT_CALLBACK_CHARACTER("KnucklesActionStageMissions", _options.SetActionStageMissions,
                                       Characters_Knuckles);
    AP_REGISTER_INT_CALLBACK_CHARACTER("AmyActionStageMissions", _options.SetActionStageMissions, Characters_Amy);
    AP_REGISTER_INT_CALLBACK_CHARACTER("GammaActionStageMissions", _options.SetActionStageMissions, Characters_Gamma);
    AP_REGISTER_INT_CALLBACK_CHARACTER("BigActionStageMissions", _options.SetActionStageMissions, Characters_Big);

    AP_REGISTER_INT_CALLBACK("MusicSource", _options.SetMusicSource);
    AP_REGISTER_INT_CALLBACK("MusicShuffle", _options.SetMusicShuffle);
    AP_REGISTER_INT_CALLBACK("MusicShuffleConsistency", _options.SetMusicShuffleConsistency);
    AP_REGISTER_INT_CALLBACK("MusicShuffleSeed", _options.SetMusicShuffleSeed);
    AP_REGISTER_INT_CALLBACK("LifeCapsulesChangeSongs", _options.SetLifeCapsulesChangeSongs);

    AP_REGISTER_INT_CALLBACK("IceTrapWeight", _options.SetIceTrapWeight);
    AP_REGISTER_INT_CALLBACK("SpringTrapWeight", _options.SetSpringTrapWeight);
    AP_REGISTER_INT_CALLBACK("PoliceTrapWeight", _options.SetPoliceTrapWeight);
    AP_REGISTER_INT_CALLBACK("BuyonTrapWeight", _options.SetBuyonTrapWeight);
    AP_REGISTER_INT_CALLBACK("ReverseTrapWeight", _options.SetReverseTrapWeight);
    AP_REGISTER_INT_CALLBACK("GravityTrapWeight", _options.SetGravityTrapWeight);

    AP_REGISTER_INT_CALLBACK("ReverseControlTrapDuration", _options.SetReverseControlTrapDuration);
    AP_REGISTER_INT_CALLBACK("TrapsOnAdventureFields", _options.SetTrapsOnAdventureFields);
    AP_REGISTER_INT_CALLBACK("TrapsOnBossFights", _options.SetTrapsOnBossFights);
    AP_REGISTER_INT_CALLBACK("TrapsOnPerfectChaosFight", _options.SetTrapsOnPerfectChaosFight);


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
    if (!this->_seedName.empty())
        return true;
    if (roomInfo.seed_name.empty())
        return true;
    this->_seedName = roomInfo.seed_name;

    char seedHash = CalculateHash(this->_seedName + _settings.playerName);
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
            if (_settings.showChatMessages)
                _randomizer.QueueNewChatMessage(msg->text);
            return;
        }
    case AP_MessageType::Countdown:
        {
            if (_settings.showCountdowns)
                _randomizer.QueueNewChatMessage(msg->text);
            return;
        }
    case AP_MessageType::PlayerConnection:
        {
            if (_settings.showPlayerConnections)
                _randomizer.QueueNewChatMessage(msg->text);
            return;
        }
    case AP_MessageType::GoalReached:
        {
            if (_settings.showGoalReached)
                _randomizer.QueueNewChatMessage(msg->text);
            return;
        }
    case AP_MessageType::Plaintext:
        {
        }
    }
}
