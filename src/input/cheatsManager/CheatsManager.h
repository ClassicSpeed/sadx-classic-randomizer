#pragma once
#include "../../application/Randomizer.h"

class CheatsManager
{
public:
    explicit CheatsManager(Randomizer& randomizer);

    void SetCheatsConfiguration(bool autoSkipCutscenes, bool skipCredits, bool noLifeLossOnRestart);
    bool noLifeLossOnRestart = true;
    
private:
    Randomizer& _randomizer;
};
