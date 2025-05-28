#pragma once
#include "../pch.h"
#include "../application/structs/LocationData.h"
#include "../application/structs/ItemData.h"
#include <string>
#include <vector>

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

enum StartingArea
{
    StationSquareMain,
    Station,
    HotelArea,
    CasinoArea,
    TwinkleParkArea,
    MysticRuinsMain,
    AngelIsland,
    Jungle,
    EggCarrierOutside,
    EggCarrierInside,
    EggCarrierFrontDeck,
    NoStatingArea
};

enum Levels
{
    EmeraldCoast = 11,
    WindyValley,
    Casinopolis,
    IceCap,
    TwinklePark,
    SpeedHighway,
    RedMountain,
    SkyDeck,
    LostWorld,
    FinalEgg,
    HotShelter
};

enum ShowSongName
{
    ShowSongNameWithSongShuffle = 0,
    ShowSongNameAlwaysOn,
    ShowSongNameAlwaysOff
};

enum ShowSongNameForType
{
    ShowSongNameForTypeEverything,
    ShowSongNameForTypeEverythingButJingles,
    ShowSongNameForTypeOnlyActionLevels
};


enum MusicSource
{
    MusicSourceNone = -1,
    MusicSourceSadx = 0,
    MusicSourceSa2B,
    MusicSourceCustom,
    MusicSourceSadxSa2B,
    MusicSourceSadxCustom,
    MusicSourceSa2BCustom,
    MusicSourceSadxSa2BCustom
};

enum MusicShuffle
{
    MusicShuffleNone = -1,
    MusicShuffleDisabled = 0,
    MusicShuffleCurated,
    MusicShuffleByType,
    MusicShuffleFull,
    MusicShuffleSingularity,
};

enum MusicShuffleConsistency
{
    MusicShuffleConsistencyNone = -1,
    MusicShuffleConsistencyStatic = 0,
    MusicShuffleConsistencyOnRestart,
    MusicShuffleConsistencyPerPlay,
};


enum LifeCapsulesChangeSongs
{
    LifeCapsulesChangeSongsNone = -1,
    LifeCapsulesChangeSongsEnabled = 0,
    LifeCapsulesChangeSongsDisabled = 1,
};

class Options
{
public:
    void SetActionStageMissions(Characters character, int missions);
    void SetCharacterEnemySanity(Characters character, bool characterEnemySanity);
    bool GetCharacterEnemySanity(Characters character) const;
    void SetCharacterCapsuleSanity(Characters character, bool characterCapsuleSanity);
    bool GetCharacterCapsuleSanity(Characters character) const;
    bool GetSpecificCapsuleSanity(CapsuleType capsuleType) const;
    void SetCharacterStatingArea(Characters character, StartingArea startingArea);
    StartingArea GetCharacterStartingArea(Characters character) const;
    void SetPlayableCharacter(Characters character, bool playable);
    bool GetPlayableCharacter(Characters character) const;
    bool LocationHasProgressiveItem(int locationId);
    bool MusicSourceIncludeSadx() const;
    bool MusicSourceIncludeSa2B() const;
    bool MusicSourceIncludeCustom() const;
    bool IsTrapEnabled(FillerType filler);


    std::string playerName = "Player";
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
    bool entranceRandomizer = false;

    StartingArea sonicStartingArea = NoStatingArea;
    StartingArea tailsStartingArea = NoStatingArea;
    StartingArea knucklesStartingArea = NoStatingArea;
    StartingArea amyStartingArea = NoStatingArea;
    StartingArea bigStartingArea = NoStatingArea;
    StartingArea gammaStartingArea = NoStatingArea;

    bool enemySanity = false;

    bool sonicEnemySanity = true;
    bool tailsEnemySanity = true;
    bool knucklesEnemySanity = true;
    bool amyEnemySanity = true;
    bool bigEnemySanity = true;
    bool gammaEnemySanity = true;

    bool capsuleSanity = false;
    bool includePinballCapsules = false;

    bool fishSanity = false;
    bool lazyFishing = false;

    bool sonicCapsuleSanity = true;
    bool tailsCapsuleSanity = true;
    bool knucklesCapsuleSanity = true;
    bool amyCapsuleSanity = true;
    bool bigCapsuleSanity = true;
    bool gammaCapsuleSanity = true;

    bool lifeCapsuleSanity = true;
    bool shieldCapsuleSanity = true;
    bool powerUpCapsuleSanity = true;
    bool ringCapsuleSanity = true;

    std::vector<int> progressionItems = {};

    bool deathLinkActive = false;
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

    std::string sa2BAdxPath = "../../../../Sonic Adventure 2/resource/gd_PC/ADX/";
    std::string customAdxPath = "custom/";
    ShowSongName showSongName = ShowSongNameWithSongShuffle;
    ShowSongNameForType showSongNameForType = ShowSongNameForTypeEverything;
    bool includeVanillaSongs = true;
    bool showWarningForMissingFiles = false;

    MusicSource musicSource = MusicSourceNone;
    MusicShuffle musicShuffle = MusicShuffleNone;
    MusicShuffleConsistency musicShuffleConsistency = MusicShuffleConsistencyNone;
    LifeCapsulesChangeSongs lifeCapsulesChangeSongs = LifeCapsulesChangeSongsNone;
    int musicShuffleSeed = -1;

    bool twinkleCircuitCheck = true;
    bool multipleTwinkleCircuitChecks = true;

    bool skyChaseChecks = false;
    bool skyChaseChecksHard = false;
    std::vector<int> missionBlacklist = {};
    bool expertMode = false;

};
