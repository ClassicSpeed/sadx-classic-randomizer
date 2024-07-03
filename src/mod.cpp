#include "FunctionHook.h"
#include "IniFile.hpp"
#include "SADXModLoader.h"
#include "application/Randomizer.h"
#include "input/archipelago/ArchipelagoManager.h"
#include "input/autowin/AutoWinManager.h"
#include "input/eventDetector/EventDetector.h"
#include "input/characterLoading/CharacterLoadingDetector.h"
#include "output/archipelagoMessenger/ArchipelagoMessenger.h"
#include "output/locationRepository/LocationRepository.h"

extern "C" {
DisplayManager displayManager = DisplayManager();
UpgradeManager upgradeManager = UpgradeManager();
MenuManager menuManager = MenuManager();
ItemRepository itemRepository = ItemRepository();
LocationRepository checkRepository = LocationRepository();
ArchipelagoMessenger archipelagoMessenger = ArchipelagoMessenger();

Randomizer randomizer = Randomizer(displayManager,
                                   upgradeManager,
                                   menuManager,
                                   itemRepository,
                                   checkRepository,
                                   archipelagoMessenger);

AutoWinManager autoWinManager = AutoWinManager(randomizer);
ArchipelagoManager archipelagoManager = ArchipelagoManager(randomizer);
EventDetector eventDetector = EventDetector(randomizer);
CharacterLoadingDetector characterLoadingDetector = CharacterLoadingDetector(randomizer);


__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
{
    // const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
    archipelagoManager.SetConfigPath(std::string(path) + "\\config.ini");
}

__declspec(dllexport) void __cdecl OnFrame()
{
    archipelagoManager.OnFrame();
    displayManager.OnFrame();
    autoWinManager.OnPlayingFrame();
    if (Current_CharObj2 != nullptr)
    {
        eventDetector.OnPlayingFrame();
        characterLoadingDetector.OnPlayingFrame();
    }
}


__declspec(dllexport) ModInfo SADXModInfo = {ModLoaderVer}; // This is needed for the Mod Loader to recognize the DLL.
}

