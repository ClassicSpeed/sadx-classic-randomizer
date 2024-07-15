#include "pch.h"

#include "application/Randomizer.h"
#include "input/archipelago/ArchipelagoManager.h"
#include "input/cheatsManager/CheatsManager.h"
#include "input/eventDetector/EventDetector.h"
#include "input/characterLoading/CharacterLoadingDetector.h"
#include "output/archipelagoMessenger/ArchipelagoMessenger.h"
#include "output/locationRepository/LocationRepository.h"
#include "output/saveFileManager/SaveFileManager.h"
#include "output/worldStateManager/WorldStateManager.h"

extern "C" {
DisplayManager displayManager = DisplayManager();
UpgradeManager upgradeManager = UpgradeManager();
WorldStateManager worldStateManager = WorldStateManager();
ItemRepository itemRepository = ItemRepository();
LocationRepository checkRepository = LocationRepository();
ArchipelagoMessenger archipelagoMessenger = ArchipelagoMessenger();

Randomizer randomizer = Randomizer(displayManager,
                                   upgradeManager,
                                   worldStateManager,
                                   itemRepository,
                                   checkRepository,
                                   archipelagoMessenger);

CheatsManager cheatsManager = CheatsManager(randomizer);
ArchipelagoManager archipelagoManager = ArchipelagoManager(randomizer);
EventDetector eventDetector = EventDetector(randomizer);
CharacterLoadingDetector characterLoadingDetector = CharacterLoadingDetector(randomizer);
SaveFileManager saveFileManager = SaveFileManager();


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
    const bool skipCredits = settingsIni->getBool("GameSettings", "SkippeableCredits", true);
    const bool winButtonEnabled = settingsIni->getBool("GameSettings", "AutoWinButton", false);

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

bool saveFileSelected = false;
FunctionHook<BOOL> onTrialMenuLoaded(0x506780, []()-> BOOL
{
    if (GameMode == GameModes_Menu && !saveFileSelected)
    {
        saveFileManager.OnSaveFileLoaded();
        archipelagoManager.OnSaveFileLoaded();
        saveFileSelected = true;
    }

    //Blocks trial menu
    return false;
});
//Blocks mission menu
FunctionHook<BOOL> blockMissionMenu(0x506410, []() -> BOOL { return false; });


__declspec(dllexport) ModInfo SADXModInfo = {ModLoaderVer}; // This is needed for the Mod Loader to recognize the DLL.
}
