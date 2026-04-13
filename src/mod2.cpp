#include "pch.h"

extern "C" {
__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
{
}

// Simple OnFrame test
__declspec(dllexport) void __cdecl OnFrame()
{
    Rings = 12345;
    DisplayDebugString(NJM_LOCATION(2, 1), "Testing");
}

__declspec(dllexport) ModInfo SADXModInfo = {ModLoaderVer};
}
