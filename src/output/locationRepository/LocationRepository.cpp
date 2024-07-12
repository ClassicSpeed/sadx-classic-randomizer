#include "LocationRepository.h"
#include "../../pch.h"

#define MISSION_C  2
#define MISSION_B  1
#define MISSION_A  0

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


        {100, GetLocationFromUpgrade(EventFlags_Sonic_LightShoes, "Light shoes upgrade (Sonic)", 10)},
        {101, GetLocationFromUpgrade(EventFlags_Sonic_CrystalRing, "Crystal ring upgrade (Sonic)", 11)},
        {102, GetLocationFromUpgrade(EventFlags_Sonic_AncientLight, "Ancient light upgrade (Sonic)", 12)},

        {200, GetLocationFromUpgrade(EventFlags_Tails_JetAnklet, "Jet Ankle upgrade (Tails)", 20)},
        // {201, GetLocationFromUpgrade(EventFlags_Tails_RhythmBadge, "Rhythm Badge upgrade (Tails)", 21)},

        {300, GetLocationFromUpgrade(EventFlags_Knuckles_ShovelClaw, "Shovel claw upgrade (Knuckles)", 30)},
        {301, GetLocationFromUpgrade(EventFlags_Knuckles_FightingGloves, "Fighting gloves upgrade (Knuckles)", 31)},

        {400, GetLocationFromUpgrade(EventFlags_Amy_WarriorFeather, "Warrior feather upgrade (Amy)", 41)},
        {401, GetLocationFromUpgrade(EventFlags_Amy_LongHammer, "Long Hammer upgrade (Amy)", 41)},

        {500, GetLocationFromUpgrade(EventFlags_Gamma_JetBooster, "Jet booster upgrade (Gamma)", 50)},
        {501, GetLocationFromUpgrade(EventFlags_Gamma_LaserBlaster, "Laser Blaster upgrade (Gamma)", 51)},

        {600, GetLocationFromUpgrade(EventFlags_Big_LifeRing, "Life belt upgrade (Big)", 60)},
        {601, GetLocationFromUpgrade(EventFlags_Big_PowerRod, "Power rod upgrade (Big)", 61)},
        // //Check if the check works
        // {62, GetLocationFromUpgrade(static_cast<EventFlags>(FLAG_BIG_RUAR_BLUE), "Lure 1 upgrade (Big)", 61)},
        // {63, GetLocationFromUpgrade(static_cast<EventFlags>(FLAG_BIG_RUAR_GOLD), "Lure 2 upgrade (Big)", 61)},
        // {64, GetLocationFromUpgrade(static_cast<EventFlags>(FLAG_BIG_RUAR_RED), "Lure 3 upgrade (Big)", 61)},
        // {65, GetLocationFromUpgrade(static_cast<EventFlags>(FLAG_BIG_RUAR_SILVER), "Lure 4 upgrade (Big)", 61)},

        //Level id: ABXX where A is the character, B is the level in the story order, and XX is the check in that level 

        //Sonic's Levels
        {1000, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_EmeraldCoast, MISSION_A)},
        {1001, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_EmeraldCoast, MISSION_B)},
        {1002, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_EmeraldCoast, MISSION_C)},
        {1100, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_WindyValley, MISSION_A)},
        {1101, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_WindyValley, MISSION_B)},
        {1102, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_WindyValley, MISSION_C)},
        {1200, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_Casinopolis, MISSION_A)},
        {1201, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_Casinopolis, MISSION_B)},
        {1202, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_Casinopolis, MISSION_C)},
        {1300, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_IceCap, MISSION_A)},
        {1301, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_IceCap, MISSION_B)},
        {1302, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_IceCap, MISSION_C)},
        {1400, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_TwinklePark, MISSION_A)},
        {1401, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_TwinklePark, MISSION_B)},
        {1402, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_TwinklePark, MISSION_C)},
        {1500, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_SpeedHighway, MISSION_A)},
        {1501, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_SpeedHighway, MISSION_B)},
        {1502, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_SpeedHighway, MISSION_C)},
        {1600, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_RedMountain, MISSION_A)},
        {1601, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_RedMountain, MISSION_B)},
        {1602, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_RedMountain, MISSION_C)},
        {1700, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_SkyDeck, MISSION_A)},
        {1701, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_SkyDeck, MISSION_B)},
        {1702, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_SkyDeck, MISSION_C)},
        {1800, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_LostWorld, MISSION_A)},
        {1801, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_LostWorld, MISSION_B)},
        {1802, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_LostWorld, MISSION_C)},
        {1900, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_FinalEgg, MISSION_A)},
        {1901, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_FinalEgg, MISSION_B)},
        {1902, this->GetLocationFromLevel(Characters_Sonic, LevelIDs_FinalEgg, MISSION_C)},
        //Tails' Levels
        {2000, this->GetLocationFromLevel(Characters_Tails, LevelIDs_WindyValley, MISSION_A)},
        {2001, this->GetLocationFromLevel(Characters_Tails, LevelIDs_WindyValley, MISSION_B)},
        {2002, this->GetLocationFromLevel(Characters_Tails, LevelIDs_WindyValley, MISSION_C)},
        {2100, this->GetLocationFromLevel(Characters_Tails, LevelIDs_Casinopolis, MISSION_A)},
        {2101, this->GetLocationFromLevel(Characters_Tails, LevelIDs_Casinopolis, MISSION_B)},
        {2102, this->GetLocationFromLevel(Characters_Tails, LevelIDs_Casinopolis, MISSION_C)},
        {2200, this->GetLocationFromLevel(Characters_Tails, LevelIDs_IceCap, MISSION_A)},
        {2201, this->GetLocationFromLevel(Characters_Tails, LevelIDs_IceCap, MISSION_B)},
        {2202, this->GetLocationFromLevel(Characters_Tails, LevelIDs_IceCap, MISSION_C)},
        {2300, this->GetLocationFromLevel(Characters_Tails, LevelIDs_SkyDeck, MISSION_A)},
        {2301, this->GetLocationFromLevel(Characters_Tails, LevelIDs_SkyDeck, MISSION_B)},
        {2302, this->GetLocationFromLevel(Characters_Tails, LevelIDs_SkyDeck, MISSION_C)},
        {2400, this->GetLocationFromLevel(Characters_Tails, LevelIDs_SpeedHighway, MISSION_A)},
        {2401, this->GetLocationFromLevel(Characters_Tails, LevelIDs_SpeedHighway, MISSION_B)},
        {2402, this->GetLocationFromLevel(Characters_Tails, LevelIDs_SpeedHighway, MISSION_C)},
        //Knuckles' levels
        {3000, this->GetLocationFromLevel(Characters_Knuckles, LevelIDs_SpeedHighway, MISSION_A)},
        {3001, this->GetLocationFromLevel(Characters_Knuckles, LevelIDs_SpeedHighway, MISSION_B)},
        {3002, this->GetLocationFromLevel(Characters_Knuckles, LevelIDs_SpeedHighway, MISSION_C)},
        {3100, this->GetLocationFromLevel(Characters_Knuckles, LevelIDs_Casinopolis, MISSION_A)},
        {3101, this->GetLocationFromLevel(Characters_Knuckles, LevelIDs_Casinopolis, MISSION_B)},
        {3102, this->GetLocationFromLevel(Characters_Knuckles, LevelIDs_Casinopolis, MISSION_C)},
        {3200, this->GetLocationFromLevel(Characters_Knuckles, LevelIDs_RedMountain, MISSION_A)},
        {3201, this->GetLocationFromLevel(Characters_Knuckles, LevelIDs_RedMountain, MISSION_B)},
        {3202, this->GetLocationFromLevel(Characters_Knuckles, LevelIDs_RedMountain, MISSION_C)},
        {3300, this->GetLocationFromLevel(Characters_Knuckles, LevelIDs_LostWorld, MISSION_A)},
        {3301, this->GetLocationFromLevel(Characters_Knuckles, LevelIDs_LostWorld, MISSION_B)},
        {3302, this->GetLocationFromLevel(Characters_Knuckles, LevelIDs_LostWorld, MISSION_C)},
        {3400, this->GetLocationFromLevel(Characters_Knuckles, LevelIDs_SkyDeck, MISSION_A)},
        {3401, this->GetLocationFromLevel(Characters_Knuckles, LevelIDs_SkyDeck, MISSION_B)},
        {3402, this->GetLocationFromLevel(Characters_Knuckles, LevelIDs_SkyDeck, MISSION_C)},
        //Amy's levels
        {4000, this->GetLocationFromLevel(Characters_Amy, LevelIDs_TwinklePark, MISSION_A)},
        {4001, this->GetLocationFromLevel(Characters_Amy, LevelIDs_TwinklePark, MISSION_B)},
        {4002, this->GetLocationFromLevel(Characters_Amy, LevelIDs_TwinklePark, MISSION_C)},
        {4100, this->GetLocationFromLevel(Characters_Amy, LevelIDs_HotShelter, MISSION_A)},
        {4101, this->GetLocationFromLevel(Characters_Amy, LevelIDs_HotShelter, MISSION_B)},
        {4102, this->GetLocationFromLevel(Characters_Amy, LevelIDs_HotShelter, MISSION_C)},
        {4200, this->GetLocationFromLevel(Characters_Amy, LevelIDs_FinalEgg, MISSION_A)},
        {4201, this->GetLocationFromLevel(Characters_Amy, LevelIDs_FinalEgg, MISSION_B)},
        {4202, this->GetLocationFromLevel(Characters_Amy, LevelIDs_FinalEgg, MISSION_C)},
        //Gamma's levels
        {5000, this->GetLocationFromLevel(Characters_Gamma, LevelIDs_FinalEgg, MISSION_A)},
        {5001, this->GetLocationFromLevel(Characters_Gamma, LevelIDs_FinalEgg, MISSION_B)},
        {5002, this->GetLocationFromLevel(Characters_Gamma, LevelIDs_FinalEgg, MISSION_C)},
        {5100, this->GetLocationFromLevel(Characters_Gamma, LevelIDs_EmeraldCoast, MISSION_A)},
        {5101, this->GetLocationFromLevel(Characters_Gamma, LevelIDs_EmeraldCoast, MISSION_B)},
        {5102, this->GetLocationFromLevel(Characters_Gamma, LevelIDs_EmeraldCoast, MISSION_C)},
        {5200, this->GetLocationFromLevel(Characters_Gamma, LevelIDs_WindyValley, MISSION_A)},
        {5201, this->GetLocationFromLevel(Characters_Gamma, LevelIDs_WindyValley, MISSION_B)},
        {5202, this->GetLocationFromLevel(Characters_Gamma, LevelIDs_WindyValley, MISSION_C)},
        {5300, this->GetLocationFromLevel(Characters_Gamma, LevelIDs_RedMountain, MISSION_A)},
        {5301, this->GetLocationFromLevel(Characters_Gamma, LevelIDs_RedMountain, MISSION_B)},
        {5302, this->GetLocationFromLevel(Characters_Gamma, LevelIDs_RedMountain, MISSION_C)},
        {5400, this->GetLocationFromLevel(Characters_Gamma, LevelIDs_HotShelter, MISSION_A)},
        {5401, this->GetLocationFromLevel(Characters_Gamma, LevelIDs_HotShelter, MISSION_B)},
        {5402, this->GetLocationFromLevel(Characters_Gamma, LevelIDs_HotShelter, MISSION_C)},
        //Big's levels
        {6000, this->GetLocationFromLevel(Characters_Big, LevelIDs_TwinklePark, MISSION_A)},
        {6001, this->GetLocationFromLevel(Characters_Big, LevelIDs_TwinklePark, MISSION_B)},
        {6002, this->GetLocationFromLevel(Characters_Big, LevelIDs_TwinklePark, MISSION_C)},
        {6100, this->GetLocationFromLevel(Characters_Big, LevelIDs_IceCap, MISSION_A)},
        {6101, this->GetLocationFromLevel(Characters_Big, LevelIDs_IceCap, MISSION_B)},
        {6102, this->GetLocationFromLevel(Characters_Big, LevelIDs_IceCap, MISSION_C)},
        {6200, this->GetLocationFromLevel(Characters_Big, LevelIDs_EmeraldCoast, MISSION_A)},
        {6201, this->GetLocationFromLevel(Characters_Big, LevelIDs_EmeraldCoast, MISSION_B)},
        {6202, this->GetLocationFromLevel(Characters_Big, LevelIDs_EmeraldCoast, MISSION_C)},
        {6300, this->GetLocationFromLevel(Characters_Big, LevelIDs_HotShelter, MISSION_A)},
        {6301, this->GetLocationFromLevel(Characters_Big, LevelIDs_HotShelter, MISSION_B)},
        {6302, this->GetLocationFromLevel(Characters_Big, LevelIDs_HotShelter, MISSION_C)},

        // //TODO: Check sub-levels
        // {15, this->GetLocationFromSubLevel(static_cast<EventFlags>(LevelIDs_SandHill), "Sand Hill A", -1)},
        // {16, this->GetLocationFromSubLevel(static_cast<EventFlags>(LevelIDs_SandHill), "Sand Hill B", -1)},
        // {25, this->GetLocationFromSubLevel(static_cast<EventFlags>(LevelIDs_SandHill), "Twinkle Circuit A", -1)},
        // {26, this->GetLocationFromSubLevel(static_cast<EventFlags>(LevelIDs_SandHill), "Twinkle Circuit B", -1)},

        // //TODO: Check for emblems
        // {10, this->GetLocationFromFieldEmblem(static_cast<EventFlags>(0), "Station Emblem", -1)},
        // {11, this->GetLocationFromFieldEmblem(static_cast<EventFlags>(0), "Burger Shop Emblem", -1)},
        // {12, this->GetLocationFromFieldEmblem(static_cast<EventFlags>(0), "City Hall Emblem", -1)},
        // {13, this->GetLocationFromFieldEmblem(static_cast<EventFlags>(0), "Casino Emblem", -1)},
        // {20, this->GetLocationFromFieldEmblem(static_cast<EventFlags>(0), "Tails' Workshop Emblem", -1)},
        // {21, this->GetLocationFromFieldEmblem(static_cast<EventFlags>(0), "Shrine Emblem", -1)},
        // {22, this->GetLocationFromFieldEmblem(static_cast<EventFlags>(0), "Jungle Path Emblem", -1)},
        // {23, this->GetLocationFromFieldEmblem(static_cast<EventFlags>(0), "Tree Stump Emblem", -1)},
        // {30, this->GetLocationFromFieldEmblem(static_cast<EventFlags>(0), "Pool Emblem", -1)},
        // {31, this->GetLocationFromFieldEmblem(static_cast<EventFlags>(0), "Spinning Platform Emblem", -1)},
        // {32, this->GetLocationFromFieldEmblem(static_cast<EventFlags>(0), "Hidden Bed Emblem", -1)},
        // {3, this->GetLocationFromFieldEmblem(static_cast<EventFlags>(0), "Main Platform Emblem", -1)},


    };
}


static int Combine(const int character, const int level, const int mission)
{
    return (character << 16) | (level << 8) | mission;
}


std::string LocationRepository::GetLocationName(const Characters character, const LevelIDs levelId, int mission)
{
    std::string characterName;
    const auto characterElement = _charactersMap.find(character);
    if (characterElement != _charactersMap.end())
        characterName = characterElement->second;
    else
        characterName = "Unknown Character";

    std::string levelName;
    const auto levelElement = _levelsMap.find(levelId);
    if (levelElement != _levelsMap.end())
        levelName = levelElement->second;
    else
        levelName = "Unknown Level";

    std::string missionName = (mission == 0)
                                  ? "Mission A"
                                  : (mission == 1)
                                  ? "Mission B"
                                  : (mission == 2)
                                  ? "Mission C"
                                  : "Unknown Mission";

    return levelName + " (" + characterName + " - " + missionName + ")";
}

LocationData LocationRepository::GetLocationFromUpgrade(EventFlags eventFlags, const char* str, int i)
{
    return LocationData(eventFlags, LocationUpgrade, str, i);
}

LocationData LocationRepository::GetLocationFromLevel(const Characters character, const LevelIDs levelId,
                                                      const int mission)
{
    return LocationData(Combine(character, levelId, mission), LocationLevel,
                        GetLocationName(character, levelId, mission), -1);
}


LocationData LocationRepository::GetLocationFromSubLevel(const EventFlags eventFlags, const char* str, const int i)
{
    return LocationData(eventFlags, LocationCharacter, str, i);
}

LocationData LocationRepository::GetLocationFromFieldEmblem(const EventFlags eventFlags, const char* str, const int i)
{
    return LocationData(eventFlags, LocationCharacter, str, i);
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
