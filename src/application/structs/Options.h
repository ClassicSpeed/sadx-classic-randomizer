﻿#pragma once

enum RingLoss
{
    Classic,
    Modern,
    OneHitKnockOut
};

enum StartingArea
{
    StationSquareMain,
    HotelArea,
    CasinoArea,
    MysticRuinsMain,
    Jungle,
    EggCarrier,
    None
};

struct Options
{
    int emblemGoal = -1;
    StartingArea startingArea = None;
    // bool fieldEmblems = true;
    // bool lifeSanity = false;
    // bool pinballCapsules = false;
    // bool subLevelChecks = false;
    bool deathLinkActive = false;
    bool ringLinkActive = false;
    RingLoss ringLoss = Classic;

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
};
