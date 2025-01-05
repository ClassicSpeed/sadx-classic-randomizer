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
        {6018.640f, 6.00f, 1076.440f, LevelAndActIDs_EmeraldCoast3, Characters_Big, 62000}, // DX & DC - Kiki
        {6061.590f, 6.00f, 885.390f, LevelAndActIDs_EmeraldCoast3, Characters_Big, 62001}, // DX & DC - Kiki
        {5579.450f, 6.90f, 1081.570f, LevelAndActIDs_EmeraldCoast3, Characters_Big, 62002}, // DX - Kiki
        {5579.450f, 6.00f, 1081.570f, LevelAndActIDs_EmeraldCoast3, Characters_Big, 62002}, // DC - Kiki
    };

    _capsules = {
        {6061.480f, -0.01f, 878.860f, LevelAndActIDs_EmeraldCoast3, Characters_Big, TenRingsCapsule, 62500}, // DX & DC 
        {6086.910f, 78.29f, 1186.960f, LevelAndActIDs_EmeraldCoast3, Characters_Big, ExtraLifeCapsule, 62501}, // DX & DC 
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
