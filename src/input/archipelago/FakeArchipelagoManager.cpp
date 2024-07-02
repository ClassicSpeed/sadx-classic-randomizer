#include "FakeArchipelagoManager.h"
#include "SADXModLoader.h"

bool test = false;

void FakeArchipelagoManager::OnPlayingFrame() const
{
    if (PressedButtons.empty())
        return;

    for (const auto& button : PressedButtons)

        if (button & WhistleButtons && Current_CharObj2 != nullptr)
        {
            //Insta win 
            if (CurrentLevel < LevelIDs_StationSquare || CurrentLevel == LevelIDs_SandHill)
            {
                SetTailsRaceVictory();
                LoadLevelResults();
            }
            // //Receive item
            // if (test)
            // {
            //     _randomizer.OnItemReceived(1);
            //     test = false;
            // }
            // else
            // {
            //     _randomizer.OnItemReceived(3);
            //     test = true;
            // }
        }
}
