#include "CheatsManager.h"


void CheatsManager::SetCheatsConfiguration(bool autoSkipCutscenes, bool skipCredits)
{
    //Auto Skip All Cutscenes by MainMemory
    if (autoSkipCutscenes)
        WriteData<2>((void*)0x00431521, 0x90);
    //"Can Always Skip Credits"
    if (skipCredits)
        WriteData<2>((void*)0x00641232, 0x90);
}
