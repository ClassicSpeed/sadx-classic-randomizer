// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define SADX_AP_VERSION_MAJOR 0
#define SADX_AP_VERSION_MINOR 3
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
#include "../lib/APCpp/Archipelago.h"



#endif //PCH_H
#define FunctionHookAdd(address, hookFunction) FunctionHook<void> hook_##address(address, [] { hookFunction(); hook_##address.Original();  })
