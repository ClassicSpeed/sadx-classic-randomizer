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


extern "C" {
std::vector<IOnFrame*> onFrameObjects;

__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
{
    Settings* settings = &Settings::Init(path, helperFunctions);
    Options* options = &Options::Init(*settings);
    ReactionManager* reactionManager = &ReactionManager::Init(*options, *settings);
    DisplayManager* displayManager = &DisplayManager::Init(*options, *settings, path, helperFunctions);
    CharacterManager* characterManager = &CharacterManager::Init(*options, *settings, *reactionManager);
    WorldStateManager* worldStateManager = &WorldStateManager::Init(*options, *settings);
    ItemRepository* itemRepository = &ItemRepository::Init();
    LocationRepository* checkRepository = &LocationRepository::Init();
    ArchipelagoMessenger* archipelagoMessenger = &ArchipelagoMessenger::Init(*options);
    SaveFileManager* saveFileManager = &SaveFileManager::Init();
    MusicManager* musicManager = &MusicManager::Init(*options, *settings, helperFunctions);
    Randomizer* randomizer = &Randomizer::Init(*options, *settings, *displayManager, *characterManager,
                                               *worldStateManager,
                                               *itemRepository,
                                               *checkRepository, *archipelagoMessenger, *saveFileManager, *musicManager,
                                               *reactionManager);
    CheatsManager* cheatsManager = &CheatsManager::Init(*settings);
    ArchipelagoManager* archipelagoManager = &ArchipelagoManager::Init(*options, *settings, *randomizer);
    EventDetector* eventDetector = &EventDetector::Init(*options, *settings, *randomizer);
    CharacterLoadingDetector* characterLoadingDetector = &CharacterLoadingDetector::Init(*randomizer);
    onFrameObjects = {
        saveFileManager, archipelagoManager, displayManager, worldStateManager,
        eventDetector, characterLoadingDetector, randomizer, characterManager
    };
}

__declspec(dllexport) void __cdecl OnFrame()
{
    for (auto* obj : onFrameObjects)
        obj->OnFrame();
}

__declspec(dllexport) ModInfo SADXModInfo = {ModLoaderVer}; // This is needed for the Mod Loader to recognize the DLL.
}
