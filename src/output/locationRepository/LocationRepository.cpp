﻿#include "LocationRepository.h"

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

    _lifeCapsules = {
        {1053.08f, -6.77f, 745.21f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 1010},
        {6297.18f, 312.70f, 1271.14f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 1011},
        {6297.18f, 316.95f, 1271.14f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 1011}, //DC
        {1078.81f, 656.17f, -748.29f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 1012},
        {1078.81f, 650.54f, -748.29f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 1012},
        {1086.19f, 650.54f, -753.55f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 1012}, //DC
        {3161.46f, -0.28f, -2630.8f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 1013},
        {3161.46f, 0.44f, -2630.8f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 1013}, //DC
        {2212.05f, -567.0f, -16.74f, LevelAndActIDs_WindyValley1, Characters_Sonic, 1110}, // R:Light Shoes
        {2996.38f, -434.8972f, -1504.0f, LevelAndActIDs_WindyValley1, Characters_Sonic, 1111},
        {1147.72f, -2209.17f, 1260.16f, LevelAndActIDs_WindyValley3, Characters_Sonic, 1112},
        {1677.8f, -2577.0f, 1117.49f, LevelAndActIDs_WindyValley3, Characters_Sonic, 1113}, // R:Light Shoes
        {4159.61f, -4484.5f, -1826.59f, LevelAndActIDs_WindyValley3, Characters_Sonic, 1114},
        {-2.18f, -8.14f, 104.95f, LevelAndActIDs_Casinopolis2, Characters_Sonic, 1210},
        {-2.18f, -3.0f, 104.95f, LevelAndActIDs_Casinopolis2, Characters_Sonic, 1210},
        {-161.4f, 55.0f, 2.32f, LevelAndActIDs_Casinopolis3, Characters_Sonic, 1211}, //evil tower bypass lol
        {-161.4f, 50.0f, 12.32f, LevelAndActIDs_Casinopolis3, Characters_Sonic, 1211}, //evil tower bypass but DX
        {166.62f, 50.0f, 14.55f, LevelAndActIDs_Casinopolis3, Characters_Sonic, 1212}, //bumper tower bypass
        {487.79f, 250.67f, 1149.06f, LevelAndActIDs_IceCap1, Characters_Sonic, 1310},
        {487.79f, 249.67f, 1149.06f, LevelAndActIDs_IceCap1, Characters_Sonic, 1310}, //DX
        {-2537.78f, -208.31f, 7597.23f, LevelAndActIDs_TwinklePark1, Characters_Sonic, 1410},
        {119.35f, -1519.96f, 7602.92f, LevelAndActIDs_TwinklePark1, Characters_Sonic, 1411},
        {372.47f, 317.02f, -363.36f, LevelAndActIDs_TwinklePark2, Characters_Sonic, 1412},
        {-24.25f, 425.3f, 125.35f, LevelAndActIDs_TwinklePark2, Characters_Sonic, 1413},
        {1904.17f, -93.17f, 21.84f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, 1510},
        {1912.92f, -93.17f, 594.75f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, 1511},
        {1772.14f, -683.0f, 304.35f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, 1512},
        {3798.5f, -1370.0f, 159.9f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, 1513},
        {4626.2f, -1675.0f, 1667.93f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, 1514},
        {4271.06f, -1525.98f, 4152.68f, LevelAndActIDs_SpeedHighway1, Characters_Sonic, 1515},
        {1.0f, -5565.0f, -55.4f, LevelAndActIDs_SpeedHighway2, Characters_Sonic, 1516},
        {8.0f, -5565.0f, -55.4f, LevelAndActIDs_SpeedHighway2, Characters_Sonic, 1516}, //m
        {-138.84f, 185.0f, -1014.24f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, 1517},
        {14.83f, 0.0f, -1688.95f, LevelAndActIDs_SpeedHighway3, Characters_Sonic, 1518},
        {-534.08f, 1255.3f, -170.27f, LevelAndActIDs_RedMountain1, Characters_Sonic, 1610},
        {-534.08f, 1254.21f, -170.27f, LevelAndActIDs_RedMountain1, Characters_Sonic, 1610}, //No Fixed Edition
        {-855.52f, 1096.57f, -347.76f, LevelAndActIDs_RedMountain1, Characters_Sonic, 1611},
        {-3035.25f, 173.02f, -1385.02f, LevelAndActIDs_RedMountain1, Characters_Sonic, 1612},
        {-3452.31f, 134.38f, -1580.31f, LevelAndActIDs_RedMountain1, Characters_Sonic, 1613},
        {-2954.26f, 884.3f, -1751.26f, LevelAndActIDs_RedMountain1, Characters_Sonic, 1614}, // R:Light Shoes
        {-2969.36f, 884.3f, -1738.15f, LevelAndActIDs_RedMountain1, Characters_Sonic, 1615}, // R:Light Shoes
        {-3767.93f, 1221.38f, -1908.67f, LevelAndActIDs_RedMountain1, Characters_Sonic, 1616},
        {-3767.93f, 1226.38f, -1929.57f, LevelAndActIDs_RedMountain1, Characters_Sonic, 1616}, //DX
        {-907.53f, 137.85f, 871.08f, LevelAndActIDs_RedMountain2, Characters_Sonic, 1617},
        {400.11f, -260.01f, 1125.68f, LevelAndActIDs_SkyDeck1, Characters_Sonic, 1710},
        {401.52f, -210.01f, 1320.11f, LevelAndActIDs_SkyDeck1, Characters_Sonic, 1711},
        {399.05f, -330.01f, 1320.09f, LevelAndActIDs_SkyDeck1, Characters_Sonic, 1712},
        {487.7f, -450.0f, 3727.33f, LevelAndActIDs_SkyDeck1, Characters_Sonic, 1713},
        {401.04f, -601.0f, 4220.15f, LevelAndActIDs_SkyDeck1, Characters_Sonic, 1714},
        {401.04f, -599.5f, 4220.15f, LevelAndActIDs_SkyDeck1, Characters_Sonic, 1714}, //DX
        {-277.49f, -38.98f, 2545.97f, LevelAndActIDs_SkyDeck2, Characters_Sonic, 1715}, //No fixed edition
        {-277.3672f, -37.6f, 2546.101f, LevelAndActIDs_SkyDeck2, Characters_Sonic, 1715},
        {-408.93f, -7.59f, 1069.63f, LevelAndActIDs_SkyDeck2, Characters_Sonic, 1716},
        {-473.49f, -2.309165f, 44.75f, LevelAndActIDs_SkyDeck2, Characters_Sonic, 1717},
        {-473.49f, 1.5f, 44.75f, LevelAndActIDs_SkyDeck2, Characters_Sonic, 1717}, //DX
        {181.6f, 0.0f, -4277.61f, LevelAndActIDs_SkyDeck2, Characters_Sonic, 1718},
        {99.44f, 0.0f, -4278.86f, LevelAndActIDs_SkyDeck2, Characters_Sonic, 1719},
        {-696.41f, -2.0f, -209.24f, LevelAndActIDs_SkyDeck3, Characters_Sonic, 1720},
        {-696.41f, 2.0f, -209.24f, LevelAndActIDs_SkyDeck3, Characters_Sonic, 1720}, //m
        {245.39f, -20.4f, 2.38f, LevelAndActIDs_SkyDeck3, Characters_Sonic, 1721},
        {251.39f, -20.4f, 2.38f, LevelAndActIDs_SkyDeck3, Characters_Sonic, 1721}, //m
        {5629.72f, -2545.0f, 1672.61f, LevelAndActIDs_LostWorld1, Characters_Sonic, 1810},
        {7539.95f, -2545.0f, 1097.54f, LevelAndActIDs_LostWorld2, Characters_Sonic, 1811},
        {177.63f, -102.98f, -144.15f, LevelAndActIDs_FinalEgg1, Characters_Sonic, 1910},
        {1486.61f, 203.0f, -1314.31f, LevelAndActIDs_FinalEgg1, Characters_Sonic, 1911},
        {1898.99f, 203.99f, -1066.92f, LevelAndActIDs_FinalEgg1, Characters_Sonic, 1912},
        {942.18f, 86.56f, -744.57f, LevelAndActIDs_FinalEgg2, Characters_Sonic, 1913},
        {942.18f, 88.93f, -744.57f, LevelAndActIDs_FinalEgg2, Characters_Sonic, 1913}, //DX
        {799.51f, 90.78f, -1108.67f, LevelAndActIDs_FinalEgg2, Characters_Sonic, 1914},
        {1093.7f, -10.62f, -826.47f, LevelAndActIDs_FinalEgg3, Characters_Sonic, 1915},
        {1209.16f, 111.17f, -980.11f, LevelAndActIDs_FinalEgg3, Characters_Sonic, 1916},
        {1317.62f, -297.22f, -1461.64f, LevelAndActIDs_FinalEgg3, Characters_Sonic, 1917},
        {1468.63f, -357.65f, -1444.59f, LevelAndActIDs_FinalEgg3, Characters_Sonic, 1918},
        {2615.22f, -278.9f, -1764.73f, LevelAndActIDs_FinalEgg3, Characters_Sonic, 1919},
        {2260.76f, -2739.37f, -1175.08f, LevelAndActIDs_FinalEgg3, Characters_Sonic, 1920},
        {856.85f, -3171.438f, -489.48f, LevelAndActIDs_FinalEgg3, Characters_Sonic, 1921},
        {-3.58f, -3003.81f, -278.32f, LevelAndActIDs_FinalEgg3, Characters_Sonic, 1922},
        {16.42f, -3003.81f, -298.32f, LevelAndActIDs_FinalEgg3, Characters_Sonic, 1923},
        {16.42f, -3003.81f, -278.32f, LevelAndActIDs_FinalEgg3, Characters_Sonic, 1924},
        {-3.58f, -3003.81f, -298.32f, LevelAndActIDs_FinalEgg3, Characters_Sonic, 1925},

        {5327.94f, -4014.36f, -2284.31f, LevelAndActIDs_WindyValley3, Characters_Tails, 2010},
        {-1173.27f, -1239.73f, 2849.5f, LevelAndActIDs_Casinopolis2, Characters_Tails, 2110},
        {-1945.4f, -1475.73f, 3009.3f, LevelAndActIDs_Casinopolis2, Characters_Tails, 2111},
        {-1945.4f, -1485.73f, 3019.3f, LevelAndActIDs_Casinopolis2, Characters_Tails, 2111}, //m
        {400.11f, -260.01f, 1125.68f, LevelAndActIDs_SkyDeck1, Characters_Tails, 2310},
        {401.52f, -210.01f, 1320.11f, LevelAndActIDs_SkyDeck1, Characters_Tails, 2311},
        {487.7f, -450.0f, 3727.33f, LevelAndActIDs_SkyDeck1, Characters_Tails, 2312},
        {401.04f, -601.0f, 4220.15f, LevelAndActIDs_SkyDeck1, Characters_Tails, 2313},
        {401.04f, -599.5f, 4220.15f, LevelAndActIDs_SkyDeck1, Characters_Tails, 2313}, //DX
        {4956.11f, -1714.0f, 1364.51f, LevelAndActIDs_SpeedHighway1, Characters_Tails, 2410},
        {4626.2f, -1675.0f, 1667.93f, LevelAndActIDs_SpeedHighway1, Characters_Tails, 2411},
        {4259.64f, -1704.04f, 4095.85f, LevelAndActIDs_SpeedHighway1, Characters_Tails, 2412},
        {4259.64f, -1705.34f, 4095.85f, LevelAndActIDs_SpeedHighway1, Characters_Tails, 2412}, //DX
        {5246.12f, -2332.0f, 7842.45f, LevelAndActIDs_SpeedHighway1, Characters_Tails, 2413},

        {14.83f, 0.0f, -1688.95f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, 3010},
        {70.51f, 24.5f, 223.17f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, 3011},
        {-138.84f, 185.0f, -1014.24f, LevelAndActIDs_SpeedHighway3, Characters_Knuckles, 3012},
        {510.5f, 165.89f, -304.94f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, 3110},
        {5.1f, 448.0f, 0.25f, LevelAndActIDs_Casinopolis1, Characters_Knuckles, 3111},
        {-3666.69f, 63.45f, -2346.65f, LevelAndActIDs_RedMountain3, Characters_Knuckles, 3210},
        {-3666.69f, 62.2f, -2346.65f, LevelAndActIDs_RedMountain3, Characters_Knuckles, 3210}, //DX
        {-3349.6f, 206.0f, -1142.93f, LevelAndActIDs_RedMountain3, Characters_Knuckles, 3211},
        {-1895.37f, 58.92f, -1854.58f, LevelAndActIDs_RedMountain3, Characters_Knuckles, 3212},
        {-3804.06f, 1122.98f, -2094.58f, LevelAndActIDs_RedMountain3, Characters_Knuckles, 3213},
        {342.68f, 178.18f, 434.17f, LevelAndActIDs_SkyDeck3, Characters_Knuckles, 3410},

        {267.4f, 306.02f, -297.65f, LevelAndActIDs_TwinklePark2, Characters_Amy, 4010},
        {-320.14f, 250.0f, -248.29f, LevelAndActIDs_HotShelter2, Characters_Amy, 4110},
        {-320.14f, 253.95f, -248.29f, LevelAndActIDs_HotShelter2, Characters_Amy, 4110}, //No fixed edition
        {-29.18f, 50.78f, -437.51f, LevelAndActIDs_HotShelter2, Characters_Amy, 4111},
        {538.82f, 1040.0f, -2092.6f, LevelAndActIDs_HotShelter2, Characters_Amy, 4112},
        {841.84f, 428.24f, -3295.21f, LevelAndActIDs_HotShelter2, Characters_Amy, 4113},
        {548.45f, -232.0f, -1552.75f, LevelAndActIDs_FinalEgg1, Characters_Amy, 4210},
        {1629.58f, 240.0f, -1319.99f, LevelAndActIDs_FinalEgg1, Characters_Amy, 4211},

        {1048.05f, -5.07f, 747.43f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 5110},
        {635.3f, -61.0f, 247.38f, LevelAndActIDs_WindyValley1, Characters_Gamma, 5210},
        {2028.11f, -467.0f, 6.6f, LevelAndActIDs_WindyValley1, Characters_Gamma, 5211},
        {-253.36f, 239.01f, 549.6f, LevelAndActIDs_RedMountain2, Characters_Gamma, 5310},
        {-28.29f, 50.78f, -433.41f, LevelAndActIDs_HotShelter3, Characters_Gamma, 5410},
        {-808.61f, 343.99f, -2115.52f, LevelAndActIDs_HotShelter3, Characters_Gamma, 5411},
        {-848.5f, 825.0f, -3620.1f, LevelAndActIDs_HotShelter3, Characters_Gamma, 5412},
        {-848.5f, 820.0f, -3620.1f, LevelAndActIDs_HotShelter3, Characters_Gamma, 5412}, //DX
        {-664.08f, 474.0215f, -3583.48f, LevelAndActIDs_HotShelter3, Characters_Gamma, 5413},

        {1174.01f, 332.79f, -256.39f, LevelAndActIDs_IceCap4, Characters_Big, 6110},
        {6086.91f, 78.29f, 1186.96f, LevelAndActIDs_EmeraldCoast3, Characters_Big, 6210},
        {931.23f, 0.99f, -659.31f, LevelAndActIDs_HotShelter1, Characters_Big, 6310}
    };

    for (auto& capsule : _lifeCapsules)
    {
        _checkData[capsule.locationId] = LocationData::LifeCapsuleLocation(capsule);
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

std::vector<LifeBoxLocationData> LocationRepository::GetLifeCapsules()
{
    return _lifeCapsules;
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
    if(_checkData[905].checked)
        chaoStatus.racesCompleted++;
    if(_checkData[906].checked)
        chaoStatus.racesCompleted++;
    if(_checkData[907].checked)
        chaoStatus.racesCompleted++;
    if(_checkData[908].checked)
        chaoStatus.racesCompleted++;
    if(_checkData[909].checked)
        chaoStatus.racesCompleted++;
    
    return chaoStatus;
}
