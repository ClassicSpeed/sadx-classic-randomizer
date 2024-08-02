#include <chrono>

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

#define ReplacePNG_Common(a) do { \
_snprintf_s(pathbuf, LengthOfArray(pathbuf), "%s\\textures\\pvr_common\\index.txt", path); \
helperFunctions.ReplaceFile("system\\" a ".PVR", pathbuf); \
} while (0)

constexpr int SYNC_RATE = 10;

extern "C" {
    
std::chrono::time_point<std::chrono::system_clock> timestamp = std::chrono::system_clock::now();
const int instance_id = std::chrono::duration_cast<std::chrono::seconds>(timestamp.time_since_epoch()).count();
constexpr int64_t base_id = 543800000;
int syncTimer = 0;
    

DisplayManager displayManager = DisplayManager();
CharacterManager characterManager = CharacterManager();
WorldStateManager worldStateManager = WorldStateManager();
ItemRepository itemRepository = ItemRepository();
LocationRepository checkRepository = LocationRepository();
ArchipelagoMessenger archipelagoMessenger = ArchipelagoMessenger(instance_id, base_id);

Randomizer randomizer = Randomizer(displayManager,
                                   characterManager,
                                   worldStateManager,
                                   itemRepository,
                                   checkRepository,
                                   archipelagoMessenger);

CheatsManager cheatsManager = CheatsManager(randomizer);
ArchipelagoManager archipelagoManager = ArchipelagoManager(randomizer,instance_id, base_id);
EventDetector eventDetector = EventDetector(randomizer);
CharacterLoadingDetector characterLoadingDetector = CharacterLoadingDetector(randomizer);
SaveFileManager saveFileManager = SaveFileManager();


__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
{
    if (helperFunctions.Mods->find_by_name("Steam Achievements Mod"))
    {
        MessageBox(WindowHandle,
                   L"The Steam Achievements Mod is not compatible with the SADX Archipelago Randomizer.\n\nPlease disable it and try again.",
                   L"SADX Archipelago Error: Incompatible Mod", MB_OK | MB_ICONERROR);
        exit(0);
    }

    if (helperFunctions.Mods->find_by_name("Fixes, Adds, and Beta Restores"))
    {
        MessageBox(WindowHandle,
                   L"The Fixes, Adds, and Beta Restores Mod is not compatible with the SADX Archipelago Randomizer.\n\nPlease disable it and try again.",
                   L"SADX Archipelago Error: Incompatible Mod", MB_OK | MB_ICONERROR);
        exit(0);
    }

    const IniFile* settingsIni = new IniFile(std::string(path) + "\\config.ini");

    if (!settingsIni)
        return randomizer.ShowStatusInformation("Invalid Settings INI");

    const std::string serverIp = settingsIni->getString("AP", "IP");
    const std::string playerName = settingsIni->getString("AP", "PlayerName");
    const std::string serverPassword = settingsIni->getString("AP", "Password");

    archipelagoManager.SetServerConfiguration(serverIp, playerName, serverPassword);

    const bool completeMultipleLevelMissions = settingsIni->getBool("GameSettings", "CompleteMultipleLevelMissions",
                                                                    true);
    const bool autoSkipCutscenes = settingsIni->getBool("GameSettings", "AutoSkipCutscenes", true);
    const bool skipCredits = settingsIni->getBool("GameSettings", "SkippeableCredits", true);
    const bool winButtonEnabled = settingsIni->getBool("GameSettings", "AutoWinButton", false);

    cheatsManager.SetCheatsConfiguration(autoSkipCutscenes, skipCredits, winButtonEnabled);
    eventDetector.SetMultipleMissions(completeMultipleLevelMissions);

    char pathbuf[MAX_PATH];
    ReplacePNG_Common("HYOJI_EMBLEM0");
    ReplacePNG_Common("HYOJI_EMBLEM1");
}

__declspec(dllexport) void __cdecl OnFrame()
{
    saveFileManager.OnFrame();
    archipelagoManager.OnFrame();
    displayManager.OnFrame();
    cheatsManager.OnPlayingFrame();
    if (Current_CharObj2 != nullptr)
    {
        eventDetector.OnPlayingFrame();
        characterLoadingDetector.OnPlayingFrame();
        randomizer.OnPlayingFrame();
    }
    if(syncTimer == 0)
    {
        randomizer.OnSync();
        syncTimer = SYNC_RATE;
    }
    else
        syncTimer--;
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
