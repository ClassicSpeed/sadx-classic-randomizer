#include "LocationRepository.h"

#include "../../application/structs/MissionStatus.h"


LocationRepository::LocationRepository()
{
    _checkData = {
        {100, LocationData::UpgradeLocation(FLAG_SONIC_SS_LIGHTSHOOSE, "Light Shoes Upgrade (Sonic)", 10)},
        {101, LocationData::UpgradeLocation(FLAG_SONIC_SS_CRYSTALRING, "Crystal Ring Upgrade (Sonic)", 11)},
        {102, LocationData::UpgradeLocation(FLAG_SONIC_MR_ANCIENT_LIGHT, "Ancient Light Upgrade (Sonic)", 12)},

        {200, LocationData::UpgradeLocation(FLAG_MILES_SS_JETANKLET, "Jet Ankle Upgrade (Tails)", 20)},
        {201, LocationData::UpgradeLocation(FLAG_MILES_MR_RHYTHMBROOCH, "Rhythm Badge Upgrade (Tails)", 21)},

        {300, LocationData::UpgradeLocation(FLAG_KNUCKLES_MR_SHOVELCLAW, "Shovel Claw Upgrade (Knuckles)", 30)},
        {301, LocationData::UpgradeLocation(FLAG_KNUCKLES_MR_FIGHTINGGROVE, "Fighting Gloves Upgrade (Knuckles)", 31)},

        {400, LocationData::UpgradeLocation(FLAG_AMY_MR_FIGHTERSFEATHER, "Warrior Feather Upgrade (Amy)", 40)},
        {401, LocationData::UpgradeLocation(FLAG_AMY_EC_LONGHAMMER, "Long Hammer Upgrade (Amy)", 41)},

        {500, LocationData::UpgradeLocation(FLAG_E102_EC_BOOSTER, "Jet Booster Upgrade (Gamma)", 50)},
        {501, LocationData::UpgradeLocation(FLAG_E102_EC_TYPE3LASER, "Laser Blaster Upgrade (Gamma)", 51)},

        {600, LocationData::UpgradeLocation(FLAG_BIG_MR_LIFEBELT, "Life Belt Upgrade (Big)", 60)},
        {601, LocationData::UpgradeLocation(FLAG_BIG_MR_POWERROD, "Power Rod Upgrade (Big)", 61)},

        {602, LocationData::UpgradeLocation(FLAG_BIG_RUAR_NORMAL, "Lure 1 Upgrade (Big)", -1)},
        {603, LocationData::UpgradeLocation(FLAG_BIG_RUAR_RED, "Lure 2 Upgrade (Big)", -1)},
        {604, LocationData::UpgradeLocation(FLAG_BIG_RUAR_GOLD, "Lure 3 Upgrade (Big)", -1)},
        {605, LocationData::UpgradeLocation(FLAG_BIG_RUAR_BLUE, "Lure 4 Upgrade (Big)", -1)},

        //Level id: ABXX where A is the character, B is the level in the story order, and XX is the check in that level 

        //Sonic's Levels
        {1000, LocationData::LevelLocation(Characters_Sonic, LevelIDs_EmeraldCoast, MISSION_A)},
        {1001, LocationData::LevelLocation(Characters_Sonic, LevelIDs_EmeraldCoast, MISSION_B)},
        {1002, LocationData::LevelLocation(Characters_Sonic, LevelIDs_EmeraldCoast, MISSION_C)},
        {1100, LocationData::LevelLocation(Characters_Sonic, LevelIDs_WindyValley, MISSION_A)},
        {1101, LocationData::LevelLocation(Characters_Sonic, LevelIDs_WindyValley, MISSION_B)},
        {1102, LocationData::LevelLocation(Characters_Sonic, LevelIDs_WindyValley, MISSION_C)},
        {1200, LocationData::LevelLocation(Characters_Sonic, LevelIDs_Casinopolis, MISSION_A)},
        {1201, LocationData::LevelLocation(Characters_Sonic, LevelIDs_Casinopolis, MISSION_B)},
        {1202, LocationData::LevelLocation(Characters_Sonic, LevelIDs_Casinopolis, MISSION_C)},
        {1300, LocationData::LevelLocation(Characters_Sonic, LevelIDs_IceCap, MISSION_A)},
        {1301, LocationData::LevelLocation(Characters_Sonic, LevelIDs_IceCap, MISSION_B)},
        {1302, LocationData::LevelLocation(Characters_Sonic, LevelIDs_IceCap, MISSION_C)},
        {1400, LocationData::LevelLocation(Characters_Sonic, LevelIDs_TwinklePark, MISSION_A)},
        {1401, LocationData::LevelLocation(Characters_Sonic, LevelIDs_TwinklePark, MISSION_B)},
        {1402, LocationData::LevelLocation(Characters_Sonic, LevelIDs_TwinklePark, MISSION_C)},
        {1500, LocationData::LevelLocation(Characters_Sonic, LevelIDs_SpeedHighway, MISSION_A)},
        {1501, LocationData::LevelLocation(Characters_Sonic, LevelIDs_SpeedHighway, MISSION_B)},
        {1502, LocationData::LevelLocation(Characters_Sonic, LevelIDs_SpeedHighway, MISSION_C)},
        {1600, LocationData::LevelLocation(Characters_Sonic, LevelIDs_RedMountain, MISSION_A)},
        {1601, LocationData::LevelLocation(Characters_Sonic, LevelIDs_RedMountain, MISSION_B)},
        {1602, LocationData::LevelLocation(Characters_Sonic, LevelIDs_RedMountain, MISSION_C)},
        {1700, LocationData::LevelLocation(Characters_Sonic, LevelIDs_SkyDeck, MISSION_A)},
        {1701, LocationData::LevelLocation(Characters_Sonic, LevelIDs_SkyDeck, MISSION_B)},
        {1702, LocationData::LevelLocation(Characters_Sonic, LevelIDs_SkyDeck, MISSION_C)},
        {1800, LocationData::LevelLocation(Characters_Sonic, LevelIDs_LostWorld, MISSION_A)},
        {1801, LocationData::LevelLocation(Characters_Sonic, LevelIDs_LostWorld, MISSION_B)},
        {1802, LocationData::LevelLocation(Characters_Sonic, LevelIDs_LostWorld, MISSION_C)},
        {1900, LocationData::LevelLocation(Characters_Sonic, LevelIDs_FinalEgg, MISSION_A)},
        {1901, LocationData::LevelLocation(Characters_Sonic, LevelIDs_FinalEgg, MISSION_B)},
        {1902, LocationData::LevelLocation(Characters_Sonic, LevelIDs_FinalEgg, MISSION_C)},
        //Tails' Levels
        {2000, LocationData::LevelLocation(Characters_Tails, LevelIDs_WindyValley, MISSION_A)},
        {2001, LocationData::LevelLocation(Characters_Tails, LevelIDs_WindyValley, MISSION_B)},
        {2002, LocationData::LevelLocation(Characters_Tails, LevelIDs_WindyValley, MISSION_C)},
        {2100, LocationData::LevelLocation(Characters_Tails, LevelIDs_Casinopolis, MISSION_A)},
        {2101, LocationData::LevelLocation(Characters_Tails, LevelIDs_Casinopolis, MISSION_B)},
        {2102, LocationData::LevelLocation(Characters_Tails, LevelIDs_Casinopolis, MISSION_C)},
        {2200, LocationData::LevelLocation(Characters_Tails, LevelIDs_IceCap, MISSION_A)},
        {2201, LocationData::LevelLocation(Characters_Tails, LevelIDs_IceCap, MISSION_B)},
        {2202, LocationData::LevelLocation(Characters_Tails, LevelIDs_IceCap, MISSION_C)},
        {2300, LocationData::LevelLocation(Characters_Tails, LevelIDs_SkyDeck, MISSION_A)},
        {2301, LocationData::LevelLocation(Characters_Tails, LevelIDs_SkyDeck, MISSION_B)},
        {2302, LocationData::LevelLocation(Characters_Tails, LevelIDs_SkyDeck, MISSION_C)},
        {2400, LocationData::LevelLocation(Characters_Tails, LevelIDs_SpeedHighway, MISSION_A)},
        {2401, LocationData::LevelLocation(Characters_Tails, LevelIDs_SpeedHighway, MISSION_B)},
        {2402, LocationData::LevelLocation(Characters_Tails, LevelIDs_SpeedHighway, MISSION_C)},
        //Knuckles' levels
        {3000, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_SpeedHighway, MISSION_A)},
        {3001, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_SpeedHighway, MISSION_B)},
        {3002, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_SpeedHighway, MISSION_C)},
        {3100, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_Casinopolis, MISSION_A)},
        {3101, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_Casinopolis, MISSION_B)},
        {3102, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_Casinopolis, MISSION_C)},
        {3200, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_RedMountain, MISSION_A)},
        {3201, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_RedMountain, MISSION_B)},
        {3202, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_RedMountain, MISSION_C)},
        {3300, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_LostWorld, MISSION_A)},
        {3301, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_LostWorld, MISSION_B)},
        {3302, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_LostWorld, MISSION_C)},
        {3400, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_SkyDeck, MISSION_A)},
        {3401, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_SkyDeck, MISSION_B)},
        {3402, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_SkyDeck, MISSION_C)},
        //Amy's levels
        {4000, LocationData::LevelLocation(Characters_Amy, LevelIDs_TwinklePark, MISSION_A)},
        {4001, LocationData::LevelLocation(Characters_Amy, LevelIDs_TwinklePark, MISSION_B)},
        {4002, LocationData::LevelLocation(Characters_Amy, LevelIDs_TwinklePark, MISSION_C)},
        {4100, LocationData::LevelLocation(Characters_Amy, LevelIDs_HotShelter, MISSION_A)},
        {4101, LocationData::LevelLocation(Characters_Amy, LevelIDs_HotShelter, MISSION_B)},
        {4102, LocationData::LevelLocation(Characters_Amy, LevelIDs_HotShelter, MISSION_C)},
        {4200, LocationData::LevelLocation(Characters_Amy, LevelIDs_FinalEgg, MISSION_A)},
        {4201, LocationData::LevelLocation(Characters_Amy, LevelIDs_FinalEgg, MISSION_B)},
        {4202, LocationData::LevelLocation(Characters_Amy, LevelIDs_FinalEgg, MISSION_C)},
        //Gamma's levels
        {5000, LocationData::LevelLocation(Characters_Gamma, LevelIDs_FinalEgg, MISSION_A)},
        {5001, LocationData::LevelLocation(Characters_Gamma, LevelIDs_FinalEgg, MISSION_B)},
        {5002, LocationData::LevelLocation(Characters_Gamma, LevelIDs_FinalEgg, MISSION_C)},
        {5100, LocationData::LevelLocation(Characters_Gamma, LevelIDs_EmeraldCoast, MISSION_A)},
        {5101, LocationData::LevelLocation(Characters_Gamma, LevelIDs_EmeraldCoast, MISSION_B)},
        {5102, LocationData::LevelLocation(Characters_Gamma, LevelIDs_EmeraldCoast, MISSION_C)},
        {5200, LocationData::LevelLocation(Characters_Gamma, LevelIDs_WindyValley, MISSION_A)},
        {5201, LocationData::LevelLocation(Characters_Gamma, LevelIDs_WindyValley, MISSION_B)},
        {5202, LocationData::LevelLocation(Characters_Gamma, LevelIDs_WindyValley, MISSION_C)},
        {5300, LocationData::LevelLocation(Characters_Gamma, LevelIDs_RedMountain, MISSION_A)},
        {5301, LocationData::LevelLocation(Characters_Gamma, LevelIDs_RedMountain, MISSION_B)},
        {5302, LocationData::LevelLocation(Characters_Gamma, LevelIDs_RedMountain, MISSION_C)},
        {5400, LocationData::LevelLocation(Characters_Gamma, LevelIDs_HotShelter, MISSION_A)},
        {5401, LocationData::LevelLocation(Characters_Gamma, LevelIDs_HotShelter, MISSION_B)},
        {5402, LocationData::LevelLocation(Characters_Gamma, LevelIDs_HotShelter, MISSION_C)},
        //Big's levels
        {6000, LocationData::LevelLocation(Characters_Big, LevelIDs_TwinklePark, MISSION_A)},
        {6001, LocationData::LevelLocation(Characters_Big, LevelIDs_TwinklePark, MISSION_B)},
        {6002, LocationData::LevelLocation(Characters_Big, LevelIDs_TwinklePark, MISSION_C)},
        {6100, LocationData::LevelLocation(Characters_Big, LevelIDs_IceCap, MISSION_A)},
        {6101, LocationData::LevelLocation(Characters_Big, LevelIDs_IceCap, MISSION_B)},
        {6102, LocationData::LevelLocation(Characters_Big, LevelIDs_IceCap, MISSION_C)},
        {6200, LocationData::LevelLocation(Characters_Big, LevelIDs_EmeraldCoast, MISSION_A)},
        {6201, LocationData::LevelLocation(Characters_Big, LevelIDs_EmeraldCoast, MISSION_B)},
        {6202, LocationData::LevelLocation(Characters_Big, LevelIDs_EmeraldCoast, MISSION_C)},
        {6300, LocationData::LevelLocation(Characters_Big, LevelIDs_HotShelter, MISSION_A)},
        {6301, LocationData::LevelLocation(Characters_Big, LevelIDs_HotShelter, MISSION_B)},
        {6302, LocationData::LevelLocation(Characters_Big, LevelIDs_HotShelter, MISSION_C)},

        //Sub levels
        {15, LocationData::SubLevelLocation(LevelIDs_TwinkleCircuit, MISSION_B)},
        {16, LocationData::SubLevelLocation(LevelIDs_TwinkleCircuit, MISSION_A)},

        {25, LocationData::SubLevelLocation(LevelIDs_SandHill, MISSION_B)},
        {26, LocationData::SubLevelLocation(LevelIDs_SandHill, MISSION_A)},

        {27, LocationData::SubLevelLocation(LevelIDs_SkyChase1, MISSION_B)},
        {28, LocationData::SubLevelLocation(LevelIDs_SkyChase1, MISSION_A)},

        {35, LocationData::SubLevelLocation(LevelIDs_SkyChase2, MISSION_B)},
        {36, LocationData::SubLevelLocation(LevelIDs_SkyChase2, MISSION_A)},

        // Field Emblems
        {10, LocationData::FieldEmblemLocation(119, "Station Emblem")},
        {11, LocationData::FieldEmblemLocation(121, "Burger Shop Emblem")},
        {12, LocationData::FieldEmblemLocation(120, "City Hall Emblem")},
        {13, LocationData::FieldEmblemLocation(118, "Casino Emblem")},
        {20, LocationData::FieldEmblemLocation(126, "Tails' Workshop Emblem")},
        {21, LocationData::FieldEmblemLocation(129, "Shrine Emblem")},
        {22, LocationData::FieldEmblemLocation(128, "Jungle Path Emblem")},
        {23, LocationData::FieldEmblemLocation(127, "Tree Stump Emblem")},
        {30, LocationData::FieldEmblemLocation(125, "Pool Emblem")},
        {31, LocationData::FieldEmblemLocation(123, "Spinning Platform Emblem")},
        {32, LocationData::FieldEmblemLocation(124, "Hidden Bed Emblem")},
        {33, LocationData::FieldEmblemLocation(122, "Main Platform Emblem")},

        //Boss Fight
        {700, LocationData::BossFightLocation(Characters_Sonic, LevelIDs_Chaos0)},
        {710, LocationData::BossFightLocation(Characters_Knuckles, LevelIDs_Chaos2)},
        {720, LocationData::BossFightLocation(Characters_Tails, LevelIDs_EggWalker)},

        {730, LocationData::BossFightLocation(Characters_Sonic, LevelIDs_EggHornet)},
        {731, LocationData::BossFightLocation(Characters_Tails, LevelIDs_EggHornet)},
        {739, LocationData::BossFightLocation(-1, LevelIDs_EggHornet)},

        {740, LocationData::BossFightLocation(Characters_Sonic, LevelIDs_Chaos4)},
        {741, LocationData::BossFightLocation(Characters_Tails, LevelIDs_Chaos4)},
        {742, LocationData::BossFightLocation(Characters_Knuckles, LevelIDs_Chaos4)},
        {749, LocationData::BossFightLocation(-1, LevelIDs_Chaos4)},

        {750, LocationData::BossFightLocation(Characters_Sonic, LevelIDs_EggViper)},
        {760, LocationData::BossFightLocation(Characters_Gamma, LevelIDs_E101)},

        {770, LocationData::BossFightLocation(Characters_Sonic, LevelIDs_Chaos6)},
        {771, LocationData::BossFightLocation(Characters_Knuckles, LevelIDs_Chaos6)},
        {772, LocationData::BossFightLocation(Characters_Big, LevelIDs_Chaos6)},
        {779, LocationData::BossFightLocation(-1, LevelIDs_Chaos6)},

        {780, LocationData::BossFightLocation(Characters_Gamma, LevelIDs_E101R)},
        {790, LocationData::BossFightLocation(Characters_Amy, LevelIDs_Zero)},

        //Missions
        {801, LocationData::MissionLocation(Characters_Sonic, 1)},
        {802, LocationData::MissionLocation(Characters_Sonic, 2)},
        {803, LocationData::MissionLocation(Characters_Sonic, 3)},
        {804, LocationData::MissionLocation(Characters_Tails, 4)},
        {805, LocationData::MissionLocation(Characters_Knuckles, 5)},
        {806, LocationData::MissionLocation(Characters_Amy, 6)},
        {807, LocationData::MissionLocation(Characters_Gamma, 7)},
        {808, LocationData::MissionLocation(Characters_Big, 8)},
        {809, LocationData::MissionLocation(Characters_Sonic, 9)},
        {810, LocationData::MissionLocation(Characters_Tails, 10)},
        {811, LocationData::MissionLocation(Characters_Sonic, 11)},
        {812, LocationData::MissionLocation(Characters_Knuckles, 12)},
        {813, LocationData::MissionLocation(Characters_Sonic, 13)},
        {814, LocationData::MissionLocation(Characters_Big, 14)},
        {815, LocationData::MissionLocation(Characters_Sonic, 15)},
        {816, LocationData::MissionLocation(Characters_Tails, 16)},
        {817, LocationData::MissionLocation(Characters_Sonic, 17)},
        {818, LocationData::MissionLocation(Characters_Amy, 18)},
        {819, LocationData::MissionLocation(Characters_Amy, 19)},
        {820, LocationData::MissionLocation(Characters_Sonic, 20)},
        {821, LocationData::MissionLocation(Characters_Gamma, 21)},
        {822, LocationData::MissionLocation(Characters_Big, 22)},
        {823, LocationData::MissionLocation(Characters_Sonic, 23)},
        {824, LocationData::MissionLocation(Characters_Tails, 24)},
        {825, LocationData::MissionLocation(Characters_Knuckles, 25)},
        {826, LocationData::MissionLocation(Characters_Knuckles, 26)},
        {827, LocationData::MissionLocation(Characters_Sonic, 27)},
        {828, LocationData::MissionLocation(Characters_Sonic, 28)},
        {829, LocationData::MissionLocation(Characters_Big, 29)},
        {830, LocationData::MissionLocation(Characters_Sonic, 30)},
        {831, LocationData::MissionLocation(Characters_Tails, 31)},
        {832, LocationData::MissionLocation(Characters_Knuckles, 32)},
        {833, LocationData::MissionLocation(Characters_Sonic, 33)},
        {834, LocationData::MissionLocation(Characters_Sonic, 34)},
        {835, LocationData::MissionLocation(Characters_Big, 35)},
        {836, LocationData::MissionLocation(Characters_Sonic, 36)},
        {837, LocationData::MissionLocation(Characters_Tails, 37)},
        {838, LocationData::MissionLocation(Characters_Knuckles, 38)},
        {839, LocationData::MissionLocation(Characters_Gamma, 39)},
        {840, LocationData::MissionLocation(Characters_Sonic, 40)},
        {841, LocationData::MissionLocation(Characters_Sonic, 41)},
        {842, LocationData::MissionLocation(Characters_Gamma, 42)},
        {843, LocationData::MissionLocation(Characters_Amy, 43)},
        {844, LocationData::MissionLocation(Characters_Big, 44)},
        {845, LocationData::MissionLocation(Characters_Sonic, 45)},
        {846, LocationData::MissionLocation(Characters_Sonic, 46)},
        {847, LocationData::MissionLocation(Characters_Tails, 47)},
        {848, LocationData::MissionLocation(Characters_Knuckles, 48)},
        {849, LocationData::MissionLocation(Characters_Sonic, 49)},
        {850, LocationData::MissionLocation(Characters_Amy, 50)},
        {851, LocationData::MissionLocation(Characters_Gamma, 51)},
        {852, LocationData::MissionLocation(Characters_Big, 52)},
        {853, LocationData::MissionLocation(Characters_Sonic, 53)},
        {854, LocationData::MissionLocation(Characters_Tails, 54)},
        {855, LocationData::MissionLocation(Characters_Sonic, 55)},
        {856, LocationData::MissionLocation(Characters_Knuckles, 56)},
        {857, LocationData::MissionLocation(Characters_Sonic, 57)},
        {858, LocationData::MissionLocation(Characters_Sonic, 58)},
        {859, LocationData::MissionLocation(Characters_Knuckles, 59)},
        {860, LocationData::MissionLocation(Characters_Big, 60)},

        {900, LocationData::ChaoEggLocation(FLAG_GET_GOLDEGG, "Gold Chao Egg")},
        {901, LocationData::ChaoEggLocation(FLAG_GET_SILVEREGG, "Silver Chao Egg")},
        {902, LocationData::ChaoEggLocation(FLAG_GET_BLACKEGG, "Black Chao Egg")},

        {905, LocationData::ChaoRaceLocation(106, "Pearl Course")},
        {906, LocationData::ChaoRaceLocation(107, "Amethyst Course")},
        {907, LocationData::ChaoRaceLocation(108, "Sapphire Course")},
        {908, LocationData::ChaoRaceLocation(109, "Ruby Course")},
        {909, LocationData::ChaoRaceLocation(110, "Emerald Course")},

    };

    _enemies = {
        {-225.41f, 2.25f, 98.78f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Rhinotank, 10001},
        {-109.48f, 17.32f, 250.48f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10002}, //DX
        {-107.64f, 19.02f, 253.84f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10002}, //DC
        {-455.68f, 39.68f, 184.61f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10003}, //DX
        {-457.45f, 55.68f, 183.66f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10003}, //DC
        {-590.10f, 13.20f, 377.86f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Rhinotank, 10004},
        {225.16f, 17.39f, 713.43f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10005}, //DX
        {225.63f, 18.39f, 712.55f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10005}, //DC
        {837.83f, 82.74f, 631.37f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10006}, //DX
        {837.83f, 83.50f, 631.37f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10006}, //DC
        {-640.64f, 49.84f, 900.30f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10007}, //DX
        {-641.14f, 50.50f, 898.14f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10007}, //DC
        {887.66f, 82.74f, 671.68f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10008}, //DX
        {887.66f, 83.50f, 671.68f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10008}, //DC
        {5708.03f, 40.00f, 1163.94f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10009}, //DX
        {5708.58f, 42.20f, 1167.10f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10009}, //DC
        {5781.37f, 453.00f, 678.19f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10010}, //DX
        {5780.66f, 454.10f, 677.27f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10010}, //DC
        {5997.52f, 11.10f, 1017.93f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10011}, //DX
        {6001.29f, 12.10f, 1018.92f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, Kiki, 10011}, //DC
        {422.98f, 614.01f, -1043.49f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, Kiki, 10012}, //DX
        {422.98f, 612.41f, -1043.49f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, Kiki, 10012}, //DC
        {713.28f, 540.49f, -869.65f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, Sweep, 10013}, //DX
        {713.28f, 540.49f, -817.90f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, Sweep, 10013}, //DC
        {935.83f, 555.49f, -889.97f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, Sweep, 10014},
        {1460.75f, 552.00f, -952.46f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, Kiki, 10015}, //DX
        {1460.75f, 549.80f, -952.46f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, Kiki, 10015}, //DC
        {2710.50f, 301.30f, -2622.15f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, Kiki, 10016}, //DX
        {2728.50f, 299.40f, -2603.15f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, Kiki, 10016}, //DC
        {3333.82f, 74.00f, -2707.87f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, Kiki, 10017}, //DX
        {3333.82f, 74.60f, -2707.87f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, Kiki, 10017}, //DC
        {4073.22f, 501.98f, -2841.51f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, Kiki, 10018}, //DX
        {4073.22f, 500.88f, -2841.51f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, Kiki, 10018}, //DC

        {-148.12f, 36.65f, 1.20f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51001},
        {-206.86f, 31.05f, 97.71f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51002},
        {-184.56f, 30.95f, 136.20f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51003},
        {-279.22f, 31.65f, 205.20f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51004},
        {-318.64f, 31.65f, 224.49f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51005},
        {-438.52f, 8.00f, 209.10f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Rhinotank, 51006}, //DX
        {-438.52f, 4.00f, 209.10f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Rhinotank, 51006}, //DC
        {-577.63f, 8.00f, 455.66f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Rhinotank, 51007}, //DX
        {-577.63f, 4.00f, 455.66f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Rhinotank, 51007}, //DC
        {-617.94f, 8.00f, 426.07f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Rhinotank, 51008}, //DX
        {-617.94f, 4.00f, 426.07f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Rhinotank, 51008}, //DC
        {310.42f, 34.00f, 702.06f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51009},
        {351.11f, 32.40f, 700.75f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51010},
        {703.28f, 23.32f, 642.08f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Rhinotank, 51011}, //DX
        {703.28f, 19.32f, 642.08f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Rhinotank, 51011}, //DC
        {-176.44f, 49.50f, 994.39f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51012},
        {-274.80f, 49.50f, 1005.61f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51013},
        {145.06f, 8.00f, 1039.75f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Rhinotank, 51014}, //DX
        {145.06f, 4.00f, 1039.75f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Rhinotank, 51014}, //DC
        {-622.31f, 57.00f, 893.70f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51015},
        {847.10f, 84.53f, 705.50f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51016},
        {-623.95f, 57.00f, 932.75f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51017},
        {901.72f, 84.53f, 698.25f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51018}, //DX
        {901.72f, 83.53f, 698.25f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51018}, //DC
        {881.00f, 84.53f, 735.34f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51019},
        {-618.23f, 57.00f, 978.43f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51020},
        {928.35f, 84.53f, 719.94f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51021}, //DX
        {928.35f, 83.00f, 719.94f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51021}, //DC
        {915.70f, 84.53f, 759.40f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51022}, //DX
        {915.70f, 83.63f, 759.40f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51022}, //DC
        {855.55f, 47.53f, 895.31f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Rhinotank, 51023}, //DX
        {855.55f, 43.53f, 895.31f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Rhinotank, 51023}, //DC
        {-617.18f, 127.00f, 1170.59f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51024},
        {-633.11f, 126.90f, 1171.17f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51025},
        {-671.29f, 127.30f, 1247.21f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51026},
        {-642.17f, 58.00f, 1479.55f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51027},
        {-763.75f, 58.00f, 1560.10f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51028},
        {-891.23f, 58.00f, 1556.61f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, Kiki, 51029},

        {6018.64f, 6.00f, 1076.44f, LevelAndActIDs_EmeraldCoast3, Characters_Big, Kiki, 62001},
        {6061.59f, 6.00f, 885.39f, LevelAndActIDs_EmeraldCoast3, Characters_Big, Kiki, 62002},
        {5579.45f, 6.00f, 1081.57f, LevelAndActIDs_EmeraldCoast3, Characters_Big, Kiki, 62003}, //DX
        {5579.45f, 6.90f, 1081.57f, LevelAndActIDs_EmeraldCoast3, Characters_Big, Kiki, 62003}, //DC

        {1575.37f, -467.49f, 94.79f, LevelAndActIDs_WindyValley1, Characters_Sonic, Leon, 11001},
        {1744.55f, -553.49f, 230.39f, LevelAndActIDs_WindyValley1, Characters_Sonic, BoaBoa, 11002},
        {2042.95f, -463.00f, 7.61f, LevelAndActIDs_WindyValley1, Characters_Sonic, Leon, 11003},
        {3125.27f, -503.00f, -1487.49f, LevelAndActIDs_WindyValley1, Characters_Sonic, Leon, 11004},
        {470.14f, -374.00f, -1076.62f, LevelAndActIDs_WindyValley3, Characters_Sonic, BoaBoa, 11005},
        {425.71f, -381.93f, -1269.22f, LevelAndActIDs_WindyValley3, Characters_Sonic, Leon, 11006},
        {1142.37f, -2630.02f, 1411.51f, LevelAndActIDs_WindyValley3, Characters_Sonic, Leon, 11007},
        {1348.23f, -2650.10f, 1385.73f, LevelAndActIDs_WindyValley3, Characters_Sonic, Rhinotank, 11008}, //DX
        {1348.23f, -2661.00f, 1385.73f, LevelAndActIDs_WindyValley3, Characters_Sonic, Rhinotank, 11008}, //DC
        {4227.74f, -4395.01f, -1555.39f, LevelAndActIDs_WindyValley3, Characters_Sonic, Leon, 11009},
        {4267.84f, -4450.00f, -1689.32f, LevelAndActIDs_WindyValley3, Characters_Sonic, Rhinotank, 11010}, //DX
        {4267.84f, -4460.01f, -1689.32f, LevelAndActIDs_WindyValley3, Characters_Sonic, Rhinotank, 11010}, //DC

        {409.48f, -401.00f, -1369.01f, LevelAndActIDs_WindyValley3, Characters_Tails, Leon, 20001}, //DX
        {409.48f, -405.00f, -1369.01f, LevelAndActIDs_WindyValley3, Characters_Tails, Leon, 20001}, //DC
        {1348.23f, -2650.10f, 1385.73f, LevelAndActIDs_WindyValley3, Characters_Tails, Rhinotank, 20002}, //DX
        {1348.23f, -2661.00f, 1385.73f, LevelAndActIDs_WindyValley3, Characters_Tails, Rhinotank, 20002}, //DC
        {4267.84f, -4450.00f, -1689.32f, LevelAndActIDs_WindyValley3, Characters_Tails, Rhinotank, 20003}, //DX
        {4267.84f, -4460.01f, -1689.32f, LevelAndActIDs_WindyValley3, Characters_Tails, Rhinotank, 20003}, //DC

        {145.99f, -161.00f, 282.36f, LevelAndActIDs_WindyValley1, Characters_Gamma, BoaBoa, 52001},
        {531.08f, -238.00f, 254.70f, LevelAndActIDs_WindyValley1, Characters_Gamma, Rhinotank, 52002},
        {634.86f, -202.00f, 248.79f, LevelAndActIDs_WindyValley1, Characters_Gamma, BoaBoa, 52003},
        {977.70f, -148.00f, -118.67f, LevelAndActIDs_WindyValley1, Characters_Gamma, BoaBoa, 52004},
        {1065.40f, -155.03f, -113.47f, LevelAndActIDs_WindyValley1, Characters_Gamma, Leon, 52005},
        {1139.56f, -129.03f, -95.81f, LevelAndActIDs_WindyValley1, Characters_Gamma, Leon, 52006},
        {1317.76f, -355.00f, -152.46f, LevelAndActIDs_WindyValley1, Characters_Gamma, BoaBoa, 52007},
        {1499.16f, -480.00f, 168.68f, LevelAndActIDs_WindyValley1, Characters_Gamma, BoaBoa, 52008},
        {1745.64f, -552.00f, 225.60f, LevelAndActIDs_WindyValley1, Characters_Gamma, BoaBoa, 52009},
        {2541.89f, -567.00f, -812.66f, LevelAndActIDs_WindyValley1, Characters_Gamma, BoaBoa, 52010},
        {2747.72f, -640.00f, -1229.67f, LevelAndActIDs_WindyValley1, Characters_Gamma, Rhinotank, 52011}, //DX
        {2747.72f, -642.00f, -1229.67f, LevelAndActIDs_WindyValley1, Characters_Gamma, Rhinotank, 52011}, //DC


        {-1982.93f, 1755.00f, -769.43f, LevelAndActIDs_TwinklePark1, Characters_Sonic, Kiki, 14001}, //DX
        {-1971.96f, 1754.10f, -770.24f, LevelAndActIDs_TwinklePark1, Characters_Sonic, Kiki, 14001}, //DC
        {-2033.90f, 1755.00f, -767.52f, LevelAndActIDs_TwinklePark1, Characters_Sonic, Kiki, 14002}, //DX
        {-2033.90f, 1754.10f, -767.52f, LevelAndActIDs_TwinklePark1, Characters_Sonic, Kiki, 14002}, //DC
        {-3247.01f, 416.63f, 7572.08f, LevelAndActIDs_TwinklePark1, Characters_Sonic, Kiki, 14003}, //DX
        {-3243.05f, 415.93f, 7571.55f, LevelAndActIDs_TwinklePark1, Characters_Sonic, Kiki, 14003}, //DC
        {-3248.17f, 416.63f, 7605.05f, LevelAndActIDs_TwinklePark1, Characters_Sonic, Kiki, 14004}, //DX
        {-3248.17f, 415.93f, 7605.05f, LevelAndActIDs_TwinklePark1, Characters_Sonic, Kiki, 14004}, //DC
        {-3249.33f, 416.63f, 7638.03f, LevelAndActIDs_TwinklePark1, Characters_Sonic, Kiki, 14005}, //DX
        {-3250.47f, 416.03f, 7641.86f, LevelAndActIDs_TwinklePark1, Characters_Sonic, Kiki, 14005}, //DC
        {-1509.83f, -1235.37f, 7553.54f, LevelAndActIDs_TwinklePark1, Characters_Sonic, Kiki, 14006}, //DX
        {-1510.42f, -1235.87f, 7557.50f, LevelAndActIDs_TwinklePark1, Characters_Sonic, Kiki, 14006}, //DC
        {-1517.38f, -1235.37f, 7600.94f, LevelAndActIDs_TwinklePark1, Characters_Sonic, Kiki, 14007}, //DX
        {-1514.78f, -1235.57f, 7603.98f, LevelAndActIDs_TwinklePark1, Characters_Sonic, Kiki, 14007}, //DC
        {-1524.46f, -1235.37f, 7645.39f, LevelAndActIDs_TwinklePark1, Characters_Sonic, Kiki, 14008}, //DX
        {-1523.57f, -1234.87f, 7645.85f, LevelAndActIDs_TwinklePark1, Characters_Sonic, Kiki, 14008}, //DC
        {347.55f, 0.00f, 795.28f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Buyon, 14009},
        {310.11f, 0.00f, 729.57f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Buyon, 14010},
        {69.85f, 227.89f, 589.59f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Sweep, 14011},
        {-79.09f, -8.43f, 625.06f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Sweep, 14012},
        {-62.73f, -8.43f, 579.43f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Sweep, 14013}, //DX
        {-79.09f, -8.43f, 625.06f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Sweep, 14013}, //DC
        {354.83f, 676.10f, 111.23f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14014}, //DX
        {354.25f, 676.10f, 110.42f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14014}, //DC
        {558.73f, 123.02f, 327.69f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14015},
        {621.39f, 123.02f, 321.89f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14016},
        {308.56f, 676.10f, 107.27f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14017},
        {327.81f, 670.20f, 105.67f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Buyon, 14018},
        {-93.91f, -0.17f, 348.40f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Buyon, 14019},
        {878.49f, 20.81f, 147.29f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14020},
        {877.60f, 33.81f, 103.17f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14021},
        {881.68f, 38.81f, 85.38f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14022},
        {32.18f, 223.00f, -36.76f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14023}, //DX
        {31.55f, 223.00f, -37.54f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14023}, //DC
        {406.95f, 405.00f, -229.85f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14024},
        {362.85f, 253.90f, -291.32f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14025},
        {372.35f, 272.01f, -362.17f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14026}, //DX
        {373.52f, 272.01f, -360.54f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14026}, //DC
        {-111.94f, 322.80f, -366.16f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14027},
        {76.41f, 3.76f, -469.09f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14028}, //DX
        {109.58f, 3.76f, -461.62f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14028}, //DC
        {-60.34f, 22.70f, -729.07f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14029},
        {-119.90f, 22.58f, -737.66f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14030},
        {220.32f, 5.89f, -934.72f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14031}, //DX
        {220.64f, 5.89f, -933.77f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14031}, //DC
        {495.82f, 5.89f, -971.56f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14032}, //DX
        {496.82f, 5.89f, -971.55f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14032}, //DC
        {231.68f, 5.89f, -964.77f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14033}, //DX
        {234.71f, 5.89f, -968.75f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14033}, //DC
        {206.99f, 5.89f, -972.61f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14034}, //DX
        {206.05f, 5.89f, -972.96f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Kiki, 14034}, //DC

        {583.34f, 256.02f, -366.16f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40001}, //DX
        {569.57f, 254.02f, -380.67f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40001}, //DC
        {543.06f, 256.02f, -334.05f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40002}, //DX
        {537.77f, 254.02f, -348.08f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40002}, //DC
        {518.45f, 256.02f, -303.80f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40003}, //DX
        {504.05f, 254.02f, -289.92f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40003}, //DC
        {274.99f, 272.02f, -302.59f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40004}, //DX
        {266.85f, 272.02f, -298.75f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40004}, //DC
        {878.49f, 20.81f, 147.29f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40005}, //DX
        {875.92f, 18.01f, 151.58f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40005}, //DC
        {468.82f, 4.25f, -971.19f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40006}, //DX
        {468.95f, 4.25f, -972.18f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40006}, //DC
        {712.42f, 103.85f, 374.58f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40007}, //DX
        {711.95f, 103.85f, 373.70f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40007}, //DC
        {284.69f, 3.66f, -979.10f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40008}, //DX
        {285.46f, 3.96f, -978.46f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40008}, //DC
        {570.10f, 100.02f, 406.06f, LevelAndActIDs_TwinklePark2, Characters_Amy, Buyon, 40009},
        {108.82f, 3.96f, -839.80f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40010}, //DX
        {108.98f, 3.96f, -839.26f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40010}, //DC
        {-76.50f, 4.99f, -552.86f, LevelAndActIDs_TwinklePark3, Characters_Amy, Kiki, 40011}, //DX
        {-76.17f, 3.99f, -542.86f, LevelAndActIDs_TwinklePark3, Characters_Amy, Kiki, 40011}, //DC
        {-89.49f, 4.99f, -559.12f, LevelAndActIDs_TwinklePark3, Characters_Amy, Kiki, 40012}, //DX
        {-89.04f, 3.99f, -558.23f, LevelAndActIDs_TwinklePark3, Characters_Amy, Kiki, 40012}, //DC
        {203.54f, 4.00f, -99.29f, LevelAndActIDs_TwinklePark3, Characters_Amy, Kiki, 40013}, //DX
        {204.35f, 4.00f, -98.70f, LevelAndActIDs_TwinklePark3, Characters_Amy, Kiki, 40013}, //DC
        {796.20f, -35.00f, -451.74f, LevelAndActIDs_TwinklePark3, Characters_Amy, Buyon, 40014},
        {-85.46f, 105.00f, 487.88f, LevelAndActIDs_TwinklePark3, Characters_Amy, Kiki, 40015}, //DX
        {-85.00f, 104.00f, 486.99f, LevelAndActIDs_TwinklePark3, Characters_Amy, Kiki, 40015}, //DC
        {124.76f, 100.00f, 675.01f, LevelAndActIDs_TwinklePark3, Characters_Amy, Buyon, 40016},
        {87.39f, 100.00f, 691.81f, LevelAndActIDs_TwinklePark3, Characters_Amy, Buyon, 40017},

        {68.07f, 6.00f, -454.61f, LevelAndActIDs_TwinklePark2, Characters_Big, Kiki, 60001}, //DX
        {68.07f, 4.00f, -454.61f, LevelAndActIDs_TwinklePark2, Characters_Big, Kiki, 60001}, //DC
        {165.72f, 6.00f, -887.51f, LevelAndActIDs_TwinklePark2, Characters_Big, Kiki, 60002},
        {660.64f, 6.00f, -561.42f, LevelAndActIDs_TwinklePark2, Characters_Big, Kiki, 60003}, //DX
        {660.64f, 4.00f, -561.42f, LevelAndActIDs_TwinklePark2, Characters_Big, Kiki, 60003}, //DC
        {322.83f, 6.00f, -985.34f, LevelAndActIDs_TwinklePark2, Characters_Big, Kiki, 60004},
    };

    _capsules = {
        {72.76f, 6.01f, -96.21f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, TenRingsCapsule, 10501},
        {54.36f, 9.01f, -109.38f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, TenRingsCapsule, 10502},
        {74.60f, 9.01f, -118.22f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, TenRingsCapsule, 10503},
        {828.02f, 79.74f, 626.83f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, RandomRingsCapsule, 10504},
        {1053.08f, -6.77f, 745.21f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, ExtraLifeCapsule, 10505},
        {2590.28f, 30.00f, 423.34f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, TenRingsCapsule, 10506},
        {6061.48f, -0.01f, 878.86f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, TenRingsCapsule, 10507},
        {6297.18f, 316.95f, 1271.14f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, ExtraLifeCapsule, 10508}, //DX
        {6297.18f, 312.70f, 1271.14f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, ExtraLifeCapsule, 10508}, //DC
        {6379.65f, -0.30f, 1194.23f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, RandomRingsCapsule, 10509},
        {6387.11f, -0.30f, 1177.90f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, RandomRingsCapsule, 10510},
        {6392.47f, -0.30f, 1154.71f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, RandomRingsCapsule, 10511},
        {270.32f, 787.09f, -1741.71f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, SpeedUpCapsule, 10512}, //DX
        {260.72f, 796.40f, -1732.51f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, SpeedUpCapsule, 10512}, //DC
        {426.01f, 604.92f, -1011.94f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, TenRingsCapsule, 10513},
        {1279.87f, 544.77f, -1105.75f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, TenRingsCapsule, 10514},
        {1086.20f, 650.54f, -753.55f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, ExtraLifeCapsule, 10515}, //DX
        {1078.81f, 656.17f, -748.29f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, ExtraLifeCapsule, 10515}, //DC
        {3161.46f, 0.44f, -2630.80f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, ExtraLifeCapsule, 10516}, //DX
        {3161.46f, -0.28f, -2630.80f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, ExtraLifeCapsule, 10516}, //DC
        {3355.25f, 69.70f, -2746.10f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, FiveRingsCapsule, 10517},
        {3369.42f, 69.70f, -2765.88f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, FiveRingsCapsule, 10518},
        {3384.58f, 69.70f, -2739.77f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, FiveRingsCapsule, 10519},
        {3672.62f, 139.60f, -2596.53f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, RandomRingsCapsule, 10520}, //DX
        {3672.56f, 140.72f, -2596.53f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, RandomRingsCapsule, 10520}, //DC

        {72.76f, 6.01f, -96.21f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, TenRingsCapsule, 51501},
        {54.36f, 9.01f, -109.38f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, TenRingsCapsule, 51502},
        {74.60f, 9.01f, -118.22f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, TenRingsCapsule, 51503},
        {-269.15f, 49.65f, 350.81f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, FiveRingsCapsule, 51504},
        {-734.38f, 28.65f, 294.60f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, FiveRingsCapsule, 51505},
        {-326.69f, 31.65f, 917.44f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, FiveRingsCapsule, 51506},
        {65.00f, 148.65f, 1037.50f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, FiveRingsCapsule, 51507},
        {61.42f, 172.65f, 1061.23f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, FiveRingsCapsule, 51508},
        {56.50f, 148.65f, 1093.87f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, FiveRingsCapsule, 51509},
        {1048.05f, -5.07f, 747.43f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, ExtraLifeCapsule, 51510},
        {-603.34f, 58.65f, 1233.52f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, FiveRingsCapsule, 51511},
        {-840.48f, 58.65f, 1468.46f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, FiveRingsCapsule, 51512},
        {-675.62f, 3.86f, 1559.55f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, RandomRingsCapsule, 51513}, //DX
        {-675.62f, 3.76f, 1559.55f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, RandomRingsCapsule, 51513}, //DC

        {6061.48f, -0.01f, 878.86f, LevelAndActIDs_EmeraldCoast3, Characters_Big, TenRingsCapsule, 62501},
        {6086.91f, 78.29f, 1186.96f, LevelAndActIDs_EmeraldCoast3, Characters_Big, ExtraLifeCapsule, 62502},

        {1600.56f, -472.00f, 123.31f, LevelAndActIDs_WindyValley1, Characters_Sonic, TenRingsCapsule, 11501}, //DX
        {1600.56f, -472.62f, 123.31f, LevelAndActIDs_WindyValley1, Characters_Sonic, TenRingsCapsule, 11501}, //DC
        {2004.75f, -412.00f, 101.19f, LevelAndActIDs_WindyValley1, Characters_Sonic, MagneticShieldCapsule, 11502},
        {1993.49f, -599.98f, 180.78f, LevelAndActIDs_WindyValley1, Characters_Sonic, ShieldCapsule, 11503}, //DX
        {1993.49f, -600.10f, 180.78f, LevelAndActIDs_WindyValley1, Characters_Sonic, ShieldCapsule, 11503}, //DC
        {2212.05f, -567.00f, -16.74f, LevelAndActIDs_WindyValley1, Characters_Sonic, ExtraLifeCapsule, 11504},
        {2903.39f, -433.80f, -1011.87f, LevelAndActIDs_WindyValley1, Characters_Sonic, RandomRingsCapsule, 11505}, //DX
        {2903.39f, -434.00f, -1011.87f, LevelAndActIDs_WindyValley1, Characters_Sonic, RandomRingsCapsule, 11505}, //DC
        {2996.38f, -434.90f, -1504.00f, LevelAndActIDs_WindyValley1, Characters_Sonic, ExtraLifeCapsule, 11506}, //DX
        {2996.38f, -434.89f, -1504.00f, LevelAndActIDs_WindyValley1, Characters_Sonic, ExtraLifeCapsule, 11506}, //DC
        {499.44f, -388.20f, -1286.16f, LevelAndActIDs_WindyValley3, Characters_Sonic, SpeedUpCapsule, 11507}, //DX
        {499.44f, -388.18f, -1286.16f, LevelAndActIDs_WindyValley3, Characters_Sonic, SpeedUpCapsule, 11507}, //DC
        {1147.72f, -2209.17f, 1260.16f, LevelAndActIDs_WindyValley3, Characters_Sonic, ExtraLifeCapsule, 11508},
        {1474.79f, -2619.00f, 960.98f, LevelAndActIDs_WindyValley3, Characters_Sonic, MagneticShieldCapsule, 11509},
        {1677.80f, -2577.00f, 1117.49f, LevelAndActIDs_WindyValley3, Characters_Sonic, ExtraLifeCapsule, 11510},
        {1120.90f, -2622.99f, 1349.91f, LevelAndActIDs_WindyValley3, Characters_Sonic, RandomRingsCapsule, 11511},
        {4206.01f, -4295.83f, -1686.53f, LevelAndActIDs_WindyValley3, Characters_Sonic, MagneticShieldCapsule, 11512},
        //DX
        {4206.01f, -4296.01f, -1686.53f, LevelAndActIDs_WindyValley3, Characters_Sonic, MagneticShieldCapsule, 11512},
        //DC
        {3995.66f, -4456.73f, -1644.02f, LevelAndActIDs_WindyValley3, Characters_Sonic, RandomRingsCapsule, 11513}, //DX
        {3995.66f, -4458.00f, -1644.02f, LevelAndActIDs_WindyValley3, Characters_Sonic, RandomRingsCapsule, 11513}, //DC
        {4171.99f, -4399.00f, -1743.84f, LevelAndActIDs_WindyValley3, Characters_Sonic, RandomRingsCapsule, 11514}, //DX
        {4171.99f, -4398.99f, -1743.84f, LevelAndActIDs_WindyValley3, Characters_Sonic, RandomRingsCapsule, 11514}, //DC
        {4160.34f, -4484.50f, -1812.61f, LevelAndActIDs_WindyValley3, Characters_Sonic, MagneticShieldCapsule, 11515},
        {4159.61f, -4484.50f, -1826.59f, LevelAndActIDs_WindyValley3, Characters_Sonic, ExtraLifeCapsule, 11516},
        {5681.68f, -10755.00f, -791.06f, LevelAndActIDs_WindyValley3, Characters_Sonic, RandomRingsCapsule, 11517},

        {499.44f, -388.18f, -1286.16f, LevelAndActIDs_WindyValley3, Characters_Tails, SpeedUpCapsule, 20501},
        {1474.79f, -2619.00f, 960.98f, LevelAndActIDs_WindyValley3, Characters_Tails, FiveRingsCapsule, 20502},
        {1677.80f, -2577.00f, 1117.49f, LevelAndActIDs_WindyValley3, Characters_Tails, SpeedUpCapsule, 20503},
        {1120.90f, -2622.99f, 1349.91f, LevelAndActIDs_WindyValley3, Characters_Tails, RandomRingsCapsule, 20504},
        {1173.89f, -2571.02f, 1497.21f, LevelAndActIDs_WindyValley3, Characters_Tails, TenRingsCapsule, 20505},
        {4119.69f, -4299.01f, -1503.75f, LevelAndActIDs_WindyValley3, Characters_Tails, TenRingsCapsule, 20506},
        {3995.66f, -4456.73f, -1644.02f, LevelAndActIDs_WindyValley3, Characters_Tails, RandomRingsCapsule, 20507}, //DX
        {3995.66f, -4458.00f, -1644.02f, LevelAndActIDs_WindyValley3, Characters_Tails, RandomRingsCapsule, 20507}, //DC
        {4160.33f, -4437.50f, -1812.61f, LevelAndActIDs_WindyValley3, Characters_Tails, SpeedUpCapsule, 20508},
        {5327.94f, -4014.36f, -2284.31f, LevelAndActIDs_WindyValley3, Characters_Tails, ExtraLifeCapsule, 20509},
        {5686.74f, -10755.00f, -792.74f, LevelAndActIDs_WindyValley3, Characters_Tails, RandomRingsCapsule, 20510},

        {635.30f, -61.00f, 247.38f, LevelAndActIDs_WindyValley1, Characters_Gamma, ExtraLifeCapsule, 52501},
        {803.36f, -310.50f, -72.85f, LevelAndActIDs_WindyValley1, Characters_Gamma, SpeedUpCapsule, 52502}, //DX
        {803.36f, -311.00f, -72.85f, LevelAndActIDs_WindyValley1, Characters_Gamma, SpeedUpCapsule, 52502}, //DC
        {979.54f, -177.81f, -160.69f, LevelAndActIDs_WindyValley1, Characters_Gamma, TenRingsCapsule, 52503}, //DX
        {979.54f, -178.31f, -160.69f, LevelAndActIDs_WindyValley1, Characters_Gamma, TenRingsCapsule, 52503}, //DC
        {1072.98f, -157.81f, -25.14f, LevelAndActIDs_WindyValley1, Characters_Gamma, FiveRingsCapsule, 52504}, //DX
        {1072.98f, -158.31f, -25.14f, LevelAndActIDs_WindyValley1, Characters_Gamma, FiveRingsCapsule, 52504}, //DC
        {1216.96f, -269.75f, -174.80f, LevelAndActIDs_WindyValley1, Characters_Gamma, InvincibilityCapsule, 52505},
        {1240.69f, -267.75f, -94.64f, LevelAndActIDs_WindyValley1, Characters_Gamma, MagneticShieldCapsule, 52506},
        {2014.17f, -467.00f, 5.39f, LevelAndActIDs_WindyValley1, Characters_Gamma, RandomRingsCapsule, 52507},
        {2028.11f, -467.00f, 6.60f, LevelAndActIDs_WindyValley1, Characters_Gamma, ExtraLifeCapsule, 52508},
        {2043.06f, -467.00f, 7.89f, LevelAndActIDs_WindyValley1, Characters_Gamma, RandomRingsCapsule, 52509},
        {2897.02f, -461.03f, -1274.20f, LevelAndActIDs_WindyValley1, Characters_Gamma, RandomRingsCapsule, 52510},

        {-2039.84f, 1520.50f, 1362.67f, LevelAndActIDs_TwinklePark1, Characters_Sonic, FiveRingsCapsule, 14501},
        {-2909.14f, 1294.00f, 2272.62f, LevelAndActIDs_TwinklePark1, Characters_Sonic, TenRingsCapsule, 14502},
        {-2960.27f, 1223.00f, 3272.37f, LevelAndActIDs_TwinklePark1, Characters_Sonic, RandomRingsCapsule, 14503},
        {-2957.79f, 725.00f, 5216.49f, LevelAndActIDs_TwinklePark1, Characters_Sonic, FiveRingsCapsule, 14504},
        {-3037.67f, 740.00f, 6360.84f, LevelAndActIDs_TwinklePark1, Characters_Sonic, FiveRingsCapsule, 14505},
        {-3205.38f, 745.00f, 6808.61f, LevelAndActIDs_TwinklePark1, Characters_Sonic, FiveRingsCapsule, 14506},
        {-3051.10f, 745.00f, 7214.05f, LevelAndActIDs_TwinklePark1, Characters_Sonic, FiveRingsCapsule, 14507},
        {-2537.78f, -208.31f, 7597.23f, LevelAndActIDs_TwinklePark1, Characters_Sonic, ExtraLifeCapsule, 14508},
        {-1815.37f, -1177.00f, 7632.06f, LevelAndActIDs_TwinklePark1, Characters_Sonic, BombCapsule, 14509},
        {119.35f, -1519.96f, 7602.92f, LevelAndActIDs_TwinklePark1, Characters_Sonic, ExtraLifeCapsule, 14510},
        {1921.49f, -1715.19f, 8560.98f, LevelAndActIDs_TwinklePark1, Characters_Sonic, FiveRingsCapsule, 14511},
        {2158.00f, -1715.19f, 8640.33f, LevelAndActIDs_TwinklePark1, Characters_Sonic, FiveRingsCapsule, 14512},
        {2571.95f, -1715.19f, 8561.77f, LevelAndActIDs_TwinklePark1, Characters_Sonic, FiveRingsCapsule, 14513},
        {-261.12f, -2430.25f, 9345.16f, LevelAndActIDs_TwinklePark1, Characters_Sonic, FiveRingsCapsule, 14514},
        {3294.22f, -1821.26f, 8926.81f, LevelAndActIDs_TwinklePark1, Characters_Sonic, FiveRingsCapsule, 14515},
        {2222.65f, -2229.00f, 9362.36f, LevelAndActIDs_TwinklePark1, Characters_Sonic, TenRingsCapsule, 14516},
        {-6256.02f, -4875.18f, 16102.47f, LevelAndActIDs_TwinklePark1, Characters_Sonic, FiveRingsCapsule, 14517},
        {-6333.45f, -4887.18f, 16118.63f, LevelAndActIDs_TwinklePark1, Characters_Sonic, FiveRingsCapsule, 14518},
        {-6397.05f, -4894.18f, 16121.53f, LevelAndActIDs_TwinklePark1, Characters_Sonic, FiveRingsCapsule, 14519},
        {164.42f, 403.80f, 594.07f, LevelAndActIDs_TwinklePark2, Characters_Sonic, InvincibilityCapsule, 14520},
        {616.04f, 140.60f, 536.35f, LevelAndActIDs_TwinklePark2, Characters_Sonic, FiveRingsCapsule, 14521},
        {685.65f, 159.60f, 383.72f, LevelAndActIDs_TwinklePark2, Characters_Sonic, InvincibilityCapsule, 14522},
        {446.45f, 620.00f, 160.82f, LevelAndActIDs_TwinklePark2, Characters_Sonic, FiveRingsCapsule, 14523},
        {426.48f, 620.00f, 161.95f, LevelAndActIDs_TwinklePark2, Characters_Sonic, FiveRingsCapsule, 14524},
        {466.41f, 620.00f, 159.69f, LevelAndActIDs_TwinklePark2, Characters_Sonic, FiveRingsCapsule, 14525},
        {-24.25f, 425.30f, 125.35f, LevelAndActIDs_TwinklePark2, Characters_Sonic, ExtraLifeCapsule, 14526},
        {767.00f, 82.39f, -129.81f, LevelAndActIDs_TwinklePark2, Characters_Sonic, FiveRingsCapsule, 14527},
        {967.21f, 93.39f, -106.72f, LevelAndActIDs_TwinklePark2, Characters_Sonic, FiveRingsCapsule, 14528},
        {763.90f, 81.39f, -221.39f, LevelAndActIDs_TwinklePark2, Characters_Sonic, FiveRingsCapsule, 14529},
        {-300.68f, 310.00f, -183.25f, LevelAndActIDs_TwinklePark2, Characters_Sonic, TenRingsCapsule, 14530},
        {990.39f, 87.39f, -212.64f, LevelAndActIDs_TwinklePark2, Characters_Sonic, ShieldCapsule, 14531},
        {372.47f, 317.02f, -363.36f, LevelAndActIDs_TwinklePark2, Characters_Sonic, ExtraLifeCapsule, 14532},
        {965.93f, 93.39f, -284.82f, LevelAndActIDs_TwinklePark2, Characters_Sonic, FiveRingsCapsule, 14533},
        {109.96f, 200.02f, -371.39f, LevelAndActIDs_TwinklePark2, Characters_Sonic, RandomRingsCapsule, 14534},
        {703.07f, -0.11f, -511.70f, LevelAndActIDs_TwinklePark2, Characters_Sonic, RandomRingsCapsule, 14535},
        {688.49f, -0.11f, -532.23f, LevelAndActIDs_TwinklePark2, Characters_Sonic, RandomRingsCapsule, 14536},
        {709.47f, -0.11f, -535.84f, LevelAndActIDs_TwinklePark2, Characters_Sonic, RandomRingsCapsule, 14537},
        {314.77f, 66.26f, -591.00f, LevelAndActIDs_TwinklePark2, Characters_Sonic, RandomRingsCapsule, 14538},
        {-162.02f, 0.00f, -579.30f, LevelAndActIDs_TwinklePark2, Characters_Sonic, RandomRingsCapsule, 14539},
        {-51.71f, 0.01f, -1034.34f, LevelAndActIDs_TwinklePark2, Characters_Sonic, FiveRingsCapsule, 14540},

        {703.07f, -0.11f, -511.70f, LevelAndActIDs_TwinklePark2, Characters_Amy, RandomRingsCapsule, 40501},
        {688.49f, -0.11f, -532.23f, LevelAndActIDs_TwinklePark2, Characters_Amy, RandomRingsCapsule, 40502},
        {709.47f, -0.11f, -535.84f, LevelAndActIDs_TwinklePark2, Characters_Amy, RandomRingsCapsule, 40503},
        {435.98f, 297.02f, -255.54f, LevelAndActIDs_TwinklePark2, Characters_Amy, TenRingsCapsule, 40504},
        {267.40f, 306.02f, -297.65f, LevelAndActIDs_TwinklePark2, Characters_Amy, ExtraLifeCapsule, 40505},
        {619.40f, 41.96f, -871.16f, LevelAndActIDs_TwinklePark2, Characters_Amy, SpeedUpCapsule, 40506},
        {18.14f, 0.00f, -631.67f, LevelAndActIDs_TwinklePark2, Characters_Amy, ShieldCapsule, 40507},
        {779.32f, 120.00f, 408.08f, LevelAndActIDs_TwinklePark2, Characters_Amy, RandomRingsCapsule, 40508},
        {611.41f, 145.00f, 551.92f, LevelAndActIDs_TwinklePark2, Characters_Amy, RandomRingsCapsule, 40509},

        {69.93f, 0.00f, -442.74f, LevelAndActIDs_TwinklePark2, Characters_Big, RandomRingsCapsule, 60501},
        {643.80f, 0.00f, -565.22f, LevelAndActIDs_TwinklePark2, Characters_Big, RandomRingsCapsule, 60502},

    };


    for (auto& capsule : _capsules)
    {
        _checkData[capsule.locationId] = LocationData::CapsuleLocation(capsule);
    }

    for (auto& enemy : _enemies)
    {
        _checkData[enemy.locationId] = LocationData::EnemyLocation(enemy);
    }
}


LocationData LocationRepository::SetLocationChecked(const int checkId)
{
    _checkData[checkId].checked = true;
    return _checkData[checkId];
}

LocationData LocationRepository::GetLocation(const int checkId)
{
    return _checkData[checkId];
}

std::map<int, LocationData> LocationRepository::GetLocations()
{
    return _checkData;
}

std::vector<CapsuleLocationData> LocationRepository::GetCapsuleLocations()
{
    return _capsules;
}

std::vector<EnemyLocationData> LocationRepository::GetEnemyLocations()
{
    return _enemies;
}


LevelStatus LocationRepository::GetLevelStatus(Options options)
{
    auto levelStatus = LevelStatus();
    levelStatus.sonicEmeraldCoast = _checkData[1002].checked;
    levelStatus.sonicWindyValley = _checkData[1102].checked;
    levelStatus.sonicCasinopolis = _checkData[1202].checked;
    levelStatus.sonicIceCap = _checkData[1302].checked;
    levelStatus.sonicTwinklePark = _checkData[1402].checked;
    levelStatus.sonicSpeedHighway = _checkData[1502].checked;
    levelStatus.sonicRedMountain = _checkData[1602].checked;
    levelStatus.sonicSkyDeck = _checkData[1702].checked;
    levelStatus.sonicLostWorld = _checkData[1802].checked;
    levelStatus.sonicFinalEgg = _checkData[1902].checked;

    levelStatus.tailsWindyValley = _checkData[2002].checked;
    levelStatus.tailsCasinopolis = _checkData[2102].checked;
    levelStatus.tailsIceCap = _checkData[2202].checked;
    levelStatus.tailsSkyDeck = _checkData[2302].checked;
    levelStatus.tailsSpeedHighway = _checkData[2402].checked;

    levelStatus.knucklesSpeedHighway = _checkData[3002].checked;
    levelStatus.knucklesCasinopolis = _checkData[3102].checked;
    levelStatus.knucklesRedMountain = _checkData[3202].checked;
    levelStatus.knucklesLostWorld = _checkData[3302].checked;
    levelStatus.knucklesSkyDeck = _checkData[3402].checked;

    levelStatus.amyTwinklePark = _checkData[4002].checked;
    levelStatus.amyHotShelter = _checkData[4102].checked;
    levelStatus.amyFinalEgg = _checkData[4202].checked;

    levelStatus.bigTwinklePark = _checkData[6002].checked;
    levelStatus.bigIceCap = _checkData[6102].checked;
    levelStatus.bigEmeraldCoast = _checkData[6202].checked;
    levelStatus.bigHotShelter = _checkData[6302].checked;

    levelStatus.gammaFinalEgg = _checkData[5002].checked;
    levelStatus.gammaWindyValley = _checkData[5102].checked;
    levelStatus.gammaEmeraldCoast = _checkData[5202].checked;
    levelStatus.gammaRedMountain = _checkData[5302].checked;
    levelStatus.gammaHotShelter = _checkData[5402].checked;


    if (options.sonicActionStageMissions > 0 && options.playableSonic)
    {
        int count = 0;
        if (levelStatus.sonicEmeraldCoast) count++;
        if (levelStatus.sonicWindyValley) count++;
        if (levelStatus.sonicCasinopolis) count++;
        if (levelStatus.sonicIceCap) count++;
        if (levelStatus.sonicTwinklePark) count++;
        if (levelStatus.sonicSpeedHighway) count++;
        if (levelStatus.sonicRedMountain) count++;
        if (levelStatus.sonicSkyDeck) count++;
        if (levelStatus.sonicLostWorld) count++;
        if (levelStatus.sonicFinalEgg) count++;

        levelStatus.sonicLevelsTotal = 10;
        levelStatus.sonicLevelsCompleted = count;
    }
    if (options.tailsActionStageMissions > 0 && options.playableTails)
    {
        int count = 0;
        if (levelStatus.tailsWindyValley) count++;
        if (levelStatus.tailsCasinopolis) count++;
        if (levelStatus.tailsIceCap) count++;
        if (levelStatus.tailsSkyDeck) count++;
        if (levelStatus.tailsSpeedHighway) count++;
        levelStatus.tailsLevelsTotal = 5;
        levelStatus.tailsLevelsCompleted = count;
    }
    if (options.knucklesActionStageMissions > 0 && options.playableKnuckles)
    {
        int count = 0;
        if (levelStatus.knucklesSpeedHighway) count++;
        if (levelStatus.knucklesCasinopolis) count++;
        if (levelStatus.knucklesRedMountain) count++;
        if (levelStatus.knucklesLostWorld) count++;
        if (levelStatus.knucklesSkyDeck) count++;
        levelStatus.knucklesLevelsTotal = 5;
        levelStatus.knucklesLevelsCompleted = count;
    }
    if (options.amyActionStageMissions > 0 && options.playableAmy)
    {
        int count = 0;
        if (levelStatus.amyTwinklePark) count++;
        if (levelStatus.amyHotShelter) count++;
        if (levelStatus.amyFinalEgg) count++;
        levelStatus.amyLevelsTotal = 3;
        levelStatus.amyLevelsCompleted = count;
    }
    if (options.bigActionStageMissions > 0 && options.playableBig)
    {
        int count = 0;
        if (levelStatus.bigTwinklePark) count++;
        if (levelStatus.bigIceCap) count++;
        if (levelStatus.bigEmeraldCoast) count++;
        if (levelStatus.bigHotShelter) count++;
        levelStatus.bigLevelsTotal = 4;
        levelStatus.bigLevelsCompleted = count;
    }
    if (options.gammaActionStageMissions > 0 && options.playableGamma)
    {
        int count = 0;
        if (levelStatus.gammaFinalEgg) count++;
        if (levelStatus.gammaWindyValley) count++;
        if (levelStatus.gammaEmeraldCoast) count++;
        if (levelStatus.gammaRedMountain) count++;
        if (levelStatus.gammaHotShelter) count++;
        levelStatus.gammaLevelsTotal = 5;
        levelStatus.gammaLevelsCompleted = count;
    }

    levelStatus.levelsCompleted = levelStatus.sonicLevelsCompleted + levelStatus.tailsLevelsCompleted
        + levelStatus.knucklesLevelsCompleted + levelStatus.amyLevelsCompleted
        + levelStatus.bigLevelsCompleted + levelStatus.gammaLevelsCompleted;

    return levelStatus;
}

MissionStatus LocationRepository::GetMissionStatus(Options options)
{
    auto missionStatus = MissionStatus();
    auto vector = options.missionBlacklist;
    for (int index = 801; index <= 860; index++)
    {
        if (std::find(vector.begin(), vector.end(), _checkData[index].missionNumber) != vector.end())
            continue;

        if (_checkData[index].character == Characters_Sonic)
        {
            missionStatus.sonicMissionsTotal++;
            if (_checkData[index].checked)
                missionStatus.sonicMissionsCompleted++;
        }
        else if (_checkData[index].character == Characters_Tails)
        {
            missionStatus.tailsMissionsTotal++;
            if (_checkData[index].checked)
                missionStatus.tailsMissionsCompleted++;
        }
        else if (_checkData[index].character == Characters_Knuckles)
        {
            missionStatus.knucklesMissionsTotal++;
            if (_checkData[index].checked)
                missionStatus.knucklesMissionsCompleted++;
        }
        else if (_checkData[index].character == Characters_Amy)
        {
            missionStatus.amyMissionsTotal++;
            if (_checkData[index].checked)
                missionStatus.amyMissionsCompleted++;
        }
        else if (_checkData[index].character == Characters_Gamma)
        {
            missionStatus.gammaMissionsTotal++;
            if (_checkData[index].checked)
                missionStatus.gammaMissionsCompleted++;
        }
        else if (_checkData[index].character == Characters_Big)
        {
            missionStatus.bigMissionsTotal++;
            if (_checkData[index].checked)
                missionStatus.bigMissionsCompleted++;
        }
        if (_checkData[index].checked)
            missionStatus.missionsCompleted++;
    }
    return missionStatus;
}


BossesStatus LocationRepository::GetBossesStatus(const Options& options)
{
    auto bossesStatus = BossesStatus();
    //Chaos 0
    if (_checkData[700].checked)
    {
        bossesStatus.sonicBossesCompleted++;
        bossesStatus.bossesCompleted++;
    }
    //Chaos 2
    if (_checkData[710].checked)
    {
        bossesStatus.knucklesBossesCompleted++;
        bossesStatus.bossesCompleted++;
    }
    //Egg Walker
    if (_checkData[720].checked)
    {
        bossesStatus.tailsBossesCompleted++;
        bossesStatus.bossesCompleted++;
    }
    //Egg Hornet 
    if (options.unifyEggHornet)
    {
        if (_checkData[739].checked)
        {
            bossesStatus.sonicBossesCompleted++;
            bossesStatus.tailsBossesCompleted++;
            bossesStatus.bossesCompleted++;
        }
    }
    else
    {
        if (_checkData[730].checked)
        {
            bossesStatus.sonicBossesCompleted++;
            bossesStatus.bossesCompleted++;
        }
        if (_checkData[731].checked)
        {
            bossesStatus.tailsBossesCompleted++;
            bossesStatus.bossesCompleted++;
        }
    }

    //Chaos 4 
    if (options.unifyChaos4)
    {
        if (_checkData[749].checked)
        {
            bossesStatus.sonicBossesCompleted++;
            bossesStatus.tailsBossesCompleted++;
            bossesStatus.knucklesBossesCompleted++;
            bossesStatus.bossesCompleted++;
        }
    }
    else
    {
        if (_checkData[740].checked)
        {
            bossesStatus.sonicBossesCompleted++;
            bossesStatus.bossesCompleted++;
        }
        if (_checkData[741].checked)
        {
            bossesStatus.tailsBossesCompleted++;
            bossesStatus.bossesCompleted++;
        }
        if (_checkData[742].checked)
        {
            bossesStatus.knucklesBossesCompleted++;
            bossesStatus.bossesCompleted++;
        }
    }
    //Egg Viper
    if (_checkData[750].checked)
    {
        bossesStatus.sonicBossesCompleted++;
        bossesStatus.bossesCompleted++;
    }
    //Beta
    if (_checkData[760].checked)
    {
        bossesStatus.gammaBossesCompleted++;
        bossesStatus.bossesCompleted++;
    }

    //Chaos 6 
    if (options.unifyChaos6)
    {
        if (_checkData[779].checked)
        {
            bossesStatus.sonicBossesCompleted++;
            bossesStatus.knucklesBossesCompleted++;
            bossesStatus.bigBossesCompleted++;
            bossesStatus.bossesCompleted++;
        }
    }
    else
    {
        if (_checkData[770].checked)
        {
            bossesStatus.sonicBossesCompleted++;
            bossesStatus.bossesCompleted++;
        }

        if (_checkData[771].checked)
        {
            bossesStatus.knucklesBossesCompleted++;
            bossesStatus.bossesCompleted++;
        }

        if (_checkData[772].checked)
        {
            bossesStatus.bigBossesCompleted++;
            bossesStatus.bossesCompleted++;
        }
    }
    //Beta 2
    if (_checkData[780].checked)
    {
        bossesStatus.gammaBossesCompleted++;
        bossesStatus.bossesCompleted++;
    }

    //Zero
    if (_checkData[790].checked)
    {
        bossesStatus.amyBossesCompleted++;
        bossesStatus.bossesCompleted++;
    }

    return bossesStatus;
}

ChaoStatus LocationRepository::GetChaoStatus()
{
    auto chaoStatus = ChaoStatus();
    if (_checkData[905].checked)
        chaoStatus.racesCompleted++;
    if (_checkData[906].checked)
        chaoStatus.racesCompleted++;
    if (_checkData[907].checked)
        chaoStatus.racesCompleted++;
    if (_checkData[908].checked)
        chaoStatus.racesCompleted++;
    if (_checkData[909].checked)
        chaoStatus.racesCompleted++;

    return chaoStatus;
}
