#pragma once
#include "../../application/Randomizer.h"

class CheatsManager
{
public:
    static CheatsManager& Init()
    {
        if (_instance == nullptr)
            _instance = new CheatsManager();
        return *_instance;
    }

    void SetCheatsConfiguration(bool autoSkipCutscenes, bool skipCredits, bool newNoLifeLossOnRestart);
    bool noLifeLossOnRestart = true;
    
private:
    explicit CheatsManager();
    inline static CheatsManager* _instance = nullptr;

    inline static FunctionHook<void, std::int16_t> _giveLivesHook{0x425B60};
    static void OnGiveLives(std::int16_t lives);
};
