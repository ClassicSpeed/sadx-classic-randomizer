#pragma once

struct UnlockStatus
{
    int currentEmblems = 0;

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
    bool keyStationKey;
    bool keyShutterKey;
    bool keyHotelKey;
    bool keyCasinoKey;
    bool keyTwinkleParkTicket;
    bool keyEmployeeCard;
    bool keyDynamite;
    bool keyIceStone;
    bool keyWindStone;
    bool keyJungleCart;
    bool keyEgglift;
    bool keyMonorail;
    bool keyPoolKey;
    bool keyPolicePass;
    bool keyTimeMachine;

    bool GotAllChaosEmeralds() const
    {
        return whiteEmerald && redEmerald && cyanEmerald && purpleEmerald && greenEmerald && yellowEmerald &&
            blueEmerald;
    }

    int CountChaosEmeralds() const
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
