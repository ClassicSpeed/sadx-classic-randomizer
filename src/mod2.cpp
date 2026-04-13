#include <pch.h>
#include "Settings.h"
#include "Options.h"
#include "GameStatus.h"

extern "C" {
__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
{
    
    //Configuration
    Settings& settings = Settings::Init(path, helperFunctions);
    Options& options = Options::Init(settings);
    GameStatus& gameStatus = GameStatus::Init(options);
}

// Simple OnFrame test
__declspec(dllexport) void __cdecl OnFrame()
{
    Rings = 12345;
    DisplayDebugString(NJM_LOCATION(2, 1), "Testing");
}

__declspec(dllexport) ModInfo SADXModInfo = {ModLoaderVer};
}
