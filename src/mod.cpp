#include "FunctionHook.h"
#include "SADXModLoader.h"
#include "application/Randomizer.h"
#include "input/archipelago/FakeArchipelagoManager.h"
#include "input/upgrade/UpgradeDetector.h"
#include "input/characterLoading/CharacterLoadingDetector.h"

extern "C" {
DisplayManager displayManager = DisplayManager();
UpgradeManager upgradeManager = UpgradeManager();
ItemRepository itemRepository = ItemRepository();
CheckRepository checkRepository = CheckRepository();

Randomizer randomizer = Randomizer(displayManager, upgradeManager, itemRepository,checkRepository);

FakeArchipelagoManager archipelagoManager = FakeArchipelagoManager(randomizer);
UpgradeDetector upgradeDetector = UpgradeDetector(randomizer);
CharacterLoadingDetector characterLoadingDetector = CharacterLoadingDetector(randomizer);


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
    // Executed every running frame of SADX
    if (Current_CharObj2 != nullptr)
    {
        upgradeDetector.OnPlayingFrame();
        archipelagoManager.OnPlayingFrame();
        characterLoadingDetector.OnPlayingFrame();
    }
}


void OnCharacterLoad();
FunctionHook<void> loadCharacterHook(0x4157C0, OnCharacterLoad);

void OnCharacterLoad()
{
    loadCharacterHook.Original();
    characterLoadingDetector.OnCharacterLoaded();
}


__declspec(dllexport) ModInfo SADXModInfo = {ModLoaderVer}; // This is needed for the Mod Loader to recognize the DLL.
}
