#include <pch.h>
#include "settings/Settings.h"
#include "options/Options.h"
#include "gameStatus/GameStatus.h"
#include "output/reactionManager/ReactionManager.h"
#include "output/displayManager/DisplayManager.h"

extern "C" {
__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
{
    
    //Configuration

    Settings& settings = Settings::Init(path, helperFunctions);
    Options& options = Options::Init(settings);
    GameStatus& gameStatus = GameStatus::Init(options);


    // Output Managers
    ReactionManager& reactionManager = ReactionManager::Init(settings, gameStatus);
    DisplayManager& displayManager = DisplayManager::Init(options, settings, gameStatus, path, helperFunctions);
    // CharacterManager& characterManager = CharacterManager::Init(options, settings, gameStatus, reactionManager);
    // ItemRepository& itemRepository = ItemRepository::Init(gameStatus);
    // LocationRepository& locationRepository = LocationRepository::Init(options, gameStatus);
    // ArchipelagoMessenger& archipelagoMessenger = ArchipelagoMessenger::Init(options, gameStatus);
    // WorldStateManager& worldStateManager = WorldStateManager::Init(options, settings, gameStatus, archipelagoMessenger);
    // SaveFileManager& saveFileManager = SaveFileManager::Init();
    // MusicManager& musicManager = MusicManager::Init(options, settings, helperFunctions);
}

// Simple OnFrame test
__declspec(dllexport) void __cdecl OnFrame()
{
    Rings = 12345;
    DisplayDebugString(NJM_LOCATION(2, 1), "Testing");
}

__declspec(dllexport) ModInfo SADXModInfo = {ModLoaderVer};
}
