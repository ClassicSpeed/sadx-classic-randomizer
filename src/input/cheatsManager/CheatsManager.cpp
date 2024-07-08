#include "CheatsManager.h"

bool test = false;

void CheatsManager::OnPlayingFrame() const
{
    if (!_winButtonEnabled)
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
        }
}

void CheatsManager::SetCheatsConfiguration(bool autoSkipCutscenes, bool skipCredits, bool winButtonEnabled)
{
    //Auto Skip All Cutscenes by MainMemory
    if (autoSkipCutscenes)
        WriteData<2>((void*)0x00431521, 0x90);
    //"Can Always Skip Credits"
    if (skipCredits)
        WriteData<2>((void*)0x00641232, 0x90);
    _winButtonEnabled = winButtonEnabled;
}
