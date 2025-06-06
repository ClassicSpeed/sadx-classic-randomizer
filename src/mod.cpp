#include "pch.h"

#include "application/randomizer/Randomizer.h"
#include "configuration/gameStatus/GameStatus.h"
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
    Settings& settings = Settings::Init(path, helperFunctions);
    Options& options = Options::Init(settings);
    GameStatus& gameStatus = GameStatus::Init();
    ReactionManager& reactionManager = ReactionManager::Init(settings, gameStatus);
    DisplayManager& displayManager = DisplayManager::Init(options, settings, gameStatus, path, helperFunctions);
    CharacterManager& characterManager = CharacterManager::Init(options, settings,gameStatus, reactionManager);
    WorldStateManager& worldStateManager = WorldStateManager::Init(options, settings, gameStatus);
    ItemRepository& itemRepository = ItemRepository::Init(gameStatus);
    LocationRepository& locationRepository = LocationRepository::Init(options, gameStatus);
    ArchipelagoMessenger& archipelagoMessenger = ArchipelagoMessenger::Init(options);
    SaveFileManager& saveFileManager = SaveFileManager::Init();
    MusicManager& musicManager = MusicManager::Init(options, settings, helperFunctions);

    Randomizer& randomizer = Randomizer::Init(options, settings, gameStatus, displayManager, characterManager,
                                              worldStateManager, itemRepository, locationRepository,
                                              archipelagoMessenger, saveFileManager, musicManager, reactionManager);

    CheatsManager& cheatsManager = CheatsManager::Init(settings);
    ArchipelagoManager& archipelagoManager = ArchipelagoManager::Init(options, settings, randomizer);
    EventDetector& eventDetector = EventDetector::Init(options, settings, randomizer);
    CharacterLoadingDetector& characterLoadingDetector = CharacterLoadingDetector::Init(randomizer);

    onFrameObjects = {
        &saveFileManager, &archipelagoManager, &displayManager, &worldStateManager,
        &eventDetector, &characterLoadingDetector, &randomizer, &characterManager
    };
}

__declspec(dllexport) void __cdecl OnFrame()
{
    for (const auto manager : onFrameObjects)
        manager->OnFrame();
}

// Required for Mod Loader to recognize the DLL
__declspec(dllexport) ModInfo SADXModInfo = {ModLoaderVer};
}
