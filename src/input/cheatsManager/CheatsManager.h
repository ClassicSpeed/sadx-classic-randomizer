#pragma once
#include "../../application/Randomizer.h"

class CheatsManager
{
public:
    explicit CheatsManager(Randomizer& randomizer)
        : _randomizer(randomizer)
    {
    }

    void OnPlayingFrame() const;
    void SetCheatsConfiguration(bool autoSkipCutscenes, bool skipCredits, bool winButtonEnabled);

private:
    Randomizer& _randomizer;
    bool _winButtonEnabled = false;
};
