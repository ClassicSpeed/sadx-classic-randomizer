#pragma once
#include "../../application/Randomizer.h"

class CheatsManager
{
public:
    explicit CheatsManager(Randomizer& randomizer)
        : _randomizer(randomizer)
    {
        
    }

    void SetCheatsConfiguration(bool autoSkipCutscenes, bool skipCredits);

private:
    Randomizer& _randomizer;
};
