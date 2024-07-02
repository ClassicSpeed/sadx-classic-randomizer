#include "LocationRepository.h"
#include "SADXModLoader.h"

LocationRepository::LocationRepository()
{
    _checkData = {

        // {1, LocationData(EventFlags_SonicUnlockedAdventure, "Unlock Sonic's Story", 1)},
        {2, LocationData(EventFlags_TailsUnlockedAdventure, "Unlock Tails' Story", 2)},
        {3, LocationData(EventFlags_KnucklesUnlockedAdventure, "Unlock Knuckles' Story", 3)},
        {4, LocationData(EventFlags_AmyUnlockedAdventure, "Unlock Amy's Story", 4)},
        {5, LocationData(EventFlags_GammaUnlockedAdventure, "Unlock Gamma's Story", 5)},
        {6, LocationData(EventFlags_BigUnlockedAdventure, "Unlock Big's Story", 6)},

        {10, LocationData(EventFlags_Sonic_LightShoes, "Light shoes upgrade (Sonic)", 10)},
        {11, LocationData(EventFlags_Sonic_CrystalRing, "Crystal ring upgrade (Sonic)", 11)},
        {12, LocationData(EventFlags_Sonic_AncientLight, "Ancient light upgrade (Sonic)", 12)},

        {20, LocationData(EventFlags_Tails_JetAnklet, "Jet Ankle upgrade (Tails)", 20)},
        {21, LocationData(EventFlags_Tails_RhythmBadge, "Rhythm Badge upgrade (Tails)", 21)},

        {30, LocationData(EventFlags_Knuckles_ShovelClaw, "Shovel claw upgrade (Knuckles)", 30)},
        {31, LocationData(EventFlags_Knuckles_FightingGloves, "Fighting gloves upgrade (Knuckles)", 31)},

        {40, LocationData(EventFlags_Amy_LongHammer, "Long Hammer upgrade (Amy)", 40)},
        {41, LocationData(EventFlags_Amy_WarriorFeather, "Warrior feather upgrade (Amy)", 41)},

        {50, LocationData(EventFlags_Gamma_LaserBlaster, "Laser Blaster upgrade (Gamma)", 50)},
        {51, LocationData(EventFlags_Gamma_JetBooster, "Jet booster upgrade (Gamma)", 51)},

        {60, LocationData(EventFlags_Big_LifeRing, "Life belt upgrade (Big)", 60)},
        {61, LocationData(EventFlags_Big_PowerRod, "Power rod upgrade (Big)", 61)},

    };
}



LocationData LocationRepository::SetChecked(const int checkId)
{
    _checkData[checkId].checked = true;
    return _checkData[checkId];
}

LocationData LocationRepository::GetCheck(const int checkId)
{
    return _checkData[checkId];
}

std::map<int, LocationData> LocationRepository::GetChecks()
{
    return _checkData;
}
