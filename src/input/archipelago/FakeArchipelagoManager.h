#pragma once
#include "../../application/Randomizer.h"

class FakeArchipelagoManager
{
public:
    explicit FakeArchipelagoManager(Randomizer& randomizer)
        : _randomizer(randomizer)
    {
    }

    void OnPlayingFrame() const;
    
private:
    Randomizer& _randomizer;
    
};
