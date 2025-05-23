﻿#pragma once
#include "LocationData.h"

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
    MusicSourceSadxCustom,
    MusicSourceSa2B,
    MusicSourceSa2BCustom,
    MusicSourceSadxSa2B,
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

struct Options
{
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

    void SetActionStageMissions(const Characters character, const int missions)
    {
        switch (character)
        {
        case Characters_Sonic:
            this->sonicActionStageMissions = missions;
            break;
        case Characters_Tails:
            this->tailsActionStageMissions = missions;
            break;
        case Characters_Knuckles:
            this->knucklesActionStageMissions = missions;
            break;
        case Characters_Amy:
            this->amyActionStageMissions = missions;
            break;
        case Characters_Big:
            this->bigActionStageMissions = missions;
            break;
        case Characters_Gamma:
            this->gammaActionStageMissions = missions;
            break;
        case Characters_Eggman:
        case Characters_Tikal:
        case Characters_MetalSonic:
            break;
        }
    }

    void SetCharacterEnemySanity(const Characters character, const bool characterEnemySanity)
    {
        switch (character)
        {
        case Characters_Sonic:
            this->sonicEnemySanity = characterEnemySanity;
            break;
        case Characters_Tails:
            this->tailsEnemySanity = characterEnemySanity;
            break;
        case Characters_Knuckles:
            this->knucklesEnemySanity = characterEnemySanity;
            break;
        case Characters_Amy:
            this->amyEnemySanity = characterEnemySanity;
            break;
        case Characters_Big:
            this->bigEnemySanity = characterEnemySanity;
            break;
        case Characters_Gamma:
            this->gammaEnemySanity = characterEnemySanity;
            break;
        case Characters_Eggman:
        case Characters_Tikal:
        case Characters_MetalSonic:
            break;
        }
    }

    bool GetCharacterEnemySanity(const Characters character) const
    {
        switch (character)
        {
        case Characters_Sonic:
            return this->sonicEnemySanity;
        case Characters_Tails:
            return this->tailsEnemySanity;
        case Characters_Knuckles:
            return this->knucklesEnemySanity;
        case Characters_Amy:
            return this->amyEnemySanity;
        case Characters_Big:
            return this->bigEnemySanity;
        case Characters_Gamma:
            return this->gammaEnemySanity;
        case Characters_Eggman:
        case Characters_Tikal:
        case Characters_MetalSonic:
            break;
        }
        return false;
    }

    void SetCharacterCapsuleSanity(const Characters character, const bool characterCapsuleSanity)
    {
        switch (character)
        {
        case Characters_Sonic:
            this->sonicCapsuleSanity = characterCapsuleSanity;
            break;
        case Characters_Tails:
            this->tailsCapsuleSanity = characterCapsuleSanity;
            break;
        case Characters_Knuckles:
            this->knucklesCapsuleSanity = characterCapsuleSanity;
            break;
        case Characters_Amy:
            this->amyCapsuleSanity = characterCapsuleSanity;
            break;
        case Characters_Big:
            this->bigCapsuleSanity = characterCapsuleSanity;
            break;
        case Characters_Gamma:
            this->gammaCapsuleSanity = characterCapsuleSanity;
            break;
        case Characters_Eggman:
        case Characters_Tikal:
        case Characters_MetalSonic:
            break;
        }
    }

    bool GetCharacterCapsuleSanity(const Characters character) const
    {
        switch (character)
        {
        case Characters_Sonic:
            return this->sonicCapsuleSanity;
        case Characters_Tails:
            return this->tailsCapsuleSanity;
        case Characters_Knuckles:
            return this->knucklesCapsuleSanity;
        case Characters_Amy:
            return this->amyCapsuleSanity;
        case Characters_Big:
            return this->bigCapsuleSanity;
        case Characters_Gamma:
            return this->gammaCapsuleSanity;
        case Characters_Eggman:
        case Characters_Tikal:
        case Characters_MetalSonic:
            break;
        }
        return false;
    }

    bool GetSpecificCapsuleSanity(const CapsuleType capsuleType) const
    {
        switch (capsuleType)
        {
        case ExtraLifeCapsule:
            return this->lifeCapsuleSanity;
        case ShieldCapsule:
        case MagneticShieldCapsule:
            return this->shieldCapsuleSanity;
        case SpeedUpCapsule:
        case InvincibilityCapsule:
        case BombCapsule:
            return this->powerUpCapsuleSanity;
        case FiveRingsCapsule:
        case TenRingsCapsule:
        case RandomRingsCapsule:
            return this->ringCapsuleSanity;
        }
        return false;
    }

    void SetCharacterStatingArea(const Characters character, const StartingArea startingArea)
    {
        switch (character)
        {
        case Characters_Sonic:
            this->sonicStartingArea = startingArea;
            break;
        case Characters_Tails:
            this->tailsStartingArea = startingArea;
            break;
        case Characters_Knuckles:
            this->knucklesStartingArea = startingArea;
            break;
        case Characters_Amy:
            this->amyStartingArea = startingArea;
            break;
        case Characters_Big:
            this->bigStartingArea = startingArea;
            break;
        case Characters_Gamma:
            this->gammaStartingArea = startingArea;
            break;
        case Characters_Eggman:
        case Characters_Tikal:
        case Characters_MetalSonic:
            break;
        }
    }

    StartingArea GetCharacterStartingArea(const Characters character) const
    {
        switch (character)
        {
        case Characters_Sonic:
            return this->sonicStartingArea;
        case Characters_Tails:
            return this->tailsStartingArea;
        case Characters_Knuckles:
            return this->knucklesStartingArea;
        case Characters_Amy:
            return this->amyStartingArea;
        case Characters_Big:
            return this->bigStartingArea;
        case Characters_Gamma:
            return this->gammaStartingArea;
        case Characters_Eggman:
        case Characters_Tikal:
        case Characters_MetalSonic:
            break;
        }
        return StationSquareMain;
    }

    void SetPlayableCharacter(const Characters character, const bool playable)
    {
        switch (character)
        {
        case Characters_Sonic:
            this->playableSonic = playable;
            break;
        case Characters_Tails:
            this->playableTails = playable;
            break;
        case Characters_Knuckles:
            this->playableKnuckles = playable;
            break;
        case Characters_Amy:
            this->playableAmy = playable;
            break;
        case Characters_Big:
            this->playableBig = playable;
            break;
        case Characters_Gamma:
            this->playableGamma = playable;
            break;
        case Characters_Eggman:
        case Characters_Tikal:
        case Characters_MetalSonic:
            break;
        }
    }

    bool GetPlayableCharacter(const Characters character) const
    {
        switch (character)
        {
        case Characters_Sonic:
            return this->playableSonic;
        case Characters_Tails:
            return this->playableTails;
        case Characters_Knuckles:
            return this->playableKnuckles;
        case Characters_Amy:
            return this->playableAmy;
        case Characters_Big:
            return this->playableBig;
        case Characters_Gamma:
            return this->playableGamma;
        case Characters_Eggman:
        case Characters_Tikal:
        case Characters_MetalSonic:
            break;
        }
        return false;
    }

    bool LocationHasProgressiveItem(int locationId)
    {
        return std::find(progressionItems.begin(), progressionItems.end(), locationId) != progressionItems.end();
    }

    bool MusicSourceIncludeSadx() const
    {
        return this->musicSource == MusicSourceSadx || this->musicSource == MusicSourceSadxCustom || this->musicSource
            == MusicSourceSadxSa2B ||
            this->musicSource == MusicSourceSadxSa2BCustom;
    }

    bool MusicSourceIncludeSa2B() const
    {
        return this->musicSource == MusicSourceSa2B || this->musicSource == MusicSourceSa2BCustom || this->musicSource
            == MusicSourceSadxSa2B ||
            this->musicSource == MusicSourceSadxSa2BCustom;
    }

    bool MusicSourceIncludeCustom() const
    {
        return this->musicSource == MusicSourceSadxCustom || this->musicSource == MusicSourceSa2BCustom || this->
            musicSource == MusicSourceSadxSa2BCustom;
    }
};
