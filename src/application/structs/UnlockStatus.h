#pragma once

struct UnlockStatus
{
    int currentEmblems;
    // int emblemGoal;

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
    bool bigLifeRingUnlocked;
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
};
