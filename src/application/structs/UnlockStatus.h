#pragma once

struct UnlockStatus
{
    int currentEmblems;

    bool whiteEmerald;
    bool redEmerald;
    bool cyanEmerald;
    bool purpleEmerald;
    bool greenEmerald;
    bool yellowEmerald;
    bool blueEmerald;

    bool sonicUnlocked;
    bool sonicLightShoesUnlocked;
    bool sonicCrystalRingUnlocked;
    bool sonicAncientLightUnlocked;

    bool tailsUnlocked;
    bool tailsJetAnkletUnlocked;
    bool tailsRhythmBadgeUnlocked;

    bool knucklesUnlocked;
    bool knucklesShovelClawUnlocked;
    bool knucklesFightingGlovesUnlocked;

    bool amyUnlocked;
    bool amyLongHammerUnlocked;
    bool amyWarriorFeatherUnlocked;

    bool gammaUnlocked;
    bool gammaLaserBlasterUnlocked;
    bool gammaJetBoosterUnlocked;

    bool bigUnlocked;
    bool bigLifeBeltUnlocked;
    bool bigPowerRodUnlocked;
    int bigLureQuantity = 0;

    bool keyTrain;
    bool keyBoat;
    bool keyRaft;
    bool keyStationKeys;
    bool keyHotelKeys;
    bool keyCasinoKeys;
    bool keyTwinkleParkTicket;
    bool keyEmployeeCard;
    bool keyDynamite;
    bool keyIceStone;
    bool keyWindStone;
    bool jungleCart;

    bool GotAllChaosEmeralds()
    {
        return whiteEmerald && redEmerald && cyanEmerald && purpleEmerald && greenEmerald && yellowEmerald && blueEmerald;
    }

    int CountChaosEmeralds()
    {
        int count = 0;
        count += whiteEmerald;
        count += redEmerald;
        count += cyanEmerald;
        count += purpleEmerald;
        count += greenEmerald;
        count += yellowEmerald;
        count += blueEmerald;
        return count;
    }
};
