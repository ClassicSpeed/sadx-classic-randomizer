#pragma once
#include <chrono>

#include "../../pch.h"
#include "../../application/structs/LocationData.h"
#include "../../application/structs/ItemData.h"
#include <vector>

#include "../settings/Settings.h"

enum Goal
{
    GoalLevels,
    GoalEmblems,
    GoalEmeraldHunt,
    GoalLevelsAndEmeraldHunt,
    GoalEmblemsAndEmeraldHunt,
    GoalMissions,
    GoalMissionsAndEmeraldHunt,
    None
};

enum RingLoss
{
    Classic,
    Modern,
    OneHitKnockOut,
    OneHitKnockOutNoShields
};


enum EnemySanityCategory
{
    SonicEnemySanity = 0,
    TailsEnemySanity,
    KnucklesEnemySanity,
    AmyEnemySanity,
    BigEnemySanity,
    GammaEnemySanity
};

enum CapsuleSanityCategory
{
    SonicLife = 0,
    SonicShield,
    SonicPowerUp,
    SonicRing,
    TailsLife,
    TailsShield,
    TailsPowerUp,
    TailsRing,
    KnucklesLife,
    KnucklesShield,
    KnucklesPowerUp,
    KnucklesRing,
    AmyLife,
    AmyShield,
    AmyPowerUp,
    AmyRing,
    BigLife,
    BigShield,
    BigPowerUp,
    BigRing,
    GammaLife,
    GammaShield,
    GammaPowerUp,
    GammaRing,
};


enum StartingArea
{
    CityHall = 0,
    Station,
    Casino,
    Sewers,
    SSMain,
    TPTunnel,
    Hotel,
    HotelPool,
    TPLobby,
    MRMain,
    AngelIsland,
    IceCave,
    PastAltar,
    PastMain,
    Jungle,
    FinalEggTower,
    ECOutside,
    ECBridge,
    ECDeck,
    CaptainRoom,
    PrivateRoom,
    ECPool,
    Arsenal,
    ECInside,
    HedgehogHammer,
    PrisonHall,
    WaterTank,
    WarpHall,
    SSChaoGarden,
    MRChaoGarden,
    ECChaoGarden,
    NoStatingArea
};

enum GatingMode
{
    EmblemGating = 0,
    KeyItemGating,
    NoGating
};


enum EntranceId
{
    // City Hall
    CityHallToSsMain = 0,
    CityHallToSewers,
    CityHallToSpeedHighway,
    CityHallToChaos0,

    // Station
    StationToSsMain,
    StationToMrMain,
    StationToCasino,

    //Casino
    CasinoToStation,
    CasinoToCasinopolis,
    CasinoToHotel,
    CasinoToEggWalker,

    // Sewers
    SewersToCityHall,
    SewersToTwinkleParkTunnel,

    // SSMain
    SsMainToHotel,
    SsMainToStation,
    SsMainToCityHall,
    SsMainToTwinkleParkTunnel,
    SsMainToEcOutside,
    SsMainToBridge,
    SsMainToSpeedHighway,

    // Hotel
    HotelToSsMain,
    HotelToCasino,
    HotelToSsChaoGarden,
    HotelToChaos2,
    HotelToHotelPool,

    // Hotel Pool
    HotelPoolToHotel,
    HotelPoolToEmeraldCoast,

    // Twinkle Park Tunnel
    TwinkleParkTunnelToSsMain,
    TwinkleParkTunnelToTwinkleParkLobby,
    TwinkleParkTunnelToSewers,

    // Twinkle Park Lobby
    TwinkleParkLobbyToTwinkleParkTunnel,
    TwinkleParkLobbyToTwinklePark,
    TwinkleParkLobbyToTwinkleCircuit,

    // MRMain
    MrMainToStation,
    MrMainToEcOutside,
    MrMainToBridge,
    MrMainToAngelIsland,
    MrMainToWindyValley,
    MrMainToJungle,
    MrMainToChaos4,
    MrMainToEggHornet,
    MrMainToMrChaoGarden,
    MrMainToSkyChase1,

    // Angel Island
    AngelIslandToMrMain,
    AngelIslandToIceCave,
    AngelIslandToRedMountain,
    AngelIslandToPastAltar,

    // Ice Cave
    IceCaveToAngelIsland,
    IceCaveToIceCap,

    // Past Altar
    PastAltarToAngelIsland,
    PastAltarToPastMain,

    // Past Main
    PastMainToPastAltar,
    PastMainToJungle,

    // Jungle
    JungleToMrMain,
    JungleToLostWorld,
    JungleToLostWorldAlternative,
    JungleToFinalEggTower,
    JungleToSandHill,
    JungleToPastMain,

    // Final Egg Tower
    FinalEggTowerToJungle,
    FinalEggTowerToFinalEgg,
    FinalEggTowerToFinalEggAlternative,
    FinalEggTowerToBetaEggViper,
    FinalEggTowerToEcInside,


    // Egg Carrier Outside (Untransformed)
    EcOutsideToSsMain,
    EcOutsideToMrMain,
    EcOutsideToSkyChase2,
    EcOutsideToChaos6ZeroBeta,
    EcOutsideToEcInsideMonorail,
    EcOutsideToEcInsideEggLift,
    EcOutsideToCaptainRoom,
    EcOutsideToPool,

    // Bridge (Transformed) 
    BridgeToSsMain,
    BridgeToMrMain,
    BridgeToSkyDeck,
    BridgeToSkyChase2,
    BridgeToChaos6ZeroBeta,
    BridgeToEcInsideMonorail,

    // Deck (Transformed) 
    DeckToPool,
    DeckToCaptainRoom,
    DeckToPrivateRoom,
    DeckToPrivateRoomAlternative,
    DeckToEcInsideEggLift,

    // Captain Room
    CaptainRoomToEcOutside,
    CaptainRoomToDeck,
    CaptainRoomToPrivateRoom,

    // Private Room
    PrivateRoomToCaptainRoom,
    PrivateRoomToDeck,
    PrivateRoomToDeckAlternative,

    // Pool
    PoolToEcOutside,
    PoolToDeck,
    PoolToSkyDeck,

    // Arsenal
    ArsenalToEcInside,

    // Egg Carrier Inside
    EcInsideToEcOutsideEggLift,
    EcInsideToEcOutsideMonorail,
    EcInsideToDeckEggLift,
    EcInsideToBridgeMonorail,
    EcInsideToHotShelter,
    EcInsideToHedgehogHammer,
    EcInsideToFinalEggTower,
    EcInsideToWarpHall,
    EcInsideToArsenal,
    EcInsideToWaterTank,

    // Hedgehog Hammer
    HedgehogHammerToEcInside,
    HedgehogHammerToPrisonHall,

    // Prison Hall
    PrisonHallToHedgehogHammer,

    // Water Tank
    WaterTankToEcInside,

    // Warp Hall
    WarpHallToEcInside,
    WarpHallToEcChaoGarden,

    // SS Chao Garden
    SsChaoGardenToHotel,

    // Mr Chao Garden
    MrChaoGardenToMrMain,

    // Ec Chao Garden
    EcChaoGardenToWarpHall,


    // Levels
    SpeedHighwayToCityHall,
    Chaos0ToCityHall,
    CasinopolisToCasino,
    EggWalkerToCasino,
    SpeedHighwayToSsMain,
    EmeraldCoastToHotelPool,
    Chaos2ToHotel,
    TwinkleParkToTwinkleParkLobby,
    TwinkleCircuitToTwinkleParkLobby,
    WindyValleyToMrMain,
    Chaos4ToMrMain,
    EggHornetToMrMain,
    SkyChase1ToMrMain,
    IceCapToIceCave,
    RedMountainToAngelIsland,
    LostWorldToJungle,
    LostWorldToJungleAlternative,
    SandHillToJungle,
    FinalEggToFinalEggTower,
    FinalEggToFinalEggTowerAlternative,
    BetaEggViperToFinalEggTower,
    SkyChase2ToEcOutside,
    SkyChase2ToBridge,
    Chaos6ZeroBetaToEcOutside,
    Chaos6ZeroBetaToBridge,
    SkyDeckToBridge,
    SkyDeckToPool,
    HotShelterToEcInside,

    InvalidEntranceId
};


static int Clamp(const int value, const int min, const int max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

class Options
{
public:
    static Options& Init(Settings& settings)
    {
        if (_instance == nullptr)
            _instance = new Options(settings);
        return *_instance;
    }


    void GoalRequiresLevels(int newGoalRequiresLevels);
    void GoalRequiresChaosEmeralds(int newGoalRequiresChaosEmeralds);
    void GoalRequiresEmblems(int newGoalRequiresEmblems);
    void GoalRequiresMissions(int newGoalRequiresMissions);
    void GoalRequiresBosses(int newGoalRequiresBosses);
    void GoalRequiresChaoRaces(int newGoalRequiresChaoRaces);
    void LogicLevel(int logicLevel);
    void SetGatingMode(int gatingMode);
    void EmblemsForPerfectChaos(int newEmblemGoal);
    void LevelForPerfectChaos(int newLevelGoal);
    void MissionForPerfectChaos(int newMissionGoal);
    void BossesForPerfectChaos(int newBossesGoal);
    void MissionModeChecks(int newMissionModeEnabled);
    void MissionBlackList(const std::map<int, int>& newMissionBlacklist);
    void AutoStartMissions(int newAutoStartMissions);
    void EnemySanity(int newEnemySanity);
    void EnemySanityList(const std::map<int, int>& newEnemySanityList);
    void MissableEnemies(int newMissableEnemies);
    void CapsuleSanity(int newCapsuleSanity);
    void CapsuleSanityList(const std::map<int, int>& newCapsuleSanityList);
    void MissableCapsules(int newMissableCapsules);
    void PinballCapsules(int newIncludePinballCapsules);
    void FishSanity(int newFishSanity);
    void LazyFishing(int newLazyFishing);
    void ProgressionItems(const std::map<int, int>& newProgressionItems);
    void StartingCharacter(int newStartingCharacterIndex);
    void LevelEntranceMap(const std::map<int, int>& levelEntrancesValues);
    void SetEntranceRandomizer(int enableEntranceRandomizer);
    void SetDeathLink(int newDeathLinkActive);
    void SendDeathLinkChance(int newSendDeathLinkChance);
    void ReceiveDeathLinkChance(int newReceiveDeathLinkChance);
    void SetRingLink(int newRingLinkActive);
    void SetCasinopolisRingLink(int newCasinopolisRingLink);
    void SetHardRingLink(int newHardRingLinkActive);
    void SetTrapLink(int newTrapLinkActive);
    void SetRingLoss(int newRingLoss);
    void TwinkleCircuitCheck(int newTwinkleCircuitCheck);
    void MultipleTwinkleCircuitChecks(int newMultipleTwinkleCircuitChecks);
    void SkyChaseChecks(int newSkyChaseChecks);
    void SkyChaseChecksHard(int newSkyChaseChecksHard);
    void BossChecks(int newBossChecks);
    void UnifyChaos4(int newUnifyChaos4);
    void UnifyChaos6(int newUnifyChaos6);
    void UnifyEggHornet(int newUnifyEggHornet);
    void SetMusicSource(int newMusicSource);
    void SetMusicShuffle(int newMusicShuffle);
    void SetMusicShuffleConsistency(int newMusicShuffleConsistency);
    void SetMusicShuffleSeed(int newMusicShuffleSeed);
    void SetLifeCapsulesChangeSongs(int newLifeCapsulesChangeSongs);
    void SetIceTrapWeight(int newIceTrapWeight);
    void SetSpringTrapWeight(int newSpringTrapWeight);
    void SetPoliceTrapWeight(int newPoliceTrapWeight);
    void SetBuyonTrapWeight(int newBuyonTrapWeight);
    void SetReverseTrapWeight(int newReverseTrapWeight);
    void SetGravityTrapWeight(int newGravityTrapWeight);
    void SetReverseControlTrapDuration(int reverseControlTrapDuration);
    void SetTrapsOnAdventureFields(int newTrapsOnAdventureFields);
    void SetTrapsOnBossFights(int newTrapsOnBossFights);
    void SetTrapsOnPerfectChaosFight(int newTrapsOnPerfectChaosFight);


    void SetActionStageMissions(Characters character, int missions);
    bool GetCharacterEnemySanity(Characters character) const;
    bool GetCapsuleSanityByType(Characters character, CapsuleType capsuleType) const;
    void SetCharacterStatingArea(Characters character, int startingArea);
    StartingArea GetCharacterStartingArea(Characters character) const;
    void SetPlayableCharacter(Characters character, bool playable);
    bool GetPlayableCharacter(Characters character) const;
    bool LocationHasProgressiveItem(int locationId);
    bool MusicSourceIncludeSadx() const;
    bool MusicSourceIncludeSa2B() const;
    bool MusicSourceIncludeCustom() const;
    bool IsTrapEnabled(FillerType filler) const;
    void SetEntranceEmblemValueMap(const std::map<int, int>& map);


    //Constant values
    const int64_t baseId = 543800000;

    std::chrono::time_point<std::chrono::system_clock> timestamp = std::chrono::system_clock::now();
    const int instanceId = std::chrono::duration_cast<std::chrono::seconds>(timestamp.time_since_epoch()).count();

    // YAML Options
    bool goalRequiresLevels = true;
    bool goalRequiresEmblems = true;
    bool goalRequiresChaosEmeralds = true;
    bool goalRequiresMissions = true;
    bool goalRequiresBosses = true;
    bool goalRequiresChaoRaces = true;
    int emblemGoal = 999999;
    int levelGoal = 999999;
    int missionGoal = 999999;
    int bossesGoal = 999999;

    bool missionModeEnabled = false;
    bool autoStartMissions = false;
    bool entranceRandomizer = false;

    StartingArea sonicStartingArea = NoStatingArea;
    StartingArea tailsStartingArea = NoStatingArea;
    StartingArea knucklesStartingArea = NoStatingArea;
    StartingArea amyStartingArea = NoStatingArea;
    StartingArea bigStartingArea = NoStatingArea;
    StartingArea gammaStartingArea = NoStatingArea;

    bool enemySanity = false;
    std::vector<EnemySanityCategory> enemySanityList = {};
    bool missableEnemies = true;

    bool capsuleSanity = false;
    std::vector<CapsuleSanityCategory> capsuleSanityList = {};
    bool missableCapsules = true;
    bool includePinballCapsules = false;

    bool fishSanity = false;
    bool lazyFishing = false;

    std::vector<int64_t> progressionItems = {};
    int startingCharacterIndex = 1;
    std::map<int, int> levelEntrancesMap;

    bool deathLinkActive = false;
    int sendDeathLinkChance = 100;
    int receiveDeathLinkChance = 100;
    bool ringLinkActive = false;
    bool casinopolisRingLink = false;
    bool hardRingLinkActive = false;
    bool trapLinkActive = false;
    RingLoss ringLoss = Classic;

    bool bossChecks = false;
    bool unifyChaos4 = false;
    bool unifyChaos6 = false;
    bool unifyEggHornet = false;


    bool playableSonic = true;
    bool playableTails = true;
    bool playableKnuckles = true;
    bool playableAmy = true;
    bool playableBig = true;
    bool playableGamma = true;

    int sonicActionStageMissions = 0;
    int tailsActionStageMissions = 0;
    int knucklesActionStageMissions = 0;
    int amyActionStageMissions = 0;
    int bigActionStageMissions = 0;
    int gammaActionStageMissions = 0;

    int iceTrapWeight = 2;
    int springTrapWeight = 2;
    int policeTrapWeight = 2;
    int buyonTrapWeight = 2;
    int reverseTrapWeight = 2;
    int gravityTrapWeight = 2;


    float reverseControlsDuration = 7.0f;
    bool trapsOnAdventureFields = true;
    bool trapsOnBossFights = true;
    bool trapsOnPerfectChaosFight = false;

    MusicSource musicSource = MusicSourceNone;
    MusicShuffle musicShuffle = MusicShuffleNone;
    MusicShuffleConsistency musicShuffleConsistency = MusicShuffleConsistencyNone;
    LifeCapsulesChangeSongs lifeCapsulesChangeSongs = LifeCapsulesChangeSongsNone;
    int musicShuffleSeed = -1;

    int twinkleCircuitChecks = 1;
    int skyChaseChecks = 1;
    std::vector<int> missionBlacklist = {};
    bool expertMode = false;


    //TODO: Make this a value
    bool connectFinalEggToEggCarrier;

    //TODO: Change this
    bool emblemGating = true;
    GatingMode gatingMode = EmblemGating;
    std::map<int, int> entranceEmblemValueMap = {
    };

    AdventureFieldRandomization entranceRandomization = AdventureFieldRandomizationDisabled;
    std::map<EntranceId, EntranceId> entranceRandomizationMap;

private:
    explicit Options(Settings& settings);
    inline static Options* _instance = nullptr;
    Settings& _settings;
};
