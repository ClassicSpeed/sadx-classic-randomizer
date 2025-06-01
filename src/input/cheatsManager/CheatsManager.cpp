#include "CheatsManager.h"


CheatsManager::CheatsManager(Settings& settings): _settings(settings)
{
    _giveLivesHook.Hook(OnGiveLives);

    
    //Auto Skip All Cutscenes by MainMemory
    if (_settings.autoSkipCutscenes)
        WriteData<2>((void*)0x00431521, 0x90);
    
    //"Can Always Skip Credits"
    if (_settings.skipCredits)
        WriteData<2>((void*)0x00641232, 0x90);
    
    //Remove unlock message for minigames
    WriteData<1>((char*)0x004B5800, 0xC3u);
}


void CheatsManager::OnGiveLives(const std::int16_t lives)
{
    if (lives == -1 && GameState == MD_GAME_FADEOUT_MISS_RESTART && _instance->_settings.noLifeLossOnRestart)
        return;

    _giveLivesHook.Original(lives);
};
