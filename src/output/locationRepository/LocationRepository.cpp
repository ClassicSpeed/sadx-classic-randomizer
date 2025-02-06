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
        {15, LocationData::SubLevelLocation(LevelIDs_TwinkleCircuit, SUB_LEVEL_MISSION_B)},
        {40, LocationData::SubLevelLocation(LevelIDs_TwinkleCircuit, TWINKLE_CIRCUIT_SONIC)},
        {41, LocationData::SubLevelLocation(LevelIDs_TwinkleCircuit, TWINKLE_CIRCUIT_TAILS)},
        {42, LocationData::SubLevelLocation(LevelIDs_TwinkleCircuit, TWINKLE_CIRCUIT_KNUCKLES)},
        {43, LocationData::SubLevelLocation(LevelIDs_TwinkleCircuit, TWINKLE_CIRCUIT_AMY)},
        {44, LocationData::SubLevelLocation(LevelIDs_TwinkleCircuit, TWINKLE_CIRCUIT_BIG)},
        {45, LocationData::SubLevelLocation(LevelIDs_TwinkleCircuit, TWINKLE_CIRCUIT_GAMMA)},

        {25, LocationData::SubLevelLocation(LevelIDs_SandHill, SUB_LEVEL_MISSION_B)},
        {26, LocationData::SubLevelLocation(LevelIDs_SandHill, SUB_LEVEL_MISSION_A)},

        {27, LocationData::SubLevelLocation(LevelIDs_SkyChase1, SUB_LEVEL_MISSION_B)},
        {28, LocationData::SubLevelLocation(LevelIDs_SkyChase1, SUB_LEVEL_MISSION_A)},

        {35, LocationData::SubLevelLocation(LevelIDs_SkyChase2, SUB_LEVEL_MISSION_B)},
        {36, LocationData::SubLevelLocation(LevelIDs_SkyChase2, SUB_LEVEL_MISSION_A)},

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
        {-62.73f, -8.43f, 579.43f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Sweep, 14013}, //DC
        {-2.73f, -8.43f, 703.43f, LevelAndActIDs_TwinklePark2, Characters_Sonic, Sweep, 14013}, //DX
        
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


        {468.82f, 4.25f, -971.19f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40001}, //DX
        {468.95f, 4.25f, -972.18f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40001}, //DC
        {284.69f, 3.66f, -979.10f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40002}, //DX
        {285.46f, 3.96f, -978.46f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40002}, //DC
        {108.82f, 3.96f, -839.80f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40003}, //DX
        {108.98f, 3.96f, -839.26f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40003}, //DC
        {-76.50f, 4.99f, -552.86f, LevelAndActIDs_TwinklePark3, Characters_Amy, Kiki, 40004}, //DX
        {-76.17f, 3.99f, -542.86f, LevelAndActIDs_TwinklePark3, Characters_Amy, Kiki, 40004}, //DC
        {-89.49f, 4.99f, -559.12f, LevelAndActIDs_TwinklePark3, Characters_Amy, Kiki, 40005}, //DX
        {-89.04f, 3.99f, -558.23f, LevelAndActIDs_TwinklePark3, Characters_Amy, Kiki, 40005}, //DC
        {203.54f, 4.00f, -99.29f, LevelAndActIDs_TwinklePark3, Characters_Amy, Kiki, 40006}, //DX
        {204.35f, 4.00f, -98.70f, LevelAndActIDs_TwinklePark3, Characters_Amy, Kiki, 40006}, //DC
        {796.20f, -35.00f, -451.74f, LevelAndActIDs_TwinklePark3, Characters_Amy, Buyon, 40007},
        {-85.46f, 105.00f, 487.88f, LevelAndActIDs_TwinklePark3, Characters_Amy, Kiki, 40008}, //DX
        {-85.00f, 104.00f, 486.99f, LevelAndActIDs_TwinklePark3, Characters_Amy, Kiki, 40008}, //DC
        {124.76f, 100.00f, 675.01f, LevelAndActIDs_TwinklePark3, Characters_Amy, Buyon, 40009},
        {87.39f, 100.00f, 691.81f, LevelAndActIDs_TwinklePark3, Characters_Amy, Buyon, 40010},
        {583.34f, 256.02f, -366.16f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40011}, //DX
        {569.57f, 254.02f, -380.67f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40011}, //DC
        {543.06f, 256.02f, -334.05f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40012}, //DX
        {537.77f, 254.02f, -348.08f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40012}, //DC
        {518.45f, 256.02f, -303.80f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40013}, //DX
        {504.05f, 254.02f, -289.92f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40013}, //DC
        {274.99f, 272.02f, -302.59f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40014}, //DX
        {266.85f, 272.02f, -298.75f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40014}, //DC
        {712.42f, 103.85f, 374.58f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40015}, //DX
        {711.95f, 103.85f, 373.70f, LevelAndActIDs_TwinklePark2, Characters_Amy, Kiki, 40015}, //DC
        {570.10f, 100.02f, 406.06f, LevelAndActIDs_TwinklePark2, Characters_Amy, Buyon, 40016},

        {68.07f, 6.00f, -454.61f, LevelAndActIDs_TwinklePark2, Characters_Big, Kiki, 60001}, //DX
        {68.07f, 4.00f, -454.61f, LevelAndActIDs_TwinklePark2, Characters_Big, Kiki, 60001}, //DC
        {165.72f, 6.00f, -887.51f, LevelAndActIDs_TwinklePark2, Characters_Big, Kiki, 60002},
        {660.64f, 6.00f, -561.42f, LevelAndActIDs_TwinklePark2, Characters_Big, Kiki, 60003}, //DX
        {660.64f, 4.00f, -561.42f, LevelAndActIDs_TwinklePark2, Characters_Big, Kiki, 60003}, //DC
        {322.83f, 6.00f, -985.34f, LevelAndActIDs_TwinklePark2, Characters_Big, Kiki, 60004},

        {2238.86f, -1353.74f, 702.69f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, Spinner, 15001},
        {2242.16f, -1353.74f, 835.26f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, Spinner, 15002},
        {2386.12f, -1287.96f, 720.86f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, Spinner, 15003},
        {2386.27f, -1287.96f, 807.07f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, Spinner, 15004},
        {1905.58f, -1317.00f, 1829.89f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15005}, //DX
        {1905.58f, -1326.00f, 1829.89f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15005}, //DC
        {1902.47f, -1317.00f, 1916.31f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15006},
        {1974.44f, -1314.00f, 1902.25f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, Spinner, 15007},
        {1902.45f, -1317.00f, 2021.69f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15008}, //DX
        {1902.45f, -1326.00f, 2021.69f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15008}, //DC
        {1940.67f, -1314.00f, 2021.50f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, Spinner, 15009},
        {3659.03f, -1422.00f, -226.08f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, SpikySpinner, 15010},
        {3855.70f, -1360.03f, 190.91f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15011},
        {3999.61f, -1418.00f, -251.88f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, SpikySpinner, 15012},
        {4063.51f, -1665.00f, 1682.75f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, SpikySpinner, 15013},
        {2600.07f, -2015.00f, 3745.23f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15014},
        {4558.23f, -1372.00f, -67.18f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15015},
        {4557.01f, -1372.00f, -178.73f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15016},
        {4589.17f, -1356.00f, -280.92f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, Spinner, 15017},
        {4635.70f, -1356.00f, -31.89f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, Spinner, 15018},
        {2864.16f, -2015.00f, 3676.78f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15019},
        {2801.76f, -2015.00f, 3860.93f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15020},
        {3156.90f, -2015.00f, 3678.87f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15021}, //DX
        {3156.90f, -2021.00f, 3678.87f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15021}, //DC
        {3082.82f, -2015.00f, 3773.65f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15022},
        {3078.14f, -2015.00f, 3862.94f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15023}, //DX
        {3078.14f, -2021.00f, 3862.94f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15023}, //DC
        {3923.75f, -1311.76f, 3828.35f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, Spinner, 15024},
        {3956.97f, -1335.76f, 3879.56f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, Spinner, 15025},
        {3998.51f, -1351.76f, 3923.08f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, Spinner, 15026},
        {4051.44f, -1385.76f, 3944.83f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, Spinner, 15027},
        {4101.71f, -1419.18f, 3973.65f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, Spinner, 15028},
        {4148.65f, -1446.76f, 4012.70f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, Spinner, 15029},
        {4179.59f, -1470.76f, 4060.56f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, Spinner, 15030},
        {4239.51f, -1889.26f, 4190.74f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15031},
        {4378.04f, -1858.98f, 4084.22f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, Spinner, 15032},
        {4328.01f, -1889.26f, 4170.71f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15033},
        {4346.98f, -1889.26f, 4259.18f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, CopSpeeder, 15034},
        {88.53f, 3.43f, -87.53f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, CopSpeeder, 15035},
        {53.53f, 3.43f, -87.53f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, CopSpeeder, 15036},
        {-201.50f, 7.56f, -269.79f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, ElectroSpinner, 15037},
        {-103.78f, 3.56f, -330.75f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, ElectroSpinner, 15038},
        {-330.74f, 19.43f, -558.42f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, Spinner, 15039},
        {-358.65f, 74.43f, -918.45f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, Spinner, 15040},
        {-845.43f, 38.92f, -864.73f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, CopSpeeder, 15041},
        {-43.32f, 2.92f, -1438.94f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, CopSpeeder, 15042},
        {-649.72f, 22.92f, -1291.16f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, CopSpeeder, 15043},
        {-1158.87f, 74.92f, -977.14f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, CopSpeeder, 15044},
        {-1498.36f, 114.92f, -872.50f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, CopSpeeder, 15045},
        {-1278.33f, 80.92f, -1290.84f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, CopSpeeder, 15046},
        {-1701.65f, 103.92f, -1015.31f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, CopSpeeder, 15047},
        {-1742.79f, 114.92f, -1356.76f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, CopSpeeder, 15048},

        {2238.86f, -1353.74f, 702.69f, LevelAndActIDs_SpeedHighway1, Characters_Tails, Spinner, 24001},
        {2242.16f, -1353.74f, 835.26f, LevelAndActIDs_SpeedHighway1, Characters_Tails, Spinner, 24002},
        {2386.12f, -1287.96f, 720.86f, LevelAndActIDs_SpeedHighway1, Characters_Tails, Spinner, 24003},
        {2386.27f, -1287.96f, 807.07f, LevelAndActIDs_SpeedHighway1, Characters_Tails, Spinner, 24004},
        {3659.03f, -1422.00f, -226.08f, LevelAndActIDs_SpeedHighway1, Characters_Tails, SpikySpinner, 24005},
        {3565.09f, -1325.32f, 1356.11f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24006},
        {3568.86f, -1325.32f, 1462.95f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24007},
        {3855.70f, -1360.03f, 190.91f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24008},
        {3999.61f, -1418.00f, -251.88f, LevelAndActIDs_SpeedHighway1, Characters_Tails, SpikySpinner, 24009},
        {4063.51f, -1665.00f, 1682.75f, LevelAndActIDs_SpeedHighway1, Characters_Tails, SpikySpinner, 24010},
        {2600.07f, -2015.00f, 3745.23f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24011},
        {4558.23f, -1372.00f, -67.18f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24012},
        {4557.01f, -1372.00f, -178.73f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24013},
        {3532.16f, -1489.98f, 3109.60f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24014},
        {4589.17f, -1356.00f, -280.92f, LevelAndActIDs_SpeedHighway1, Characters_Tails, Spinner, 24015},
        {4635.70f, -1356.00f, -31.89f, LevelAndActIDs_SpeedHighway1, Characters_Tails, Spinner, 24016},
        {2864.16f, -2015.00f, 3676.78f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24017},
        {2801.76f, -2015.00f, 3860.93f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24018},
        {3156.90f, -2015.00f, 3678.87f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24019}, //DX
        {3156.90f, -2021.00f, 3678.87f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24019}, //DC
        {3082.82f, -2015.00f, 3773.65f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24020},
        {3078.14f, -2015.00f, 3862.94f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24021}, //DX
        {3078.14f, -2021.00f, 3862.94f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24021}, //DC
        {4239.51f, -1889.26f, 4190.74f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24022},
        {4328.01f, -1889.26f, 4170.71f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24023},
        {4346.98f, -1889.26f, 4259.18f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24024},
        {6065.16f, -1940.02f, 5376.01f, LevelAndActIDs_SpeedHighway1, Characters_Tails, SpikySpinner, 24025},
        {6092.91f, -1940.02f, 5443.40f, LevelAndActIDs_SpeedHighway1, Characters_Tails, SpikySpinner, 24026},
        {6162.83f, -1940.02f, 5361.14f, LevelAndActIDs_SpeedHighway1, Characters_Tails, SpikySpinner, 24027},
        {6752.76f, -1988.12f, 6556.21f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24028},
        {5234.11f, -2325.00f, 7913.96f, LevelAndActIDs_SpeedHighway1, Characters_Tails, SpikySpinner, 24029},
        {5421.58f, -2318.00f, 7954.07f, LevelAndActIDs_SpeedHighway1, Characters_Tails, SpikySpinner, 24030},
        {6586.68f, -1988.12f, 7246.36f, LevelAndActIDs_SpeedHighway1, Characters_Tails, CopSpeeder, 24031},

        {-43.32f, 2.92f, -1438.94f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, CopSpeeder, 30001},
        {-649.72f, 22.92f, -1291.16f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, CopSpeeder, 30002},
        {-20.85f, 2.92f, -1034.02f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, CopSpeeder, 30003},
        {-70.81f, 207.81f, -930.16f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, Spinner, 30004},
        {-753.86f, 216.36f, -1092.37f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, SpikySpinner, 30005},
        {-845.43f, 38.92f, -864.73f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, CopSpeeder, 30006},
        {-1278.33f, 80.92f, -1290.84f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, CopSpeeder, 30007},
        {-139.13f, 146.36f, -578.40f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, SpikySpinner, 30008},
        {-1158.87f, 74.92f, -977.14f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, CopSpeeder, 30009},
        {-1391.75f, 296.36f, -1179.12f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, SpikySpinner, 30010},
        {-229.12f, 43.56f, -288.38f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, ElectroSpinner, 30011},
        {-103.80f, 21.56f, -294.30f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, ElectroSpinner, 30012},
        {-1498.36f, 114.92f, -872.50f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, CopSpeeder, 30013},
        {-1742.79f, 114.92f, -1356.76f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, CopSpeeder, 30014},
        {-1656.19f, 254.36f, -1083.73f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, SpikySpinner, 30015},
        {67.70f, 3.43f, -87.48f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, CopSpeeder, 30016},


        {-118.27f, 57.67f, 590.19f, LevelAndActIDs_RedMountain1, Characters_Sonic, Kiki, 16001}, //DX
        {-118.27f, 58.37f, 590.19f, LevelAndActIDs_RedMountain1, Characters_Sonic, Kiki, 16001}, //DC
        {-102.97f, 77.87f, 552.55f, LevelAndActIDs_RedMountain1, Characters_Sonic, Kiki, 16002}, //DX
        {-102.97f, 78.87f, 552.55f, LevelAndActIDs_RedMountain1, Characters_Sonic, Kiki, 16002}, //DC
        {-145.27f, 37.37f, 647.86f, LevelAndActIDs_RedMountain1, Characters_Sonic, Kiki, 16003}, //DX
        {-145.27f, 36.37f, 647.86f, LevelAndActIDs_RedMountain1, Characters_Sonic, Kiki, 16003}, //DC
        {-105.57f, 45.16f, 396.78f, LevelAndActIDs_RedMountain1, Characters_Sonic, Gola, 16004},
        {52.16f, 518.31f, 562.97f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16005},
        {51.36f, 523.31f, 523.84f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16006},
        {-55.70f, 545.70f, 672.85f, LevelAndActIDs_RedMountain1, Characters_Sonic, Kiki, 16007}, //DX
        {-55.70f, 545.62f, 672.85f, LevelAndActIDs_RedMountain1, Characters_Sonic, Kiki, 16007}, //DC
        {-206.70f, 928.62f, 18.85f, LevelAndActIDs_RedMountain1, Characters_Sonic, Kiki, 16008},
        {75.32f, 988.42f, -118.25f, LevelAndActIDs_RedMountain1, Characters_Sonic, Gola, 16009},
        {-34.59f, 1084.09f, -40.96f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16010},
        {-74.11f, 1084.09f, -112.26f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16011},
        {-878.09f, 866.93f, -940.67f, LevelAndActIDs_RedMountain1, Characters_Sonic, Gola, 16012},
        {-2994.64f, 161.49f, -1388.64f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16013},
        {-2984.10f, 137.49f, -1406.55f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16014},
        {-3172.22f, 457.64f, -1270.04f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16015},
        {-3214.98f, 454.00f, -1233.59f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16016},
        {-3274.66f, 454.00f, -1251.58f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16017},
        {-3317.32f, 454.00f, -1210.60f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16018},
        {-3282.50f, 158.38f, -1500.64f, LevelAndActIDs_RedMountain1, Characters_Sonic, Kiki, 16019},
        {-3251.29f, 766.32f, -1581.19f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16020},
        {-3339.85f, 158.38f, -1573.27f, LevelAndActIDs_RedMountain1, Characters_Sonic, Kiki, 16021}, //DX
        {-3339.85f, 161.38f, -1573.27f, LevelAndActIDs_RedMountain1, Characters_Sonic, Kiki, 16021}, //DC
        {-3536.73f, 381.00f, -1489.59f, LevelAndActIDs_RedMountain1, Characters_Sonic, Gola, 16022},
        {-3697.63f, 405.51f, -1801.91f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16023},
        {-3723.72f, 380.51f, -1793.37f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16024},
        {-3759.29f, 407.51f, -1780.18f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16025},
        {-3807.46f, 443.51f, -1717.80f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16026},
        {-3784.29f, 422.51f, -1779.85f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16027},
        {-3781.81f, 435.51f, -1787.10f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16028},
        {-3801.93f, 403.51f, -1785.33f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16029},
        {-3843.96f, 467.51f, -1803.13f, LevelAndActIDs_RedMountain1, Characters_Sonic, Spinner, 16030},
        {-4001.92f, 581.37f, -1831.20f, LevelAndActIDs_RedMountain1, Characters_Sonic, Gola, 16031}, //DX
        {-3873.77f, 594.07f, -1806.53f, LevelAndActIDs_RedMountain1, Characters_Sonic, Gola, 16031}, //DC
        {-3932.06f, 1138.58f, -1932.72f, LevelAndActIDs_RedMountain1, Characters_Sonic, Kiki, 16032},
        {-1106.40f, 529.74f, 2077.08f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16033},
        {-1119.21f, 526.74f, 2034.03f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16034},
        {-1118.80f, 543.74f, 2116.72f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16035},
        {-186.39f, 162.87f, 727.24f, LevelAndActIDs_RedMountain2, Characters_Sonic, Gola, 16036},
        {-1072.66f, 306.72f, 1127.21f, LevelAndActIDs_RedMountain2, Characters_Sonic, Gola, 16037},
        {-1113.24f, 286.72f, 1151.29f, LevelAndActIDs_RedMountain2, Characters_Sonic, Gola, 16038},
        {-1408.08f, 439.01f, 1645.99f, LevelAndActIDs_RedMountain2, Characters_Sonic, Kiki, 16039},
        {-1486.02f, 439.01f, 1663.27f, LevelAndActIDs_RedMountain2, Characters_Sonic, Kiki, 16040},
        {-1056.85f, 302.20f, 614.94f, LevelAndActIDs_RedMountain2, Characters_Sonic, Gola, 16041},
        {-1480.65f, 444.12f, 773.75f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16042},
        {-1469.75f, 433.12f, 738.30f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16043},
        {-1479.59f, 423.12f, 713.27f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16044},
        {-1898.55f, 272.52f, 1479.17f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16045},
        {-1901.36f, 438.23f, 982.26f, LevelAndActIDs_RedMountain2, Characters_Sonic, Kiki, 16046},
        {-2034.97f, 258.52f, 1416.83f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16047},
        {-2057.54f, 258.52f, 1448.72f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16048},
        {-2060.58f, 258.52f, 1411.26f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16049},
        {-1942.72f, 438.23f, 975.09f, LevelAndActIDs_RedMountain2, Characters_Sonic, Kiki, 16050},
        {-1756.76f, 170.00f, 607.26f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16051},
        {-1824.22f, 180.00f, 632.07f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16052},
        {-1795.67f, 175.00f, 594.86f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16053},
        {-2227.86f, 258.52f, 1401.49f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16054},
        {-2249.64f, 258.52f, 1355.47f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16055},
        {-1932.18f, 186.00f, 671.41f, LevelAndActIDs_RedMountain2, Characters_Sonic, Kiki, 16056},
        {-1906.08f, 186.00f, 609.62f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16057},
        {-1930.32f, 444.48f, 485.50f, LevelAndActIDs_RedMountain2, Characters_Sonic, Kiki, 16058},
        {-2004.25f, 447.23f, 524.97f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16059},
        {-2067.65f, 461.23f, 561.00f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16060},
        {-2369.89f, 258.52f, 1315.16f, LevelAndActIDs_RedMountain2, Characters_Sonic, Spinner, 16061},

        {-3214.98f, 454.00f, -1233.59f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Spinner, 32001},
        {-3274.66f, 454.00f, -1251.58f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Spinner, 32002},
        {-3317.32f, 454.00f, -1210.60f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Spinner, 32003},
        {-3518.36f, 404.37f, -1445.95f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Spinner, 32004},
        {-2691.88f, 543.91f, -1524.21f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Kiki, 32005}, //DX
        {-2691.88f, 545.91f, -1524.21f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Kiki, 32005}, //DC
        {-3547.60f, 412.37f, -1481.48f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Spinner, 32006},
        {-3607.03f, 466.37f, -1389.01f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Spinner, 32007},
        {-2949.62f, 118.49f, -1462.17f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Spinner, 32008},
        {-3390.69f, 138.23f, -1534.23f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Gola, 32009},
        {-2901.37f, 53.37f, -1616.52f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Spinner, 32010},
        {-3826.61f, 1085.04f, -1842.77f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Kiki, 32011},
        {-3494.02f, 501.37f, -2153.79f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Spinner, 32012},
        {-3693.75f, 1268.66f, -2014.14f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Spinner, 32013},
        {-4001.92f, 581.37f, -1831.20f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Gola, 32014},
        {-3658.23f, 1268.66f, -2126.34f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Spinner, 32015},
        {-2514.94f, 64.21f, -1837.96f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Spinner, 32016},
        {-3757.22f, 1154.66f, -2248.79f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Spinner, 32017},
        {-3663.04f, 1117.66f, -2322.18f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Kiki, 32018}, //DX
        {-3663.04f, 1119.66f, -2322.18f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Kiki, 32018}, //DC
        {-3781.63f, 1160.66f, -2232.32f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Spinner, 32019},
        {-3947.98f, 1220.04f, -2137.93f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Kiki, 32020},
        {-2276.92f, 65.37f, -1853.73f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Spinner, 32021},
        {-2240.40f, 55.93f, -1921.60f, LevelAndActIDs_RedMountain3, Characters_Knuckles, Kiki, 32022},

        {-307.15f, 574.43f, 1581.80f, LevelAndActIDs_RedMountain2, Characters_Gamma, Kiki, 53001},
        {-387.12f, 547.43f, 1562.41f, LevelAndActIDs_RedMountain2, Characters_Gamma, Kiki, 53002},
        {-390.58f, 373.43f, 1339.84f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53003},
        {-405.56f, 337.43f, 1325.24f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53004},
        {-379.60f, 336.43f, 1299.16f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53005},
        {-395.43f, 337.43f, 1268.63f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53006},
        {-305.70f, 192.80f, 921.48f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53007},
        {-292.32f, 174.01f, 827.76f, LevelAndActIDs_RedMountain2, Characters_Gamma, Kiki, 53008},
        {-212.62f, 160.41f, 817.80f, LevelAndActIDs_RedMountain2, Characters_Gamma, Kiki, 53009},
        {-158.97f, 157.21f, 771.06f, LevelAndActIDs_RedMountain2, Characters_Gamma, Kiki, 53010},
        {-234.63f, 166.32f, 759.20f, LevelAndActIDs_RedMountain2, Characters_Gamma, Kiki, 53011},
        {-292.08f, 201.01f, 699.69f, LevelAndActIDs_RedMountain2, Characters_Gamma, Kiki, 53012},
        {-1572.18f, 54.34f, 1619.20f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53013},
        {-1612.72f, 68.21f, 1848.19f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53014},
        {-214.35f, 221.80f, 290.65f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53015},
        {-1285.41f, 284.60f, 742.68f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53016},
        {-226.45f, 233.80f, 250.42f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53017},
        {-227.79f, 197.80f, 262.57f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53018},
        {-198.82f, 248.80f, 230.17f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53019},
        {-1289.11f, 269.60f, 716.79f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53020},
        {-1675.39f, 92.90f, 2290.92f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53021},
        {-205.57f, 206.80f, 236.90f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53022},
        {-1724.23f, 105.90f, 2250.72f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53023},
        {-1666.59f, 143.77f, 1312.34f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53024},
        {-1686.70f, 143.77f, 1363.54f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53025},
        {-1017.06f, 221.19f, 366.05f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53026},
        {-989.02f, 229.19f, 345.36f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53027},
        {-980.27f, 199.19f, 328.65f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53028},
        {-1012.74f, 203.19f, 340.59f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53029},
        {-1514.25f, 171.57f, 622.81f, LevelAndActIDs_RedMountain2, Characters_Gamma, Kiki, 53030},
        {-1872.62f, 98.90f, 2587.91f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53031},
        {-1875.14f, 113.90f, 2611.16f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53032},
        {-1917.08f, 130.99f, 1270.75f, LevelAndActIDs_RedMountain2, Characters_Gamma, Kiki, 53033},
        {-1546.91f, 171.57f, 604.22f, LevelAndActIDs_RedMountain2, Characters_Gamma, Kiki, 53034},
        {-1522.62f, 167.77f, 568.59f, LevelAndActIDs_RedMountain2, Characters_Gamma, Kiki, 53035},
        {-1956.86f, 96.90f, 2562.43f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53036},
        {-1961.67f, 76.90f, 2580.04f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53037},
        {-1991.32f, 184.77f, 1210.32f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53038},
        {-1970.55f, 160.77f, 1161.36f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53039},
        {-1998.07f, 149.77f, 1183.84f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53040},
        {-1821.91f, 168.62f, 653.27f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53041},
        {-1954.66f, 175.30f, 771.49f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53042},
        {-1993.30f, 249.30f, 758.33f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53043},
        {-1957.66f, 168.30f, 678.41f, LevelAndActIDs_RedMountain2, Characters_Gamma, Kiki, 53044},
        {-1946.08f, 167.90f, 631.53f, LevelAndActIDs_RedMountain2, Characters_Gamma, Kiki, 53045},
        {-2427.11f, 181.00f, 780.85f, LevelAndActIDs_RedMountain2, Characters_Gamma, Kiki, 53046},
        {-2609.23f, 175.99f, 1038.43f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53047},
        {-2597.82f, 140.99f, 984.99f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53048},
        {-2629.84f, 165.99f, 974.42f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53049},
        {-2657.98f, 175.99f, 997.54f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53050},
        {-2635.87f, 150.99f, 931.62f, LevelAndActIDs_RedMountain2, Characters_Gamma, Spinner, 53051},

        {48.72f, -330.01f, 1054.67f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17001},
        {13.69f, -330.01f, 1103.86f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17002},
        {422.90f, -233.01f, 1017.82f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17003},
        {65.05f, -330.01f, 1139.16f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17004},
        {6.46f, -330.01f, 1162.34f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17005},
        {379.62f, -233.01f, 1085.51f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17006},
        {-40.41f, -330.01f, 1206.02f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17007},
        {8.98f, -330.01f, 1251.40f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17008},
        {260.47f, -495.01f, 2535.07f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17009},
        {310.47f, -510.32f, 2561.07f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17010},
        {210.47f, -480.01f, 2590.07f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17011},
        {757.91f, -568.43f, 3060.70f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17012},
        {807.91f, -568.43f, 3120.70f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17013},
        {359.83f, -450.00f, 3735.31f, LevelAndActIDs_SkyDeck1, Characters_Sonic, ElectroSpinner, 17014},
        {259.98f, -444.21f, 3748.42f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17015},
        {423.74f, -450.00f, 3735.89f, LevelAndActIDs_SkyDeck1, Characters_Sonic, ElectroSpinner, 17016},
        {169.84f, -444.31f, 3784.24f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17017},
        {174.22f, -444.21f, 3864.43f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17018},
        {262.63f, -444.71f, 3891.91f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17019},
        {429.01f, -587.02f, 4366.35f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17020},
        {375.00f, -573.02f, 4405.44f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17021},
        {722.63f, -324.00f, 4597.13f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17022},
        {681.95f, -337.00f, 4609.88f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17023},
        {763.95f, -337.00f, 4609.88f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17024},
        {801.74f, -324.00f, 4609.81f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17025},
        {841.76f, -337.00f, 4609.46f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17026},
        {413.68f, -442.00f, 4769.43f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17027},
        {383.68f, -442.00f, 4809.43f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17028},
        {399.71f, -567.00f, 4810.81f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17029},
        {399.97f, -434.00f, 4860.83f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17030},
        {399.71f, -557.00f, 4860.81f, LevelAndActIDs_SkyDeck1, Characters_Sonic, Spinner, 17031},
        {524.10f, -90.00f, 910.58f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17032},
        {604.10f, -90.00f, 910.58f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17033},
        {564.10f, -90.00f, 890.58f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17034},
        {684.10f, -90.00f, 910.58f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17035},
        {644.10f, -90.00f, 890.58f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17036},
        {724.10f, -90.00f, 890.58f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17037},
        {-524.43f, 10.00f, 978.70f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17038},
        {-564.43f, 10.00f, 998.70f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17039},
        {-604.43f, 10.00f, 978.70f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17040},
        {-644.43f, 10.00f, 998.70f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17041},
        {272.44f, -63.92f, 608.68f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17042},
        {296.76f, -66.92f, 577.26f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17043},
        {266.42f, -66.92f, 546.59f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17044},
        {296.76f, -66.92f, 511.26f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17045},
        {264.15f, -66.92f, 472.25f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17046},
        {296.76f, -66.92f, 448.26f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17047},
        {296.76f, -66.92f, 178.26f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17048},
        {266.76f, -66.92f, 148.26f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17049},
        {296.76f, -66.92f, 108.26f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17050},
        {266.76f, -66.92f, 78.26f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17051},
        {296.76f, -66.92f, 46.26f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ElectroSpinner, 17052},
        {-1023.65f, 4.00f, 163.89f, LevelAndActIDs_SkyDeck3, Characters_Sonic, ElectroSpinner, 17053},
        {-1020.31f, 16.00f, 1.15f, LevelAndActIDs_SkyDeck3, Characters_Sonic, SpikySpinner, 17054},
        {-1077.07f, -85.00f, 161.93f, LevelAndActIDs_SkyDeck3, Characters_Sonic, ElectroSpinner, 17055},
        {-656.97f, -100.00f, -326.89f, LevelAndActIDs_SkyDeck3, Characters_Sonic, ElectroSpinner, 17056},
        {-793.19f, -100.00f, -332.40f, LevelAndActIDs_SkyDeck3, Characters_Sonic, ElectroSpinner, 17057},
        {-1027.15f, -100.00f, -238.31f, LevelAndActIDs_SkyDeck3, Characters_Sonic, ElectroSpinner, 17058},
        {422.90f, -233.01f, 1017.82f, LevelAndActIDs_SkyDeck1, Characters_Tails, Spinner, 23001},
        {379.62f, -233.01f, 1085.51f, LevelAndActIDs_SkyDeck1, Characters_Tails, Spinner, 23002},
        {415.69f, -450.01f, 3733.29f, LevelAndActIDs_SkyDeck1, Characters_Tails, Spinner, 23003},
        {232.22f, -450.21f, 3753.11f, LevelAndActIDs_SkyDeck1, Characters_Tails, Spinner, 23004},
        {244.69f, -450.01f, 3887.99f, LevelAndActIDs_SkyDeck1, Characters_Tails, Spinner, 23005},
        {681.95f, -337.00f, 4609.88f, LevelAndActIDs_SkyDeck1, Characters_Tails, Spinner, 23006},
        {763.95f, -337.00f, 4609.88f, LevelAndActIDs_SkyDeck1, Characters_Tails, Spinner, 23007},
        {841.76f, -337.00f, 4609.46f, LevelAndActIDs_SkyDeck1, Characters_Tails, Spinner, 23008},
        {1006.24f, -324.00f, 4609.61f, LevelAndActIDs_SkyDeck1, Characters_Tails, SpikySpinner, 23009},

        {678.16f, -94.00f, 208.07f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, ElectroSpinner, 34001},
        {694.78f, -94.00f, -208.01f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, ElectroSpinner, 34002},
        {378.24f, -53.00f, -101.25f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, ElectroSpinner, 34003},
        {375.55f, -53.00f, -135.38f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, ElectroSpinner, 34004},
        {338.66f, -64.00f, 8.85f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, Spinner, 34005},
        {318.20f, -46.00f, -7.04f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, ElectroSpinner, 34006},
        {339.45f, -76.00f, -30.14f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, Spinner, 34007},
        {298.66f, -54.00f, -31.15f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, Spinner, 34008},
        {298.66f, -74.00f, 8.85f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, Spinner, 34009},
        {180.62f, -53.00f, 185.96f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, ElectroSpinner, 34010},
        {180.82f, -53.00f, 221.31f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, ElectroSpinner, 34011},
        {-101.71f, 0.00f, 278.26f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, ElectroSpinner, 34012},
        {-106.32f, 0.00f, -260.70f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, ElectroSpinner, 34013},
        {-656.97f, -100.00f, -326.89f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, ElectroSpinner, 34014},
        {-793.19f, -100.00f, -332.40f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, ElectroSpinner, 34015},
        {-786.90f, -184.00f, -350.03f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, ElectroSpinner, 34016},


        {-42.44f, -33.98f, -165.24f, LevelAndActIDs_LostWorld1, Characters_Sonic, BoaBoa, 18001},
        {80.85f, -81.00f, -137.54f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18002}, //DX
        {80.85f, -86.00f, -137.54f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18002}, //DC
        {132.58f, -73.00f, 98.30f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18003}, //DX
        {132.58f, -80.00f, 98.30f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18003}, //DC
        {77.06f, -28.00f, 199.77f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18004}, //DX
        {77.06f, -34.00f, 199.77f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18004}, //DC
        {4459.89f, -2729.00f, 1337.04f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18005},
        {5213.02f, -2673.00f, 1243.67f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18006}, //DX
        {5213.02f, -2678.00f, 1243.67f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18006}, //DC
        {5454.85f, -2546.00f, 983.92f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18007},
        {5743.55f, -2673.00f, 1051.82f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18008}, //DX
        {5743.55f, -2678.00f, 1051.82f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18008}, //DC
        {5598.13f, -2674.00f, 1683.36f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18009},
        {5856.45f, -2457.01f, 1472.63f, LevelAndActIDs_LostWorld1, Characters_Sonic, Gola, 18010}, //DX
        {5856.45f, -2457.01f, 1472.63f, LevelAndActIDs_LostWorld1, Characters_Sonic, Gola, 18010}, //DC
        {5847.13f, -2674.00f, 1501.81f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18011}, //DX
        {5847.13f, -2674.00f, 1501.81f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18011}, //DC
        {5870.85f, -2674.00f, 1412.47f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18012}, //DX
        {5870.85f, -2674.00f, 1412.47f, LevelAndActIDs_LostWorld1, Characters_Sonic, Leon, 18012}, //DC
        {261.89f, 135.01f, -60.93f, LevelAndActIDs_LostWorld2, Characters_Sonic, Gola, 18013},
        {462.41f, 156.01f, 600.37f, LevelAndActIDs_LostWorld2, Characters_Sonic, Gola, 18014},
        {357.45f, 152.00f, 1438.32f, LevelAndActIDs_LostWorld2, Characters_Sonic, Leon, 18015}, //DX
        {357.45f, 147.00f, 1438.32f, LevelAndActIDs_LostWorld2, Characters_Sonic, Leon, 18015}, //DC
        {319.85f, 152.00f, 1511.19f, LevelAndActIDs_LostWorld2, Characters_Sonic, Leon, 18016}, //DX
        {319.85f, 147.00f, 1511.19f, LevelAndActIDs_LostWorld2, Characters_Sonic, Leon, 18016}, //DC
        {7141.35f, -2331.96f, 785.31f, LevelAndActIDs_LostWorld2, Characters_Sonic, Gola, 18017},
        {7352.91f, -2661.96f, 976.08f, LevelAndActIDs_LostWorld2, Characters_Sonic, Gola, 18018},
        {7441.25f, -2685.96f, 704.31f, LevelAndActIDs_LostWorld2, Characters_Sonic, Leon, 18019}, //DX
        {7441.25f, -2697.96f, 704.31f, LevelAndActIDs_LostWorld2, Characters_Sonic, Leon, 18019}, //DC
        {7482.70f, -2671.96f, 731.77f, LevelAndActIDs_LostWorld2, Characters_Sonic, Gola, 18020},
        {7290.57f, -2666.00f, 1369.67f, LevelAndActIDs_LostWorld2, Characters_Sonic, BoaBoa, 18021},
        {7602.73f, -2593.79f, 674.61f, LevelAndActIDs_LostWorld2, Characters_Sonic, Leon, 18022},
        {7644.03f, -2685.96f, 894.60f, LevelAndActIDs_LostWorld2, Characters_Sonic, Leon, 18023}, //DX
        {7644.03f, -2694.96f, 894.60f, LevelAndActIDs_LostWorld2, Characters_Sonic, Leon, 18023}, //DC

        {7375.19f, -2665.96f, 940.11f, LevelAndActIDs_LostWorld2, Characters_Knuckles, Leon, 33001},
        {7644.03f, -2682.96f, 894.60f, LevelAndActIDs_LostWorld2, Characters_Knuckles, Leon, 33002}, //DX
        {7644.03f, -2693.96f, 894.60f, LevelAndActIDs_LostWorld2, Characters_Knuckles, Leon, 33002}, //DC
        {7441.25f, -2680.96f, 704.31f, LevelAndActIDs_LostWorld2, Characters_Knuckles, Leon, 33003}, //DX
        {7441.25f, -2693.96f, 704.31f, LevelAndActIDs_LostWorld2, Characters_Knuckles, Leon, 33003}, //DC
        {7597.67f, -2589.79f, 709.35f, LevelAndActIDs_LostWorld2, Characters_Knuckles, Leon, 33004}, //DX
        {7597.67f, -2593.79f, 709.35f, LevelAndActIDs_LostWorld2, Characters_Knuckles, Leon, 33004}, //DC
        {7251.10f, -2669.96f, 1065.83f, LevelAndActIDs_LostWorld2, Characters_Knuckles, Leon, 33005}, //DX
        {7251.10f, -2673.96f, 1065.83f, LevelAndActIDs_LostWorld2, Characters_Knuckles, Leon, 33005}, //DC
        {7526.26f, -2379.00f, 720.66f, LevelAndActIDs_LostWorld2, Characters_Knuckles, Gola, 33006},
        {7771.88f, -2427.00f, 955.95f, LevelAndActIDs_LostWorld2, Characters_Knuckles, Gola, 33007},
        {7127.74f, -2328.00f, 781.67f, LevelAndActIDs_LostWorld2, Characters_Knuckles, Gola, 33008},
        {7290.57f, -2700.00f, 1369.67f, LevelAndActIDs_LostWorld2, Characters_Knuckles, Gola, 33009},
        {7055.46f, -2329.96f, 819.02f, LevelAndActIDs_LostWorld2, Characters_Knuckles, Leon, 33010}, //DX
        {7055.46f, -2339.96f, 819.02f, LevelAndActIDs_LostWorld2, Characters_Knuckles, Leon, 33010}, //DC

        {1436.74f, -26.36f, 1144.80f, LevelAndActIDs_IceCap1, Characters_Sonic, IceBall, 13001},
        {517.95f, 41.54f, 945.41f, LevelAndActIDs_IceCap1, Characters_Sonic, IceBall, 13002},
        {509.80f, 42.28f, 961.87f, LevelAndActIDs_IceCap1, Characters_Sonic, IceBall, 13003}, //DX
        {509.80f, 33.28f, 961.87f, LevelAndActIDs_IceCap1, Characters_Sonic, IceBall, 13003}, //DC
        {1328.80f, 27.68f, -109.74f, LevelAndActIDs_IceCap2, Characters_Sonic, BoaBoa, 13004},
        {1387.97f, -18.11f, -154.65f, LevelAndActIDs_IceCap2, Characters_Sonic, IceBall, 13005}, //DX
        {1298.29f, 183.56f, -323.83f, LevelAndActIDs_IceCap2, Characters_Sonic, IceBall, 13005}, //DC
        {1298.29f, 186.56f, -323.83f, LevelAndActIDs_IceCap2, Characters_Sonic, IceBall, 13006}, //DX
        {1298.29f, 183.56f, -323.83f, LevelAndActIDs_IceCap2, Characters_Sonic, IceBall, 13006}, //DC

        {-246.47f, -1808.00f, 2853.75f, LevelAndActIDs_Casinopolis2, Characters_Sonic, Spinner, 12001},
        {-290.29f, -1769.00f, 2884.71f, LevelAndActIDs_Casinopolis2, Characters_Sonic, Spinner, 12002},
        {-318.35f, -1734.00f, 2868.71f, LevelAndActIDs_Casinopolis2, Characters_Sonic, Spinner, 12003},
        {-536.62f, -1720.00f, 2857.20f, LevelAndActIDs_Casinopolis2, Characters_Sonic, Spinner, 12004},
        {-605.14f, -1664.00f, 2886.06f, LevelAndActIDs_Casinopolis2, Characters_Sonic, Spinner, 12005},
        {-663.19f, -1614.00f, 2859.65f, LevelAndActIDs_Casinopolis2, Characters_Sonic, Spinner, 12006},
        {-1170.38f, -1627.90f, 2635.53f, LevelAndActIDs_Casinopolis2, Characters_Sonic, Spinner, 12007},
        {-1177.75f, -1719.90f, 2642.70f, LevelAndActIDs_Casinopolis2, Characters_Sonic, Spinner, 12008},
        {-1183.29f, -1970.90f, 2639.81f, LevelAndActIDs_Casinopolis2, Characters_Sonic, Spinner, 12009},
        {-1183.89f, -2030.90f, 2642.74f, LevelAndActIDs_Casinopolis2, Characters_Sonic, Spinner, 12010},

        {-318.35f, -1734.00f, 2868.71f, LevelAndActIDs_Casinopolis2, Characters_Tails, Spinner, 21001},
        {-428.93f, -1721.00f, 2884.10f, LevelAndActIDs_Casinopolis2, Characters_Tails, Spinner, 21002},
        {-493.59f, -1720.00f, 2852.10f, LevelAndActIDs_Casinopolis2, Characters_Tails, Spinner, 21003},

        {137.67f, -192.00f, 74.14f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, Spinner, 31001},
        {-172.64f, -176.00f, -81.47f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, Spinner, 31002},
        {177.10f, 22.00f, 280.43f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, Spinner, 31003},
        {277.76f, 41.00f, 199.53f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, ElectroSpinner, 31004},
        {242.15f, 23.00f, 251.00f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, Spinner, 31005},
        {310.37f, 0.00f, 205.50f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, Spinner, 31006},
        {-290.87f, 2.00f, 251.33f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, Spinner, 31007},
        {235.33f, 8.00f, 306.44f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, Spinner, 31008},
        {333.44f, 30.00f, 194.33f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, Spinner, 31009},
        {300.92f, 15.00f, 254.64f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, Spinner, 31010},
        {228.77f, 9.00f, -341.66f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, Spinner, 31011},
        {379.40f, -159.04f, -149.68f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, Spinner, 31012},
        {376.90f, -181.04f, -170.43f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, Spinner, 31013},
        {406.91f, -165.04f, -175.83f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, Spinner, 31014},
        {434.36f, -186.04f, -173.14f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, Spinner, 31015},
        {474.99f, -195.04f, -192.50f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, ElectroSpinner, 31016},

        {168.11f, -167.00f, 366.54f, LevelAndActIDs_FinalEgg1, Characters_Sonic, EggKeeper, 19001},
        {194.58f, -164.99f, 68.81f, LevelAndActIDs_FinalEgg1, Characters_Sonic, Spinner, 19002},
        {133.93f, -166.99f, 22.11f, LevelAndActIDs_FinalEgg1, Characters_Sonic, Spinner, 19003},
        {171.32f, -165.99f, -42.43f, LevelAndActIDs_FinalEgg1, Characters_Sonic, Spinner, 19004},
        {193.69f, -207.02f, -1416.53f, LevelAndActIDs_FinalEgg1, Characters_Sonic, EggKeeper, 19005},
        {193.10f, -207.02f, -1527.57f, LevelAndActIDs_FinalEgg1, Characters_Sonic, EggKeeper, 19006},
        {1632.65f, 259.00f, -1295.62f, LevelAndActIDs_FinalEgg1, Characters_Sonic, Spinner, 19007},
        {1642.55f, 275.00f, -1330.14f, LevelAndActIDs_FinalEgg1, Characters_Sonic, Spinner, 19008},
        {1614.26f, 227.18f, -1407.40f, LevelAndActIDs_FinalEgg1, Characters_Sonic, ElectroSpinner, 19009},
        {1637.60f, 227.18f, -1443.32f, LevelAndActIDs_FinalEgg1, Characters_Sonic, ElectroSpinner, 19010},
        {2072.58f, 209.99f, -1122.12f, LevelAndActIDs_FinalEgg1, Characters_Sonic, Spinner, 19011},
        {2056.54f, 209.99f, -1145.05f, LevelAndActIDs_FinalEgg1, Characters_Sonic, Spinner, 19012},
        {1598.22f, 199.18f, -1570.78f, LevelAndActIDs_FinalEgg1, Characters_Sonic, ElectroSpinner, 19013},
        {1016.90f, 589.76f, -900.88f, LevelAndActIDs_FinalEgg2, Characters_Sonic, Spinner, 19014},
        {1011.43f, 585.76f, -931.80f, LevelAndActIDs_FinalEgg2, Characters_Sonic, Spinner, 19015},
        {995.03f, 110.58f, -753.03f, LevelAndActIDs_FinalEgg2, Characters_Sonic, Spinner, 19016},
        {1019.03f, 110.58f, -804.24f, LevelAndActIDs_FinalEgg2, Characters_Sonic, Spinner, 19017},
        {985.52f, 110.58f, -840.31f, LevelAndActIDs_FinalEgg2, Characters_Sonic, Spinner, 19018},
        {1089.07f, -470.03f, -915.66f, LevelAndActIDs_FinalEgg2, Characters_Sonic, Spinner, 19019},
        {1125.81f, -470.03f, -924.36f, LevelAndActIDs_FinalEgg2, Characters_Sonic, Spinner, 19020},
        {1125.86f, -470.03f, -962.16f, LevelAndActIDs_FinalEgg2, Characters_Sonic, Spinner, 19021},
        {829.14f, -844.00f, -820.80f, LevelAndActIDs_FinalEgg2, Characters_Sonic, Spinner, 19022},
        {786.01f, -844.00f, -856.85f, LevelAndActIDs_FinalEgg2, Characters_Sonic, Spinner, 19023},
        {829.49f, -844.00f, -891.03f, LevelAndActIDs_FinalEgg2, Characters_Sonic, Spinner, 19024},
        {1747.05f, -286.72f, -1738.09f, LevelAndActIDs_FinalEgg3, Characters_Sonic, Spinner, 19025},
        {1703.82f, -277.72f, -1772.17f, LevelAndActIDs_FinalEgg3, Characters_Sonic, Spinner, 19026},
        {2115.24f, -361.42f, -1778.67f, LevelAndActIDs_FinalEgg3, Characters_Sonic, Spinner, 19027},
        {2171.50f, -361.42f, -1736.75f, LevelAndActIDs_FinalEgg3, Characters_Sonic, Spinner, 19028},
        {1263.64f, -3257.57f, -414.80f, LevelAndActIDs_FinalEgg3, Characters_Sonic, EggKeeper, 19029},
        {1264.49f, -3257.57f, -411.34f, LevelAndActIDs_FinalEgg3, Characters_Sonic, EggKeeper, 19030},
        {1277.25f, -3262.57f, -416.35f, LevelAndActIDs_FinalEgg3, Characters_Sonic, EggKeeper, 19031},
        {1733.96f, -3279.19f, -220.39f, LevelAndActIDs_FinalEgg3, Characters_Sonic, EggKeeper, 19032},
        {167.63f, -3229.66f, -241.14f, LevelAndActIDs_FinalEgg3, Characters_Sonic, Spinner, 19033},
        {1661.08f, -3295.57f, -197.40f, LevelAndActIDs_FinalEgg3, Characters_Sonic, Spinner, 19034},
        {1751.27f, -3287.57f, -283.31f, LevelAndActIDs_FinalEgg3, Characters_Sonic, Spinner, 19035},
        {111.02f, -3222.66f, -292.67f, LevelAndActIDs_FinalEgg3, Characters_Sonic, EggKeeper, 19036},
        {124.71f, -3229.66f, -256.40f, LevelAndActIDs_FinalEgg3, Characters_Sonic, Spinner, 19037},
        {96.68f, -3229.66f, -224.39f, LevelAndActIDs_FinalEgg3, Characters_Sonic, Spinner, 19038},
        {36.73f, -3222.66f, -275.10f, LevelAndActIDs_FinalEgg3, Characters_Sonic, EggKeeper, 19039},
        {1828.13f, -3290.57f, -201.58f, LevelAndActIDs_FinalEgg3, Characters_Sonic, Spinner, 19040},


        {150.91f, -165.99f, -77.09f, LevelAndActIDs_FinalEgg1, Characters_Amy, Spinner, 42001},
        {198.21f, -166.99f, -96.23f, LevelAndActIDs_FinalEgg1, Characters_Amy, Spinner, 42002},
        {208.75f, -204.01f, -1445.04f, LevelAndActIDs_FinalEgg1, Characters_Amy, EggKeeper, 42003},
        {272.32f, -204.01f, -1567.91f, LevelAndActIDs_FinalEgg1, Characters_Amy, EggKeeper, 42004},
        {1628.82f, 228.00f, -1441.37f, LevelAndActIDs_FinalEgg1, Characters_Amy, Spinner, 42005},
        {1734.73f, 249.00f, -1421.21f, LevelAndActIDs_FinalEgg1, Characters_Amy, Spinner, 42006},
        {2546.98f, 5270.01f, -2095.50f, LevelAndActIDs_FinalEgg1, Characters_Amy, Spinner, 42007},

        {1263.64f, -3257.57f, -414.80f, LevelAndActIDs_FinalEgg3, Characters_Gamma, EggKeeper, 50001},
        {1264.49f, -3257.57f, -411.34f, LevelAndActIDs_FinalEgg3, Characters_Gamma, EggKeeper, 50002},

        {-37.40f, 19.00f, -205.30f, LevelAndActIDs_HotShelter1, Characters_Amy, Kiki, 41001},
        {-251.27f, 12.00f, -373.29f, LevelAndActIDs_HotShelter1, Characters_Amy, EggKeeper, 41002},
        {44.98f, 4.00f, -659.85f, LevelAndActIDs_HotShelter1, Characters_Amy, Kiki, 41003},
        {511.62f, 4.00f, -639.13f, LevelAndActIDs_HotShelter1, Characters_Amy, Kiki, 41004},
        {513.42f, 4.00f, -670.16f, LevelAndActIDs_HotShelter1, Characters_Amy, Kiki, 41005},
        {161.06f, 261.97f, -256.63f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41006},
        {159.12f, 261.97f, -216.25f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41007},
        {-309.37f, 261.96f, -258.77f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41008},
        {-308.94f, 261.96f, -218.05f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41009},
        {55.72f, -206.00f, -617.66f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41010},
        {-81.70f, -210.00f, -536.05f, LevelAndActIDs_HotShelter2, Characters_Amy, Leon, 41011},
        {-0.66f, 82.00f, -1188.09f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41012},
        {18.71f, 82.00f, -1228.70f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41013},
        {51.80f, 113.00f, -1251.34f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41014},
        {665.58f, 82.00f, -1791.25f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41015},
        {622.20f, 82.00f, -1811.97f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41016},
        {666.48f, 82.00f, -1834.25f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41017},
        {620.73f, 10.00f, -2051.97f, LevelAndActIDs_HotShelter2, Characters_Amy, Leon, 41018},
        {540.14f, 153.00f, -2321.49f, LevelAndActIDs_HotShelter2, Characters_Amy, Leon, 41019}, //DX
        {540.14f, 150.00f, -2321.49f, LevelAndActIDs_HotShelter2, Characters_Amy, Leon, 41019}, //DC
        {511.26f, 153.98f, -2356.89f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41020}, //DX
        {511.26f, 153.00f, -2356.89f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41020}, //DC
        {563.57f, 153.98f, -2366.54f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41021}, //DX
        {563.57f, 153.00f, -2366.54f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41021}, //DC
        {481.95f, 153.01f, -3085.07f, LevelAndActIDs_HotShelter2, Characters_Amy, EggKeeper, 41022},
        {986.50f, 219.01f, -3097.79f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41023},
        {171.49f, 374.00f, -3589.12f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41024},
        {131.49f, 374.00f, -3589.12f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41025},
        {91.49f, 374.00f, -3589.12f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41026},
        {151.28f, 374.00f, -3615.77f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41027},
        {111.85f, 374.00f, -3614.94f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41028},
        {171.49f, 374.00f, -3639.12f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41029},
        {131.49f, 374.00f, -3639.12f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41030},
        {91.49f, 374.00f, -3639.12f, LevelAndActIDs_HotShelter2, Characters_Amy, Kiki, 41031},

        {-20.58f, 266.00f, -188.43f, LevelAndActIDs_HotShelter3, Characters_Gamma, EggKeeper, 54001},
        {75.31f, 255.00f, -165.60f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54002}, //DX
        {75.31f, 254.00f, -165.60f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54002}, //DC
        {-122.83f, 253.00f, -166.60f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54003}, //DX
        {-122.83f, 254.00f, -166.60f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54003}, //DC
        {-41.63f, 254.00f, -270.51f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54004},
        {-0.21f, 254.00f, -272.51f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54005},
        {160.47f, 260.58f, -257.00f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54006},
        {213.39f, 255.03f, -223.64f, LevelAndActIDs_HotShelter3, Characters_Gamma, Leon, 54007},
        {-201.75f, 255.03f, -261.89f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54008}, //DX
        {-201.75f, 254.03f, -261.89f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54008}, //DC
        {-201.04f, 255.03f, -288.80f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54009}, //DX
        {-201.04f, 254.03f, -288.80f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54009}, //DC
        {-308.42f, 262.58f, -216.99f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54010},
        {269.15f, 260.58f, -217.48f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54011},
        {159.46f, 260.58f, -297.45f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54012},
        {-309.17f, 262.58f, -257.84f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54013},
        {269.90f, 260.58f, -257.47f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54014},
        {-308.30f, 262.58f, -297.59f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54015}, //DX
        {-308.30f, 261.58f, -297.59f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54015}, //DC
        {270.65f, 260.58f, -297.47f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54016},
        {82.71f, -100.00f, -734.68f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54017}, //DX
        {82.71f, -101.00f, -734.68f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54017}, //DC
        {115.92f, -100.00f, -738.61f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54018}, //DX
        {115.92f, -101.00f, -738.61f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54018}, //DC
        {128.69f, -101.00f, -763.98f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54019},
        {28.49f, 113.00f, -1170.84f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54020}, //DX
        {28.49f, 112.50f, -1170.84f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54020}, //DC
        {-61.03f, 113.00f, -1219.66f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54021}, //DX
        {-61.03f, 112.50f, -1219.66f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54021}, //DC
        {51.62f, 113.00f, -1250.73f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54022}, //DX
        {51.62f, 112.60f, -1250.53f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54022}, //DC
        {-51.01f, 113.00f, -1318.92f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54023}, //DX
        {-51.01f, 112.60f, -1318.92f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54023}, //DC
        {50.71f, 113.00f, -1319.09f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54024}, //DX
        {50.71f, 112.40f, -1319.09f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54024}, //DC
        {2.40f, 88.00f, -1323.69f, LevelAndActIDs_HotShelter3, Characters_Gamma, EggKeeper, 54025}, //DX
        {2.40f, 78.00f, -1323.69f, LevelAndActIDs_HotShelter3, Characters_Gamma, EggKeeper, 54025}, //DC
        {-773.12f, 50.00f, -1470.84f, LevelAndActIDs_HotShelter3, Characters_Gamma, Leon, 54026},
        {-527.72f, 84.00f, -1768.76f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54027},
        {-528.59f, 84.00f, -1791.33f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54028},
        {-529.35f, 84.00f, -1812.64f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54029},
        {-531.12f, 84.00f, -1832.11f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54030},
        {-529.57f, 84.00f, -1855.65f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54031},
        {-752.34f, 204.01f, -1910.78f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54032},
        {-779.33f, 204.01f, -1911.57f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54033},
        {-804.50f, 204.01f, -1910.20f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54034},
        {-1520.78f, 184.00f, -1488.54f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54035},
        {-1499.72f, 178.00f, -1578.83f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54036},
        {-1267.32f, 180.00f, -1769.52f, LevelAndActIDs_HotShelter3, Characters_Gamma, EggKeeper, 54037}, //DX
        {-1267.32f, 170.00f, -1769.52f, LevelAndActIDs_HotShelter3, Characters_Gamma, EggKeeper, 54037}, //DC
        {-1508.86f, 218.00f, -1609.84f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54038},
        {-1497.87f, 178.00f, -1642.36f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54039},
        {-1535.44f, 180.00f, -1611.01f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54040},
        {-1519.58f, 138.00f, -1642.16f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54041},
        {-1264.85f, 180.00f, -1849.32f, LevelAndActIDs_HotShelter3, Characters_Gamma, EggKeeper, 54042}, //DX
        {-1264.85f, 170.00f, -1849.32f, LevelAndActIDs_HotShelter3, Characters_Gamma, EggKeeper, 54042}, //DC
        {-692.16f, 285.00f, -2286.30f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54043},
        {-746.38f, 283.00f, -2288.08f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54044},
        {-815.21f, 283.00f, -2283.63f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54045}, //DX
        {-815.21f, 284.30f, -2283.63f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54045}, //DC
        {-723.41f, 282.00f, -2491.67f, LevelAndActIDs_HotShelter3, Characters_Gamma, Leon, 54046},
        {-832.87f, 282.00f, -2480.38f, LevelAndActIDs_HotShelter3, Characters_Gamma, Leon, 54047},
        {-870.06f, 174.00f, -3561.43f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54048},
        {-798.07f, 1034.00f, -3552.88f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54049},
        {-901.78f, 174.00f, -3563.60f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54050},
        {-842.90f, 174.00f, -3578.11f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54051},
        {-899.36f, 1034.00f, -3551.49f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54052},
        {-938.03f, 174.00f, -3577.60f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54053},
        {-769.14f, 1034.00f, -3594.38f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54054},
        {-932.76f, 1034.00f, -3596.56f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54055},
        {-769.15f, 1034.00f, -3645.44f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54056},
        {-841.98f, 174.00f, -3660.54f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54057},
        {-933.54f, 174.00f, -3663.29f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54058},
        {-783.68f, 1534.00f, -3566.24f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54059},
        {-932.91f, 1034.00f, -3644.77f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54060},
        {-872.37f, 174.00f, -3689.94f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54061},
        {-799.65f, 1034.00f, -3686.79f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54062},
        {-906.61f, 174.00f, -3690.32f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54063},
        {-768.64f, 1534.00f, -3600.32f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54064},
        {-915.80f, 1534.00f, -3567.49f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54065},
        {-897.09f, 1034.00f, -3692.40f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54066},
        {-767.82f, 1534.00f, -3637.49f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54067},
        {-931.99f, 1534.00f, -3602.80f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54068},
        {-930.60f, 1534.00f, -3640.78f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54069},
        {-788.67f, 1534.00f, -3674.65f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54070},
        {-912.36f, 1534.00f, -3675.10f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54071},
        {-786.21f, 2034.00f, -3561.35f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54072},
        {-914.27f, 2034.00f, -3560.86f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54073},
        {-771.20f, 2034.00f, -3605.07f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54074},
        {-769.25f, 2034.00f, -3635.77f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54075},
        {-932.65f, 2034.00f, -3606.55f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54076},
        {-931.42f, 2034.00f, -3635.53f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54077},
        {-785.88f, 2034.00f, -3679.65f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54078},
        {-913.74f, 2034.00f, -3679.95f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54079},
        {-829.91f, 3008.98f, -3393.70f, LevelAndActIDs_HotShelter3, Characters_Gamma, Leon, 54080},
        {-866.07f, 3008.98f, -3395.74f, LevelAndActIDs_HotShelter3, Characters_Gamma, Leon, 54081},
        {-849.69f, 3008.98f, -3452.16f, LevelAndActIDs_HotShelter3, Characters_Gamma, Leon, 54082},
        {-783.75f, 3004.00f, -3563.80f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54083},
        {-919.37f, 3004.00f, -3569.17f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54084},
        {-60.07f, 10010.99f, 11.41f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54085},
        {-34.70f, 10010.99f, -24.71f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54086},
        {-71.70f, 10010.99f, -22.67f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54087},
        {-39.02f, 10011.02f, 640.86f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54088},
        {-67.19f, 10011.02f, 639.78f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54089},
        {-25.28f, 10011.02f, 665.86f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54090},
        {-79.90f, 10011.02f, 662.98f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54091},
        {-51.46f, 10011.02f, 692.40f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54092},
        {-37.34f, 10037.30f, 368.58f, LevelAndActIDs_HotShelter3, Characters_Gamma, EggKeeper, 54093},
        {-67.77f, 10038.80f, 367.99f, LevelAndActIDs_HotShelter3, Characters_Gamma, EggKeeper, 54094},
        {-47.07f, 10012.99f, 1010.07f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54095},
        {-48.58f, 10013.99f, 1034.02f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54096}, //DX
        {-48.58f, 10012.99f, 1034.02f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54096}, //DC
        {-62.39f, 10012.99f, 1175.95f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54097},
        {-45.68f, 10012.99f, 1187.22f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54098},
        {-45.34f, 10012.99f, 1204.25f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54099},
        {-58.99f, 10012.99f, 1211.36f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54100},
        {-47.64f, 10020.99f, 1357.48f, LevelAndActIDs_HotShelter3, Characters_Gamma, EggKeeper, 54101},
        {-45.93f, 10020.99f, 1382.42f, LevelAndActIDs_HotShelter3, Characters_Gamma, EggKeeper, 54102},
        {-51.56f, 10020.99f, 1522.88f, LevelAndActIDs_HotShelter3, Characters_Gamma, EggKeeper, 54103},
        {-49.50f, 10020.99f, 1552.81f, LevelAndActIDs_HotShelter3, Characters_Gamma, EggKeeper, 54104},
        {-33.59f, 10072.00f, 1344.36f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54105},
        {-37.97f, 10072.00f, 1385.83f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54106},
        {-37.04f, 10072.00f, 1518.81f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54107},
        {-32.11f, 10072.00f, 1562.76f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54108},
        {-68.49f, 10040.80f, 1854.24f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54109},
        {-38.53f, 10040.80f, 1855.84f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54110},
        {-55.00f, 10040.80f, 1866.10f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54111},
        {-57.48f, 10011.10f, 3028.14f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54112}, //DX
        {-57.48f, 10011.10f, 3028.14f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54112}, //DC
        {-68.40f, 10011.10f, 3064.61f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54113}, //DX
        {-68.40f, 10012.80f, 3064.61f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54113}, //DC
        {-32.33f, 10011.10f, 3074.86f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54114}, //DX
        {-32.33f, 10011.10f, 3074.86f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54114}, //DC
        {-42.81f, 10011.10f, 3123.20f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54115}, //DX
        {-42.81f, 10011.10f, 3123.20f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54115}, //DC
        {-75.63f, 10011.10f, 3128.27f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54116}, //DX
        {-75.63f, 10011.10f, 3128.27f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54116}, //DC
        {-51.79f, 10058.00f, 3306.52f, LevelAndActIDs_HotShelter3, Characters_Gamma, Kiki, 54117},

        {-242.09f, 3.99f, -361.62f, LevelAndActIDs_HotShelter1, Characters_Big, Kiki, 63001}, //DX
        {-242.09f, 4.20f, -361.62f, LevelAndActIDs_HotShelter1, Characters_Big, Kiki, 63001}, //DC
        {172.89f, 5.00f, -659.14f, LevelAndActIDs_HotShelter1, Characters_Big, Kiki, 63002}, //DX
        {172.89f, 5.20f, -659.14f, LevelAndActIDs_HotShelter1, Characters_Big, Kiki, 63002}, //DC
        {-173.22f, 85.98f, -500.13f, LevelAndActIDs_HotShelter1, Characters_Big, Kiki, 63003}, //DX
        {-173.22f, 85.20f, -500.13f, LevelAndActIDs_HotShelter1, Characters_Big, Kiki, 63003}, //DC
        {-233.30f, 85.98f, -790.48f, LevelAndActIDs_HotShelter1, Characters_Big, Kiki, 63004}, //DX
        {-233.30f, 84.20f, -790.48f, LevelAndActIDs_HotShelter1, Characters_Big, Kiki, 63004}, //DC
        {-300.33f, 85.98f, -772.62f, LevelAndActIDs_HotShelter1, Characters_Big, Kiki, 63005}, //DX
        {-300.33f, 84.20f, -772.62f, LevelAndActIDs_HotShelter1, Characters_Big, Kiki, 63005}, //DC
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
        {619.40f, 41.96f, -871.16f, LevelAndActIDs_TwinklePark2, Characters_Amy, SpeedUpCapsule, 40504},
        {18.14f, 0.00f, -631.67f, LevelAndActIDs_TwinklePark2, Characters_Amy, ShieldCapsule, 40505},
        {435.98f, 297.02f, -255.54f, LevelAndActIDs_TwinklePark2, Characters_Amy, TenRingsCapsule, 40506},
        {267.40f, 306.02f, -297.65f, LevelAndActIDs_TwinklePark2, Characters_Amy, ExtraLifeCapsule, 40507},
        {779.32f, 120.00f, 408.08f, LevelAndActIDs_TwinklePark2, Characters_Amy, RandomRingsCapsule, 40508},
        {611.41f, 145.00f, 551.92f, LevelAndActIDs_TwinklePark2, Characters_Amy, RandomRingsCapsule, 40509},

        {69.93f, 0.00f, -442.74f, LevelAndActIDs_TwinklePark2, Characters_Big, RandomRingsCapsule, 60501},
        {643.80f, 0.00f, -565.22f, LevelAndActIDs_TwinklePark2, Characters_Big, RandomRingsCapsule, 60502},

        {791.85f, -565.00f, 411.87f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, MagneticShieldCapsule, 15501},
        {1772.14f, -683.00f, 286.35f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, FiveRingsCapsule, 15502}, //DX
        {1772.14f, -683.18f, 286.35f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, FiveRingsCapsule, 15502}, //DC
        {1772.14f, -683.00f, 304.35f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, ExtraLifeCapsule, 15503}, //DX
        {1772.14f, -683.18f, 304.35f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, ExtraLifeCapsule, 15503}, //DC
        {1772.14f, -683.00f, 322.35f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, FiveRingsCapsule, 15504}, //DX
        {1772.14f, -683.18f, 322.35f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, FiveRingsCapsule, 15504}, //DC
        {1904.17f, -93.17f, 21.84f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, ExtraLifeCapsule, 15505},
        {1912.92f, -93.17f, 594.75f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, ExtraLifeCapsule, 15506},
        {1848.73f, -1326.00f, 1866.06f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, SpeedUpCapsule, 15507},
        {3365.33f, -1432.48f, -305.32f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, SpeedUpCapsule, 15508}, //DX
        {3367.83f, -1430.48f, -305.32f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, SpeedUpCapsule, 15508}, //DC
        {3762.78f, -1125.00f, -313.84f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, InvincibilityCapsule, 15509},
        {3831.56f, -850.00f, -313.26f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, SpeedUpCapsule, 15510},
        {3798.50f, -1370.00f, 159.90f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, ExtraLifeCapsule, 15511},
        {3917.88f, -1675.00f, 1665.49f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, RandomRingsCapsule, 15512},
        {2718.36f, -1997.00f, 3664.15f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, FiveRingsCapsule, 15513},
        {2921.09f, -1997.00f, 3660.93f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, FiveRingsCapsule, 15514},
        {2820.73f, -1997.00f, 3764.18f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, FiveRingsCapsule, 15515},
        {4790.28f, -1380.00f, -317.21f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, TenRingsCapsule, 15516},
        {4808.28f, -1380.00f, -317.21f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, ShieldCapsule, 15517},
        {4626.20f, -1675.00f, 1667.93f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, ExtraLifeCapsule, 15518},
        {4726.38f, -1444.33f, 1652.14f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, SpeedUpCapsule, 15519},
        {3127.95f, -2020.60f, 3960.12f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, ShieldCapsule, 15520}, //DX
        {3127.95f, -2021.10f, 3960.12f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, ShieldCapsule, 15520}, //DC
        {4955.38f, -1676.00f, 1441.51f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, RandomRingsCapsule, 15521},
        {4271.06f, -1525.98f, 4152.68f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, ExtraLifeCapsule, 15522},
        {4380.14f, -1838.98f, 4081.59f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, BombCapsule, 15523},
        {1.35f, -4080.00f, -100.40f, LevelAndActIDs_SpeedHighway2, Characters_Sonic, SpeedUpCapsule, 15524},
        {1.00f, -4962.00f, -55.40f, LevelAndActIDs_SpeedHighway2, Characters_Sonic, FiveRingsCapsule, 15525},
        {1.00f, -5565.00f, -55.40f, LevelAndActIDs_SpeedHighway2, Characters_Sonic, ExtraLifeCapsule, 15526},
        {-0.17f, -6886.00f, 97.60f, LevelAndActIDs_SpeedHighway2, Characters_Sonic, TenRingsCapsule, 15527},
        {-2.80f, -8650.00f, -48.68f, LevelAndActIDs_SpeedHighway2, Characters_Sonic, RandomRingsCapsule, 15528},
        {-0.73f, -11978.00f, -1.75f, LevelAndActIDs_SpeedHighway2, Characters_Sonic, FiveRingsCapsule, 15529},
        {-0.94f, -12372.00f, -51.66f, LevelAndActIDs_SpeedHighway2, Characters_Sonic, RandomRingsCapsule, 15530},
        {-4.83f, -14692.00f, 89.20f, LevelAndActIDs_SpeedHighway2, Characters_Sonic, FiveRingsCapsule, 15531},
        {-1.69f, -17743.00f, -91.20f, LevelAndActIDs_SpeedHighway2, Characters_Sonic, MagneticShieldCapsule, 15532},
        {-110.45f, 100.00f, -164.45f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, SpeedUpCapsule, 15533},
        {-359.64f, 62.50f, -356.49f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, ShieldCapsule, 15534},
        {-85.23f, 145.00f, -499.37f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, FiveRingsCapsule, 15535},
        {-138.84f, 185.00f, -1014.24f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, ExtraLifeCapsule, 15536},
        {-641.95f, 210.00f, -1200.72f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, FiveRingsCapsule, 15537},
        {-641.76f, 210.00f, -1239.20f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, FiveRingsCapsule, 15538},
        {14.83f, 0.00f, -1688.95f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, ExtraLifeCapsule, 15539},
        {-1649.65f, 290.00f, -1383.52f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, RandomRingsCapsule, 15540},
        {-1674.69f, 223.07f, -1386.02f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, SpeedUpCapsule, 15541},
        {-1674.79f, 290.00f, -1379.44f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, RandomRingsCapsule, 15542},
        {-1699.09f, 290.00f, -1374.88f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, RandomRingsCapsule, 15543},

        {791.10f, -565.00f, 411.21f, LevelAndActIDs_SpeedHighway1, Characters_Tails, MagneticShieldCapsule, 24501},
        {3365.33f, -1432.48f, -305.32f, LevelAndActIDs_SpeedHighway1, Characters_Tails, SpeedUpCapsule, 24502}, //DX
        {3367.83f, -1430.48f, -305.32f, LevelAndActIDs_SpeedHighway1, Characters_Tails, SpeedUpCapsule, 24502}, //DC
        {3798.50f, -1370.00f, 159.90f, LevelAndActIDs_SpeedHighway1, Characters_Tails, ShieldCapsule, 24503},
        {3917.88f, -1675.00f, 1665.49f, LevelAndActIDs_SpeedHighway1, Characters_Tails, RandomRingsCapsule, 24504},
        {2718.36f, -1997.00f, 3664.15f, LevelAndActIDs_SpeedHighway1, Characters_Tails, FiveRingsCapsule, 24505},
        {2921.09f, -1997.00f, 3660.93f, LevelAndActIDs_SpeedHighway1, Characters_Tails, FiveRingsCapsule, 24506},
        {2820.73f, -1997.00f, 3764.18f, LevelAndActIDs_SpeedHighway1, Characters_Tails, FiveRingsCapsule, 24507},
        {4790.28f, -1380.00f, -317.21f, LevelAndActIDs_SpeedHighway1, Characters_Tails, TenRingsCapsule, 24508},
        {4808.28f, -1380.00f, -317.21f, LevelAndActIDs_SpeedHighway1, Characters_Tails, ShieldCapsule, 24509},
        {4626.20f, -1675.00f, 1667.93f, LevelAndActIDs_SpeedHighway1, Characters_Tails, ExtraLifeCapsule, 24510},
        {4730.87f, -1446.33f, 1650.32f, LevelAndActIDs_SpeedHighway1, Characters_Tails, SpeedUpCapsule, 24511},
        {3127.95f, -2021.10f, 3960.12f, LevelAndActIDs_SpeedHighway1, Characters_Tails, ShieldCapsule, 24512},
        {4956.11f, -1714.00f, 1364.51f, LevelAndActIDs_SpeedHighway1, Characters_Tails, ExtraLifeCapsule, 24513},
        {4247.71f, -1910.00f, 4001.48f, LevelAndActIDs_SpeedHighway1, Characters_Tails, TenRingsCapsule, 24514},
        {4241.26f, -1910.00f, 4012.77f, LevelAndActIDs_SpeedHighway1, Characters_Tails, MagneticShieldCapsule, 24515},
        {4234.79f, -1910.00f, 4024.05f, LevelAndActIDs_SpeedHighway1, Characters_Tails, TenRingsCapsule, 24516},
        {4259.64f, -1704.04f, 4095.85f, LevelAndActIDs_SpeedHighway1, Characters_Tails, ExtraLifeCapsule, 24517}, //DX
        {4259.64f, -1705.34f, 4095.85f, LevelAndActIDs_SpeedHighway1, Characters_Tails, ExtraLifeCapsule, 24517}, //DC
        {4261.77f, -1890.00f, 4273.03f, LevelAndActIDs_SpeedHighway1, Characters_Tails, RandomRingsCapsule, 24518},
        {5434.11f, -2332.00f, 7538.42f, LevelAndActIDs_SpeedHighway1, Characters_Tails, MagneticShieldCapsule, 24519},
        {5406.19f, -2332.00f, 7667.90f, LevelAndActIDs_SpeedHighway1, Characters_Tails, FiveRingsCapsule, 24520},
        {5246.12f, -2332.00f, 7842.45f, LevelAndActIDs_SpeedHighway1, Characters_Tails, ExtraLifeCapsule, 24521},
        {5462.74f, -2332.00f, 7888.70f, LevelAndActIDs_SpeedHighway1, Characters_Tails, RandomRingsCapsule, 24522},
        {6087.48f, -1900.00f, 8040.36f, LevelAndActIDs_SpeedHighway1, Characters_Tails, SpeedUpCapsule, 24523},

        {-347.94f, 110.00f, -1696.57f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, ShieldCapsule, 30501},
        {14.83f, 0.00f, -1688.95f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, ExtraLifeCapsule, 30502},
        {-138.84f, 185.00f, -1014.24f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, ExtraLifeCapsule, 30503},
        {-85.23f, 145.00f, -499.37f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, RandomRingsCapsule, 30504},
        {-359.64f, 62.50f, -356.49f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, MagneticShieldCapsule, 30505},
        {-1455.19f, 282.00f, -1026.87f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, TenRingsCapsule, 30506},
        {-1779.31f, 290.00f, -1326.34f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, ShieldCapsule, 30507},
        {70.51f, 24.50f, 223.17f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, ExtraLifeCapsule, 30508}, //DX
        {70.51f, 24.40f, 223.17f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, ExtraLifeCapsule, 30508}, //DC

        {-254.40f, 595.97f, 592.58f, LevelAndActIDs_RedMountain1, Characters_Sonic, TenRingsCapsule, 16501}, //DX
        {-254.40f, 595.97f, 571.58f, LevelAndActIDs_RedMountain1, Characters_Sonic, TenRingsCapsule, 16501}, //DC
        {-211.72f, 1023.13f, -88.97f, LevelAndActIDs_RedMountain1, Characters_Sonic, SpeedUpCapsule, 16502}, //DX
        {-225.72f, 1021.53f, -88.97f, LevelAndActIDs_RedMountain1, Characters_Sonic, SpeedUpCapsule, 16502}, //DC
        {-534.08f, 1255.30f, -170.27f, LevelAndActIDs_RedMountain1, Characters_Sonic, ExtraLifeCapsule, 16503}, //DX
        {-534.08f, 1254.21f, -170.27f, LevelAndActIDs_RedMountain1, Characters_Sonic, ExtraLifeCapsule, 16503}, //DC
        {-551.98f, 1255.30f, -161.34f, LevelAndActIDs_RedMountain1, Characters_Sonic, RandomRingsCapsule, 16504}, //DX
        {-551.98f, 1254.21f, -161.34f, LevelAndActIDs_RedMountain1, Characters_Sonic, RandomRingsCapsule, 16504}, //DC
        {-553.44f, 1255.30f, -183.68f, LevelAndActIDs_RedMountain1, Characters_Sonic, RandomRingsCapsule, 16505}, //DX
        {-553.44f, 1254.21f, -183.68f, LevelAndActIDs_RedMountain1, Characters_Sonic, RandomRingsCapsule, 16505}, //DC
        {-855.52f, 1096.57f, -347.76f, LevelAndActIDs_RedMountain1, Characters_Sonic, ExtraLifeCapsule, 16506},
        {-1084.28f, 601.55f, -1327.18f, LevelAndActIDs_RedMountain1, Characters_Sonic, TenRingsCapsule, 16507},
        {-2719.90f, 121.20f, -1774.73f, LevelAndActIDs_RedMountain1, Characters_Sonic, TenRingsCapsule, 16508},
        {-3035.25f, 173.02f, -1385.02f, LevelAndActIDs_RedMountain1, Characters_Sonic, ExtraLifeCapsule, 16509}, //DX
        {-3035.25f, 172.22f, -1385.02f, LevelAndActIDs_RedMountain1, Characters_Sonic, ExtraLifeCapsule, 16509}, //DC
        {-2781.22f, 39.84f, -1740.92f, LevelAndActIDs_RedMountain1, Characters_Sonic, FiveRingsCapsule, 16510},
        {-2954.26f, 884.30f, -1751.26f, LevelAndActIDs_RedMountain1, Characters_Sonic, ExtraLifeCapsule, 16511},
        {-2969.36f, 884.30f, -1738.15f, LevelAndActIDs_RedMountain1, Characters_Sonic, ExtraLifeCapsule, 16512},
        {-3452.31f, 134.38f, -1580.31f, LevelAndActIDs_RedMountain1, Characters_Sonic, ExtraLifeCapsule, 16513},
        {-3604.83f, 451.69f, -1487.25f, LevelAndActIDs_RedMountain1, Characters_Sonic, TenRingsCapsule, 16514},
        {-3550.27f, 231.43f, -1940.90f, LevelAndActIDs_RedMountain1, Characters_Sonic, TenRingsCapsule, 16515}, //DX
        {-3576.10f, 240.07f, -1910.75f, LevelAndActIDs_RedMountain1, Characters_Sonic, TenRingsCapsule, 16515}, //DC
        {-3767.93f, 1221.38f, -1908.67f, LevelAndActIDs_RedMountain1, Characters_Sonic, ExtraLifeCapsule, 16516}, //DX
        {-3767.93f, 1226.38f, -1929.57f, LevelAndActIDs_RedMountain1, Characters_Sonic, ExtraLifeCapsule, 16516}, //DC
        {-4106.05f, 648.92f, -1948.05f, LevelAndActIDs_RedMountain1, Characters_Sonic, RandomRingsCapsule, 16517},
        {-3864.85f, 1115.91f, -2271.23f, LevelAndActIDs_RedMountain1, Characters_Sonic, RandomRingsCapsule, 16518},
        {-1232.38f, 433.08f, 1497.01f, LevelAndActIDs_RedMountain2, Characters_Sonic, RandomRingsCapsule, 16519}, //DX
        {-1232.38f, 432.28f, 1497.01f, LevelAndActIDs_RedMountain2, Characters_Sonic, RandomRingsCapsule, 16519}, //DC
        {-1248.04f, 432.28f, 1474.47f, LevelAndActIDs_RedMountain2, Characters_Sonic, TenRingsCapsule, 16520},
        {-1258.02f, 432.28f, 1501.33f, LevelAndActIDs_RedMountain2, Characters_Sonic, RandomRingsCapsule, 16521},
        {-980.78f, 285.65f, 1114.55f, LevelAndActIDs_RedMountain2, Characters_Sonic, RandomRingsCapsule, 16522}, //DX
        {-980.78f, 286.65f, 1114.55f, LevelAndActIDs_RedMountain2, Characters_Sonic, RandomRingsCapsule, 16522}, //DC
        {-1158.70f, 287.55f, 1088.07f, LevelAndActIDs_RedMountain2, Characters_Sonic, TenRingsCapsule, 16523}, //DX
        {-1158.70f, 286.65f, 1088.07f, LevelAndActIDs_RedMountain2, Characters_Sonic, TenRingsCapsule, 16523}, //DC
        {-907.53f, 137.85f, 871.08f, LevelAndActIDs_RedMountain2, Characters_Sonic, ExtraLifeCapsule, 16524}, //DX
        {-907.53f, 137.65f, 871.08f, LevelAndActIDs_RedMountain2, Characters_Sonic, ExtraLifeCapsule, 16524}, //DC
        {-251.83f, 239.00f, 529.82f, LevelAndActIDs_RedMountain2, Characters_Sonic, SpeedUpCapsule, 16525},
        {-1721.42f, 515.36f, 1399.58f, LevelAndActIDs_RedMountain2, Characters_Sonic, TenRingsCapsule, 16526},
        {-1785.81f, 479.11f, 765.20f, LevelAndActIDs_RedMountain2, Characters_Sonic, TenRingsCapsule, 16527},
        {-1624.23f, 164.82f, 599.80f, LevelAndActIDs_RedMountain2, Characters_Sonic, ShieldCapsule, 16528}, //DX
        {-1624.23f, 163.82f, 599.80f, LevelAndActIDs_RedMountain2, Characters_Sonic, ShieldCapsule, 16528}, //DC
        {-2508.08f, 278.55f, 1304.08f, LevelAndActIDs_RedMountain2, Characters_Sonic, ShieldCapsule, 16529},

        {-3248.85f, 760.02f, -1531.15f, LevelAndActIDs_RedMountain3, Characters_Knuckles, TenRingsCapsule, 32501},
        {-3109.15f, 697.02f, -1124.04f, LevelAndActIDs_RedMountain3, Characters_Knuckles, TenRingsCapsule, 32502},
        {-3143.69f, 424.02f, -1560.80f, LevelAndActIDs_RedMountain3, Characters_Knuckles, RandomRingsCapsule, 32503},
        {-2883.10f, 649.02f, -1662.80f, LevelAndActIDs_RedMountain3, Characters_Knuckles, TenRingsCapsule, 32504},
        {-3153.36f, 277.05f, -1303.56f, LevelAndActIDs_RedMountain3, Characters_Knuckles, FiveRingsCapsule, 32505},
        {-3148.07f, 865.02f, -1875.48f, LevelAndActIDs_RedMountain3, Characters_Knuckles, TenRingsCapsule, 32506},
        {-3252.81f, 547.02f, -1840.57f, LevelAndActIDs_RedMountain3, Characters_Knuckles, ShieldCapsule, 32507},
        {-3349.60f, 206.00f, -1142.93f, LevelAndActIDs_RedMountain3, Characters_Knuckles, ExtraLifeCapsule, 32508}, //DX
        {-3349.60f, 205.25f, -1142.93f, LevelAndActIDs_RedMountain3, Characters_Knuckles, ExtraLifeCapsule, 32508}, //DC
        {-3653.56f, 287.42f, -1317.51f, LevelAndActIDs_RedMountain3, Characters_Knuckles, RandomRingsCapsule, 32509},
        //DX
        {-3653.56f, 286.92f, -1317.51f, LevelAndActIDs_RedMountain3, Characters_Knuckles, RandomRingsCapsule, 32509},
        //DC
        {-3618.18f, 382.02f, -1752.26f, LevelAndActIDs_RedMountain3, Characters_Knuckles, TenRingsCapsule, 32510},
        {-3542.00f, 335.18f, -1955.67f, LevelAndActIDs_RedMountain3, Characters_Knuckles, InvincibilityCapsule, 32511},
        //DX
        {-3537.00f, 334.18f, -1956.67f, LevelAndActIDs_RedMountain3, Characters_Knuckles, InvincibilityCapsule, 32511},
        //DC
        {-3537.53f, 507.76f, -2067.51f, LevelAndActIDs_RedMountain3, Characters_Knuckles, TenRingsCapsule, 32512},
        {-2463.27f, 124.02f, -1627.66f, LevelAndActIDs_RedMountain3, Characters_Knuckles, TenRingsCapsule, 32513},
        {-3804.06f, 1122.98f, -2094.58f, LevelAndActIDs_RedMountain3, Characters_Knuckles, ExtraLifeCapsule, 32514},
        {-4106.05f, 648.92f, -1948.05f, LevelAndActIDs_RedMountain3, Characters_Knuckles, RandomRingsCapsule, 32515},
        //DX
        {-4080.00f, 592.98f, -1980.95f, LevelAndActIDs_RedMountain3, Characters_Knuckles, RandomRingsCapsule, 32515},
        //DC
        {-4067.33f, 977.00f, -2006.24f, LevelAndActIDs_RedMountain3, Characters_Knuckles, RandomRingsCapsule, 32516},
        //DX
        {-4067.33f, 976.24f, -2006.24f, LevelAndActIDs_RedMountain3, Characters_Knuckles, RandomRingsCapsule, 32516},
        //DC
        {-3726.38f, 342.76f, -2333.64f, LevelAndActIDs_RedMountain3, Characters_Knuckles, TenRingsCapsule, 32517},
        {-4086.43f, 553.02f, -2111.23f, LevelAndActIDs_RedMountain3, Characters_Knuckles, FiveRingsCapsule, 32518}, //DX
        {-4086.43f, 552.22f, -2111.23f, LevelAndActIDs_RedMountain3, Characters_Knuckles, FiveRingsCapsule, 32518}, //DC
        {-4119.10f, 894.76f, -2169.29f, LevelAndActIDs_RedMountain3, Characters_Knuckles, TenRingsCapsule, 32519},
        {-3666.69f, 63.45f, -2346.65f, LevelAndActIDs_RedMountain3, Characters_Knuckles, ExtraLifeCapsule, 32520}, //DX
        {-3666.69f, 62.20f, -2346.65f, LevelAndActIDs_RedMountain3, Characters_Knuckles, ExtraLifeCapsule, 32520}, //DC
        {-2136.42f, 69.02f, -1937.02f, LevelAndActIDs_RedMountain3, Characters_Knuckles, TenRingsCapsule, 32521},
        {-1895.37f, 58.92f, -1854.58f, LevelAndActIDs_RedMountain3, Characters_Knuckles, ExtraLifeCapsule, 32522}, //DX
        {-1895.37f, 58.32f, -1854.58f, LevelAndActIDs_RedMountain3, Characters_Knuckles, ExtraLifeCapsule, 32522}, //DC
        {-3825.48f, 867.02f, -2772.23f, LevelAndActIDs_RedMountain3, Characters_Knuckles, TenRingsCapsule, 32523},

        {-253.36f, 239.01f, 549.60f, LevelAndActIDs_RedMountain2, Characters_Gamma, ExtraLifeCapsule, 53501}, //DX
        {-253.36f, 238.51f, 549.60f, LevelAndActIDs_RedMountain2, Characters_Gamma, ExtraLifeCapsule, 53501}, //DC
        {-1307.60f, 263.59f, 761.86f, LevelAndActIDs_RedMountain2, Characters_Gamma, FiveRingsCapsule, 53502},
        {-1334.64f, 278.59f, 743.83f, LevelAndActIDs_RedMountain2, Characters_Gamma, FiveRingsCapsule, 53503},
        {-1322.05f, 260.59f, 712.15f, LevelAndActIDs_RedMountain2, Characters_Gamma, FiveRingsCapsule, 53504},
        {-224.25f, 213.46f, 196.32f, LevelAndActIDs_RedMountain2, Characters_Gamma, ShieldCapsule, 53505},
        {-1974.16f, 69.70f, 2310.23f, LevelAndActIDs_RedMountain2, Characters_Gamma, FiveRingsCapsule, 53506},
        {-1622.49f, 164.67f, 613.90f, LevelAndActIDs_RedMountain2, Characters_Gamma, TenRingsCapsule, 53507},
        {-1806.52f, 158.33f, 561.50f, LevelAndActIDs_RedMountain2, Characters_Gamma, TenRingsCapsule, 53508},
        {-2125.88f, 215.77f, 742.30f, LevelAndActIDs_RedMountain2, Characters_Gamma, RandomRingsCapsule, 53509},
        {-2114.25f, 214.12f, 712.83f, LevelAndActIDs_RedMountain2, Characters_Gamma, TenRingsCapsule, 53510},

        {344.57f, -340.00f, 909.15f, LevelAndActIDs_SkyDeck1, Characters_Sonic, RandomRingsCapsule, 17501},
        {400.11f, -260.01f, 1125.68f, LevelAndActIDs_SkyDeck1, Characters_Sonic, ExtraLifeCapsule, 17502},
        {30.53f, -430.00f, 1331.03f, LevelAndActIDs_SkyDeck1, Characters_Sonic, RandomRingsCapsule, 17503},
        {399.05f, -330.11f, 1320.09f, LevelAndActIDs_SkyDeck1, Characters_Sonic, ExtraLifeCapsule, 17504},
        {401.52f, -210.01f, 1320.11f, LevelAndActIDs_SkyDeck1, Characters_Sonic, ExtraLifeCapsule, 17505},
        {352.96f, -550.00f, 3059.67f, LevelAndActIDs_SkyDeck1, Characters_Sonic, MagneticShieldCapsule, 17506}, //DX
        {355.96f, -550.00f, 3059.67f, LevelAndActIDs_SkyDeck1, Characters_Sonic, MagneticShieldCapsule, 17506}, //DC
        {436.63f, -350.00f, 3643.61f, LevelAndActIDs_SkyDeck1, Characters_Sonic, MagneticShieldCapsule, 17507}, //DX
        {312.60f, -390.00f, 3650.00f, LevelAndActIDs_SkyDeck1, Characters_Sonic, MagneticShieldCapsule, 17507}, //DC
        {66.46f, -424.02f, 3688.62f, LevelAndActIDs_SkyDeck1, Characters_Sonic, BombCapsule, 17508},
        {487.70f, -450.00f, 3727.33f, LevelAndActIDs_SkyDeck1, Characters_Sonic, ExtraLifeCapsule, 17509},
        {487.18f, -450.00f, 3746.73f, LevelAndActIDs_SkyDeck1, Characters_Sonic, InvincibilityCapsule, 17510},
        {503.13f, -280.00f, 3750.18f, LevelAndActIDs_SkyDeck1, Characters_Sonic, SpeedUpCapsule, 17511}, //DX
        {503.13f, -280.00f, 3750.58f, LevelAndActIDs_SkyDeck1, Characters_Sonic, SpeedUpCapsule, 17511}, //DC
        {401.77f, -390.01f, 3900.33f, LevelAndActIDs_SkyDeck1, Characters_Sonic, TenRingsCapsule, 17512},
        {400.33f, -330.01f, 3900.05f, LevelAndActIDs_SkyDeck1, Characters_Sonic, TenRingsCapsule, 17513},
        {598.43f, -360.01f, 3898.98f, LevelAndActIDs_SkyDeck1, Characters_Sonic, TenRingsCapsule, 17514},
        {599.71f, -420.01f, 3900.24f, LevelAndActIDs_SkyDeck1, Characters_Sonic, TenRingsCapsule, 17515},
        {401.04f, -601.00f, 4220.15f, LevelAndActIDs_SkyDeck1, Characters_Sonic, ExtraLifeCapsule, 17516}, //DX
        {401.04f, -599.50f, 4220.15f, LevelAndActIDs_SkyDeck1, Characters_Sonic, ExtraLifeCapsule, 17516}, //DC
        {400.71f, -340.00f, 4637.70f, LevelAndActIDs_SkyDeck1, Characters_Sonic, MagneticShieldCapsule, 17517},
        {399.90f, -451.00f, 4638.84f, LevelAndActIDs_SkyDeck1, Characters_Sonic, MagneticShieldCapsule, 17518},
        {399.90f, -571.00f, 4638.84f, LevelAndActIDs_SkyDeck1, Characters_Sonic, MagneticShieldCapsule, 17519},
        {364.98f, -68.80f, 2262.72f, LevelAndActIDs_SkyDeck2, Characters_Sonic, FiveRingsCapsule, 17520}, //DX
        {364.98f, -66.29f, 2262.72f, LevelAndActIDs_SkyDeck2, Characters_Sonic, FiveRingsCapsule, 17520}, //DC
        {286.93f, -68.60f, 2262.42f, LevelAndActIDs_SkyDeck2, Characters_Sonic, FiveRingsCapsule, 17521}, //DX
        {286.98f, -66.29f, 2262.72f, LevelAndActIDs_SkyDeck2, Characters_Sonic, FiveRingsCapsule, 17521}, //DC
        {365.99f, -61.70f, 2217.62f, LevelAndActIDs_SkyDeck2, Characters_Sonic, FiveRingsCapsule, 17522}, //DX
        {365.99f, -62.29f, 2217.62f, LevelAndActIDs_SkyDeck2, Characters_Sonic, FiveRingsCapsule, 17522}, //DC
        {287.99f, -61.70f, 2217.62f, LevelAndActIDs_SkyDeck2, Characters_Sonic, FiveRingsCapsule, 17523}, //DX
        {287.99f, -62.29f, 2217.62f, LevelAndActIDs_SkyDeck2, Characters_Sonic, FiveRingsCapsule, 17523}, //DC
        {-277.37f, -37.60f, 2546.10f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ExtraLifeCapsule, 17524}, //DX
        {-277.49f, -38.98f, 2545.97f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ExtraLifeCapsule, 17524}, //DC
        {-297.37f, -37.60f, 2546.90f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ShieldCapsule, 17525}, //DX
        {-297.49f, -38.98f, 2546.77f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ShieldCapsule, 17525}, //DC
        {589.16f, -100.00f, 1607.41f, LevelAndActIDs_SkyDeck2, Characters_Sonic, MagneticShieldCapsule, 17526},
        {-378.36f, -10.19f, 1069.44f, LevelAndActIDs_SkyDeck2, Characters_Sonic, FiveRingsCapsule, 17527},
        {-408.93f, -7.59f, 1069.63f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ExtraLifeCapsule, 17528},
        {-438.36f, -5.14f, 1069.44f, LevelAndActIDs_SkyDeck2, Characters_Sonic, FiveRingsCapsule, 17529},
        {-602.06f, 0.00f, 1062.98f, LevelAndActIDs_SkyDeck2, Characters_Sonic, BombCapsule, 17530},
        {-841.79f, 0.00f, 1236.95f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ShieldCapsule, 17531},
        {561.12f, -100.00f, 800.44f, LevelAndActIDs_SkyDeck2, Characters_Sonic, TenRingsCapsule, 17532},
        {213.67f, -71.20f, 516.15f, LevelAndActIDs_SkyDeck2, Characters_Sonic, RandomRingsCapsule, 17533},
        {61.21f, -56.21f, 310.93f, LevelAndActIDs_SkyDeck2, Characters_Sonic, RandomRingsCapsule, 17534},
        {-839.37f, 0.00f, 453.12f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ShieldCapsule, 17535},
        {211.34f, -71.32f, 107.86f, LevelAndActIDs_SkyDeck2, Characters_Sonic, MagneticShieldCapsule, 17536},
        {-473.49f, -2.31f, 44.75f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ExtraLifeCapsule, 17537}, //DX
        {-473.49f, 1.50f, 44.75f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ExtraLifeCapsule, 17537}, //DC
        {1163.86f, -119.67f, -3243.07f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ShieldCapsule, 17538},
        {-838.87f, 0.00f, -3387.65f, LevelAndActIDs_SkyDeck2, Characters_Sonic, FiveRingsCapsule, 17539},
        {-840.66f, 0.00f, -3415.38f, LevelAndActIDs_SkyDeck2, Characters_Sonic, FiveRingsCapsule, 17540},
        {140.96f, 0.00f, -4208.06f, LevelAndActIDs_SkyDeck2, Characters_Sonic, RandomRingsCapsule, 17541},
        {181.60f, 0.00f, -4277.61f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ExtraLifeCapsule, 17542},
        {99.44f, 0.00f, -4278.86f, LevelAndActIDs_SkyDeck2, Characters_Sonic, ExtraLifeCapsule, 17543},
        {139.84f, 0.00f, -4346.03f, LevelAndActIDs_SkyDeck2, Characters_Sonic, RandomRingsCapsule, 17544},
        {-837.65f, 0.00f, -4285.22f, LevelAndActIDs_SkyDeck2, Characters_Sonic, FiveRingsCapsule, 17545},
        {-838.78f, 0.00f, -4314.20f, LevelAndActIDs_SkyDeck2, Characters_Sonic, FiveRingsCapsule, 17546},
        {1171.68f, -125.75f, -4404.73f, LevelAndActIDs_SkyDeck2, Characters_Sonic, InvincibilityCapsule, 17547},
        {1172.93f, -125.75f, -4474.71f, LevelAndActIDs_SkyDeck2, Characters_Sonic, MagneticShieldCapsule, 17548},
        {-534.58f, -200.00f, 323.40f, LevelAndActIDs_SkyDeck3, Characters_Sonic, InvincibilityCapsule, 17549},
        {-864.91f, -200.00f, 324.45f, LevelAndActIDs_SkyDeck3, Characters_Sonic, MagneticShieldCapsule, 17550},
        {-400.57f, -110.60f, 230.93f, LevelAndActIDs_SkyDeck3, Characters_Sonic, FiveRingsCapsule, 17551}, //DX
        {-400.57f, -113.44f, 230.93f, LevelAndActIDs_SkyDeck3, Characters_Sonic, FiveRingsCapsule, 17551}, //DC
        {-696.41f, -2.00f, -209.24f, LevelAndActIDs_SkyDeck3, Characters_Sonic, ExtraLifeCapsule, 17552},
        {-866.26f, -200.00f, -243.99f, LevelAndActIDs_SkyDeck3, Characters_Sonic, TenRingsCapsule, 17553},
        {-280.59f, -110.60f, 300.86f, LevelAndActIDs_SkyDeck3, Characters_Sonic, FiveRingsCapsule, 17554}, //DX
        {-280.59f, -112.94f, 300.86f, LevelAndActIDs_SkyDeck3, Characters_Sonic, FiveRingsCapsule, 17554}, //DC
        {-401.32f, -110.60f, -230.47f, LevelAndActIDs_SkyDeck3, Characters_Sonic, FiveRingsCapsule, 17555}, //DX
        {-401.32f, -113.01f, -230.47f, LevelAndActIDs_SkyDeck3, Characters_Sonic, FiveRingsCapsule, 17555}, //DC
        {-1013.48f, -100.30f, -305.27f, LevelAndActIDs_SkyDeck3, Characters_Sonic, RandomRingsCapsule, 17556},
        {-1029.01f, -100.30f, -304.77f, LevelAndActIDs_SkyDeck3, Characters_Sonic, InvincibilityCapsule, 17557},
        {-1044.14f, -100.30f, -304.02f, LevelAndActIDs_SkyDeck3, Characters_Sonic, ShieldCapsule, 17558},
        {-280.28f, -110.60f, -300.64f, LevelAndActIDs_SkyDeck3, Characters_Sonic, FiveRingsCapsule, 17559}, //DX
        {-280.28f, -113.01f, -300.64f, LevelAndActIDs_SkyDeck3, Characters_Sonic, FiveRingsCapsule, 17559}, //DC
        {193.59f, -55.00f, -136.90f, LevelAndActIDs_SkyDeck3, Characters_Sonic, FiveRingsCapsule, 17560},
        {245.39f, -20.40f, 2.38f, LevelAndActIDs_SkyDeck3, Characters_Sonic, ExtraLifeCapsule, 17561},
        {272.30f, -55.00f, -314.10f, LevelAndActIDs_SkyDeck3, Characters_Sonic, TenRingsCapsule, 17562},
        {417.65f, 61.65f, 136.86f, LevelAndActIDs_SkyDeck3, Characters_Sonic, TenRingsCapsule, 17563},
        {417.65f, 61.65f, 116.86f, LevelAndActIDs_SkyDeck3, Characters_Sonic, TenRingsCapsule, 17564},
        {417.65f, 61.65f, 156.86f, LevelAndActIDs_SkyDeck3, Characters_Sonic, TenRingsCapsule, 17565},
        {391.91f, -55.00f, -243.16f, LevelAndActIDs_SkyDeck3, Characters_Sonic, RandomRingsCapsule, 17566},

        {431.62f, -340.00f, 908.56f, LevelAndActIDs_SkyDeck1, Characters_Tails, RandomRingsCapsule, 23501},
        {400.11f, -260.01f, 1125.68f, LevelAndActIDs_SkyDeck1, Characters_Tails, ExtraLifeCapsule, 23502},
        {30.53f, -430.00f, 1331.03f, LevelAndActIDs_SkyDeck1, Characters_Tails, RandomRingsCapsule, 23503},
        {401.52f, -210.01f, 1320.11f, LevelAndActIDs_SkyDeck1, Characters_Tails, ExtraLifeCapsule, 23504},
        {225.96f, -460.99f, 2558.69f, LevelAndActIDs_SkyDeck1, Characters_Tails, RandomRingsCapsule, 23505},
        {353.07f, -550.00f, 3062.50f, LevelAndActIDs_SkyDeck1, Characters_Tails, MagneticShieldCapsule, 23506}, //DX
        {358.07f, -550.00f, 3062.50f, LevelAndActIDs_SkyDeck1, Characters_Tails, MagneticShieldCapsule, 23506}, //DC
        {607.46f, -433.00f, 3092.82f, LevelAndActIDs_SkyDeck1, Characters_Tails, RandomRingsCapsule, 23507}, //DX
        {607.46f, -431.43f, 3092.82f, LevelAndActIDs_SkyDeck1, Characters_Tails, RandomRingsCapsule, 23507}, //DC
        {172.68f, -432.32f, 3258.83f, LevelAndActIDs_SkyDeck1, Characters_Tails, RandomRingsCapsule, 23508}, //DX
        {172.68f, -431.43f, 3258.83f, LevelAndActIDs_SkyDeck1, Characters_Tails, RandomRingsCapsule, 23508}, //DC
        {422.34f, -350.00f, 3644.50f, LevelAndActIDs_SkyDeck1, Characters_Tails, MagneticShieldCapsule, 23509}, //DX
        {312.60f, -390.00f, 3650.00f, LevelAndActIDs_SkyDeck1, Characters_Tails, MagneticShieldCapsule, 23509}, //DC
        {65.42f, -424.72f, 3689.73f, LevelAndActIDs_SkyDeck1, Characters_Tails, InvincibilityCapsule, 23510},
        {487.70f, -450.00f, 3727.33f, LevelAndActIDs_SkyDeck1, Characters_Tails, ExtraLifeCapsule, 23511},
        {487.18f, -450.00f, 3746.73f, LevelAndActIDs_SkyDeck1, Characters_Tails, InvincibilityCapsule, 23512},
        {503.13f, -280.00f, 3750.18f, LevelAndActIDs_SkyDeck1, Characters_Tails, SpeedUpCapsule, 23513}, //DX
        {507.48f, -277.00f, 3750.65f, LevelAndActIDs_SkyDeck1, Characters_Tails, SpeedUpCapsule, 23513}, //DC
        {401.77f, -388.01f, 3900.33f, LevelAndActIDs_SkyDeck1, Characters_Tails, TenRingsCapsule, 23514},
        {400.33f, -330.01f, 3900.05f, LevelAndActIDs_SkyDeck1, Characters_Tails, TenRingsCapsule, 23515},
        {598.43f, -360.01f, 3898.98f, LevelAndActIDs_SkyDeck1, Characters_Tails, TenRingsCapsule, 23516},
        {599.71f, -420.01f, 3900.24f, LevelAndActIDs_SkyDeck1, Characters_Tails, TenRingsCapsule, 23517},
        {401.04f, -601.00f, 4220.15f, LevelAndActIDs_SkyDeck1, Characters_Tails, ExtraLifeCapsule, 23518}, //DX
        {401.04f, -599.50f, 4220.15f, LevelAndActIDs_SkyDeck1, Characters_Tails, ExtraLifeCapsule, 23518}, //DC
        {400.71f, -340.00f, 4637.70f, LevelAndActIDs_SkyDeck1, Characters_Tails, InvincibilityCapsule, 23519},
        {399.90f, -451.00f, 4638.84f, LevelAndActIDs_SkyDeck1, Characters_Tails, ShieldCapsule, 23520},
        {399.90f, -571.00f, 4638.84f, LevelAndActIDs_SkyDeck1, Characters_Tails, ShieldCapsule, 23521},
        {97.24f, -281.02f, 4859.46f, LevelAndActIDs_SkyDeck1, Characters_Tails, FiveRingsCapsule, 23522},
        {197.24f, -281.02f, 4859.46f, LevelAndActIDs_SkyDeck1, Characters_Tails, FiveRingsCapsule, 23523},
        {297.24f, -281.02f, 4859.46f, LevelAndActIDs_SkyDeck1, Characters_Tails, FiveRingsCapsule, 23524},
        {-200.29f, -401.60f, 5248.75f, LevelAndActIDs_SkyDeck1, Characters_Tails, TenRingsCapsule, 23525},
        {-200.29f, -401.60f, 5348.75f, LevelAndActIDs_SkyDeck1, Characters_Tails, TenRingsCapsule, 23526},
        {-200.29f, -401.60f, 5448.75f, LevelAndActIDs_SkyDeck1, Characters_Tails, TenRingsCapsule, 23527},
        {-201.25f, -281.55f, 5568.55f, LevelAndActIDs_SkyDeck1, Characters_Tails, FiveRingsCapsule, 23528},
        {-201.25f, -521.60f, 5568.55f, LevelAndActIDs_SkyDeck1, Characters_Tails, RandomRingsCapsule, 23529},
        {-201.25f, -281.55f, 5668.55f, LevelAndActIDs_SkyDeck1, Characters_Tails, FiveRingsCapsule, 23530},
        {-201.25f, -521.60f, 5668.55f, LevelAndActIDs_SkyDeck1, Characters_Tails, RandomRingsCapsule, 23531},
        {-201.25f, -281.55f, 5768.55f, LevelAndActIDs_SkyDeck1, Characters_Tails, FiveRingsCapsule, 23532},
        {-201.25f, -521.60f, 5768.55f, LevelAndActIDs_SkyDeck1, Characters_Tails, RandomRingsCapsule, 23533},
        {511.45f, -401.60f, 6060.44f, LevelAndActIDs_SkyDeck1, Characters_Tails, TenRingsCapsule, 23534},
        {611.45f, -401.60f, 6060.44f, LevelAndActIDs_SkyDeck1, Characters_Tails, TenRingsCapsule, 23535},
        {711.45f, -401.60f, 6060.44f, LevelAndActIDs_SkyDeck1, Characters_Tails, TenRingsCapsule, 23536},

        {430.12f, 38.50f, 0.99f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, SpeedUpCapsule, 34501},
        {675.50f, -81.00f, 118.59f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, RandomRingsCapsule, 34502},
        {378.06f, -54.00f, -117.40f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, RandomRingsCapsule, 34503},
        {686.63f, -81.00f, -301.66f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, ShieldCapsule, 34504},
        {342.68f, 178.18f, 434.17f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, ExtraLifeCapsule, 34505},
        {180.25f, -54.00f, 203.10f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, RandomRingsCapsule, 34506},
        {104.37f, 181.18f, -440.92f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, FiveRingsCapsule, 34507},
        {-535.71f, -200.00f, 323.03f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, TenRingsCapsule, 34508}, //DX
        {-535.71f, -199.00f, 323.03f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, TenRingsCapsule, 34508}, //DC
        {-600.60f, -176.00f, -374.95f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, ShieldCapsule, 34509},
        {-865.65f, -200.00f, 323.07f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, TenRingsCapsule, 34510}, //DX
        {-865.65f, -199.00f, 323.07f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, TenRingsCapsule, 34510}, //DC
        {-1013.48f, -100.30f, -305.27f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, RandomRingsCapsule, 34511},
        {-1044.14f, -100.30f, -304.02f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, ShieldCapsule, 34512},

        {4066.71f, -2818.00f, 1305.42f, LevelAndActIDs_LostWorld1, Characters_Sonic, SpeedUpCapsule, 18501},
        {4284.63f, -2721.00f, 1339.32f, LevelAndActIDs_LostWorld1, Characters_Sonic, TenRingsCapsule, 18502},
        {5300.60f, -2514.00f, 1215.86f, LevelAndActIDs_LostWorld1, Characters_Sonic, MagneticShieldCapsule, 18503},
        {5259.94f, -2662.49f, 1544.19f, LevelAndActIDs_LostWorld1, Characters_Sonic, FiveRingsCapsule, 18504}, //DX
        {5259.94f, -2663.29f, 1544.19f, LevelAndActIDs_LostWorld1, Characters_Sonic, FiveRingsCapsule, 18504}, //DC
        {5709.06f, -2619.00f, 1157.37f, LevelAndActIDs_LostWorld1, Characters_Sonic, RandomRingsCapsule, 18505},
        {5607.78f, -2545.00f, 1675.57f, LevelAndActIDs_LostWorld1, Characters_Sonic, MagneticShieldCapsule, 18506},
        {5629.72f, -2545.00f, 1672.61f, LevelAndActIDs_LostWorld1, Characters_Sonic, ExtraLifeCapsule, 18507}, //DX
        {5629.72f, -2545.20f, 1672.61f, LevelAndActIDs_LostWorld1, Characters_Sonic, ExtraLifeCapsule, 18507}, //DC
        {5771.92f, -2480.00f, 1582.92f, LevelAndActIDs_LostWorld1, Characters_Sonic, TenRingsCapsule, 18508},
        {520.78f, 137.00f, -5.51f, LevelAndActIDs_LostWorld2, Characters_Sonic, ShieldCapsule, 18509},
        {660.24f, 177.00f, 379.51f, LevelAndActIDs_LostWorld2, Characters_Sonic, MagneticShieldCapsule, 18510},
        {1446.97f, -1325.60f, 1219.04f, LevelAndActIDs_LostWorld2, Characters_Sonic, ShieldCapsule, 18511}, //DX
        {1446.97f, -1326.00f, 1219.04f, LevelAndActIDs_LostWorld2, Characters_Sonic, ShieldCapsule, 18511}, //DC
        {3476.32f, -1692.00f, 1381.89f, LevelAndActIDs_LostWorld2, Characters_Sonic, RandomRingsCapsule, 18512},
        {5310.11f, -2239.00f, 1350.63f, LevelAndActIDs_LostWorld2, Characters_Sonic, MagneticShieldCapsule, 18513},
        {6123.63f, -2531.00f, 1358.49f, LevelAndActIDs_LostWorld2, Characters_Sonic, RandomRingsCapsule, 18514},
        {7117.84f, -2340.05f, 854.00f, LevelAndActIDs_LostWorld2, Characters_Sonic, FiveRingsCapsule, 18515}, //DX
        {7117.84f, -2340.07f, 854.00f, LevelAndActIDs_LostWorld2, Characters_Sonic, FiveRingsCapsule, 18515}, //DC
        {7223.73f, -2644.98f, 662.76f, LevelAndActIDs_LostWorld2, Characters_Sonic, RandomRingsCapsule, 18516},
        {7215.16f, -2540.19f, 1047.94f, LevelAndActIDs_LostWorld2, Characters_Sonic, TenRingsCapsule, 18517}, //DX
        {7215.16f, -2540.59f, 1047.94f, LevelAndActIDs_LostWorld2, Characters_Sonic, TenRingsCapsule, 18517}, //DC
        {7214.43f, -2540.19f, 1066.19f, LevelAndActIDs_LostWorld2, Characters_Sonic, TenRingsCapsule, 18518}, //DX
        {7214.43f, -2540.59f, 1066.19f, LevelAndActIDs_LostWorld2, Characters_Sonic, TenRingsCapsule, 18518}, //DC
        {7207.14f, -2639.03f, 1100.62f, LevelAndActIDs_LostWorld2, Characters_Sonic, FiveRingsCapsule, 18519}, //DX
        {7207.14f, -2639.59f, 1100.62f, LevelAndActIDs_LostWorld2, Characters_Sonic, FiveRingsCapsule, 18519}, //DC
        {7663.00f, -2346.52f, 640.49f, LevelAndActIDs_LostWorld2, Characters_Sonic, RandomRingsCapsule, 18520}, //DX
        {7663.00f, -2346.92f, 640.49f, LevelAndActIDs_LostWorld2, Characters_Sonic, RandomRingsCapsule, 18520}, //DC
        {7412.23f, -2614.99f, 1369.26f, LevelAndActIDs_LostWorld2, Characters_Sonic, ShieldCapsule, 18521},
        {7539.95f, -2545.00f, 1097.54f, LevelAndActIDs_LostWorld2, Characters_Sonic, ExtraLifeCapsule, 18522}, //DX
        {7539.95f, -2545.53f, 1097.54f, LevelAndActIDs_LostWorld2, Characters_Sonic, ExtraLifeCapsule, 18522}, //DC
        {7671.74f, -2650.98f, 755.59f, LevelAndActIDs_LostWorld2, Characters_Sonic, RandomRingsCapsule, 18523},

        {7539.95f, -2545.53f, 1097.54f, LevelAndActIDs_LostWorld2, Characters_Knuckles, TenRingsCapsule, 33501},
        {7671.74f, -2650.98f, 755.59f, LevelAndActIDs_LostWorld2, Characters_Knuckles, RandomRingsCapsule, 33502},
        {7232.20f, -2644.98f, 659.70f, LevelAndActIDs_LostWorld2, Characters_Knuckles, RandomRingsCapsule, 33503},
        {7178.01f, -2440.00f, 982.54f, LevelAndActIDs_LostWorld2, Characters_Knuckles, RandomRingsCapsule, 33504},
        {7176.45f, -2440.00f, 1000.28f, LevelAndActIDs_LostWorld2, Characters_Knuckles, RandomRingsCapsule, 33505},
        {7663.00f, -2346.92f, 640.49f, LevelAndActIDs_LostWorld2, Characters_Knuckles, RandomRingsCapsule, 33506},
        {7416.14f, -2420.30f, 1334.53f, LevelAndActIDs_LostWorld2, Characters_Knuckles, BombCapsule, 33507},

        {487.79f, 250.67f, 1149.06f, LevelAndActIDs_IceCap1, Characters_Sonic, ExtraLifeCapsule, 13501}, //DX
        {487.79f, 249.67f, 1149.06f, LevelAndActIDs_IceCap1, Characters_Sonic, ExtraLifeCapsule, 13501}, //DC
        {425.06f, 156.33f, 1017.03f, LevelAndActIDs_IceCap1, Characters_Sonic, TenRingsCapsule, 13502},
        {660.97f, 457.59f, 206.05f, LevelAndActIDs_IceCap1, Characters_Sonic, RandomRingsCapsule, 13503},
        {625.70f, 457.76f, 215.63f, LevelAndActIDs_IceCap1, Characters_Sonic, RandomRingsCapsule, 13504},
        {1582.49f, 276.69f, 0.68f, LevelAndActIDs_IceCap2, Characters_Sonic, TenRingsCapsule, 13505}, //DX
        {1582.49f, 276.29f, 0.68f, LevelAndActIDs_IceCap2, Characters_Sonic, TenRingsCapsule, 13505}, //DC
        {1518.92f, 302.20f, -140.47f, LevelAndActIDs_IceCap2, Characters_Sonic, TenRingsCapsule, 13506},
        {1545.58f, 363.10f, 85.26f, LevelAndActIDs_IceCap2, Characters_Sonic, TenRingsCapsule, 13507},
        {1556.39f, 363.10f, 71.18f, LevelAndActIDs_IceCap2, Characters_Sonic, TenRingsCapsule, 13508},
        {1566.28f, 363.10f, 57.45f, LevelAndActIDs_IceCap2, Characters_Sonic, TenRingsCapsule, 13509},

        {1453.84f, 328.20f, -51.93f, LevelAndActIDs_IceCap4, Characters_Big, RandomRingsCapsule, 61501},
        {1191.96f, 332.79f, -257.73f, LevelAndActIDs_IceCap4, Characters_Big, RandomRingsCapsule, 61502},
        {1174.01f, 332.79f, -256.39f, LevelAndActIDs_IceCap4, Characters_Big, ExtraLifeCapsule, 61503},
        {1154.02f, 332.79f, -257.60f, LevelAndActIDs_IceCap4, Characters_Big, RandomRingsCapsule, 61504},
        {1302.02f, 183.14f, -317.41f, LevelAndActIDs_IceCap4, Characters_Big, TenRingsCapsule, 61505},
        {1532.63f, 231.83f, -142.15f, LevelAndActIDs_IceCap4, Characters_Big, SpeedUpCapsule, 61506}, //DX
        {1532.63f, 230.83f, -142.15f, LevelAndActIDs_IceCap4, Characters_Big, SpeedUpCapsule, 61506}, //DC
        {1374.67f, 230.65f, -325.60f, LevelAndActIDs_IceCap4, Characters_Big, SpeedUpCapsule, 61507},
        {1551.38f, 362.79f, 71.25f, LevelAndActIDs_IceCap4, Characters_Big, RandomRingsCapsule, 61508},
        {1579.57f, 362.79f, 68.37f, LevelAndActIDs_IceCap4, Characters_Big, RandomRingsCapsule, 61509},
        {2006.77f, -6.00f, 137.09f, LevelAndActIDs_IceCap4, Characters_Big, InvincibilityCapsule, 61510},
        {2216.39f, -127.00f, -400.81f, LevelAndActIDs_IceCap4, Characters_Big, FiveRingsCapsule, 61511},
        {2235.29f, -142.00f, -340.28f, LevelAndActIDs_IceCap4, Characters_Big, FiveRingsCapsule, 61512},

        {-424.39f, -1717.65f, 2871.62f, LevelAndActIDs_Casinopolis2, Characters_Sonic, BombCapsule, 12501},
        {-609.76f, -1646.90f, 2871.36f, LevelAndActIDs_Casinopolis2, Characters_Sonic, FiveRingsCapsule, 12502}, //DX
        {-609.76f, -1635.65f, 2871.36f, LevelAndActIDs_Casinopolis2, Characters_Sonic, FiveRingsCapsule, 12502}, //DC
        {-706.50f, -1551.65f, 2867.50f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12503},
        {-1193.20f, -1444.90f, 2628.37f, LevelAndActIDs_Casinopolis2, Characters_Sonic, InvincibilityCapsule, 12504},
        {-1268.27f, -1479.73f, 2990.52f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12505},
        {-1279.91f, -1467.73f, 2739.35f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12506},
        {-1371.30f, -1461.73f, 2862.83f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12507},
        {-1266.67f, -849.73f, 2993.23f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12508},
        {-1256.81f, -1058.73f, 3471.35f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12509},
        {-1564.62f, -2161.00f, 2343.22f, LevelAndActIDs_Casinopolis2, Characters_Sonic, InvincibilityCapsule, 12510},
        {-1375.96f, -654.73f, 2860.31f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12511},
        {-1546.19f, -1694.73f, 3624.62f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12512},
        {-1705.33f, -1667.78f, 3308.47f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12513},
        {-1568.32f, -2161.00f, 2146.73f, LevelAndActIDs_Casinopolis2, Characters_Sonic, ShieldCapsule, 12514},
        {-1566.39f, -2161.00f, 1975.18f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12515},
        {-1755.87f, -989.33f, 2465.20f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12516},
        {-1894.80f, -2016.78f, 2635.94f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12517},
        {-1755.29f, -1124.33f, 2222.70f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12518},
        {-1945.00f, -1654.73f, 3007.73f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12519},
        {-1945.00f, -1740.73f, 3007.73f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12520},
        {-1945.00f, -1855.73f, 3007.73f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12521},
        {-1946.66f, -1510.73f, 3004.20f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12522},
        {-1945.00f, -1962.73f, 3007.73f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12523},
        {-1812.78f, -1818.73f, 3618.87f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12524},
        {-1945.00f, -2059.73f, 3007.73f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12525},
        {-1890.55f, -1815.78f, 3500.08f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12526},
        {-1949.06f, -2162.73f, 3007.02f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12527},
        {-1949.06f, -2271.73f, 3007.02f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12528},
        {-2051.82f, -1891.73f, 3159.48f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12529},
        {-2057.31f, -2022.78f, 2646.03f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12530},
        {-2050.37f, -2017.73f, 3152.63f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12531},
        {-2049.83f, -2105.73f, 3142.37f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12532},
        {-2046.48f, -2189.73f, 3133.69f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12533},
        {-2067.68f, -1841.78f, 2364.13f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12534},
        {-2129.79f, -1825.78f, 2633.96f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12535},
        {-2046.73f, -2275.73f, 3127.69f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12536},
        {-1970.94f, -1332.33f, 2021.74f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12537},
        {-2135.76f, -1963.73f, 3618.01f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12538},
        {-2117.57f, -1409.33f, 2018.74f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12539},
        {-2216.91f, -1953.78f, 3493.92f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12540},
        {-2306.32f, -2180.78f, 2950.59f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12541},
        {-2309.81f, -2088.78f, 3205.25f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12542},
        {-2308.60f, -1641.78f, 2248.65f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12543},
        {-2378.38f, -2235.73f, 3136.15f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12544},
        {-2387.76f, -2137.73f, 3396.12f, LevelAndActIDs_Casinopolis2, Characters_Sonic, TenRingsCapsule, 12545},
        {-2.18f, -8.14f, 104.95f, LevelAndActIDs_Casinopolis2, Characters_Sonic, ExtraLifeCapsule, 12546}, //DX
        {-2.18f, -3.00f, 104.95f, LevelAndActIDs_Casinopolis2, Characters_Sonic, ExtraLifeCapsule, 12546}, //DC
        {-1.93f, -3.14f, 39.95f, LevelAndActIDs_Casinopolis2, Characters_Sonic, SpeedUpCapsule, 12547}, //DX
        {-1.93f, -3.00f, 39.95f, LevelAndActIDs_Casinopolis2, Characters_Sonic, SpeedUpCapsule, 12547}, //DC
        {166.62f, 50.00f, 14.55f, LevelAndActIDs_Casinopolis3, Characters_Sonic, ExtraLifeCapsule, 12548},
        {166.62f, 69.00f, 14.55f, LevelAndActIDs_Casinopolis3, Characters_Sonic, RandomRingsCapsule, 12549},
        {-161.40f, 55.00f, 2.32f, LevelAndActIDs_Casinopolis3, Characters_Sonic, ExtraLifeCapsule, 12550},
        {-161.40f, 73.00f, 2.32f, LevelAndActIDs_Casinopolis3, Characters_Sonic, RandomRingsCapsule, 12551},
        {-161.40f, 91.00f, 2.32f, LevelAndActIDs_Casinopolis3, Characters_Sonic, RandomRingsCapsule, 12552},

        {-268.73f, -1761.65f, 2869.84f, LevelAndActIDs_Casinopolis2, Characters_Tails, BombCapsule, 21501},
        {-609.76f, -1635.65f, 2871.36f, LevelAndActIDs_Casinopolis2, Characters_Tails, FiveRingsCapsule, 21502},
        {-651.48f, -1574.65f, 2866.62f, LevelAndActIDs_Casinopolis2, Characters_Tails, FiveRingsCapsule, 21503},
        {-745.81f, -1478.65f, 2864.56f, LevelAndActIDs_Casinopolis2, Characters_Tails, FiveRingsCapsule, 21504},
        {-841.87f, -1490.00f, 2870.30f, LevelAndActIDs_Casinopolis2, Characters_Tails, FiveRingsCapsule, 21505},
        {-1173.27f, -1239.73f, 2849.50f, LevelAndActIDs_Casinopolis2, Characters_Tails, ExtraLifeCapsule, 21506},
        {-1272.48f, -1457.73f, 2947.23f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21507},
        {-1317.33f, -1461.73f, 2859.84f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21508},
        {-306.16f, -1027.97f, 1672.03f, LevelAndActIDs_Casinopolis2, Characters_Tails, MagneticShieldCapsule, 21509},
        {-1244.95f, -1109.73f, 2957.74f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21510},
        {-1338.00f, -1047.73f, 2838.36f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21511},
        {-1291.78f, -942.73f, 2985.27f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21512},
        {-1256.81f, -1058.73f, 3471.35f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21513},
        {-1364.44f, -867.73f, 2872.27f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21514},
        {-1564.62f, -2161.00f, 2343.22f, LevelAndActIDs_Casinopolis2, Characters_Tails, ShieldCapsule, 21515},
        {-1546.19f, -1694.73f, 3624.62f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21516},
        {-1705.33f, -1667.78f, 3308.47f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21517},
        {-1568.32f, -2161.00f, 2146.73f, LevelAndActIDs_Casinopolis2, Characters_Tails, ShieldCapsule, 21518},
        {-1566.39f, -2161.00f, 1975.18f, LevelAndActIDs_Casinopolis2, Characters_Tails, ShieldCapsule, 21519},
        {-1755.87f, -989.33f, 2465.20f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21520},
        {-1894.80f, -2016.78f, 2635.94f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21521},
        {-1755.29f, -1124.33f, 2222.70f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21522},
        {-1945.40f, -1475.73f, 3009.30f, LevelAndActIDs_Casinopolis2, Characters_Tails, ExtraLifeCapsule, 21523},
        {-1812.78f, -1818.73f, 3618.87f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21524},
        {-1982.25f, -1840.73f, 3026.84f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21525},
        {-1890.55f, -1815.78f, 3500.08f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21526},
        {-1980.58f, -2031.73f, 2989.89f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21527},
        {-1949.53f, -2281.73f, 3008.51f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21528},
        {-2044.58f, -1892.73f, 3131.98f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21529},
        {-2057.31f, -2022.78f, 2646.03f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21530},
        {-2067.68f, -1841.78f, 2364.13f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21531},
        {-2043.82f, -2287.73f, 3081.74f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21532},
        {-2129.79f, -1825.78f, 2633.96f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21533},
        {-1970.94f, -1332.33f, 2021.74f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21534},
        {-2135.76f, -1963.73f, 3618.01f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21535},
        {-2117.57f, -1409.33f, 2018.74f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21536},
        {-2216.91f, -1953.78f, 3493.92f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21537},
        {-2306.32f, -2180.78f, 2950.59f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21538},
        {-2309.81f, -2088.78f, 3205.25f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21539},
        {-2308.60f, -1641.78f, 2248.65f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21540},
        {-2378.38f, -2235.73f, 3136.15f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21541},
        {-2387.76f, -2137.73f, 3396.12f, LevelAndActIDs_Casinopolis2, Characters_Tails, TenRingsCapsule, 21542},

        {-136.47f, -137.63f, 184.44f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, ShieldCapsule, 31501},
        {187.35f, -178.00f, -132.14f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, RandomRingsCapsule, 31502},
        {-125.67f, 0.00f, -299.64f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, InvincibilityCapsule, 31503},
        {122.69f, 0.00f, -329.29f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, SpeedUpCapsule, 31504},
        {-58.02f, 195.37f, 286.88f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, TenRingsCapsule, 31505},
        {158.40f, 395.00f, -62.54f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, FiveRingsCapsule, 31506},
        {-103.00f, 362.37f, -227.77f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, TenRingsCapsule, 31507},
        {5.10f, 448.00f, 0.25f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, ExtraLifeCapsule, 31508},
        {-371.68f, 256.37f, 128.00f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, TenRingsCapsule, 31509},
        {434.21f, -60.00f, -178.14f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, RandomRingsCapsule, 31510},
        {-311.90f, 347.37f, 125.55f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, TenRingsCapsule, 31511},
        {423.25f, 230.00f, -123.36f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, ShieldCapsule, 31512},
        {445.34f, -60.00f, -234.32f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, ShieldCapsule, 31513},
        {510.50f, 165.89f, -304.94f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, ExtraLifeCapsule, 31514},
        {782.74f, -133.06f, -381.49f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, ShieldCapsule, 31515},
        {826.23f, -133.06f, -286.71f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, FiveRingsCapsule, 31516},

        {177.63f, -102.98f, -144.15f, LevelAndActIDs_FinalEgg1, Characters_Sonic, ExtraLifeCapsule, 19501},
        {159.63f, -102.98f, -144.15f, LevelAndActIDs_FinalEgg1, Characters_Sonic, MagneticShieldCapsule, 19502},
        {1504.74f, 203.00f, -1297.96f, LevelAndActIDs_FinalEgg1, Characters_Sonic, TenRingsCapsule, 19503},
        {1486.61f, 203.00f, -1314.31f, LevelAndActIDs_FinalEgg1, Characters_Sonic, ExtraLifeCapsule, 19504},
        {1470.60f, 203.00f, -1329.75f, LevelAndActIDs_FinalEgg1, Characters_Sonic, TenRingsCapsule, 19505},
        {1898.63f, 203.99f, -1051.96f, LevelAndActIDs_FinalEgg1, Characters_Sonic, RandomRingsCapsule, 19506},
        {1898.99f, 203.99f, -1066.92f, LevelAndActIDs_FinalEgg1, Characters_Sonic, ExtraLifeCapsule, 19507},
        {1897.98f, 203.99f, -1082.86f, LevelAndActIDs_FinalEgg1, Characters_Sonic, RandomRingsCapsule, 19508},
        {1936.61f, 197.70f, -1459.90f, LevelAndActIDs_FinalEgg1, Characters_Sonic, RandomRingsCapsule, 19509},
        {1938.96f, 197.91f, -1477.75f, LevelAndActIDs_FinalEgg1, Characters_Sonic, RandomRingsCapsule, 19510},
        {1941.32f, 197.90f, -1495.59f, LevelAndActIDs_FinalEgg1, Characters_Sonic, RandomRingsCapsule, 19511},
        {2225.85f, 197.89f, -1201.02f, LevelAndActIDs_FinalEgg1, Characters_Sonic, TenRingsCapsule, 19512},
        {2225.97f, 197.89f, -1221.71f, LevelAndActIDs_FinalEgg1, Characters_Sonic, TenRingsCapsule, 19513},
        {944.42f, 559.19f, -992.26f, LevelAndActIDs_FinalEgg2, Characters_Sonic, FiveRingsCapsule, 19514},
        {942.18f, 86.56f, -744.57f, LevelAndActIDs_FinalEgg2, Characters_Sonic, ExtraLifeCapsule, 19515}, //DX
        {942.18f, 88.93f, -744.57f, LevelAndActIDs_FinalEgg2, Characters_Sonic, ExtraLifeCapsule, 19515}, //DC
        {806.08f, 509.33f, -1127.56f, LevelAndActIDs_FinalEgg2, Characters_Sonic, TenRingsCapsule, 19516},
        {799.51f, 90.78f, -1108.67f, LevelAndActIDs_FinalEgg2, Characters_Sonic, ExtraLifeCapsule, 19517},
        {1018.62f, -387.63f, -715.43f, LevelAndActIDs_FinalEgg2, Characters_Sonic, TenRingsCapsule, 19518}, //DX
        {1018.62f, -388.33f, -715.43f, LevelAndActIDs_FinalEgg2, Characters_Sonic, TenRingsCapsule, 19518}, //DC
        {1093.73f, -850.00f, -1072.55f, LevelAndActIDs_FinalEgg2, Characters_Sonic, FiveRingsCapsule, 19519},
        {1093.73f, -850.00f, -1092.55f, LevelAndActIDs_FinalEgg2, Characters_Sonic, FiveRingsCapsule, 19520},
        {1093.73f, -850.00f, -1112.55f, LevelAndActIDs_FinalEgg2, Characters_Sonic, FiveRingsCapsule, 19521},
        {899.22f, 47.18f, -814.03f, LevelAndActIDs_FinalEgg3, Characters_Sonic, RandomRingsCapsule, 19522},
        {1073.71f, -10.62f, -826.69f, LevelAndActIDs_FinalEgg3, Characters_Sonic, RandomRingsCapsule, 19523},
        {1093.70f, -10.62f, -826.47f, LevelAndActIDs_FinalEgg3, Characters_Sonic, ExtraLifeCapsule, 19524},
        {1052.70f, -10.62f, -826.92f, LevelAndActIDs_FinalEgg3, Characters_Sonic, MagneticShieldCapsule, 19525},
        {899.22f, 47.18f, -834.03f, LevelAndActIDs_FinalEgg3, Characters_Sonic, RandomRingsCapsule, 19526},
        {899.22f, 47.18f, -854.03f, LevelAndActIDs_FinalEgg3, Characters_Sonic, RandomRingsCapsule, 19527},
        {1209.16f, 111.17f, -980.11f, LevelAndActIDs_FinalEgg3, Characters_Sonic, ExtraLifeCapsule, 19528},
        {1317.62f, -297.22f, -1461.64f, LevelAndActIDs_FinalEgg3, Characters_Sonic, ExtraLifeCapsule, 19529},
        {1139.24f, -257.00f, -1559.41f, LevelAndActIDs_FinalEgg3, Characters_Sonic, RandomRingsCapsule, 19530},
        {1034.24f, -257.00f, -1562.28f, LevelAndActIDs_FinalEgg3, Characters_Sonic, RandomRingsCapsule, 19531},
        {1097.08f, -257.00f, -1563.25f, LevelAndActIDs_FinalEgg3, Characters_Sonic, RandomRingsCapsule, 19532},
        {994.90f, -257.00f, -1566.10f, LevelAndActIDs_FinalEgg3, Characters_Sonic, RandomRingsCapsule, 19533},
        {1468.63f, -357.65f, -1444.59f, LevelAndActIDs_FinalEgg3, Characters_Sonic, ExtraLifeCapsule, 19534},
        {1729.31f, -184.15f, -1831.08f, LevelAndActIDs_FinalEgg3, Characters_Sonic, MagneticShieldCapsule, 19535},
        {1749.31f, -184.15f, -1831.08f, LevelAndActIDs_FinalEgg3, Characters_Sonic, FiveRingsCapsule, 19536},
        {1769.31f, -184.15f, -1831.08f, LevelAndActIDs_FinalEgg3, Characters_Sonic, SpeedUpCapsule, 19537},
        {2090.62f, -343.53f, -1864.78f, LevelAndActIDs_FinalEgg3, Characters_Sonic, TenRingsCapsule, 19538}, //DX
        {2090.62f, -343.53f, -1869.78f, LevelAndActIDs_FinalEgg3, Characters_Sonic, TenRingsCapsule, 19538}, //DC
        {2147.62f, -343.53f, -1864.78f, LevelAndActIDs_FinalEgg3, Characters_Sonic, TenRingsCapsule, 19539}, //DX
        {2147.62f, -343.53f, -1869.78f, LevelAndActIDs_FinalEgg3, Characters_Sonic, TenRingsCapsule, 19539}, //DC
        {2772.57f, -525.82f, -994.46f, LevelAndActIDs_FinalEgg3, Characters_Sonic, TenRingsCapsule, 19540},
        {2615.32f, -278.90f, -1629.70f, LevelAndActIDs_FinalEgg3, Characters_Sonic, SpeedUpCapsule, 19541},
        {2615.22f, -278.90f, -1764.73f, LevelAndActIDs_FinalEgg3, Characters_Sonic, ExtraLifeCapsule, 19542},
        {2260.76f, -2739.37f, -1175.08f, LevelAndActIDs_FinalEgg3, Characters_Sonic, ExtraLifeCapsule, 19543},
        {2283.76f, -2739.37f, -1175.08f, LevelAndActIDs_FinalEgg3, Characters_Sonic, RandomRingsCapsule, 19544},
        {16.42f, -3003.81f, -298.32f, LevelAndActIDs_FinalEgg3, Characters_Sonic, ExtraLifeCapsule, 19545},
        {856.85f, -3171.44f, -489.48f, LevelAndActIDs_FinalEgg3, Characters_Sonic, ExtraLifeCapsule, 19546}, //DX
        {856.85f, -3171.89f, -489.48f, LevelAndActIDs_FinalEgg3, Characters_Sonic, ExtraLifeCapsule, 19546}, //DC
        {16.42f, -3003.81f, -278.32f, LevelAndActIDs_FinalEgg3, Characters_Sonic, ExtraLifeCapsule, 19547},
        {-3.58f, -3003.81f, -298.32f, LevelAndActIDs_FinalEgg3, Characters_Sonic, ExtraLifeCapsule, 19548},
        {778.08f, -3171.82f, -461.07f, LevelAndActIDs_FinalEgg3, Characters_Sonic, RandomRingsCapsule, 19549}, //DX
        {778.08f, -3171.89f, -461.07f, LevelAndActIDs_FinalEgg3, Characters_Sonic, RandomRingsCapsule, 19549}, //DC
        {-3.58f, -3003.81f, -278.32f, LevelAndActIDs_FinalEgg3, Characters_Sonic, ExtraLifeCapsule, 19550},
        {745.32f, -3171.89f, -416.49f, LevelAndActIDs_FinalEgg3, Characters_Sonic, RandomRingsCapsule, 19551}, //DX
        {745.32f, -3171.89f, -416.49f, LevelAndActIDs_FinalEgg3, Characters_Sonic, RandomRingsCapsule, 19551}, //DC
        {1725.38f, -3173.75f, -231.65f, LevelAndActIDs_FinalEgg3, Characters_Sonic, TenRingsCapsule, 19552},
        {1750.38f, -3173.75f, -231.65f, LevelAndActIDs_FinalEgg3, Characters_Sonic, TenRingsCapsule, 19553},
        {2269.04f, -3002.76f, -1048.76f, LevelAndActIDs_FinalEgg3, Characters_Sonic, SpeedUpCapsule, 19554},
        {2648.57f, -2888.19f, -942.62f, LevelAndActIDs_FinalEgg3, Characters_Sonic, TenRingsCapsule, 19555},
        {2660.11f, -2888.19f, -926.67f, LevelAndActIDs_FinalEgg3, Characters_Sonic, TenRingsCapsule, 19556},
        {2660.71f, -2888.19f, -957.56f, LevelAndActIDs_FinalEgg3, Characters_Sonic, TenRingsCapsule, 19557},
        {2673.09f, -2888.19f, -940.41f, LevelAndActIDs_FinalEgg3, Characters_Sonic, TenRingsCapsule, 19558},
        {2824.94f, -2973.00f, -988.95f, LevelAndActIDs_FinalEgg3, Characters_Sonic, TenRingsCapsule, 19559},
        {2824.94f, -2973.00f, -1008.95f, LevelAndActIDs_FinalEgg3, Characters_Sonic, TenRingsCapsule, 19560},
        {2824.94f, -2973.00f, -1028.95f, LevelAndActIDs_FinalEgg3, Characters_Sonic, TenRingsCapsule, 19561},

        {548.45f, -232.00f, -1552.75f, LevelAndActIDs_FinalEgg1, Characters_Amy, ExtraLifeCapsule, 42501},
        {1629.58f, 240.00f, -1319.99f, LevelAndActIDs_FinalEgg1, Characters_Amy, ExtraLifeCapsule, 42502},
        {1595.75f, 185.73f, -1573.47f, LevelAndActIDs_FinalEgg1, Characters_Amy, TenRingsCapsule, 42503},
        {2871.52f, 5253.00f, -2060.12f, LevelAndActIDs_FinalEgg1, Characters_Amy, RandomRingsCapsule, 42504},
        {2871.94f, 5253.00f, -2079.11f, LevelAndActIDs_FinalEgg1, Characters_Amy, RandomRingsCapsule, 42505},
        {2872.41f, 5253.00f, -2100.11f, LevelAndActIDs_FinalEgg1, Characters_Amy, RandomRingsCapsule, 42506},
        {2873.06f, 5253.00f, -2115.67f, LevelAndActIDs_FinalEgg1, Characters_Amy, RandomRingsCapsule, 42507},


        {763.98f, -3172.31f, -440.43f, LevelAndActIDs_FinalEgg3, Characters_Gamma, TenRingsCapsule, 50501}, //DX
        {763.98f, -3170.90f, -440.43f, LevelAndActIDs_FinalEgg3, Characters_Gamma, TenRingsCapsule, 50501}, //DC
        {785.93f, -3172.81f, -454.29f, LevelAndActIDs_FinalEgg3, Characters_Gamma, TenRingsCapsule, 50502}, //DX
        {785.93f, -3170.90f, -454.29f, LevelAndActIDs_FinalEgg3, Characters_Gamma, TenRingsCapsule, 50502}, //DC
        {806.39f, -3172.63f, -465.75f, LevelAndActIDs_FinalEgg3, Characters_Gamma, TenRingsCapsule, 50503}, //DX
        {806.39f, -3170.90f, -465.75f, LevelAndActIDs_FinalEgg3, Characters_Gamma, TenRingsCapsule, 50503}, //DC
        {823.06f, -3172.69f, -472.81f, LevelAndActIDs_FinalEgg3, Characters_Gamma, TenRingsCapsule, 50504}, //DX
        {823.06f, -3170.90f, -472.81f, LevelAndActIDs_FinalEgg3, Characters_Gamma, TenRingsCapsule, 50504}, //DC
        {873.90f, -3181.86f, -322.29f, LevelAndActIDs_FinalEgg3, Characters_Gamma, TenRingsCapsule, 50505},
        {843.19f, -3172.38f, -478.83f, LevelAndActIDs_FinalEgg3, Characters_Gamma, TenRingsCapsule, 50506}, //DX
        {843.19f, -3170.90f, -478.83f, LevelAndActIDs_FinalEgg3, Characters_Gamma, TenRingsCapsule, 50506}, //DC
        {928.87f, -3181.86f, -321.90f, LevelAndActIDs_FinalEgg3, Characters_Gamma, TenRingsCapsule, 50507},
        {1453.49f, -3173.76f, -219.26f, LevelAndActIDs_FinalEgg3, Characters_Gamma, TenRingsCapsule, 50508},
        {1453.49f, -3173.76f, -199.26f, LevelAndActIDs_FinalEgg3, Characters_Gamma, TenRingsCapsule, 50509},
        {1453.49f, -3173.76f, -179.26f, LevelAndActIDs_FinalEgg3, Characters_Gamma, TenRingsCapsule, 50510},

        {51.64f, -0.03f, -377.60f, LevelAndActIDs_HotShelter1, Characters_Amy, ShieldCapsule, 41501},
        {-226.93f, 0.00f, -628.42f, LevelAndActIDs_HotShelter1, Characters_Amy, SpeedUpCapsule, 41502},
        {-227.14f, 0.00f, -650.42f, LevelAndActIDs_HotShelter1, Characters_Amy, ShieldCapsule, 41503},
        {445.91f, 32.00f, -649.46f, LevelAndActIDs_HotShelter1, Characters_Amy, BombCapsule, 41504},
        {750.31f, -80.00f, -516.03f, LevelAndActIDs_HotShelter1, Characters_Amy, TenRingsCapsule, 41505},
        {744.53f, -80.00f, -778.16f, LevelAndActIDs_HotShelter1, Characters_Amy, TenRingsCapsule, 41506},
        {1608.51f, 35.01f, -623.03f, LevelAndActIDs_HotShelter1, Characters_Amy, RandomRingsCapsule, 41507},
        {1717.26f, 34.01f, -676.35f, LevelAndActIDs_HotShelter1, Characters_Amy, RandomRingsCapsule, 41508},
        {147.80f, 250.00f, -286.64f, LevelAndActIDs_HotShelter2, Characters_Amy, TenRingsCapsule, 41509}, //DX
        {147.80f, 253.95f, -286.64f, LevelAndActIDs_HotShelter2, Characters_Amy, TenRingsCapsule, 41509}, //DC
        {282.17f, 250.00f, -207.25f, LevelAndActIDs_HotShelter2, Characters_Amy, TenRingsCapsule, 41510}, //DX
        {282.17f, 253.95f, -207.25f, LevelAndActIDs_HotShelter2, Characters_Amy, TenRingsCapsule, 41510}, //DC
        {-20.48f, 230.99f, -360.05f, LevelAndActIDs_HotShelter2, Characters_Amy, TenRingsCapsule, 41511},
        {-14.14f, 50.78f, -437.43f, LevelAndActIDs_HotShelter2, Characters_Amy, InvincibilityCapsule, 41512},
        {-29.18f, 50.78f, -437.51f, LevelAndActIDs_HotShelter2, Characters_Amy, ExtraLifeCapsule, 41513},
        {-20.66f, 250.00f, -140.47f, LevelAndActIDs_HotShelter2, Characters_Amy, ShieldCapsule, 41514},
        {-7.56f, -210.02f, -310.00f, LevelAndActIDs_HotShelter2, Characters_Amy, SpeedUpCapsule, 41515},
        {-20.54f, -210.02f, -309.41f, LevelAndActIDs_HotShelter2, Characters_Amy, TenRingsCapsule, 41516},
        {-33.25f, -210.02f, -308.73f, LevelAndActIDs_HotShelter2, Characters_Amy, SpeedUpCapsule, 41517},
        {-320.14f, 250.00f, -248.29f, LevelAndActIDs_HotShelter2, Characters_Amy, ExtraLifeCapsule, 41518}, //DX
        {-320.14f, 253.95f, -248.29f, LevelAndActIDs_HotShelter2, Characters_Amy, ExtraLifeCapsule, 41518}, //DC
        {146.41f, -105.00f, -971.53f, LevelAndActIDs_HotShelter2, Characters_Amy, TenRingsCapsule, 41519},
        {18.51f, -12.00f, -1082.97f, LevelAndActIDs_HotShelter2, Characters_Amy, FiveRingsCapsule, 41520},
        {-216.95f, 78.00f, -1020.74f, LevelAndActIDs_HotShelter2, Characters_Amy, SpeedUpCapsule, 41521},
        {-57.49f, -12.00f, -1082.97f, LevelAndActIDs_HotShelter2, Characters_Amy, FiveRingsCapsule, 41522},
        {-233.44f, 78.00f, -1021.03f, LevelAndActIDs_HotShelter2, Characters_Amy, InvincibilityCapsule, 41523},
        {-185.03f, -105.00f, -972.24f, LevelAndActIDs_HotShelter2, Characters_Amy, TenRingsCapsule, 41524},
        {18.51f, -12.00f, -1122.97f, LevelAndActIDs_HotShelter2, Characters_Amy, FiveRingsCapsule, 41525},
        {-57.49f, -12.00f, -1122.97f, LevelAndActIDs_HotShelter2, Characters_Amy, FiveRingsCapsule, 41526},
        {783.78f, 150.00f, -1808.93f, LevelAndActIDs_HotShelter2, Characters_Amy, ShieldCapsule, 41527},
        {538.82f, 247.00f, -2162.60f, LevelAndActIDs_HotShelter2, Characters_Amy, TenRingsCapsule, 41528},
        {538.82f, 547.00f, -2202.60f, LevelAndActIDs_HotShelter2, Characters_Amy, TenRingsCapsule, 41529},
        {538.82f, 1040.00f, -2092.60f, LevelAndActIDs_HotShelter2, Characters_Amy, ExtraLifeCapsule, 41530},
        {538.82f, 840.00f, -2182.60f, LevelAndActIDs_HotShelter2, Characters_Amy, TenRingsCapsule, 41531},
        {786.87f, 428.24f, -3293.38f, LevelAndActIDs_HotShelter2, Characters_Amy, TenRingsCapsule, 41532},
        {841.84f, 428.24f, -3295.21f, LevelAndActIDs_HotShelter2, Characters_Amy, ExtraLifeCapsule, 41533},
        {129.97f, 370.00f, -3615.42f, LevelAndActIDs_HotShelter2, Characters_Amy, BombCapsule, 41534},
        {1089.12f, 246.00f, -3601.65f, LevelAndActIDs_HotShelter2, Characters_Amy, InvincibilityCapsule, 41535}, //DX
        {1089.12f, 245.60f, -3601.65f, LevelAndActIDs_HotShelter2, Characters_Amy, InvincibilityCapsule, 41535}, //DC
        {1087.79f, 246.00f, -3658.55f, LevelAndActIDs_HotShelter2, Characters_Amy, SpeedUpCapsule, 41536},
        {1087.13f, 246.00f, -3709.75f, LevelAndActIDs_HotShelter2, Characters_Amy, ShieldCapsule, 41537},

        {160.82f, 261.58f, -218.85f, LevelAndActIDs_HotShelter3, Characters_Gamma, RandomRingsCapsule, 54501},
        {-28.29f, 50.78f, -433.41f, LevelAndActIDs_HotShelter3, Characters_Gamma, ExtraLifeCapsule, 54502},
        {-13.45f, 50.78f, -433.88f, LevelAndActIDs_HotShelter3, Characters_Gamma, SpeedUpCapsule, 54503},
        {-34.67f, -210.00f, -307.87f, LevelAndActIDs_HotShelter3, Characters_Gamma, TenRingsCapsule, 54504},
        {-19.68f, -210.00f, -308.24f, LevelAndActIDs_HotShelter3, Characters_Gamma, ShieldCapsule, 54505},
        {-3.68f, -210.00f, -308.62f, LevelAndActIDs_HotShelter3, Characters_Gamma, TenRingsCapsule, 54506},
        {-21.97f, 53.99f, -609.04f, LevelAndActIDs_HotShelter3, Characters_Gamma, TenRingsCapsule, 54507},
        {8.03f, 53.99f, -609.04f, LevelAndActIDs_HotShelter3, Characters_Gamma, TenRingsCapsule, 54508},
        {-51.97f, 53.99f, -609.04f, LevelAndActIDs_HotShelter3, Characters_Gamma, TenRingsCapsule, 54509},
        {38.03f, 53.99f, -609.04f, LevelAndActIDs_HotShelter3, Characters_Gamma, TenRingsCapsule, 54510},
        {-81.97f, 53.99f, -609.04f, LevelAndActIDs_HotShelter3, Characters_Gamma, TenRingsCapsule, 54511},
        {-1197.13f, 170.00f, -1783.91f, LevelAndActIDs_HotShelter3, Characters_Gamma, RandomRingsCapsule, 54512},
        {-1237.13f, 170.00f, -1783.91f, LevelAndActIDs_HotShelter3, Characters_Gamma, FiveRingsCapsule, 54513},
        {-1197.13f, 170.00f, -1835.91f, LevelAndActIDs_HotShelter3, Characters_Gamma, RandomRingsCapsule, 54514},
        {-1237.13f, 170.00f, -1835.91f, LevelAndActIDs_HotShelter3, Characters_Gamma, RandomRingsCapsule, 54515},
        {-750.62f, 343.99f, -2116.79f, LevelAndActIDs_HotShelter3, Characters_Gamma, SpeedUpCapsule, 54516},
        {-808.61f, 343.99f, -2115.52f, LevelAndActIDs_HotShelter3, Characters_Gamma, ExtraLifeCapsule, 54517},
        {-664.08f, 474.02f, -3583.48f, LevelAndActIDs_HotShelter3, Characters_Gamma, ExtraLifeCapsule, 54518}, //DX
        {-664.08f, 474.15f, -3583.48f, LevelAndActIDs_HotShelter3, Characters_Gamma, ExtraLifeCapsule, 54518}, //DC
        {-706.70f, 471.16f, -3612.63f, LevelAndActIDs_HotShelter3, Characters_Gamma, SpeedUpCapsule, 54519}, //DX
        {-706.70f, 471.87f, -3612.63f, LevelAndActIDs_HotShelter3, Characters_Gamma, SpeedUpCapsule, 54519}, //DC
        {-666.77f, 473.84f, -3643.03f, LevelAndActIDs_HotShelter3, Characters_Gamma, InvincibilityCapsule, 54520}, //DX
        {-666.77f, 473.63f, -3643.03f, LevelAndActIDs_HotShelter3, Characters_Gamma, InvincibilityCapsule, 54520}, //DC
        {-848.50f, 825.00f, -3620.10f, LevelAndActIDs_HotShelter3, Characters_Gamma, ExtraLifeCapsule, 54521}, //DX
        {-848.50f, 820.00f, -3620.10f, LevelAndActIDs_HotShelter3, Characters_Gamma, ExtraLifeCapsule, 54521}, //DC
        {-1028.33f, 180.00f, -3595.32f, LevelAndActIDs_HotShelter3, Characters_Gamma, FiveRingsCapsule, 54522},
        {-1031.73f, 180.00f, -3643.27f, LevelAndActIDs_HotShelter3, Characters_Gamma, FiveRingsCapsule, 54523},
        {-848.11f, 1969.00f, -3625.07f, LevelAndActIDs_HotShelter3, Characters_Gamma, ShieldCapsule, 54524},
        {-744.75f, 2999.94f, -3290.73f, LevelAndActIDs_HotShelter3, Characters_Gamma, FiveRingsCapsule, 54525},
        {-767.47f, 2530.00f, -3599.93f, LevelAndActIDs_HotShelter3, Characters_Gamma, TenRingsCapsule, 54526},
        {-946.51f, 2999.94f, -3290.35f, LevelAndActIDs_HotShelter3, Characters_Gamma, FiveRingsCapsule, 54527},
        {-934.88f, 2530.00f, -3599.41f, LevelAndActIDs_HotShelter3, Characters_Gamma, TenRingsCapsule, 54528},
        {-767.47f, 2530.00f, -3639.93f, LevelAndActIDs_HotShelter3, Characters_Gamma, TenRingsCapsule, 54529},
        {-932.47f, 2530.00f, -3639.93f, LevelAndActIDs_HotShelter3, Characters_Gamma, MagneticShieldCapsule, 54530},
        {-38.48f, 10006.99f, 38.92f, LevelAndActIDs_HotShelter3, Characters_Gamma, ShieldCapsule, 54531},
        {-68.48f, 10006.99f, 38.92f, LevelAndActIDs_HotShelter3, Characters_Gamma, BombCapsule, 54532},
        {-52.09f, 10023.02f, 849.39f, LevelAndActIDs_HotShelter3, Characters_Gamma, ShieldCapsule, 54533}, //DX
        {-52.09f, 10017.02f, 849.39f, LevelAndActIDs_HotShelter3, Characters_Gamma, ShieldCapsule, 54533}, //DC

        {51.64f, -0.03f, -377.60f, LevelAndActIDs_HotShelter1, Characters_Big, ShieldCapsule, 63501},
        {-226.93f, 0.00f, -628.42f, LevelAndActIDs_HotShelter1, Characters_Big, SpeedUpCapsule, 63502},
        {-227.14f, 0.00f, -650.42f, LevelAndActIDs_HotShelter1, Characters_Big, ShieldCapsule, 63503},
        {750.31f, -80.00f, -516.03f, LevelAndActIDs_HotShelter1, Characters_Big, TenRingsCapsule, 63504},
        {744.53f, -80.00f, -778.16f, LevelAndActIDs_HotShelter1, Characters_Big, TenRingsCapsule, 63505},
        {932.88f, 0.99f, -639.38f, LevelAndActIDs_HotShelter1, Characters_Big, RandomRingsCapsule, 63506},
        {931.23f, 0.99f, -659.31f, LevelAndActIDs_HotShelter1, Characters_Big, ExtraLifeCapsule, 63507},
        {-89.14f, 80.00f, -113.88f, LevelAndActIDs_HotShelter1, Characters_Big, SpeedUpCapsule, 63508},
        {-32.62f, 80.00f, -399.02f, LevelAndActIDs_HotShelter1, Characters_Big, TenRingsCapsule, 63509},
        {28.30f, 80.00f, -402.01f, LevelAndActIDs_HotShelter1, Characters_Big, TenRingsCapsule, 63510},
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
