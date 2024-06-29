#pragma once
#include "../../../application/Randomizer.h"

class ItemReceiver
{
public:
    explicit ItemReceiver(Randomizer& randomizer)
        : _randomizer(randomizer)
    {
    }

    void OnPlayingFrame() const;
    
private:
    Randomizer& _randomizer;
    
};
