﻿#pragma once

struct Options
{
    int emblemGoal;
    // bool fieldEmblems = true;
    // bool lifeSanity = false;
    // bool pinballCapsules = false;
    // bool subLevelChecks = false;

    bool randomizeSonicUpgrades = true;
    bool randomizeTailsUpgrades = true;
    bool randomizeKnucklesUpgrades = true;
    bool randomizeAmyUpgrades = true;
    bool randomizeBigUpgrades = true;
    bool randomizeGammaUpgrades = true;

    int sonicMissions = 0;
    int tailsMissions = 0;
    int knucklesMissions = 0;
    int amyMissions = 0;
    int bigMissions = 0;
    int gammaMissions = 0;

    void SetMissions(const Characters character, int missions)
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


    void SetRandomizedUpgrades(const Characters character, const bool randomizeUpgrade)
    {
        switch (character)
        {
        case Characters_Sonic:
            this->randomizeSonicUpgrades = randomizeUpgrade;
            break;
        case Characters_Tails:
            this->randomizeTailsUpgrades = randomizeUpgrade;
            break;
        case Characters_Knuckles:
            this->randomizeKnucklesUpgrades = randomizeUpgrade;
            break;
        case Characters_Amy:
            this->randomizeAmyUpgrades = randomizeUpgrade;
            break;
        case Characters_Big:
            this->randomizeBigUpgrades = randomizeUpgrade;
            break;
        case Characters_Gamma:
            this->randomizeGammaUpgrades = randomizeUpgrade;
            break;
        case Characters_Eggman:
        case Characters_Tikal:
        case Characters_MetalSonic:
            break;
        }
    }
};