#include "CheatsManager.h"

bool test = false;

void CheatsManager::OnPlayingFrame() const
{
    if (!_winButtonEnabled)
        return;

    for (const auto& button : PressedButtons)

        if (button & WhistleButtons && Current_CharObj2 != nullptr)
        {
            // DataPointer(int, slSeqRunning, 0x90A0A8); // Story running if 1
            // DataPointer(short, ssSceneNo, 0x3B18A24); // Story ID
            // DataArray(SEQUENCE, seqTable, 0x03B183A8, 8); // Character story data array
            // DataPointer(SEQUENCE*, pCurSequence, 0x3B0EF4C); // Current character story data
            // DataPointer(SEQ_SECTIONTBL*, pCurSectionList, 0x3B18A08); // Character story sections array
            // DataPointer(SEQ_SECTION*, pCurSection, 0x3B18DB0); // Current story section
            // DataArray(char, seqVars, 0x3B18808, 512); // Story flags

            PrintDebug("r?: %d, sn: %d, s: %d, cs: %d, cssa: %d , css: %d\n",slSeqRunning,  ssSceneNo, seqTable.size(), pCurSequence->sec,
                       pCurSectionList->entrance);

            //TODO: CHECK 03C4E468	4 Bytes	Pointer to first object in object list
            // Insta win 
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
