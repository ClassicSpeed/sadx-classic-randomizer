#include "pch.h"

#include "application/Randomizer.h"
#include "input/archipelago/ArchipelagoManager.h"
#include "input/cheatsManager/CheatsManager.h"
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

CheatsManager cheatsManager = CheatsManager(randomizer);
ArchipelagoManager archipelagoManager = ArchipelagoManager(randomizer);
EventDetector eventDetector = EventDetector(randomizer);
CharacterLoadingDetector characterLoadingDetector = CharacterLoadingDetector(randomizer);


__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
{


    const IniFile* settingsIni = new IniFile(std::string(path) + "\\config.ini");

    if (!settingsIni)
        return randomizer.ShowStatusInformation("Invalid Settings INI");

    const std::string serverIp = settingsIni->getString("AP", "IP");
    const std::string playerName = settingsIni->getString("AP", "PlayerName");
    const std::string serverPassword = settingsIni->getString("AP", "Password");
    
    archipelagoManager.SetServerConfiguration(serverIp, playerName, serverPassword);

    const bool autoSkipCutscenes = settingsIni->getBool("GameSettings", "AutoSkipCutscenes", true);
    const bool skipCredits  = settingsIni->getBool("GameSettings", "SkippeableCredits", true);
    const bool winButtonEnabled  = settingsIni->getBool("GameSettings", "AutoWinButton", false);

    cheatsManager.SetCheatsConfiguration(autoSkipCutscenes, skipCredits, winButtonEnabled);
}

__declspec(dllexport) void __cdecl OnFrame()
{
    archipelagoManager.OnFrame();
    displayManager.OnFrame();
    cheatsManager.OnPlayingFrame();
    if (Current_CharObj2 != nullptr)
    {
        eventDetector.OnPlayingFrame();
        characterLoadingDetector.OnPlayingFrame();
    }
}


__declspec(dllexport) ModInfo SADXModInfo = {ModLoaderVer}; // This is needed for the Mod Loader to recognize the DLL.
}
