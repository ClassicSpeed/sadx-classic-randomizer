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
                                                const DeathLinkOverride newDeathLinkOverride,
                                                const RingLinkOverride newRingLinkOverride,
                                                const RingLossOverride newRingLossOverride,
                                                const TrapLinkOverride newTrapLinkOverride,

                                                const bool showChatMessages, const bool showGoalReached,
                                                const bool showCountdowns, const bool showPlayerConnections)
{
    this->_serverIP = Trim(serverIp);
    this->playerName = Trim(newPlayerName);
    this->_serverPassword = serverPassword;
    this->deathLinkOverride = newDeathLinkOverride;
    this->ringLinkOverride = newRingLinkOverride;
    this->ringLossOverride = newRingLossOverride;
    this->trapLinkOverride = newTrapLinkOverride;
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
        if (!strcmp(tag.c_str(), "HardRingLink"))
        {
            if (!randomizerPtr->GetOptions().ringLinkActive || !randomizerPtr->GetOptions().hardRingLinkActive)
                return;

            //Ignore our own ring link    
            if (bounceData["source"].asInt() == archipelagoManagerPtr->instanceId)
                break;

            const int amount = bounceData["amount"].asInt();

            randomizerPtr->ProcessRings(amount);
            break;
        }


        if (!strcmp(tag.c_str(), "TrapLink"))
        {
            if (!randomizerPtr->GetOptions().trapLinkActive)
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

void SADX_GoalRequiresLevels(const int goalRequiresLevels)
{
    randomizerPtr->OnGoalRequiresLevelsSet(goalRequiresLevels);
}

void SADX_GoalRequiresChaosEmeralds(const int goalRequiresChaosEmeralds)
{
    randomizerPtr->OnGoalRequiresChaosEmeraldsSet(goalRequiresChaosEmeralds);
}

void SADX_GoalRequiresEmblems(const int goalRequiresEmblems)
{
    randomizerPtr->OnGoalRequiresEmblems(goalRequiresEmblems);
}

void SADX_GoalRequiresMissions(const int goalRequiresMissions)
{
    randomizerPtr->OnGoalRequiresMissionsSet(goalRequiresMissions);
}

void SADX_GoalRequiresBosses(const int goalRequiresBosses)
{
    randomizerPtr->OnGoalRequiresBossesSet(goalRequiresBosses);
}

void SADX_GoalRequiresChaoRaces(const int goalRequiresChaoRaces)
{
    randomizerPtr->OnGoalRequiresChaoRacesSet(goalRequiresChaoRaces);
}


void SADX_CompareModVersion(const int version)
{
    randomizerPtr->OnCheckVersion(version);
}

void SADX_LogicLevel(const int logicLevel)
{
    randomizerPtr->OnSetLogicLevel(logicLevel);
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

void SADX_BossesForPerfectChaos(const int bossesGoal)
{
    randomizerPtr->OnBossesGoalSet(bossesGoal);
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

void SADX_EnemySanity(const int enemySanity)
{
    randomizerPtr->OnEnemySanitySet(enemySanity);
}

void SADX_SonicEnemySanity(const int characterEnemySanity)
{
    randomizerPtr->SetCharacterEnemySanity(Characters_Sonic, characterEnemySanity);
}

void SADX_TailsEnemySanity(const int characterEnemySanity)
{
    randomizerPtr->SetCharacterEnemySanity(Characters_Tails, characterEnemySanity);
}

void SADX_KnucklesEnemySanity(const int characterEnemySanity)
{
    randomizerPtr->SetCharacterEnemySanity(Characters_Knuckles, characterEnemySanity);
}

void SADX_AmyEnemySanity(const int characterEnemySanity)
{
    randomizerPtr->SetCharacterEnemySanity(Characters_Amy, characterEnemySanity);
}

void SADX_GammaEnemySanity(const int characterEnemySanity)
{
    randomizerPtr->SetCharacterEnemySanity(Characters_Gamma, characterEnemySanity);
}

void SADX_BigEnemySanity(const int characterEnemySanity)
{
    randomizerPtr->SetCharacterEnemySanity(Characters_Big, characterEnemySanity);
}

void SADX_CapsuleSanity(const int capsuleSanity)
{
    randomizerPtr->OnCapsuleSanitySet(capsuleSanity);
}

void SADX_PinballCapsules(const int includePinballCapsules)
{
    randomizerPtr->OnPinballCapsulesSet(includePinballCapsules);
}

void SADX_SonicCapsuleSanity(const int characterCapsuleSanity)
{
    randomizerPtr->SetCharacterCapsuleSanity(Characters_Sonic, characterCapsuleSanity);
}

void SADX_TailsCapsuleSanity(const int characterCapsuleSanity)
{
    randomizerPtr->SetCharacterCapsuleSanity(Characters_Tails, characterCapsuleSanity);
}

void SADX_KnucklesCapsuleSanity(const int characterCapsuleSanity)
{
    randomizerPtr->SetCharacterCapsuleSanity(Characters_Knuckles, characterCapsuleSanity);
}

void SADX_AmyCapsuleSanity(const int characterCapsuleSanity)
{
    randomizerPtr->SetCharacterCapsuleSanity(Characters_Amy, characterCapsuleSanity);
}

void SADX_GammaCapsuleSanity(const int characterCapsuleSanity)
{
    randomizerPtr->SetCharacterCapsuleSanity(Characters_Gamma, characterCapsuleSanity);
}

void SADX_BigCapsuleSanity(const int characterCapsuleSanity)
{
    randomizerPtr->SetCharacterCapsuleSanity(Characters_Big, characterCapsuleSanity);
}

void SADX_LifeCapsuleSanity(const int lifeCapsuleSanity)
{
    randomizerPtr->OnLifeCapsuleSanitySet(lifeCapsuleSanity);
}

void SADX_ShieldCapsuleSanity(const int shieldCapsuleSanity)
{
    randomizerPtr->OnShieldCapsuleSanitySet(shieldCapsuleSanity);
}

void SADX_PowerUpCapsuleSanity(const int powerUpCapsuleSanity)
{
    randomizerPtr->OnPowerUpCapsuleSanitySet(powerUpCapsuleSanity);
}

void SADX_RingCapsuleSanity(const int ringCapsuleSanity)
{
    randomizerPtr->OnRingCapsuleSanitySet(ringCapsuleSanity);
}

void SADX_FishSanity(const int fishSanity)
{
    randomizerPtr->OnFishSanitySet(fishSanity);
}

void SADX_LazyFishing(const int lazyFishing)
{
    randomizerPtr->OnLazyFishingSet(lazyFishing > 0);
}

void SADX_ProgressionItems(const std::map<int, int> progressionItems)
{
    if (progressionItems.empty())
        return;
    std::vector<int> progressionItemsList;

    for (const auto& progressionItem : progressionItems)
        progressionItemsList.push_back(progressionItem.first - archipelagoManagerPtr->baseId);

    randomizerPtr->UpdateProgressionItemsList(progressionItemsList);
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

void SADX_SetEntranceRandomizer(const int enableEntranceRandomizer)
{
    randomizerPtr->SetEntranceRandomizer(enableEntranceRandomizer);
}

void SADX_SetDeathLink(const int deathLinkActive)
{
    if (archipelagoManagerPtr->deathLinkOverride == DeathLinkForceEnabled)
        randomizerPtr->SetDeathLink(true);
    else if (archipelagoManagerPtr->deathLinkOverride == DeathLinkForceDisabled)
        randomizerPtr->SetDeathLink(false);
    else
        randomizerPtr->SetDeathLink(deathLinkActive);
}

void SADX_SendDeathLinkChance(const int sendDeathLinkChance)
{
    randomizerPtr->SetSendDeathLinkChance(sendDeathLinkChance);
}

void SADX_ReceiveDeathLinkChance(const int receiveDeathLinkChance)
{
    randomizerPtr->SetReceiveDeathLinkChance(receiveDeathLinkChance);
}


void SADX_SetRingLink(const int ringLinkActive)
{
    if (archipelagoManagerPtr->ringLinkOverride == RingLinkForceEnabled
        || archipelagoManagerPtr->ringLinkOverride == RingLinkForceEnabledHard)
        randomizerPtr->SetRingLink(true);
    else if (archipelagoManagerPtr->ringLinkOverride == RingLinkForceDisabled)
        randomizerPtr->SetRingLink(false);
    else
        randomizerPtr->SetRingLink(ringLinkActive);
}

void SADX_SetCasinopolisRingLink(const int casinopolisRingLink)
{
    randomizerPtr->SetCasinopolisRingLink(casinopolisRingLink);
}

void SADX_SetHardRingLink(const int hardRingLinkActive)
{
    if (archipelagoManagerPtr->ringLinkOverride == RingLinkForceEnabledHard)
        randomizerPtr->SetHardRingLink(true);
    else if (archipelagoManagerPtr->ringLinkOverride == RingLinkForceDisabled
        || archipelagoManagerPtr->ringLinkOverride == RingLinkForceEnabled)
        randomizerPtr->SetHardRingLink(false);
    else
        randomizerPtr->SetHardRingLink(hardRingLinkActive);
}

void SADX_SetTrapLink(const int trapLinkActive)
{
    if (archipelagoManagerPtr->trapLinkOverride == TrapLinkForceEnabled)
        randomizerPtr->SetTrapLink(true);
    else if (archipelagoManagerPtr->trapLinkOverride == TrapLinkForceDisabled)
        randomizerPtr->SetTrapLink(false);
    else
        randomizerPtr->SetTrapLink(trapLinkActive);
}

void SADX_RingLoss(const int ringLoss)
{
    if (archipelagoManagerPtr->ringLossOverride == RingLossDefault)
        randomizerPtr->SetRingLoss(static_cast<RingLoss>(ringLoss));
    else if (archipelagoManagerPtr->ringLossOverride == RingLossForceClassic)
        randomizerPtr->SetRingLoss(Classic);
    else if (archipelagoManagerPtr->ringLossOverride == RingLossForceModern)
        randomizerPtr->SetRingLoss(Modern);
    else if (archipelagoManagerPtr->ringLossOverride == RingLossForceOhko)
        randomizerPtr->SetRingLoss(OneHitKnockOut);
    else if (archipelagoManagerPtr->ringLossOverride == RingLossForceOhkoNoShields)
        randomizerPtr->SetRingLoss(OneHitKnockOutNoShields);
}

void SADX_TwinkleCircuitCheck(const int twinkleCircuitCheck)
{
    randomizerPtr->SetTwinkleCircuitCheck(twinkleCircuitCheck);
}

void SADX_MultipleTwinkleCircuitChecks(const int multipleTwinkleCircuitChecks)
{
    randomizerPtr->SetMultipleTwinkleCircuitChecks(multipleTwinkleCircuitChecks);
}

void SADX_SkyChaseChecks(const int skyChaseChecks)
{
    randomizerPtr->SetSkyChaseChecks(skyChaseChecks);
}

void SADX_SkyChaseChecksHard(const int skyChaseChecksHard)
{
    randomizerPtr->SetSkyChaseChecksHard(skyChaseChecksHard);
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

void SADX_MusicSource(const int musicSource)
{
    randomizerPtr->SetMusicSource(static_cast<MusicSource>(musicSource));
}

void SADX_MusicShuffle(const int musicShuffle)
{
    randomizerPtr->SetMusicShuffle(static_cast<MusicShuffle>(musicShuffle));
}

void SADX_MusicShuffleConsistency(const int musicShuffleConsistency)
{
    randomizerPtr->SetMusicShuffleConsistency(static_cast<MusicShuffleConsistency>(musicShuffleConsistency));
}

void SADX_MusicShuffleSeed(const int musicShuffleSeed)
{
    randomizerPtr->SetMusicShuffleSeed(musicShuffleSeed);
}

void SADX_LifeCapsulesChangeSongs(const int lifeCapsulesChangeSongs)
{
    randomizerPtr->SetLifeCapsulesChangeSongs(lifeCapsulesChangeSongs);
}

void SADX_ReverseControlTrapDuration(const int reverseControlTrapDuration)
{
    randomizerPtr->SetReverseControlTrapDuration(reverseControlTrapDuration);
}

void SADX_TrapsOnAdventureFields(const int trapsOnAdventureFields)
{
    randomizerPtr->SetTrapsOnAdventureFields(trapsOnAdventureFields);
}

void SADX_TrapsOnBossFights(const int trapsOnBossFights)
{
    randomizerPtr->SetTrapsOnBossFights(trapsOnBossFights);
}

void SADX_TrapsOnPerfectChaosFight(const int trapsOnPerfectChaosFight)
{
    randomizerPtr->SetTrapsOnPerfectChaosFight(trapsOnPerfectChaosFight);
}


void ArchipelagoManager::Connect()
{
    AP_Init(_serverIP.c_str(), "Sonic Adventure DX", playerName.c_str(), _serverPassword.c_str());

    AP_SetDeathLinkSupported(false);
    AP_SetItemClearCallback(&SADX_ResetItems);
    AP_SetItemRecvCallback(&SADX_RecvItem);
    AP_SetLocationCheckedCallback(&SADX_CheckLocation);
    AP_RegisterBouncedCallback(&SADX_HandleBouncedPacket);
    AP_RegisterSlotDataIntCallback("GoalRequiresLevels", &SADX_GoalRequiresLevels);
    AP_RegisterSlotDataIntCallback("GoalRequiresChaosEmeralds", &SADX_GoalRequiresChaosEmeralds);
    AP_RegisterSlotDataIntCallback("GoalRequiresEmblems", &SADX_GoalRequiresEmblems);
    AP_RegisterSlotDataIntCallback("GoalRequiresMissions", &SADX_GoalRequiresMissions);
    AP_RegisterSlotDataIntCallback("GoalRequiresBosses", &SADX_GoalRequiresBosses);
    AP_RegisterSlotDataIntCallback("GoalRequiresChaoRaces", &SADX_GoalRequiresChaoRaces);
    AP_RegisterSlotDataIntCallback("ModVersion", &SADX_CompareModVersion);
    AP_RegisterSlotDataIntCallback("LogicLevel", &SADX_LogicLevel);
    AP_RegisterSlotDataIntCallback("EmblemsForPerfectChaos", &SADX_EmblemsForPerfectChaos);
    AP_RegisterSlotDataIntCallback("LevelForPerfectChaos", &SADX_LevelForPerfectChaos);
    AP_RegisterSlotDataIntCallback("MissionForPerfectChaos", &SADX_MissionForPerfectChaos);
    AP_RegisterSlotDataIntCallback("BossesForPerfectChaos", &SADX_BossesForPerfectChaos);
    AP_RegisterSlotDataIntCallback("MissionModeChecks", &SADX_MissionModeChecks);
    AP_RegisterSlotDataMapIntIntCallback("MissionBlackList", &SADX_MissionBlackList);

    AP_RegisterSlotDataIntCallback("AutoStartMissions", &SADX_AutoStartMissions);

    AP_RegisterSlotDataIntCallback("EnemySanity", &SADX_EnemySanity);

    AP_RegisterSlotDataIntCallback("SonicEnemySanity", &SADX_SonicEnemySanity);
    AP_RegisterSlotDataIntCallback("TailsEnemySanity", &SADX_TailsEnemySanity);
    AP_RegisterSlotDataIntCallback("KnucklesEnemySanity", &SADX_KnucklesEnemySanity);
    AP_RegisterSlotDataIntCallback("AmyEnemySanity", &SADX_AmyEnemySanity);
    AP_RegisterSlotDataIntCallback("BigEnemySanity", &SADX_BigEnemySanity);
    AP_RegisterSlotDataIntCallback("GammaEnemySanity", &SADX_GammaEnemySanity);

    AP_RegisterSlotDataIntCallback("CapsuleSanity", &SADX_CapsuleSanity);
    AP_RegisterSlotDataIntCallback("PinballCapsules", &SADX_PinballCapsules);

    AP_RegisterSlotDataIntCallback("SonicCapsuleSanity", &SADX_SonicCapsuleSanity);
    AP_RegisterSlotDataIntCallback("TailsCapsuleSanity", &SADX_TailsCapsuleSanity);
    AP_RegisterSlotDataIntCallback("KnucklesCapsuleSanity", &SADX_KnucklesCapsuleSanity);
    AP_RegisterSlotDataIntCallback("AmyCapsuleSanity", &SADX_AmyCapsuleSanity);
    AP_RegisterSlotDataIntCallback("BigCapsuleSanity", &SADX_BigCapsuleSanity);
    AP_RegisterSlotDataIntCallback("GammaCapsuleSanity", &SADX_GammaCapsuleSanity);

    AP_RegisterSlotDataIntCallback("LifeCapsuleSanity", &SADX_LifeCapsuleSanity);
    AP_RegisterSlotDataIntCallback("ShieldCapsuleSanity", &SADX_ShieldCapsuleSanity);
    AP_RegisterSlotDataIntCallback("PowerUpCapsuleSanity", &SADX_PowerUpCapsuleSanity);
    AP_RegisterSlotDataIntCallback("RingCapsuleSanity", &SADX_RingCapsuleSanity);

    AP_RegisterSlotDataIntCallback("FishSanity", &SADX_FishSanity);
    AP_RegisterSlotDataIntCallback("LazyFishing", &SADX_LazyFishing);

    AP_RegisterSlotDataMapIntIntCallback("ProgressionItems", &SADX_ProgressionItems);

    AP_RegisterSlotDataIntCallback("StartingCharacter", &SADX_StartingCharacter);
    AP_RegisterSlotDataIntCallback("SonicStartingArea", &SADX_SonicStartingArea);
    AP_RegisterSlotDataIntCallback("TailsStartingArea", &SADX_TailsStartingArea);
    AP_RegisterSlotDataIntCallback("KnucklesStartingArea", &SADX_KnucklesStartingArea);
    AP_RegisterSlotDataIntCallback("AmyStartingArea", &SADX_AmyStartingArea);
    AP_RegisterSlotDataIntCallback("GammaStartingArea", &SADX_GammaStartingArea);
    AP_RegisterSlotDataIntCallback("BigStartingArea", &SADX_BigStartingArea);

    AP_RegisterSlotDataMapIntIntCallback("LevelEntranceMap", &SADX_LevelEntranceMap);
    AP_RegisterSlotDataIntCallback("EntranceRandomizer", &SADX_SetEntranceRandomizer);

    AP_RegisterSlotDataIntCallback("DeathLink", &SADX_SetDeathLink);
    AP_RegisterSlotDataIntCallback("SendDeathLinkChance", &SADX_SendDeathLinkChance);
    AP_RegisterSlotDataIntCallback("ReceiveDeathLinkChance", &SADX_ReceiveDeathLinkChance);

    AP_RegisterSlotDataIntCallback("RingLink", &SADX_SetRingLink);
    AP_RegisterSlotDataIntCallback("CasinopolisRingLink", &SADX_SetCasinopolisRingLink);
    AP_RegisterSlotDataIntCallback("HardRingLink", &SADX_SetHardRingLink);
    AP_RegisterSlotDataIntCallback("RingLoss", &SADX_RingLoss);

    AP_RegisterSlotDataIntCallback("TrapLink", &SADX_SetTrapLink);

    AP_RegisterSlotDataIntCallback("TwinkleCircuitCheck", &SADX_TwinkleCircuitCheck);
    AP_RegisterSlotDataIntCallback("MultipleTwinkleCircuitChecks", &SADX_MultipleTwinkleCircuitChecks);
    AP_RegisterSlotDataIntCallback("SkyChaseChecks", &SADX_SkyChaseChecks);
    AP_RegisterSlotDataIntCallback("SkyChaseChecksHard", &SADX_SkyChaseChecksHard);

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

    AP_RegisterSlotDataIntCallback("MusicSource", &SADX_MusicSource);
    AP_RegisterSlotDataIntCallback("MusicShuffle", &SADX_MusicShuffle);
    AP_RegisterSlotDataIntCallback("MusicShuffleConsistency", &SADX_MusicShuffleConsistency);
    AP_RegisterSlotDataIntCallback("MusicShuffleSeed", &SADX_MusicShuffleSeed);
    AP_RegisterSlotDataIntCallback("LifeCapsulesChangeSongs", &SADX_LifeCapsulesChangeSongs);


    AP_RegisterSlotDataIntCallback("ReverseControlTrapDuration", &SADX_ReverseControlTrapDuration);
    AP_RegisterSlotDataIntCallback("TrapsOnAdventureFields", &SADX_TrapsOnAdventureFields);
    AP_RegisterSlotDataIntCallback("TrapsOnBossFights", &SADX_TrapsOnBossFights);
    AP_RegisterSlotDataIntCallback("TrapsOnPerfectChaosFight", &SADX_TrapsOnPerfectChaosFight);


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
