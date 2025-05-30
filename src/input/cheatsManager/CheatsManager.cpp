#include "CheatsManager.h"


CheatsManager::CheatsManager()
{
    _giveLivesHook.Hook(OnGiveLives);
}


void CheatsManager::SetCheatsConfiguration(const bool autoSkipCutscenes, const bool skipCredits, const bool newNoLifeLossOnRestart)
{
    this->noLifeLossOnRestart = newNoLifeLossOnRestart;
    
    //Auto Skip All Cutscenes by MainMemory
    if (autoSkipCutscenes)
        WriteData<2>((void*)0x00431521, 0x90);
    
    //"Can Always Skip Credits"
    if (skipCredits)
        WriteData<2>((void*)0x00641232, 0x90);
    
    //Remove unlock message for minigames
    WriteData<1>((char*)0x004B5800, 0xC3u);
}

void CheatsManager::OnGiveLives(const std::int16_t lives)
{
    if (lives == -1 && GameState == MD_GAME_FADEOUT_MISS_RESTART && _instance->noLifeLossOnRestart)
        return;

    _giveLivesHook.Original(lives);
};
