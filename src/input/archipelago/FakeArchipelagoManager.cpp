#include "FakeArchipelagoManager.h"
#include "SADXModLoader.h"

void FakeArchipelagoManager::OnPlayingFrame() const
{
    if (PressedButtons.empty())
        return;

    for (const auto& button : PressedButtons)

        if (button & WhistleButtons && Current_CharObj2 != nullptr)
        {
            //Insta win item
            // if (CurrentLevel < LevelIDs_StationSquare || CurrentLevel == LevelIDs_SandHill)
            // {
            //     SetTailsRaceVictory();
            //     LoadLevelResults();
            // }
            //Receive item
            _randomizer.OnItemReceived(1);
        }
}
