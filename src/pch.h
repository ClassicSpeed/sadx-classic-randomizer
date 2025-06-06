// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define SADX_AP_VERSION_MAJOR 1
#define SADX_AP_VERSION_MINOR 1
#define SADX_AP_VERSION_PATCH 2

#define MISSION_S  3
#define MISSION_C  2
#define MISSION_B  1
#define MISSION_A  0


#define TWINKLE_CIRCUIT_GAMMA  7
#define TWINKLE_CIRCUIT_BIG  6
#define TWINKLE_CIRCUIT_AMY  5
#define TWINKLE_CIRCUIT_KNUCKLES  4
#define TWINKLE_CIRCUIT_TAILS  3
#define TWINKLE_CIRCUIT_SONIC  2
#define SUB_LEVEL_MISSION_B  1
#define SUB_LEVEL_MISSION_A  0

// Pre-compiled headers
#include "framework.h"
#include "../lib/sadx-mod-loader/SADXModLoader/include/SADXModLoader.h"
#include "../lib/sadx-mod-loader/SADXModLoader/include/FunctionHook.h"
#include "../lib/sadx-mod-loader/mod-loader-common/ModLoaderCommon/IniFile.hpp"
#include "../lib/sadx-mod-loader/SADXModLoader/include/UsercallFunctionHandler.h"
#include <APCpp/Archipelago.h>
#include <json/json.h>


#define FunctionHookAdd(address, hookFunction) FunctionHook<void> hook_##address(address, [] { hookFunction(); hook_##address.Original();  })
#define GET_LEVEL(levelAct) ((levelAct) >> 8)
#define GET_ACT(levelAct) ((levelAct) & 0xFF)
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

#define TIME_A_RANK 0
#define TIME_S_RANK 1
#define TIME_S_RANK_EXPERT 2

const std::unordered_map<int, std::tuple<int, int, int>> SONIC_TARGET_TIMES = {
    {LevelIDs_EmeraldCoast, std::make_tuple(7200, 6300, 6300)},
    {LevelIDs_WindyValley, std::make_tuple(10800, 7800, 7200)},
    {LevelIDs_Casinopolis, std::make_tuple(18000, 16200, 3600)},
    {LevelIDs_IceCap, std::make_tuple(14400, 9900, 1800)},
    {LevelIDs_TwinklePark, std::make_tuple(10800, 8400, 7200)},
    {LevelIDs_SpeedHighway, std::make_tuple(9000, 7200, 7200)},
    {LevelIDs_RedMountain, std::make_tuple(10800, 9000, 6300)},
    {LevelIDs_SkyDeck, std::make_tuple(18000, 9000, 7200)},
    {LevelIDs_LostWorld, std::make_tuple(16200, 9900, 9900)},
    {LevelIDs_FinalEgg, std::make_tuple(16200, 11700, 7800)},
};


const std::unordered_map<int, std::tuple<int, int, int>> TAILS_TARGET_TIMES = {
    {LevelIDs_WindyValley, std::make_tuple(5400, 3300, 2400)},
    {LevelIDs_Casinopolis, std::make_tuple(3600, 3000, 1800)},
    {LevelIDs_IceCap, std::make_tuple(7200, 6900, 6900)},
    {LevelIDs_SkyDeck, std::make_tuple(3600, 2700, 2700)},
    {LevelIDs_SpeedHighway, std::make_tuple(7200, 5400, 5400)},
};

const std::unordered_map<int, std::tuple<int, int, int>> KNUCKLES_TARGET_TIMES = {
    {LevelIDs_SpeedHighway, std::make_tuple(3600, 2700, 2700)},
    {LevelIDs_Casinopolis, std::make_tuple(3600, 2700, 2700)},
    {LevelIDs_RedMountain, std::make_tuple(3600, 2700, 2700)},
    {LevelIDs_LostWorld, std::make_tuple(3600, 2700, 2700)},
    {LevelIDs_SkyDeck, std::make_tuple(7200, 2700, 2700)},
};

const std::unordered_map<int, std::tuple<int, int, int>> AMY_TARGET_TIMES = {
    {LevelIDs_TwinklePark, std::make_tuple(7200, 5400, 5400)},
    {LevelIDs_HotShelter, std::make_tuple(23400, 12600, 9900)},
    {LevelIDs_FinalEgg, std::make_tuple(9000, 6300, 6300)},
};

const std::unordered_map<int, std::tuple<int, int, int>> GAMMA_TARGET_TIMES = {
    {LevelIDs_FinalEgg, std::make_tuple(9000, 11700, 11700)},
    {LevelIDs_EmeraldCoast, std::make_tuple(10800, 11700, 11700)},
    {LevelIDs_WindyValley, std::make_tuple(10800, 20700, 20700)},
    {LevelIDs_RedMountain, std::make_tuple(10800, 12600, 12600)},
    {LevelIDs_HotShelter, std::make_tuple(7200, 10800, 10800)},
};

class IOnFrame
{
public:
    virtual void OnFrame() = 0;
    virtual ~IOnFrame() = default;
};
#endif //PCH_H
