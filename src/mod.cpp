#include "SADXModLoader.h"

extern "C" {
short given_upgrades = false;

__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
{
    // Executed at startup, contains helperFunctions and the path to your mod (useful for getting the config file.)
    // This is where we override functions, replace static data, etc.
}

__declspec(dllexport) void __cdecl OnInitEnd()
{
    // Executed after every mod has been initialized, mainly used to check if a specific mod is also enabled.
}

__declspec(dllexport) void __cdecl OnFrame()
{
    Rings = 456;
    // Executed every running frame of SADX
}

__declspec(dllexport) void __cdecl OnInput()
{
    // Executed before the game processes input
}

__declspec(dllexport) void __cdecl OnControl()
{
    // Executed when the game processes input
}

__declspec(dllexport) void __cdecl OnRenderDeviceReset()
{
    // Executed when the window size changes
}

__declspec(dllexport) void __cdecl OnRenderDeviceLost()
{
    // Executed when the game fails to render the scene
}

__declspec(dllexport) void __cdecl OnRenderSceneStart()
{
    // Executed before the game starts rendering the scene
}

__declspec(dllexport) void __cdecl OnRenderSceneEnd()
{
    // Executed when the game finishes rendering the scene
}

__declspec(dllexport) void __cdecl OnExit()
{
    // Executed when the game is about to terminate
}

__declspec(dllexport) ModInfo SADXModInfo = {ModLoaderVer}; // This is needed for the Mod Loader to recognize the DLL.
}
