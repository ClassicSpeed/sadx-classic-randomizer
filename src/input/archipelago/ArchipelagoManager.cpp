#include "ArchipelagoManager.h"

Randomizer* randomizerPtr = nullptr;
ArchipelagoManager* archipelagoManagerPtr = nullptr;

ArchipelagoManager::ArchipelagoManager(Randomizer& randomizer, Options& options, const int instanceId,
                                       const int64_t baseId)
    : options(options), _randomizer(randomizer)
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


void ArchipelagoManager::RecvItem(const int64_t itemId, const bool notify)
{
    PrintDebug(" --- Item received: %d\n", itemId);
    randomizerPtr->OnItemReceived(itemId - archipelagoManagerPtr->baseId);
}

void ArchipelagoManager::ResetItems()
{
    PrintDebug(" --- Reset items\n");
    randomizerPtr->ResetItems();
}

void ArchipelagoManager::CheckLocation(const int64_t locationId)
{
    PrintDebug(" --- Checked location %d\n", locationId);
    randomizerPtr->MarkCheckedLocation(locationId - archipelagoManagerPtr->baseId);
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
            if (bounceData["source"].asInt() == archipelagoManagerPtr->instanceId)
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
            if (bounceData["source"].asInt() == archipelagoManagerPtr->instanceId)
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

void ArchipelagoManager::GoalRequiresLevels(const int goalRequiresLevels)
{
    options.goalRequiresLevels = goalRequiresLevels;
}

void ArchipelagoManager::GoalRequiresChaosEmeralds(const int goalRequiresChaosEmeralds)
{
    options.goalRequiresChaosEmeralds = goalRequiresChaosEmeralds;
}

void ArchipelagoManager::GoalRequiresEmblems(const int goalRequiresEmblems)
{
    options.goalRequiresEmblems = goalRequiresEmblems;
}

void ArchipelagoManager::GoalRequiresMissions(const int goalRequiresMissions)
{
    options.goalRequiresMissions = goalRequiresMissions;
}

void ArchipelagoManager::GoalRequiresBosses(const int goalRequiresBosses)
{
    options.goalRequiresBosses = goalRequiresBosses;
}

void ArchipelagoManager::GoalRequiresChaoRaces(const int goalRequiresChaoRaces)
{
    options.goalRequiresChaoRaces = goalRequiresChaoRaces;
}


void ArchipelagoManager::CompareModVersion(const int version)
{
    PrintDebug(" --- Checking mod version: %d\n", version);
    //TODO: Remove from randomizer.cpp
    randomizerPtr->OnCheckVersion(version);
}

void ArchipelagoManager::LogicLevel(const int logicLevel)
{
    if (logicLevel > 1)
        options.expertMode = true;
    else
        options.expertMode = false;
}

void ArchipelagoManager::EmblemsForPerfectChaos(const int emblemGoal)
{
    options.emblemGoal = max(1, emblemGoal);
}

void ArchipelagoManager::LevelForPerfectChaos(const int levelGoal)
{
    options.levelGoal = max(1, levelGoal);
}

void ArchipelagoManager::MissionForPerfectChaos(const int missionGoal)
{
    options.missionGoal = max(1, missionGoal);
}

void ArchipelagoManager::BossesForPerfectChaos(const int bossesGoal)
{
    options.bossesGoal = max(1, bossesGoal);
}

void ArchipelagoManager::MissionModeChecks(const int missionModeEnabled)
{
    options.missionModeEnabled = missionModeEnabled;
}

void ArchipelagoManager::MissionBlackList(const std::map<int, int> missionBlacklist)
{
    if (missionBlacklist.empty())
        return;
    std::vector<int> blacklistedMissions;

    for (const auto& mission : missionBlacklist)
        blacklistedMissions.push_back(mission.first);

    options.missionBlacklist = blacklistedMissions;
}

void ArchipelagoManager::AutoStartMissions(const int autoStartMissions)
{
    options.autoStartMissions = autoStartMissions > 0;
}

void ArchipelagoManager::EnemySanity(const int enemySanity)
{
    options.enemySanity = enemySanity;
}

void ArchipelagoManager::SonicEnemySanity(const int characterEnemySanity)
{
    options.SetCharacterEnemySanity(Characters_Sonic, characterEnemySanity);
}

void ArchipelagoManager::TailsEnemySanity(const int characterEnemySanity)
{
    options.SetCharacterEnemySanity(Characters_Tails, characterEnemySanity);
}

void ArchipelagoManager::KnucklesEnemySanity(const int characterEnemySanity)
{
    options.SetCharacterEnemySanity(Characters_Knuckles, characterEnemySanity);
}

void ArchipelagoManager::AmyEnemySanity(const int characterEnemySanity)
{
    options.SetCharacterEnemySanity(Characters_Amy, characterEnemySanity);
}

void ArchipelagoManager::GammaEnemySanity(const int characterEnemySanity)
{
    options.SetCharacterEnemySanity(Characters_Gamma, characterEnemySanity);
}

void ArchipelagoManager::BigEnemySanity(const int characterEnemySanity)
{
    options.SetCharacterEnemySanity(Characters_Big, characterEnemySanity);
}

void ArchipelagoManager::CapsuleSanity(const int capsuleSanity)
{
    options.capsuleSanity = capsuleSanity;
}

void ArchipelagoManager::PinballCapsules(const int includePinballCapsules)
{
    options.includePinballCapsules = includePinballCapsules;
}

void ArchipelagoManager::SonicCapsuleSanity(const int characterCapsuleSanity)
{
    options.SetCharacterCapsuleSanity(Characters_Sonic, characterCapsuleSanity);
}

void ArchipelagoManager::TailsCapsuleSanity(const int characterCapsuleSanity)
{
    options.SetCharacterCapsuleSanity(Characters_Tails, characterCapsuleSanity);
}

void ArchipelagoManager::KnucklesCapsuleSanity(const int characterCapsuleSanity)
{
    options.SetCharacterCapsuleSanity(Characters_Knuckles, characterCapsuleSanity);
}

void ArchipelagoManager::AmyCapsuleSanity(const int characterCapsuleSanity)
{
    options.SetCharacterCapsuleSanity(Characters_Amy, characterCapsuleSanity);
}

void ArchipelagoManager::GammaCapsuleSanity(const int characterCapsuleSanity)
{
    options.SetCharacterCapsuleSanity(Characters_Gamma, characterCapsuleSanity);
}

void ArchipelagoManager::BigCapsuleSanity(const int characterCapsuleSanity)
{
    options.SetCharacterCapsuleSanity(Characters_Big, characterCapsuleSanity);
}

void ArchipelagoManager::LifeCapsuleSanity(const int lifeCapsuleSanity)
{
    options.lifeCapsuleSanity = lifeCapsuleSanity;
}

void ArchipelagoManager::ShieldCapsuleSanity(const int shieldCapsuleSanity)
{
    options.shieldCapsuleSanity = shieldCapsuleSanity;
}

void ArchipelagoManager::PowerUpCapsuleSanity(const int powerUpCapsuleSanity)
{
    options.powerUpCapsuleSanity = powerUpCapsuleSanity;
}

void ArchipelagoManager::RingCapsuleSanity(const int ringCapsuleSanity)
{
    options.ringCapsuleSanity = ringCapsuleSanity;
}

void ArchipelagoManager::FishSanity(const int fishSanity)
{
    options.fishSanity = fishSanity;
}

void ArchipelagoManager::LazyFishing(const int lazyFishing)
{
    options.lazyFishing = lazyFishing > 0;
}

void ArchipelagoManager::ProgressionItems(const std::map<int, int> progressionItems)
{
    if (progressionItems.empty())
        return;
    std::vector<int> progressionItemsList;

    for (const auto& progressionItem : progressionItems)
        progressionItemsList.push_back(progressionItem.first - archipelagoManagerPtr->baseId);

    options.progressionItems = progressionItemsList;
}


void ArchipelagoManager::StartingCharacter(const int startingCharacterIndex)
{
    //TODO: Remove from randomizer.cpp
    randomizerPtr->SetStartingCharacter(startingCharacterIndex);
}

void ArchipelagoManager::SonicStartingArea(const int startingArea)
{
    options.SetCharacterStatingArea(Characters_Sonic, static_cast<StartingArea>(startingArea));
}

void ArchipelagoManager::TailsStartingArea(const int startingArea)
{
    options.SetCharacterStatingArea(Characters_Tails, static_cast<StartingArea>(startingArea));
}

void ArchipelagoManager::KnucklesStartingArea(const int startingArea)
{
    options.
        SetCharacterStatingArea(Characters_Knuckles, static_cast<StartingArea>(startingArea));
}

void ArchipelagoManager::AmyStartingArea(const int startingArea)
{
    options.SetCharacterStatingArea(Characters_Amy, static_cast<StartingArea>(startingArea));
}

void ArchipelagoManager::GammaStartingArea(const int startingArea)
{
    options.SetCharacterStatingArea(Characters_Gamma, static_cast<StartingArea>(startingArea));
}

void ArchipelagoManager::BigStartingArea(const int startingArea)
{
    options.SetCharacterStatingArea(Characters_Big, static_cast<StartingArea>(startingArea));
}

void ArchipelagoManager::LevelEntranceMap(const std::map<int, int> levelEntrancesValues)
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

    //TODO: Remove from randomizer.cpp
    randomizerPtr->UpdateLevelEntrances(levelEntrances);
}

void ArchipelagoManager::SetEntranceRandomizer(const int enableEntranceRandomizer)
{
    options.entranceRandomizer = enableEntranceRandomizer;
}

void ArchipelagoManager::SetDeathLink(const int deathLinkActive)
{
    if (archipelagoManagerPtr->deathLinkOverride == DeathLinkForceEnabled)
        options.deathLinkActive = true;
    else if (archipelagoManagerPtr->deathLinkOverride == DeathLinkForceDisabled)
        options.deathLinkActive = false;
    else
        options.deathLinkActive = deathLinkActive;
}

void ArchipelagoManager::SendDeathLinkChance(const int sendDeathLinkChance)
{
    //TODO: Remove from randomizer.cpp
    randomizerPtr->SetSendDeathLinkChance(sendDeathLinkChance);
}

void ArchipelagoManager::ReceiveDeathLinkChance(const int receiveDeathLinkChance)
{
    //TODO: Remove from randomizer.cpp
    randomizerPtr->SetReceiveDeathLinkChance(receiveDeathLinkChance);
}


void ArchipelagoManager::SetRingLink(const int ringLinkActive)
{
    if (archipelagoManagerPtr->ringLinkOverride == RingLinkForceEnabled
        || archipelagoManagerPtr->ringLinkOverride == RingLinkForceEnabledHard)
        options.ringLinkActive = true;
    else if (archipelagoManagerPtr->ringLinkOverride == RingLinkForceDisabled)
        options.ringLinkActive = false;
    else
        options.ringLinkActive = ringLinkActive;
}

void ArchipelagoManager::SetCasinopolisRingLink(const int casinopolisRingLink)
{
    options.casinopolisRingLink = casinopolisRingLink;
}

void ArchipelagoManager::SetHardRingLink(const int hardRingLinkActive)
{
    if (archipelagoManagerPtr->ringLinkOverride == RingLinkForceEnabledHard)
        options.hardRingLinkActive = true;
    else if (archipelagoManagerPtr->ringLinkOverride == RingLinkForceDisabled
        || archipelagoManagerPtr->ringLinkOverride == RingLinkForceEnabled)
        options.hardRingLinkActive = false;
    else
        options.hardRingLinkActive = hardRingLinkActive;
}

void ArchipelagoManager::SetTrapLink(const int trapLinkActive)
{
    if (archipelagoManagerPtr->trapLinkOverride == TrapLinkForceEnabled)
        options.trapLinkActive = true;
    else if (archipelagoManagerPtr->trapLinkOverride == TrapLinkForceDisabled)
        options.trapLinkActive = false;
    else
        options.trapLinkActive = trapLinkActive;
}

void ArchipelagoManager::SetRingLoss(const int ringLoss)
{
    if (archipelagoManagerPtr->ringLossOverride == RingLossDefault)
        options.ringLoss = static_cast<RingLoss>(ringLoss);
    else if (archipelagoManagerPtr->ringLossOverride == RingLossForceClassic)
        options.ringLoss = Classic;
    else if (archipelagoManagerPtr->ringLossOverride == RingLossForceModern)
        options.ringLoss = Modern;
    else if (archipelagoManagerPtr->ringLossOverride == RingLossForceOhko)
        options.ringLoss = OneHitKnockOut;
    else if (archipelagoManagerPtr->ringLossOverride == RingLossForceOhkoNoShields)
        options.ringLoss = OneHitKnockOutNoShields;
}

void ArchipelagoManager::TwinkleCircuitCheck(const int twinkleCircuitCheck)
{
    options.twinkleCircuitCheck = twinkleCircuitCheck;
}

void ArchipelagoManager::MultipleTwinkleCircuitChecks(const int multipleTwinkleCircuitChecks)
{
    options.multipleTwinkleCircuitChecks = multipleTwinkleCircuitChecks;
}

void ArchipelagoManager::SkyChaseChecks(const int skyChaseChecks)
{
    options.skyChaseChecks = skyChaseChecks;
}

void ArchipelagoManager::SkyChaseChecksHard(const int skyChaseChecksHard)
{
    options.skyChaseChecksHard = skyChaseChecksHard;
}

void ArchipelagoManager::BossChecks(const int bossChecks)
{
    options.bossChecks = bossChecks;
}

void ArchipelagoManager::UnifyChaos4(const int unifyChaos4)
{
    options.unifyChaos4 = unifyChaos4;
}

void ArchipelagoManager::UnifyChaos6(const int unifyChaos6)
{
    options.unifyChaos6 = unifyChaos6;
}

void ArchipelagoManager::UnifyEggHornet(const int unifyEggHornet)
{
    options.unifyEggHornet = unifyEggHornet;
}

void ArchipelagoManager::PlayableSonic(const int playable)
{
    options.SetPlayableCharacter(Characters_Sonic, playable);
}

void ArchipelagoManager::PlayableTails(const int playable)
{
    options.SetPlayableCharacter(Characters_Tails, playable);
}

void ArchipelagoManager::PlayableKnuckles(const int playable)
{
    options.SetPlayableCharacter(Characters_Knuckles, playable);
}

void ArchipelagoManager::PlayableAmy(const int playable)
{
    options.SetPlayableCharacter(Characters_Amy, playable);
}

void ArchipelagoManager::PlayableGamma(const int playable)
{
    options.SetPlayableCharacter(Characters_Gamma, playable);
}

void ArchipelagoManager::PlayableBig(const int playable)
{
    options.SetPlayableCharacter(Characters_Big, playable);
}

void ArchipelagoManager::SonicActionStageMissions(const int missions)
{
    options.SetActionStageMissions(Characters_Sonic, missions);
}

void ArchipelagoManager::TailsActionStageMissions(const int missions)
{
    options.SetActionStageMissions(Characters_Tails, missions);
}

void ArchipelagoManager::KnucklesActionStageMissions(const int missions)
{
    options.SetActionStageMissions(Characters_Knuckles, missions);
}

void ArchipelagoManager::AmyActionStageMissions(const int missions)
{
    options.SetActionStageMissions(Characters_Amy, missions);
}

void ArchipelagoManager::GammaActionStageMissions(const int missions)
{
    options.SetActionStageMissions(Characters_Gamma, missions);
}

void ArchipelagoManager::BigActionStageMissions(const int missions)
{
    options.SetActionStageMissions(Characters_Big, missions);
}

void ArchipelagoManager::SetMusicSource(const int musicSource)
{
    if (options.musicSource == MusicSourceNone)
        options.musicSource = static_cast<MusicSource>(musicSource);
}

void ArchipelagoManager::SetMusicShuffle(const int musicShuffle)
{
    if (options.musicShuffle == MusicShuffleNone)
        options.musicShuffle = static_cast<MusicShuffle>(musicShuffle);
}

void ArchipelagoManager::SetMusicShuffleConsistency(const int musicShuffleConsistency)
{
    if (options.musicShuffleConsistency == MusicShuffleConsistencyNone)
        options.musicShuffleConsistency = static_cast<MusicShuffleConsistency>(
            musicShuffleConsistency);
}

void ArchipelagoManager::SetMusicShuffleSeed(const int musicShuffleSeed)
{
    options.musicShuffleSeed = musicShuffleSeed;
}

void ArchipelagoManager::SetLifeCapsulesChangeSongs(const int lifeCapsulesChangeSongs)
{
    if (options.lifeCapsulesChangeSongs == LifeCapsulesChangeSongsNone)
        options.lifeCapsulesChangeSongs = lifeCapsulesChangeSongs
                                              ? LifeCapsulesChangeSongsEnabled
                                              : LifeCapsulesChangeSongsDisabled;
}


void ArchipelagoManager::SetIceTrapWeight(const int iceTrapWeight)
{
    options.iceTrapWeight = iceTrapWeight;
}

void ArchipelagoManager::SetSpringTrapWeight(const int springTrapWeight)
{
    options.springTrapWeight = springTrapWeight;
}

void ArchipelagoManager::SetPoliceTrapWeight(const int policeTrapWeight)
{
    options.policeTrapWeight = policeTrapWeight;
}

void ArchipelagoManager::SetBuyonTrapWeight(const int buyonTrapWeight)
{
    options.buyonTrapWeight = buyonTrapWeight;
}

void ArchipelagoManager::SetReverseTrapWeight(const int reverseTrapWeight)
{
    options.reverseTrapWeight = reverseTrapWeight;
}

void ArchipelagoManager::SetGravityTrapWeight(const int gravityTrapWeight)
{
    options.gravityTrapWeight = gravityTrapWeight;
}

void ArchipelagoManager::ReverseControlTrapDuration(const int reverseControlTrapDuration)
{
    options._reverseControlsDuration = static_cast<float>(reverseControlTrapDuration);
}

void ArchipelagoManager::TrapsOnAdventureFields(const int trapsOnAdventureFields)
{
    options._trapsOnAdventureFields = trapsOnAdventureFields > 0;
}

void ArchipelagoManager::TrapsOnBossFights(const int trapsOnBossFights)
{
    options._trapsOnBossFights = trapsOnBossFights > 0;
}

void ArchipelagoManager::TrapsOnPerfectChaosFight(const int trapsOnPerfectChaosFight)
{
    options._trapsOnPerfectChaosFight = trapsOnPerfectChaosFight > 0;
}


void ArchipelagoManager::Connect()
{
    AP_Init(_serverIP.c_str(), "Sonic Adventure DX", playerName.c_str(), _serverPassword.c_str());

    AP_SetDeathLinkSupported(false);
    AP_SetItemClearCallback([this]() { ResetItems(); });
    AP_SetItemRecvCallback([this](const int64_t itemId, const bool notify) { RecvItem(itemId, notify); });
    AP_SetLocationCheckedCallback([this](const int64_t locationId) { CheckLocation(locationId); });
    AP_RegisterBouncedCallback([this](const AP_Bounce bouncePacket) { HandleBouncedPacket(bouncePacket); });
    
    AP_REGISTER_INT_CALLBACK("GoalRequiresLevels", GoalRequiresLevels);
    AP_REGISTER_INT_CALLBACK("GoalRequiresChaosEmeralds", GoalRequiresChaosEmeralds);
    AP_REGISTER_INT_CALLBACK("GoalRequiresEmblems", GoalRequiresEmblems);
    AP_REGISTER_INT_CALLBACK("GoalRequiresMissions", GoalRequiresMissions);
    AP_REGISTER_INT_CALLBACK("GoalRequiresBosses", GoalRequiresBosses);
    AP_REGISTER_INT_CALLBACK("GoalRequiresChaoRaces", GoalRequiresChaoRaces);
    AP_REGISTER_INT_CALLBACK("ModVersion", CompareModVersion);
    AP_REGISTER_INT_CALLBACK("LogicLevel", LogicLevel);
    AP_REGISTER_INT_CALLBACK("EmblemsForPerfectChaos", EmblemsForPerfectChaos);
    AP_REGISTER_INT_CALLBACK("LevelForPerfectChaos", LevelForPerfectChaos);
    AP_REGISTER_INT_CALLBACK("MissionForPerfectChaos", MissionForPerfectChaos);
    AP_REGISTER_INT_CALLBACK("BossesForPerfectChaos", BossesForPerfectChaos);
    AP_REGISTER_INT_CALLBACK("MissionModeChecks", MissionModeChecks);
    AP_REGISTER_MAP_CALLBACK("MissionBlackList", MissionBlackList);

    AP_REGISTER_INT_CALLBACK("AutoStartMissions", AutoStartMissions);

    AP_REGISTER_INT_CALLBACK("EnemySanity", EnemySanity);

    AP_REGISTER_INT_CALLBACK("SonicEnemySanity", SonicEnemySanity);
    AP_REGISTER_INT_CALLBACK("TailsEnemySanity", TailsEnemySanity);
    AP_REGISTER_INT_CALLBACK("KnucklesEnemySanity", KnucklesEnemySanity);
    AP_REGISTER_INT_CALLBACK("AmyEnemySanity", AmyEnemySanity);
    AP_REGISTER_INT_CALLBACK("BigEnemySanity", BigEnemySanity);
    AP_REGISTER_INT_CALLBACK("GammaEnemySanity", GammaEnemySanity);

    AP_REGISTER_INT_CALLBACK("CapsuleSanity", CapsuleSanity);
    AP_REGISTER_INT_CALLBACK("PinballCapsules", PinballCapsules);

    AP_REGISTER_INT_CALLBACK("SonicCapsuleSanity", SonicCapsuleSanity);
    AP_REGISTER_INT_CALLBACK("TailsCapsuleSanity", TailsCapsuleSanity);
    AP_REGISTER_INT_CALLBACK("KnucklesCapsuleSanity", KnucklesCapsuleSanity);
    AP_REGISTER_INT_CALLBACK("AmyCapsuleSanity", AmyCapsuleSanity);
    AP_REGISTER_INT_CALLBACK("BigCapsuleSanity", BigCapsuleSanity);
    AP_REGISTER_INT_CALLBACK("GammaCapsuleSanity", GammaCapsuleSanity);

    AP_REGISTER_INT_CALLBACK("LifeCapsuleSanity", LifeCapsuleSanity);
    AP_REGISTER_INT_CALLBACK("ShieldCapsuleSanity", ShieldCapsuleSanity);
    AP_REGISTER_INT_CALLBACK("PowerUpCapsuleSanity", PowerUpCapsuleSanity);
    AP_REGISTER_INT_CALLBACK("RingCapsuleSanity", RingCapsuleSanity);

    AP_REGISTER_INT_CALLBACK("FishSanity", FishSanity);
    AP_REGISTER_INT_CALLBACK("LazyFishing", LazyFishing);

    AP_REGISTER_MAP_CALLBACK("ProgressionItems", ProgressionItems);

    AP_REGISTER_INT_CALLBACK("StartingCharacter", StartingCharacter);
    AP_REGISTER_INT_CALLBACK("SonicStartingArea", SonicStartingArea);
    AP_REGISTER_INT_CALLBACK("TailsStartingArea", TailsStartingArea);
    AP_REGISTER_INT_CALLBACK("KnucklesStartingArea", KnucklesStartingArea);
    AP_REGISTER_INT_CALLBACK("AmyStartingArea", AmyStartingArea);
    AP_REGISTER_INT_CALLBACK("GammaStartingArea", GammaStartingArea);
    AP_REGISTER_INT_CALLBACK("BigStartingArea", BigStartingArea);

    AP_REGISTER_MAP_CALLBACK("LevelEntranceMap", LevelEntranceMap);
    AP_REGISTER_INT_CALLBACK("EntranceRandomizer", SetEntranceRandomizer);

    AP_REGISTER_INT_CALLBACK("DeathLink", SetDeathLink);
    AP_REGISTER_INT_CALLBACK("SendDeathLinkChance", SendDeathLinkChance);
    AP_REGISTER_INT_CALLBACK("ReceiveDeathLinkChance", ReceiveDeathLinkChance);

    AP_REGISTER_INT_CALLBACK("RingLink", SetRingLink);
    AP_REGISTER_INT_CALLBACK("CasinopolisRingLink", SetCasinopolisRingLink);
    AP_REGISTER_INT_CALLBACK("HardRingLink", SetHardRingLink);
    AP_REGISTER_INT_CALLBACK("RingLoss", SetRingLoss);

    AP_REGISTER_INT_CALLBACK("TrapLink", SetTrapLink);

    AP_REGISTER_INT_CALLBACK("TwinkleCircuitCheck", TwinkleCircuitCheck);
    AP_REGISTER_INT_CALLBACK("MultipleTwinkleCircuitChecks", MultipleTwinkleCircuitChecks);
    AP_REGISTER_INT_CALLBACK("SkyChaseChecks", SkyChaseChecks);
    AP_REGISTER_INT_CALLBACK("SkyChaseChecksHard", SkyChaseChecksHard);

    AP_REGISTER_INT_CALLBACK("BossChecks", BossChecks);
    AP_REGISTER_INT_CALLBACK("UnifyChaos4", UnifyChaos4);
    AP_REGISTER_INT_CALLBACK("UnifyChaos6", UnifyChaos6);
    AP_REGISTER_INT_CALLBACK("UnifyEggHornet", UnifyEggHornet);


    AP_REGISTER_INT_CALLBACK("PlayableSonic", PlayableSonic);
    AP_REGISTER_INT_CALLBACK("PlayableTails", PlayableTails);
    AP_REGISTER_INT_CALLBACK("PlayableKnuckles", PlayableKnuckles);
    AP_REGISTER_INT_CALLBACK("PlayableAmy", PlayableAmy);
    AP_REGISTER_INT_CALLBACK("PlayableBig", PlayableBig);
    AP_REGISTER_INT_CALLBACK("PlayableGamma", PlayableGamma);

    AP_REGISTER_INT_CALLBACK("SonicActionStageMissions", SonicActionStageMissions);
    AP_REGISTER_INT_CALLBACK("TailsActionStageMissions", TailsActionStageMissions);
    AP_REGISTER_INT_CALLBACK("KnucklesActionStageMissions", KnucklesActionStageMissions);
    AP_REGISTER_INT_CALLBACK("AmyActionStageMissions", AmyActionStageMissions);
    AP_REGISTER_INT_CALLBACK("GammaActionStageMissions", GammaActionStageMissions);
    AP_REGISTER_INT_CALLBACK("BigActionStageMissions", BigActionStageMissions);

    AP_REGISTER_INT_CALLBACK("MusicSource", SetMusicSource);
    AP_REGISTER_INT_CALLBACK("MusicShuffle", SetMusicShuffle);
    AP_REGISTER_INT_CALLBACK("MusicShuffleConsistency", SetMusicShuffleConsistency);
    AP_REGISTER_INT_CALLBACK("MusicShuffleSeed", SetMusicShuffleSeed);
    AP_REGISTER_INT_CALLBACK("LifeCapsulesChangeSongs", SetLifeCapsulesChangeSongs);

    AP_REGISTER_INT_CALLBACK("IceTrapWeight", SetIceTrapWeight);
    AP_REGISTER_INT_CALLBACK("SpringTrapWeight", SetSpringTrapWeight);
    AP_REGISTER_INT_CALLBACK("PoliceTrapWeight", SetPoliceTrapWeight);
    AP_REGISTER_INT_CALLBACK("BuyonTrapWeight", SetBuyonTrapWeight);
    AP_REGISTER_INT_CALLBACK("ReverseTrapWeight", SetReverseTrapWeight);
    AP_REGISTER_INT_CALLBACK("GravityTrapWeight", SetGravityTrapWeight);

    AP_REGISTER_INT_CALLBACK("ReverseControlTrapDuration", ReverseControlTrapDuration);
    AP_REGISTER_INT_CALLBACK("TrapsOnAdventureFields", TrapsOnAdventureFields);
    AP_REGISTER_INT_CALLBACK("TrapsOnBossFights", TrapsOnBossFights);
    AP_REGISTER_INT_CALLBACK("TrapsOnPerfectChaosFight", TrapsOnPerfectChaosFight);


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
