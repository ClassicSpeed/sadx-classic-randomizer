#include "SADXModLoader.h"

extern "C" {
bool check_jet_anklet = false;

__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
{
    // Executed at startup, contains helperFunctions and the path to your mod (useful for getting the config file.)
    // This is where we override functions, replace static data, etc.
    SetEventFlag(EventFlags_Tails_JetAnklet);
}

__declspec(dllexport) void __cdecl OnInitEnd()
{
    // Executed after every mod has been initialized, mainly used to check if a specific mod is also enabled.
}

__declspec(dllexport) void __cdecl OnFrame()
{
    Rings = 456;
    if (Current_CharObj2 != nullptr)
    {
        // Executed every running frame of SADX
        if (!check_jet_anklet && GetEventFlag(EventFlags_Tails_JetAnklet))
        {
            check_jet_anklet = true;
            PrintDebug("Tails got the jet ankles check!\n");
            if (Current_CharObj2->Upgrades & Upgrades_JetAnklet)
                PrintDebug("And he got the upgrade too!\n");
            else
                PrintDebug("But still didn't get the upgrade....\n");

            Current_CharObj2->Upgrades &= ~Upgrades_JetAnklet;
            if (!(Current_CharObj2->Upgrades & Upgrades_JetAnklet))
                PrintDebug("Now he doesn't have it!!\n");
        }

        if (!PressedButtons.empty())
        {
            for (const auto& button : PressedButtons)

                if (button & WhistleButtons)
                {
                    if (Current_CharObj2 != nullptr)
                    {
                        SetDebugFontSize(13.0f * (unsigned short)VerticalResolution / 480.0f);
                        SetDebugFontColor(0x8e8e8e);
                        DisplayDebugStringFormatted(NJM_LOCATION(2, 1), "   Tails has the Rhythm Badge from Bob!\n");

                        PrintDebug("Tails has the Rhythm Badge!\n");
                        Current_CharObj2->Upgrades = 0;
                        Current_CharObj2->Upgrades = Upgrades_RhythmBadge;

                        if (GetEventFlag(EventFlags_Tails_JetAnklet))
                            PrintDebug("...and he already did the jet anklet upgrade!\n");
                        else
                            PrintDebug("...and he didn't do the jet anklet upgrade!\n");
                    }
                }
        }
    }
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
