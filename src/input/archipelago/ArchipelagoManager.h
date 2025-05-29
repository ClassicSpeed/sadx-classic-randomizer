#pragma once
#include "../../application/Randomizer.h"

#define AP_REGISTER_INT_CALLBACK(key, method) \
AP_RegisterSlotDataIntCallback(key, [this](const int value) { method(value); })

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

enum DeathLinkOverride
{
    DeathLinkDefault = 0,
    DeathLinkForceEnabled = 1,
    DeathLinkForceDisabled = 2,
};

enum RingLinkOverride
{
    RingLinkDefault = 0,
    RingLinkForceEnabled = 1,
    RingLinkForceEnabledHard = 2,
    RingLinkForceDisabled = 3,
};

enum RingLossOverride
{
    RingLossDefault = 0,
    RingLossForceClassic = 1,
    RingLossForceModern = 2,
    RingLossForceOhko = 3,
    RingLossForceOhkoNoShields = 4,
};

enum TrapLinkOverride
{
    TrapLinkDefault = 0,
    TrapLinkForceEnabled = 1,
    TrapLinkForceDisabled = 2,
};

class ArchipelagoManager
{
public:
    explicit ArchipelagoManager(Randomizer& randomizer, Options& options, int instanceId, int64_t baseId);

    void Connect();
    bool IsValidSaveFile();
    void OnFrame();
    bool IsWaitingForSaveFile();
    void OnSaveFileLoaded();
    void RecvItem(int64_t itemId, bool notify);
    void ResetItems();
    void CheckLocation(int64_t locationId);
    void HandleBouncedPacket(AP_Bounce bouncePacket);
    void GoalRequiresLevels(int goalRequiresLevels);
    void GoalRequiresChaosEmeralds(int goalRequiresChaosEmeralds);
    void GoalRequiresEmblems(int goalRequiresEmblems);
    void GoalRequiresMissions(int goalRequiresMissions);
    void GoalRequiresBosses(int goalRequiresBosses);
    void GoalRequiresChaoRaces(int goalRequiresChaoRaces);
    void CompareModVersion(int version);
    void LogicLevel(int logicLevel);
    void EmblemsForPerfectChaos(int emblemGoal);
    void LevelForPerfectChaos(int levelGoal);
    void MissionForPerfectChaos(int missionGoal);
    void BossesForPerfectChaos(int bossesGoal);
    void MissionModeChecks(int missionModeEnabled);
    void MissionBlackList(std::map<int, int> missionBlacklist);
    void AutoStartMissions(int autoStartMissions);
    void EnemySanity(int enemySanity);
    void SonicEnemySanity(int characterEnemySanity);
    void TailsEnemySanity(int characterEnemySanity);
    void KnucklesEnemySanity(int characterEnemySanity);
    void AmyEnemySanity(int characterEnemySanity);
    void GammaEnemySanity(int characterEnemySanity);
    void BigEnemySanity(int characterEnemySanity);
    void CapsuleSanity(int capsuleSanity);
    void PinballCapsules(int includePinballCapsules);
    void SonicCapsuleSanity(int characterCapsuleSanity);
    void TailsCapsuleSanity(int characterCapsuleSanity);
    void KnucklesCapsuleSanity(int characterCapsuleSanity);
    void AmyCapsuleSanity(int characterCapsuleSanity);
    void GammaCapsuleSanity(int characterCapsuleSanity);
    void BigCapsuleSanity(int characterCapsuleSanity);
    void LifeCapsuleSanity(int lifeCapsuleSanity);
    void ShieldCapsuleSanity(int shieldCapsuleSanity);
    void PowerUpCapsuleSanity(int powerUpCapsuleSanity);
    void RingCapsuleSanity(int ringCapsuleSanity);
    void FishSanity(int fishSanity);
    void LazyFishing(int lazyFishing);
    void ProgressionItems(std::map<int, int> progressionItems);
    void StartingCharacter(int startingCharacterIndex);
    void SonicStartingArea(int startingArea);
    void TailsStartingArea(int startingArea);
    void KnucklesStartingArea(int startingArea);
    void AmyStartingArea(int startingArea);
    void GammaStartingArea(int startingArea);
    void BigStartingArea(int startingArea);
    void LevelEntranceMap(std::map<int, int> levelEntrancesValues);
    void SetEntranceRandomizer(int enableEntranceRandomizer);
    void SetDeathLink(int deathLinkActive);
    void SendDeathLinkChance(int sendDeathLinkChance);
    void ReceiveDeathLinkChance(int receiveDeathLinkChance);
    void SetRingLink(int ringLinkActive);
    void SetCasinopolisRingLink(int casinopolisRingLink);
    void SetHardRingLink(int hardRingLinkActive);
    void SetTrapLink(int trapLinkActive);
    void SetRingLoss(int ringLoss);
    void TwinkleCircuitCheck(int twinkleCircuitCheck);
    void MultipleTwinkleCircuitChecks(int multipleTwinkleCircuitChecks);
    void SkyChaseChecks(int skyChaseChecks);
    void SkyChaseChecksHard(int skyChaseChecksHard);
    void BossChecks(int bossChecks);
    void UnifyChaos4(int unifyChaos4);
    void UnifyChaos6(int unifyChaos6);
    void UnifyEggHornet(int unifyEggHornet);
    void PlayableSonic(int playable);
    void PlayableTails(int playable);
    void PlayableKnuckles(int playable);
    void PlayableAmy(int playable);
    void PlayableGamma(int playable);
    void PlayableBig(int playable);
    void SonicActionStageMissions(int missions);
    void TailsActionStageMissions(int missions);
    void KnucklesActionStageMissions(int missions);
    void AmyActionStageMissions(int missions);
    void GammaActionStageMissions(int missions);
    void BigActionStageMissions(int missions);
    void SetMusicSource(int musicSource);
    void SetMusicShuffle(int musicShuffle);
    void SetMusicShuffleConsistency(int musicShuffleConsistency);
    void SetMusicShuffleSeed(int musicShuffleSeed);
    void SetLifeCapsulesChangeSongs(int lifeCapsulesChangeSongs);
    void SetIceTrapWeight(int iceTrapWeight);
    void SetSpringTrapWeight(int springTrapWeight);
    void SetPoliceTrapWeight(int policeTrapWeight);
    void SetBuyonTrapWeight(int buyonTrapWeight);
    void SetReverseTrapWeight(int reverseTrapWeight);
    void SetGravityTrapWeight(int gravityTrapWeight);
    void ReverseControlTrapDuration(int reverseControlTrapDuration);
    void TrapsOnAdventureFields(int trapsOnAdventureFields);
    void TrapsOnBossFights(int trapsOnBossFights);
    void TrapsOnPerfectChaosFight(int trapsOnPerfectChaosFight);
    void SetServerConfiguration(const std::string& serverIp, const std::string& newPlayerName,
                                const std::string& serverPassword, DeathLinkOverride newDeathLinkOverride,
                                RingLinkOverride newRingLinkOverride, RingLossOverride newRingLossOverride,
                                TrapLinkOverride newTrapLinkOverride,
                                bool showChatMessages, bool showGoalReached,
                                bool showCountdowns, bool showPlayerConnections);

    std::string playerName;
    int instanceId = 0;
    int64_t baseId;
    DeathLinkOverride deathLinkOverride;
    RingLinkOverride ringLinkOverride;
    RingLossOverride ringLossOverride;
    TrapLinkOverride trapLinkOverride;
    Options& options;

private:
    void ManageMessages();
    void EnqueueMessage(AP_Message* msg);

    Randomizer& _randomizer;
    mutable std::string _configPath;
    ConnectionStatus _status = ReadyForConnection;


    std::string _serverIP;
    std::string _serverPassword;
    std::string _seedName;

    const float _suggestChangingConfigWaitTime = 2.5f;
    std::clock_t _connectedAt = -1;

    bool _showChatMessages = true;
    bool _showGoalReached = true;
    bool _showCountdowns = true;
    bool _showPlayerConnections = false;
};
