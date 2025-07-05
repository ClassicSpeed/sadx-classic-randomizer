#include "pch.h"

#include "application/randomizer/Randomizer.h"
#include "application/link/Link.h"
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
    //Configuration
    Settings& settings = Settings::Init(path, helperFunctions);
    Options& options = Options::Init(settings);
    GameStatus& gameStatus = GameStatus::Init(options);

    // Output Managers
    ReactionManager& reactionManager = ReactionManager::Init(settings, gameStatus);
    DisplayManager& displayManager = DisplayManager::Init(options, settings, gameStatus, path, helperFunctions);
    CharacterManager& characterManager = CharacterManager::Init(options, settings, gameStatus, reactionManager);
    WorldStateManager& worldStateManager = WorldStateManager::Init(options, settings, gameStatus);
    ItemRepository& itemRepository = ItemRepository::Init(gameStatus);
    LocationRepository& locationRepository = LocationRepository::Init(options, gameStatus);
    ArchipelagoMessenger& archipelagoMessenger = ArchipelagoMessenger::Init(options);
    SaveFileManager& saveFileManager = SaveFileManager::Init();
    MusicManager& musicManager = MusicManager::Init(options, settings, helperFunctions);

    //Randomizer
    Randomizer& randomizer = Randomizer::Init(options, settings, gameStatus, displayManager, characterManager,
                                              worldStateManager, itemRepository, locationRepository,
                                              archipelagoMessenger, saveFileManager, musicManager, reactionManager);
    Link& link = Link::Init(options, settings, displayManager, characterManager, itemRepository, archipelagoMessenger);

    // Input Handlers
    CheatsManager& cheatsManager = CheatsManager::Init(settings);
    ArchipelagoManager& archipelagoManager = ArchipelagoManager::Init(options, settings, randomizer, link);
    EventDetector& eventDetector = EventDetector::Init(options, settings, randomizer, link);
    CharacterLoadingDetector& characterLoadingDetector = CharacterLoadingDetector::Init(randomizer);

    onFrameObjects = {
        &saveFileManager, &archipelagoManager, &displayManager, &worldStateManager,
        &eventDetector, &characterLoadingDetector, &link, &characterManager
    };
    // TODO: Remove later
    options.bossChecks = true;
    gameStatus.unlock.keyTrain = true;
    gameStatus.unlock.keyBoat = true;
    gameStatus.unlock.keyRaft = true;
    gameStatus.unlock.keyStationFrontKey = true;
    gameStatus.unlock.keyStationBackKey = true;
    gameStatus.unlock.keyHotelFrontKey = true;
    gameStatus.unlock.keyHotelBackKey = true;
    gameStatus.unlock.keyTwinkleParkTicket = true;
    gameStatus.unlock.keyEmployeeCard = true;
    gameStatus.unlock.keyDynamite = true;
    gameStatus.unlock.keyIceStone = true;
    gameStatus.unlock.keyWindStone = true;
    gameStatus.unlock.keyJungleCart = true;
    gameStatus.unlock.keyEgglift = true;
    gameStatus.unlock.keyMonorail = true;
}

__declspec(dllexport) void __cdecl OnFrame()
{
    for (const auto manager : onFrameObjects)
        manager->OnFrame();
}

// Required for Mod Loader to recognize the DLL
__declspec(dllexport) ModInfo SADXModInfo = {ModLoaderVer};
}
