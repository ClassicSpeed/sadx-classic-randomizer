// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define SADX_AP_VERSION_MAJOR 1
#define SADX_AP_VERSION_MINOR 2
#define SADX_AP_VERSION_PATCH 0

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
#define GET_LEVEL_ACT(level, act) (static_cast<LevelAndActIDs>(((level) << 8) | ((act) & 0xFF)))
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

// Checks if the given position is within 'tolerance' units of the target position
inline bool IsNearPosition(const NJS_VECTOR& position, const float targetX, const float targetY, const float targetZ,
                           const float tolerance = 3.0f)
{
    return (position.x > targetX - tolerance && position.x < targetX + tolerance) &&
        (position.y > targetY - tolerance && position.y < targetY + tolerance) &&
        (position.z > targetZ - tolerance && position.z < targetZ + tolerance);
}


class IOnFrame
{
public:
    virtual void OnFrame() = 0;
    virtual ~IOnFrame() = default;
};


inline NJS_TEXNAME entranceTextNames[42]{};
inline NJS_TEXLIST entranceTextList = {arrayptrandlength(entranceTextNames)};
inline PVMEntry EntranceSign = {"entrances", &entranceTextList};

inline NJS_TEXANIM emblem_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 1, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM line_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 2, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_0_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 3, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_1_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 4, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_2_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 5, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_3_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 6, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_4_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 7, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_5_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 8, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_6_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 9, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_7_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 10, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_8_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 11, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM number_9_lock_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 12, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM base_map[] = {{18, 18, 9, 9, 255, 255, 0, 0, 13, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM emerald_coast_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 14, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM windy_valley_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 15, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM casinopolis_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 16, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM ice_cap_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 17, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM speed_highway_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 18, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM twinkle_park_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 19, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM red_mountain_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 20, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM sky_deck_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 21, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM lost_world_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 22, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM final_egg_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 23, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM hot_shelter_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 24, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM chaos_0_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 25, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM chaos_2_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 26, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM chaos_4_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 27, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM chaos_6_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 28, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM egg_hornet_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 29, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM egg_walker_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 30, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM egg_viper_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 31, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM beta_1_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 32, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM beta_2_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 33, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM zero_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 34, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM twinkle_circuit_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 35, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM sky_chase_1_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 36, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM sky_chase_2_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 37, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM sand_hill_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 38, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM ss_garden_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 39, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM mr_garden_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 40, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM ec_garden_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 41, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM new_logo_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 42, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM location_map_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 43, NJD_SPRITE_COLOR}};
inline NJS_TEXANIM blocked_anim[] = {{18, 18, 9, 9, 255, 255, 0, 0, 44, NJD_SPRITE_COLOR}};


// Helper to get the correct number anim
inline NJS_TEXANIM* GetNumberAnim(int num)
{
    static NJS_TEXANIM* number_anims[] = {
        number_0_lock_anim, number_1_lock_anim, number_2_lock_anim, number_3_lock_anim, number_4_lock_anim,
        number_5_lock_anim, number_6_lock_anim, number_7_lock_anim, number_8_lock_anim, number_9_lock_anim
    };
    return (num >= 0 && num <= 9) ? number_anims[num] : number_0_lock_anim;
}


#endif //PCH_H
