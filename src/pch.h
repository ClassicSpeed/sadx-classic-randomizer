// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define SADX_AP_VERSION_MAJOR 0
#define SADX_AP_VERSION_MINOR 8
#define SADX_AP_VERSION_PATCH 0


#define MISSION_C  2
#define MISSION_B  1
#define MISSION_A  0


#define SUB_LEVEL_MISSION_B  1
#define SUB_LEVEL_MISSION_A  0
// add headers that you want to pre-compile here
#include "framework.h"
#include "../lib/sadx-mod-loader/SADXModLoader/include/SADXModLoader.h"
#include "../lib/sadx-mod-loader/SADXModLoader/include/FunctionHook.h"
#include "../lib/sadx-mod-loader/mod-loader-common/ModLoaderCommon/IniFile.hpp"
#include <APCpp/Archipelago.h>
#include <json/json.h>


#define FunctionHookAdd(address, hookFunction) FunctionHook<void> hook_##address(address, [] { hookFunction(); hook_##address.Original();  })
#define GET_LEVEL(levelAct) ((levelAct) >> 8)
#define BYTE1(x, n)   (*((uint8_t*)&(x)+1))


const std::unordered_map<int, std::string> CHARACTERS_MAP = {
    {Characters_Sonic, "Sonic"},
    {Characters_Tails, "Tails"},
    {Characters_Knuckles, "Knuckles"},
    {Characters_Amy, "Amy"},
    {Characters_Gamma, "Gamma"},
    {Characters_Big, "Big"}
};



const std::unordered_map<int, std::string> LEVELS_MAP = {
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
    {LevelIDs_TwinkleCircuit, "Twinkle Circuit"},
    {LevelIDs_SandHill, "Sand Hill"},
};

const std::unordered_map<int, int> SONIC_TARGET_TIMES = {
    {LevelIDs_EmeraldCoast, 7200},
    {LevelIDs_WindyValley, 10800},
    {LevelIDs_Casinopolis, 18000},
    {LevelIDs_IceCap, 14400},
    {LevelIDs_TwinklePark, 10800},
    {LevelIDs_SpeedHighway, 9000},
    {LevelIDs_RedMountain, 10800},
    {LevelIDs_SkyDeck, 18000},
    {LevelIDs_LostWorld, 16200},
    {LevelIDs_FinalEgg, 16200}
};

const std::unordered_map<int, int> TAILS_TARGET_TIMES = {
    {LevelIDs_WindyValley, 5400}, //1 min 30 sec
    {LevelIDs_Casinopolis, 3600}, //1 min
    {LevelIDs_IceCap, 7200}, // 2 min
    {LevelIDs_SkyDeck, 3600}, //1 min
    {LevelIDs_SpeedHighway, 7200}, //2 min
};


const std::unordered_map<int, int> KNUCKLES_TARGET_TIMES = {
    {LevelIDs_SpeedHighway, 3600},
    {LevelIDs_Casinopolis, 3600},
    {LevelIDs_RedMountain, 3600},
    {LevelIDs_LostWorld, 3600},
    {LevelIDs_SkyDeck, 7200},
};

const std::unordered_map<int, int> AMY_TARGET_TIMES = {
    {LevelIDs_TwinklePark, 7200},
    {LevelIDs_HotShelter, 23400},
    {LevelIDs_FinalEgg, 9000},
};

const std::unordered_map<int, int> GAMMA_TARGET_TIMES = {
    {LevelIDs_FinalEgg, 9000},
    {LevelIDs_EmeraldCoast, 10800},
    {LevelIDs_WindyValley, 10800},
    {LevelIDs_RedMountain, 10800},
    {LevelIDs_HotShelter, 7200},
};


#endif //PCH_H
