// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define SADX_AP_VERSION_MAJOR 1
#define SADX_AP_VERSION_MINOR 2
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
#include <SADXModLoader.h>
#include <FunctionHook.h>
#include <UsercallFunctionHandler.h>
#include <IniFile.hpp>
// #include "../lib/sadx-mod-loader/SADXModLoader/include/SADXModLoader.h"
// #include "../lib/sadx-mod-loader/SADXModLoader/include/FunctionHook.h"
// #include "../lib/sadx-mod-loader/mod-loader-common/ModLoaderCommon/IniFile.hpp"
// #include "../lib/sadx-mod-loader/SADXModLoader/include/UsercallFunctionHandler.h"
#include <Archipelago.h>
#include <json.h>


#endif //PCH_H
