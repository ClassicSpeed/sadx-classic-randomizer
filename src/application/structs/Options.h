#pragma once

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
    OneHitKnockOut
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
    EggCarrier,
    NoStatingArea
};

enum Levels
{
    EmeraldCoast = 9,
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

struct Options
{
    std::string playerName = "Player";
    bool goalRequiresLevels = true;
    bool goalRequiresEmblems = false;
    bool goalRequiresChaosEmeralds = false;
    bool goalRequiresMissions = false;
    int emblemGoal = -1;
    int levelGoal = -1;
    int missionGoal = -1;
    bool missionModeEnabled = false;
    
    bool entranceRandomizer = false;


    StartingArea sonicStartingArea = NoStatingArea;
    StartingArea tailsStartingArea = NoStatingArea;
    StartingArea knucklesStartingArea = NoStatingArea;
    StartingArea amyStartingArea = NoStatingArea;
    StartingArea bigStartingArea = NoStatingArea;
    StartingArea gammaStartingArea = NoStatingArea;

    bool lifeSanity = false;
    bool sonicLifeSanity = true;
    bool tailsLifeSanity = true;
    bool knucklesLifeSanity = true;
    bool amyLifeSanity = true;
    bool bigLifeSanity = true;
    bool gammaLifeSanity = true;

    bool includePinballCapsules = false;
    bool deathLinkActive = false;
    bool ringLinkActive = false;
    bool casinopolisRingLink = false;
    bool hardRingLinkActive = false;
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

    bool skyChaseChecks = false;
    std::vector<int> missionBlacklist = {};

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

    void SetCharacterLifeSanity(const Characters character, const bool characterLifeSanity)
    {
        switch (character)
        {
        case Characters_Sonic:
            this->sonicLifeSanity = characterLifeSanity;
            break;
        case Characters_Tails:
            this->tailsLifeSanity = characterLifeSanity;
            break;
        case Characters_Knuckles:
            this->knucklesLifeSanity = characterLifeSanity;
            break;
        case Characters_Amy:
            this->amyLifeSanity = characterLifeSanity;
            break;
        case Characters_Big:
            this->bigLifeSanity = characterLifeSanity;
            break;
        case Characters_Gamma:
            this->gammaLifeSanity = characterLifeSanity;
            break;
        case Characters_Eggman:
        case Characters_Tikal:
        case Characters_MetalSonic:
            break;
        }
    }

    bool GetCharacterLifeSanity(const Characters character) const
    {
        switch (character)
        {
        case Characters_Sonic:
            return this->sonicLifeSanity;
        case Characters_Tails:
            return this->tailsLifeSanity;
        case Characters_Knuckles:
            return this->knucklesLifeSanity;
        case Characters_Amy:
            return this->amyLifeSanity;
        case Characters_Big:
            return this->bigLifeSanity;
        case Characters_Gamma:
            return this->gammaLifeSanity;
        case Characters_Eggman:
        case Characters_Tikal:
        case Characters_MetalSonic:
            break;
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

};
