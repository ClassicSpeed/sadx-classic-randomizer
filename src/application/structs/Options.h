#pragma once

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
    MysticRuinsMain,
    Jungle,
    EggCarrier,
    NoStatingArea
};

struct Options
{
    std::string playerName = "Player";
    int emblemGoal = -1;
    StartingArea startingArea = NoStatingArea;
    bool lifeSanity = false;

    bool sonicLifeSanity = true;
    bool tailsLifeSanity = true;
    bool knucklesLifeSanity = true;
    bool amyLifeSanity = true;
    bool bigLifeSanity = true;
    bool gammaLifeSanity = true;

    bool pinballCapsules = false;
    bool deathLinkActive = false;
    bool ringLinkActive = false;
    bool hardRingLinkActive = false;
    RingLoss ringLoss = Classic;

    bool bossChecks = false;
    bool unifyChaos4 = false;
    bool unifyChaos6 = false;
    bool unifyEggHornet = false;

    int sonicMissions = 0;
    int tailsMissions = 0;
    int knucklesMissions = 0;
    int amyMissions = 0;
    int bigMissions = 0;
    int gammaMissions = 0;

    void SetMissions(const Characters character, const int missions)
    {
        switch (character)
        {
        case Characters_Sonic:
            this->sonicMissions = missions;
            break;
        case Characters_Tails:
            this->tailsMissions = missions;
            break;
        case Characters_Knuckles:
            this->knucklesMissions = missions;
            break;
        case Characters_Amy:
            this->amyMissions = missions;
            break;
        case Characters_Big:
            this->bigMissions = missions;
            break;
        case Characters_Gamma:
            this->gammaMissions = missions;
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
};
