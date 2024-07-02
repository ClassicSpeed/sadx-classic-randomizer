
#include "SADXModLoader.h"
#include "application/Randomizer.h"
#include "input/archipelago/ArchipelagoManager.h"
#include "input/archipelago/FakeArchipelagoManager.h"
#include "input/eventDetector/EventDetector.h"
#include "input/characterLoading/CharacterLoadingDetector.h"
#include "output/archipelagoMessenger/ArchipelagoMessenger.h"
#include "output/locationRepository/LocationRepository.h"

extern "C" {
DisplayManager displayManager = DisplayManager();
UpgradeManager upgradeManager = UpgradeManager();
CharacterSelectionManager characterSelectionManager = CharacterSelectionManager();
ItemRepository itemRepository = ItemRepository();
LocationRepository checkRepository = LocationRepository();
ArchipelagoMessenger archipelagoMessenger = ArchipelagoMessenger();
    
Randomizer randomizer = Randomizer(displayManager,
                                   upgradeManager,
                                   characterSelectionManager,
                                   itemRepository,
                                   checkRepository,
                                   archipelagoMessenger);
    
FakeArchipelagoManager fakeArchipelagoManager = FakeArchipelagoManager(randomizer);
ArchipelagoManager archipelagoManager = ArchipelagoManager(randomizer);
EventDetector eventDetector = EventDetector(randomizer);
CharacterLoadingDetector characterLoadingDetector = CharacterLoadingDetector(randomizer);


__declspec(dllexport) void __cdecl OnFrame()
{
    archipelagoManager.OnFrame();
    displayManager.OnFrame();
    if (Current_CharObj2 != nullptr)
    {
        eventDetector.OnPlayingFrame();
        fakeArchipelagoManager.OnPlayingFrame();
        characterLoadingDetector.OnPlayingFrame();
    }
}



__declspec(dllexport) ModInfo SADXModInfo = {ModLoaderVer}; // This is needed for the Mod Loader to recognize the DLL.
}
