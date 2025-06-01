#include <chrono>

#include "pch.h"

#include "application/Randomizer.h"
#include "input/archipelago/ArchipelagoManager.h"
#include "input/cheatsManager/CheatsManager.h"
#include "input/eventDetector/EventDetector.h"
#include "input/characterLoading/CharacterLoadingDetector.h"
#include "output/archipelagoMessenger/ArchipelagoMessenger.h"
#include "output/locationRepository/LocationRepository.h"
#include "output/musicManager/MusicManager.h"
#include "output/saveFileManager/SaveFileManager.h"
#include "output/worldStateManager/WorldStateManager.h"

constexpr int SYNC_RATE = 10;

void ReplaceEmblemImage(const char* path, const HelperFunctions& helperFunctions);

extern "C" {
int syncTimer = 0;

Settings* settings = nullptr;
Options* options = nullptr;
ReactionManager* reactionManager = nullptr;
DisplayManager* displayManager = nullptr;
CharacterManager* characterManager = nullptr;
WorldStateManager* worldStateManager = nullptr;
ItemRepository* itemRepository = nullptr;
LocationRepository* checkRepository = nullptr;
ArchipelagoMessenger* archipelagoMessenger = nullptr;
SaveFileManager* saveFileManager = nullptr;
MusicManager* musicManager = nullptr;
Randomizer* randomizer = nullptr;
CheatsManager* cheatsManager = nullptr;
ArchipelagoManager* archipelagoManager = nullptr;
EventDetector* eventDetector = nullptr;
CharacterLoadingDetector* characterLoadingDetector = nullptr;


__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
{
    settings = &Settings::Init(path, helperFunctions);
    options = &Options::Init(*settings);
    reactionManager = &ReactionManager::Init(*options, *settings);
    displayManager = &DisplayManager::Init(*options, *settings);
    characterManager = &CharacterManager::Init(*options, *settings, *reactionManager);
    worldStateManager = &WorldStateManager::Init(*options, *settings);
    itemRepository = &ItemRepository::Init();
    checkRepository = &LocationRepository::Init();
    archipelagoMessenger = &ArchipelagoMessenger::Init(*options);
    saveFileManager = &SaveFileManager::Init();
    musicManager = &MusicManager::Init(*options, *settings, helperFunctions);
    randomizer = &Randomizer::Init(*options, *settings, *displayManager, *characterManager, *worldStateManager,
                                   *itemRepository,
                                   *checkRepository, *archipelagoMessenger, *saveFileManager, *musicManager,
                                   *reactionManager);
    cheatsManager = &CheatsManager::Init(*settings);
    archipelagoManager = &ArchipelagoManager::Init(*options, *settings, *randomizer);
    eventDetector = &EventDetector::Init(*options, *settings, *randomizer);
    characterLoadingDetector = &CharacterLoadingDetector::Init(*randomizer);


    ReplaceEmblemImage(path, helperFunctions);
    if (helperFunctions.Mods->find_by_name("Super Sonic"))
    {
        PrintDebug("[SADX Randomizer] Super Sonic Mod detected\n");
        randomizer->SetSuperSonicModRunning(true);
    }
}

__declspec(dllexport) void __cdecl OnFrame()
{
    saveFileManager->OnFrame();
    archipelagoManager->OnFrame();
    displayManager->OnFrame();
    worldStateManager->OnFrame();

    if (Current_CharObj2 != nullptr && EntityData1Ptrs[0] != nullptr)
    {
        eventDetector->OnPlayingFrame();
        characterLoadingDetector->OnPlayingFrame();
        randomizer->OnPlayingFrame();
        characterManager->OnPlayingFrame();
    }

    if (syncTimer == 0)
    {
        randomizer->OnSync();
        syncTimer = SYNC_RATE;
    }
    else
        syncTimer--;
}

__declspec(dllexport) ModInfo SADXModInfo = {ModLoaderVer}; // This is needed for the Mod Loader to recognize the DLL.
}

#define ReplacePNG_Common(a) do { \
_snprintf_s(pathbuf, LengthOfArray(pathbuf), "%s\\textures\\pvr_common\\index.txt", path); \
helperFunctions.ReplaceFile("system\\" a ".PVR", pathbuf); \
} while (0)

void ReplaceEmblemImage(const char* path, const HelperFunctions& helperFunctions)
{
    char pathbuf[MAX_PATH];
    ReplacePNG_Common("HYOJI_EMBLEM0");
    ReplacePNG_Common("HYOJI_EMBLEM1");
}
