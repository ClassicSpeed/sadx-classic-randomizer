#include "LocationRepository.h"
#include "../../pch.h"

#define MISSION_C  2
#define MISSION_B  1
#define MISSION_A  0


#define SUB_LEVEL_MISSION_B  1
#define SUB_LEVEL_MISSION_A  0

LocationRepository::LocationRepository()
{
    _charactersMap = {
        {Characters_Sonic, "Sonic"},
        {Characters_Tails, "Tails"},
        {Characters_Knuckles, "Knuckles"},
        {Characters_Amy, "Amy"},
        {Characters_Gamma, "Gamma"},
        {Characters_Big, "Big"}
    };


    _levelsMap = {
        {LevelIDs_EmeraldCoast, "Emerald Coast"},
        {LevelIDs_WindyValley, "Windy Valley"},
        {LevelIDs_TwinklePark, "Twinkle Park"},
        {LevelIDs_SpeedHighway, "Speed Highway"},
        {LevelIDs_RedMountain, "Red Mountain"},
        {LevelIDs_SkyDeck, "Sky Deck"},
        {LevelIDs_LostWorld, "Lost World"},
        {LevelIDs_IceCap, "Ice Cap"},
        {LevelIDs_Casinopolis, "Casinopolis"},
        {LevelIDs_FinalEgg, "Final Egg"},
        {LevelIDs_HotShelter, "Hot Shelter"},
    };


    _checkData = {


        {100, LocationData::UpgradeLocation(FLAG_SONIC_SS_LIGHTSHOOSE, "Light shoes upgrade (Sonic)", 10)},
        {101, LocationData::UpgradeLocation(FLAG_SONIC_SS_CRYSTALRING, "Crystal ring upgrade (Sonic)", 11)},
        {102, LocationData::UpgradeLocation(FLAG_SONIC_MR_ANCIENT_LIGHT, "Ancient light upgrade (Sonic)", 12)},

        {200, LocationData::UpgradeLocation(FLAG_MILES_SS_JETANKLET, "Jet Ankle upgrade (Tails)", 20)},
        // {201, LocationData::UpgradeLocation(FLAG_MILES_MR_RHYTHMBROOCH, "Rhythm Badge upgrade (Tails)", 21)},

        {300, LocationData::UpgradeLocation(FLAG_KNUCKLES_MR_SHOVELCLAW, "Shovel claw upgrade (Knuckles)", 30)},
        {301, LocationData::UpgradeLocation(FLAG_KNUCKLES_MR_FIGHTINGGROVE, "Fighting gloves upgrade (Knuckles)", 31)},

        {400, LocationData::UpgradeLocation(FLAG_AMY_MR_FIGHTERSFEATHER, "Warrior feather upgrade (Amy)", 41)},
        {401, LocationData::UpgradeLocation(FLAG_AMY_EC_LONGHAMMER, "Long Hammer upgrade (Amy)", 41)},

        {500, LocationData::UpgradeLocation(FLAG_E102_EC_BOOSTER, "Jet booster upgrade (Gamma)", 50)},
        {501, LocationData::UpgradeLocation(FLAG_E102_EC_TYPE3LASER, "Laser Blaster upgrade (Gamma)", 51)},

        {600, LocationData::UpgradeLocation(FLAG_BIG_MR_LIFEBELT, "Life belt upgrade (Big)", 60)},
        {601, LocationData::UpgradeLocation(FLAG_BIG_MR_POWERROD, "Power rod upgrade (Big)", 61)},
        // //Check if the check works
        // {62, LocationData::UpgradeLocation(FLAG_BIG_RUAR_BLUE), "Lure 1 upgrade (Big)", 61)},
        // {63, LocationData::UpgradeLocation(FLAG_BIG_RUAR_GOLD), "Lure 2 upgrade (Big)", 61)},
        // {64, LocationData::UpgradeLocation(FLAG_BIG_RUAR_RED), "Lure 3 upgrade (Big)", 61)},
        // {65, LocationData::UpgradeLocation(FLAG_BIG_RUAR_SILVER), "Lure 4 upgrade (Big)", 61)},

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
        {15, LocationData::LevelLocation(Characters_Sonic, LevelIDs_SandHill, MISSION_B)},
        {15, LocationData::LevelLocation(Characters_Tails, LevelIDs_SandHill, MISSION_B)},

        {16, LocationData::LevelLocation(Characters_Sonic, LevelIDs_SandHill, MISSION_B)},
        {16, LocationData::LevelLocation(Characters_Tails, LevelIDs_SandHill, MISSION_A)},

        {25, LocationData::LevelLocation(Characters_Sonic, LevelIDs_TwinkleCircuit, MISSION_B)},
        {25, LocationData::LevelLocation(Characters_Tails, LevelIDs_TwinkleCircuit, MISSION_B)},
        {25, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_TwinkleCircuit, MISSION_B)},
        {25, LocationData::LevelLocation(Characters_Amy, LevelIDs_TwinkleCircuit, MISSION_B)},
        {25, LocationData::LevelLocation(Characters_Big, LevelIDs_TwinkleCircuit, MISSION_B)},
        {25, LocationData::LevelLocation(Characters_Gamma, LevelIDs_TwinkleCircuit, MISSION_B)},

        {26, LocationData::LevelLocation(Characters_Sonic, LevelIDs_TwinkleCircuit, MISSION_A)},
        {26, LocationData::LevelLocation(Characters_Tails, LevelIDs_TwinkleCircuit, MISSION_A)},
        {26, LocationData::LevelLocation(Characters_Knuckles, LevelIDs_TwinkleCircuit, MISSION_A)},
        {26, LocationData::LevelLocation(Characters_Amy, LevelIDs_TwinkleCircuit, MISSION_A)},
        {26, LocationData::LevelLocation(Characters_Big, LevelIDs_TwinkleCircuit, MISSION_A)},
        {26, LocationData::LevelLocation(Characters_Gamma, LevelIDs_TwinkleCircuit, MISSION_A)},

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
        
    };
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
