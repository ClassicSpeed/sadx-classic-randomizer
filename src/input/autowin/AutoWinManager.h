#pragma once
#include "../../application/Randomizer.h"

class AutoWinManager
{
public:
    explicit AutoWinManager(Randomizer& randomizer)
        : _randomizer(randomizer)
    {
    }

    void OnPlayingFrame() const;
    
private:
    Randomizer& _randomizer;
    
};
