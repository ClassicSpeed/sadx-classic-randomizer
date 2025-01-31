#include "CheatsManager.h"

CheatsManager* cheatsManagerPtr;


CheatsManager::CheatsManager(Randomizer& randomizer) : _randomizer(randomizer)
{
    cheatsManagerPtr = this;
}


void CheatsManager::SetCheatsConfiguration(const bool autoSkipCutscenes, const bool skipCredits, const bool noLifeLossOnRestart)
{
    this->noLifeLossOnRestart = noLifeLossOnRestart;
    
    //Auto Skip All Cutscenes by MainMemory
    if (autoSkipCutscenes)
        WriteData<2>((void*)0x00431521, 0x90);
    
    //"Can Always Skip Credits"
    if (skipCredits)
        WriteData<2>((void*)0x00641232, 0x90);
    
    //Remove unlock message for minigames
    WriteData<1>((char*)0x004B5800, 0xC3u);
}

FunctionHook<void, std::int16_t> onGiveLives(0x425B60, [](const std::int16_t lives)-> void
{
    if (lives == -1 && GameState == MD_GAME_FADEOUT_MISS_RESTART && cheatsManagerPtr->noLifeLossOnRestart)
        return;

    onGiveLives.Original(lives);
});
