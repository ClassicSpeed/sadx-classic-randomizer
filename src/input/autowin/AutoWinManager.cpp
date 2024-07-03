#include "AutoWinManager.h"
#include "../../pch.h"

bool test = false;

void AutoWinManager::OnPlayingFrame() const
{
    for (const auto& button : PressedButtons)

        if (button & WhistleButtons && Current_CharObj2 != nullptr)
        {
            //Insta win 
            if (CurrentLevel < LevelIDs_StationSquare || CurrentLevel == LevelIDs_SandHill)
            {
                SetTailsRaceVictory();
                LoadLevelResults();
            }
        }
}
