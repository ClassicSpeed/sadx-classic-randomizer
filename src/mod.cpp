#include "FunctionHook.h"
#include "SADXModLoader.h"
#include "application/Randomizer.h"
#include "input/archipelago/FakeArchipelagoManager.h"
#include "input/eventDetector/EventDetector.h"
#include "input/characterLoading/CharacterLoadingDetector.h"
#define FunctionHookAdd(address, hookFunction) FunctionHook<void> hook_##address(address, [] { hookFunction(); hook_##address.Original();  })


extern "C" {
DisplayManager displayManager = DisplayManager();
UpgradeManager upgradeManager = UpgradeManager();
CharacterSelectionManager characterSelectionManager = CharacterSelectionManager();
ItemRepository itemRepository = ItemRepository();
CheckRepository checkRepository = CheckRepository();

Randomizer randomizer = Randomizer(displayManager, upgradeManager, characterSelectionManager, itemRepository,
                                   checkRepository);

FakeArchipelagoManager archipelagoManager = FakeArchipelagoManager(randomizer);
EventDetector eventDetector = EventDetector(randomizer);
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
        eventDetector.OnPlayingFrame();
        archipelagoManager.OnPlayingFrame();
        characterLoadingDetector.OnPlayingFrame();
    }
}

//Character loaded
FunctionHookAdd(0x4157C0, characterLoadingDetector.OnCharacterLoaded);

//Character selection screen loaded
FunctionHookAdd(0x512BC0, []
                {
                characterLoadingDetector.OnCharacterLoaded();
                randomizer.OnCharacterSelectScreenLoaded();
                });


__declspec(dllexport) ModInfo SADXModInfo = {ModLoaderVer}; // This is needed for the Mod Loader to recognize the DLL.
}
