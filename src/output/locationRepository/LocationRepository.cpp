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

        {-225.410f, 2.25f, 98.780f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10000}, // RhinoTank
        {-107.644f, 19.02f, 253.844f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10001}, // DX - Kiki
        {-109.480f, 17.32f, 250.480f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10001}, // DC - Kiki
        {-457.455f, 55.68f, 183.665f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10002}, // DX - Kiki
        {-455.680f, 39.68f, 184.610f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10002}, // DC - Kiki
        {-590.100f, 13.20f, 377.860f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10003}, // RhinoTank
        {225.630f, 18.39f, 712.547f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10004}, // DX - Kiki
        {225.160f, 17.39f, 713.430f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10004}, // DC - Kiki
        {837.830f, 83.50f, 631.370f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10005}, // DX - Kiki
        {837.830f, 82.74f, 631.370f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10005}, // DC - Kiki
        {-641.140f, 50.50f, 898.137f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10006}, // DX - Kiki
        {-640.640f, 49.84f, 900.300f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10006}, // DC - Kiki
        {887.660f, 83.50f, 671.680f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10007}, // DX - Kiki
        {887.660f, 82.74f, 671.680f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10007}, // DC - Kiki
        {5708.577f, 42.20f, 1167.103f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10008}, // DX - Kiki
        {5708.030f, 40.00f, 1163.940f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10008}, // DC - Kiki
        {5780.659f, 454.10f, 677.274f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10009}, // DX - Kiki
        {5781.370f, 453.00f, 678.190f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10009}, // DC - Kiki
        {6001.292f, 12.10f, 1018.916f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10010}, // DX - Kiki
        {5997.520f, 11.10f, 1017.930f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, 10010}, // DC - Kiki
        {422.980f, 612.41f, -1043.490f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 10011}, // DX - Kiki
        {422.980f, 614.01f, -1043.490f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 10011}, // DC - Kiki
        {713.280f, 540.49f, -817.900f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 10012}, // DX - Water Spider
        {713.280f, 540.49f, -869.650f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 10012}, // DC - Water Spider
        {935.830f, 555.49f, -889.970f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 10013}, // Water Spider
        {1460.750f, 549.80f, -952.460f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 10014}, // DX - Kiki
        {1460.750f, 552.00f, -952.460f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 10014}, // DC - Kiki
        {2728.500f, 299.40f, -2603.150f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 10015}, // DX - Kiki
        {2710.500f, 301.30f, -2622.150f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 10015}, // DC - Kiki
        {3333.820f, 74.60f, -2707.870f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 10016}, // DX - Kiki
        {3333.820f, 74.00f, -2707.870f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 10016}, // DC - Kiki
        {4073.220f, 500.88f, -2841.510f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 10017}, // DX - Kiki
        {4073.220f, 501.98f, -2841.510f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, 10017}, // DC - Kiki

        {6018.640f, 6.00f, 1076.440f, LevelAndActIDs_EmeraldCoast3, Characters_Big, 62000}, // Kiki
        {6061.590f, 6.00f, 885.390f, LevelAndActIDs_EmeraldCoast3, Characters_Big, 62001}, // Kiki
        {5579.450f, 6.90f, 1081.570f, LevelAndActIDs_EmeraldCoast3, Characters_Big, 62002}, // DX - Kiki
        {5579.450f, 6.00f, 1081.570f, LevelAndActIDs_EmeraldCoast3, Characters_Big, 62002}, // DC - Kiki

        {-148.120f, 36.65f, 1.200f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51000}, // Kiki
        {-206.860f, 31.05f, 97.710f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51001}, // Kiki
        {-184.560f, 30.95f, 136.200f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51002}, // Kiki
        {-279.220f, 31.65f, 205.200f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51003}, // Kiki
        {-318.640f, 31.65f, 224.490f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51004}, // Kiki
        {-438.520f, 4.00f, 209.100f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51005}, // DX - RhinoTank
        {-438.520f, 8.00f, 209.100f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51005}, // DC - RhinoTank
        {-577.630f, 4.00f, 455.660f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51006}, // DX - RhinoTank
        {-577.630f, 8.00f, 455.660f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51006}, // DC - RhinoTank
        {-617.940f, 4.00f, 426.070f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51007}, // DX - RhinoTank
        {-617.940f, 8.00f, 426.070f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51007}, // DC - RhinoTank
        {310.420f, 34.00f, 702.060f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51008}, // Kiki
        {351.110f, 32.40f, 700.750f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51009}, // Kiki
        {703.280f, 19.32f, 642.080f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51010}, // DX - RhinoTank
        {703.280f, 23.32f, 642.080f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51010}, // DC - RhinoTank
        {-176.440f, 49.50f, 994.390f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51011}, // Kiki
        {-274.800f, 49.50f, 1005.610f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51012}, // Kiki
        {145.060f, 4.00f, 1039.750f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51013}, // DX - RhinoTank
        {145.060f, 8.00f, 1039.750f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51013}, // DC - RhinoTank
        {-622.310f, 57.00f, 893.700f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51014}, // Kiki
        {847.100f, 84.53f, 705.500f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51015}, // Kiki
        {-623.950f, 57.00f, 932.750f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51016}, // Kiki
        {901.720f, 83.53f, 698.250f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51017}, // DX - Kiki
        {901.720f, 84.53f, 698.250f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51017}, // DC - Kiki
        {881.000f, 84.53f, 735.340f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51018}, // Kiki
        {-618.230f, 57.00f, 978.430f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51019}, // Kiki
        {928.350f, 83.00f, 719.940f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51020}, // DX - Kiki
        {928.350f, 84.53f, 719.940f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51020}, // DC - Kiki
        {915.700f, 83.63f, 759.400f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51021}, // DX - Kiki
        {915.700f, 84.53f, 759.400f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51021}, // DC - Kiki
        {855.550f, 43.53f, 895.310f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51022}, // DX - RhinoTank
        {855.550f, 47.53f, 895.310f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51022}, // DC - RhinoTank
        {-617.180f, 127.00f, 1170.590f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51023}, // Kiki
        {-633.110f, 126.90f, 1171.170f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51024}, // Kiki
        {-671.290f, 127.30f, 1247.210f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51025}, // Kiki
        {-642.170f, 58.00f, 1479.550f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51026}, // Kiki
        {-763.750f, 58.00f, 1560.100f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51027}, // Kiki
        {-891.230f, 58.00f, 1556.610f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, 51028}, // Kiki


        {1575.370f, -467.49f, 94.790f, LevelAndActIDs_WindyValley1, Characters_Sonic, 11000}, // Leon
        {1577.020f, -472.00f, 96.850f, LevelAndActIDs_WindyValley1, Characters_Sonic, 11001}, // DX - Leon
        {1575.370f, -467.49f, 94.790f, LevelAndActIDs_WindyValley1, Characters_Sonic, 11001}, // DC - Leon
        {1744.550f, -553.49f, 230.390f, LevelAndActIDs_WindyValley1, Characters_Sonic, 11002}, // Boa-Boa
        {2042.950f, -463.00f, 7.610f, LevelAndActIDs_WindyValley1, Characters_Sonic, 11003}, // Leon
        {3125.270f, -503.00f, -1487.490f, LevelAndActIDs_WindyValley1, Characters_Sonic, 11004}, // Leon
        {470.140f, -374.00f, -1076.620f, LevelAndActIDs_WindyValley3, Characters_Sonic, 11005}, // Boa-Boa
        {425.710f, -381.93f, -1269.220f, LevelAndActIDs_WindyValley3, Characters_Sonic, 11006}, // Leon
        {1142.370f, -2630.02f, 1411.510f, LevelAndActIDs_WindyValley3, Characters_Sonic, 11007}, // Leon
        {1348.230f, -2661.00f, 1385.730f, LevelAndActIDs_WindyValley3, Characters_Sonic, 11008}, // DX - RhinoTank
        {1348.230f, -2650.10f, 1385.730f, LevelAndActIDs_WindyValley3, Characters_Sonic, 11008}, // DC - RhinoTank
        {4163.900f, -4396.01f, -1742.060f, LevelAndActIDs_WindyValley3, Characters_Sonic, 11009}, // Leon
        {4227.740f, -4395.01f, -1555.390f, LevelAndActIDs_WindyValley3, Characters_Sonic, 11010}, // Leon
        {4267.840f, -4460.01f, -1689.320f, LevelAndActIDs_WindyValley3, Characters_Sonic, 11011}, // DX - RhinoTank
        {4267.840f, -4450.00f, -1689.320f, LevelAndActIDs_WindyValley3, Characters_Sonic, 11011}, // DC - RhinoTank

        
{409.480f, -405.00f, -1369.010f, LevelAndActIDs_WindyValley3, Characters_Tails, 11005}, // DX - Leon
{409.480f, -401.00f, -1369.010f, LevelAndActIDs_WindyValley3, Characters_Tails, 11005}, // DC - Leon
{1348.230f, -2661.00f, 1385.730f, LevelAndActIDs_WindyValley3, Characters_Tails, 11006}, // DX - RhinoTank
{1348.230f, -2650.10f, 1385.730f, LevelAndActIDs_WindyValley3, Characters_Tails, 11006}, // DC - RhinoTank
{4163.900f, -4396.01f, -1742.060f, LevelAndActIDs_WindyValley3, Characters_Tails, 11007}, // Leon
{4267.840f, -4460.01f, -1689.320f, LevelAndActIDs_WindyValley3, Characters_Tails, 11008}, // DX - RhinoTank
{4267.840f, -4450.00f, -1689.320f, LevelAndActIDs_WindyValley3, Characters_Tails, 11008}, // DC - RhinoTank

        
{145.990f, -161.00f, 282.360f, LevelAndActIDs_WindyValley1, Characters_Gamma, 11005}, // Boa-Boa
{531.080f, -238.00f, 254.700f, LevelAndActIDs_WindyValley1, Characters_Gamma, 11006}, // RhinoTank
{634.860f, -202.00f, 248.790f, LevelAndActIDs_WindyValley1, Characters_Gamma, 11007}, // Boa-Boa
{977.700f, -148.00f, -118.670f, LevelAndActIDs_WindyValley1, Characters_Gamma, 11008}, // Boa-Boa
{1065.400f, -155.03f, -113.470f, LevelAndActIDs_WindyValley1, Characters_Gamma, 11009}, // Leon
{1139.560f, -129.03f, -95.810f, LevelAndActIDs_WindyValley1, Characters_Gamma, 11010}, // Leon
{1317.760f, -355.00f, -152.460f, LevelAndActIDs_WindyValley1, Characters_Gamma, 11011}, // Boa-Boa
{1499.160f, -480.00f, 168.680f, LevelAndActIDs_WindyValley1, Characters_Gamma, 11012}, // Boa-Boa
{1745.640f, -552.00f, 225.600f, LevelAndActIDs_WindyValley1, Characters_Gamma, 11013}, // Boa-Boa
{2541.890f, -567.00f, -812.660f, LevelAndActIDs_WindyValley1, Characters_Gamma, 11014}, // Boa-Boa
{2747.720f, -642.00f, -1229.670f, LevelAndActIDs_WindyValley1, Characters_Gamma, 11015}, // DX - RhinoTank
{2747.720f, -640.00f, -1229.670f, LevelAndActIDs_WindyValley1, Characters_Gamma, 11015}, // DC - RhinoTank
    };

    _capsules = {
        {72.760f, 6.01f, -96.210f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, TenRingsCapsule, 10500},
        {54.360f, 9.01f, -109.380f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, TenRingsCapsule, 10501},
        {74.600f, 9.01f, -118.220f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, TenRingsCapsule, 10502},
        {828.020f, 79.74f, 626.830f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, RandomRingsCapsule, 10503},
        {1053.080f, -6.77f, 745.210f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, ExtraLifeCapsule, 10504},
        {2590.280f, 30.00f, 423.340f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, TenRingsCapsule, 10505},
        {6061.480f, -0.01f, 878.860f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, TenRingsCapsule, 10506},
        {6297.180f, 312.70f, 1271.140f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, ExtraLifeCapsule, 10507}, // DX 
        {6297.180f, 316.95f, 1271.140f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, ExtraLifeCapsule, 10507}, // DC 
        {6379.650f, -0.30f, 1194.230f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, RandomRingsCapsule, 10508},
        {6387.110f, -0.30f, 1177.900f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, RandomRingsCapsule, 10509},
        {6392.470f, -0.30f, 1154.710f, LevelAndActIDs_EmeraldCoast1, Characters_Sonic, RandomRingsCapsule, 10510},
        {260.720f, 796.40f, -1732.510f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, SpeedUpCapsule, 10511}, // DX 
        {270.320f, 787.09f, -1741.708f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, SpeedUpCapsule, 10511}, // DC 
        {426.010f, 604.92f, -1011.940f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, TenRingsCapsule, 10512},
        {1279.870f, 544.77f, -1105.750f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, TenRingsCapsule, 10513},
        {1078.810f, 656.17f, -748.290f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, ExtraLifeCapsule, 10514}, // DX 
        {1086.199f, 650.54f, -753.551f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, ExtraLifeCapsule, 10514}, // DC 
        {3161.460f, -0.28f, -2630.800f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, ExtraLifeCapsule, 10515}, // DX 
        {3161.460f, 0.44f, -2630.800f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, ExtraLifeCapsule, 10515}, // DC 
        {3355.250f, 69.70f, -2746.100f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, FiveRingsCapsule, 10516},
        {3369.420f, 69.70f, -2765.880f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, FiveRingsCapsule, 10517},
        {3384.580f, 69.70f, -2739.770f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, FiveRingsCapsule, 10518},
        {3672.560f, 140.72f, -2596.530f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, RandomRingsCapsule, 10519},
        // DX 
        {3672.618f, 139.60f, -2596.528f, LevelAndActIDs_EmeraldCoast2, Characters_Sonic, RandomRingsCapsule, 10519},
        // DC

        {6061.480f, -0.01f, 878.860f, LevelAndActIDs_EmeraldCoast3, Characters_Big, TenRingsCapsule, 62500},
        {6086.910f, 78.29f, 1186.960f, LevelAndActIDs_EmeraldCoast3, Characters_Big, ExtraLifeCapsule, 62501},

        {72.760f, 6.01f, -96.210f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, TenRingsCapsule, 51500},
        {54.360f, 9.01f, -109.380f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, TenRingsCapsule, 51501},
        {74.600f, 9.01f, -118.220f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, TenRingsCapsule, 51502},
        {-269.150f, 49.65f, 350.810f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, FiveRingsCapsule, 51503},
        {-734.380f, 28.65f, 294.600f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, FiveRingsCapsule, 51504},
        {-326.690f, 31.65f, 917.440f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, FiveRingsCapsule, 51505},
        {65.000f, 148.65f, 1037.500f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, FiveRingsCapsule, 51506},
        {61.420f, 172.65f, 1061.230f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, FiveRingsCapsule, 51507},
        {56.500f, 148.65f, 1093.870f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, FiveRingsCapsule, 51508},
        {1048.050f, -5.07f, 747.430f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, ExtraLifeCapsule, 51509},
        {-603.340f, 58.65f, 1233.520f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, FiveRingsCapsule, 51510},
        {-840.480f, 58.65f, 1468.460f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, FiveRingsCapsule, 51511},
        {-675.620f, 3.76f, 1559.550f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, RandomRingsCapsule, 51512}, // DX 
        {-675.620f, 3.86f, 1559.550f, LevelAndActIDs_EmeraldCoast1, Characters_Gamma, RandomRingsCapsule, 51512}, // DC

        {1600.560f, -472.62f, 123.310f, LevelAndActIDs_WindyValley1, Characters_Sonic, TenRingsCapsule, 11500}, // DX 
        {1600.560f, -472.00f, 123.310f, LevelAndActIDs_WindyValley1, Characters_Sonic, TenRingsCapsule, 11500}, // DC 
        {2004.750f, -412.00f, 101.190f, LevelAndActIDs_WindyValley1, Characters_Sonic, MagneticShieldCapsule, 11501},
        {1993.490f, -600.10f, 180.780f, LevelAndActIDs_WindyValley1, Characters_Sonic, ShieldCapsule, 11502}, // DX 
        {1993.490f, -599.98f, 180.780f, LevelAndActIDs_WindyValley1, Characters_Sonic, ShieldCapsule, 11502}, // DC 
        {2212.050f, -567.00f, -16.740f, LevelAndActIDs_WindyValley1, Characters_Sonic, ExtraLifeCapsule, 11503},
        {2903.390f, -434.00f, -1011.870f, LevelAndActIDs_WindyValley1, Characters_Sonic, RandomRingsCapsule, 11504},
        // DX 
        {2903.390f, -433.80f, -1011.870f, LevelAndActIDs_WindyValley1, Characters_Sonic, RandomRingsCapsule, 11504},
        // DC 
        {2996.380f, -434.89f, -1504.000f, LevelAndActIDs_WindyValley1, Characters_Sonic, ExtraLifeCapsule, 11505},
        // DX 
        {2996.380f, -434.90f, -1504.000f, LevelAndActIDs_WindyValley1, Characters_Sonic, ExtraLifeCapsule, 11505},
        // DC 
        {499.440f, -388.18f, -1286.160f, LevelAndActIDs_WindyValley3, Characters_Sonic, SpeedUpCapsule, 11506}, // DX 
        {499.440f, -388.20f, -1286.160f, LevelAndActIDs_WindyValley3, Characters_Sonic, SpeedUpCapsule, 11506}, // DC 
        {1147.720f, -2209.17f, 1260.160f, LevelAndActIDs_WindyValley3, Characters_Sonic, ExtraLifeCapsule, 11507},
        {1474.790f, -2619.00f, 960.980f, LevelAndActIDs_WindyValley3, Characters_Sonic, MagneticShieldCapsule, 11508},
        {1677.800f, -2577.00f, 1117.490f, LevelAndActIDs_WindyValley3, Characters_Sonic, ExtraLifeCapsule, 11509},
        {1120.900f, -2622.99f, 1349.910f, LevelAndActIDs_WindyValley3, Characters_Sonic, RandomRingsCapsule, 11510},
        {4206.010f, -4296.01f, -1686.530f, LevelAndActIDs_WindyValley3, Characters_Sonic, MagneticShieldCapsule, 11511},
        // DX 
        {4206.010f, -4295.83f, -1686.530f, LevelAndActIDs_WindyValley3, Characters_Sonic, MagneticShieldCapsule, 11511},
        // DC 
        {3995.660f, -4458.00f, -1644.020f, LevelAndActIDs_WindyValley3, Characters_Sonic, RandomRingsCapsule, 11512},
        // DX 
        {3995.660f, -4456.73f, -1644.020f, LevelAndActIDs_WindyValley3, Characters_Sonic, RandomRingsCapsule, 11512},
        // DC 
        {4171.990f, -4398.99f, -1743.840f, LevelAndActIDs_WindyValley3, Characters_Sonic, RandomRingsCapsule, 11513},
        // DX 
        {4171.990f, -4399.00f, -1743.840f, LevelAndActIDs_WindyValley3, Characters_Sonic, RandomRingsCapsule, 11513},
        // DC 
        {4160.340f, -4484.50f, -1812.610f, LevelAndActIDs_WindyValley3, Characters_Sonic, MagneticShieldCapsule, 11514},
        {4159.610f, -4484.50f, -1826.590f, LevelAndActIDs_WindyValley3, Characters_Sonic, ExtraLifeCapsule, 11515},
        {5681.680f, -10755.00f, -791.060f, LevelAndActIDs_WindyValley3, Characters_Sonic, RandomRingsCapsule, 11516},

        
{499.440f, -388.18f, -1286.160f, LevelAndActIDs_WindyValley3, Characters_Tails, SpeedUpCapsule, 11506},
{1474.790f, -2619.00f, 960.980f, LevelAndActIDs_WindyValley3, Characters_Tails, FiveRingsCapsule, 11507},
{1677.800f, -2577.00f, 1117.490f, LevelAndActIDs_WindyValley3, Characters_Tails, SpeedUpCapsule, 11508},
{1120.900f, -2622.99f, 1349.910f, LevelAndActIDs_WindyValley3, Characters_Tails, RandomRingsCapsule, 11509},
{1173.890f, -2571.02f, 1497.210f, LevelAndActIDs_WindyValley3, Characters_Tails, TenRingsCapsule, 11510},
{4119.690f, -4299.01f, -1503.750f, LevelAndActIDs_WindyValley3, Characters_Tails, TenRingsCapsule, 11511},
{3995.660f, -4458.00f, -1644.020f, LevelAndActIDs_WindyValley3, Characters_Tails, RandomRingsCapsule, 11512}, // DX 
{3995.660f, -4456.73f, -1644.020f, LevelAndActIDs_WindyValley3, Characters_Tails, RandomRingsCapsule, 11512}, // DC 
{4160.330f, -4437.50f, -1812.610f, LevelAndActIDs_WindyValley3, Characters_Tails, SpeedUpCapsule, 11513},
{5327.940f, -4014.36f, -2284.310f, LevelAndActIDs_WindyValley3, Characters_Tails, ExtraLifeCapsule, 11514},
{5686.740f, -10755.00f, -792.740f, LevelAndActIDs_WindyValley3, Characters_Tails, RandomRingsCapsule, 11515},
        
{635.300f, -61.00f, 247.380f, LevelAndActIDs_WindyValley1, Characters_Gamma, ExtraLifeCapsule, 11506},
{803.360f, -311.00f, -72.850f, LevelAndActIDs_WindyValley1, Characters_Gamma, MagneticShieldCapsule, 11507}, // DX 
{803.360f, -310.50f, -72.850f, LevelAndActIDs_WindyValley1, Characters_Gamma, MagneticShieldCapsule, 11507}, // DC 
{979.540f, -178.31f, -160.690f, LevelAndActIDs_WindyValley1, Characters_Gamma, TenRingsCapsule, 11508}, // DX 
{979.540f, -177.81f, -160.690f, LevelAndActIDs_WindyValley1, Characters_Gamma, TenRingsCapsule, 11508}, // DC 
{1072.980f, -158.31f, -25.140f, LevelAndActIDs_WindyValley1, Characters_Gamma, FiveRingsCapsule, 11509}, // DX 
{1072.980f, -157.81f, -25.140f, LevelAndActIDs_WindyValley1, Characters_Gamma, FiveRingsCapsule, 11509}, // DC 
{1216.960f, -269.75f, -174.800f, LevelAndActIDs_WindyValley1, Characters_Gamma, InvincibilityCapsule, 11510},
{1240.690f, -267.75f, -94.640f, LevelAndActIDs_WindyValley1, Characters_Gamma, MagneticShieldCapsule, 11511},
{2014.170f, -467.00f, 5.390f, LevelAndActIDs_WindyValley1, Characters_Gamma, RandomRingsCapsule, 11512},
{2028.110f, -467.00f, 6.600f, LevelAndActIDs_WindyValley1, Characters_Gamma, ExtraLifeCapsule, 11513},
{2043.060f, -467.00f, 7.890f, LevelAndActIDs_WindyValley1, Characters_Gamma, RandomRingsCapsule, 11514},
{2897.020f, -461.03f, -1274.200f, LevelAndActIDs_WindyValley1, Characters_Gamma, RandomRingsCapsule, 11515},
        

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
