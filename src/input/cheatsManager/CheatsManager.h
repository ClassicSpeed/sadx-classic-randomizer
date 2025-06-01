#pragma once
#include "../../application/Randomizer.h"

class CheatsManager
{
public:
    static CheatsManager& Init(Settings& settings)
    {
        if (_instance == nullptr)
            _instance = new CheatsManager(settings);
        return *_instance;
    }

    
private:
    explicit CheatsManager(Settings& settings);
    Settings& _settings;
    inline static CheatsManager* _instance = nullptr;

    inline static FunctionHook<void, std::int16_t> _giveLivesHook{0x425B60};
    static void OnGiveLives(std::int16_t lives);
};
