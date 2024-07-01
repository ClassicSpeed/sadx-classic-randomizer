#pragma once
#include "../../application/Randomizer.h"

class ArchipelagoManager
{
public:
    explicit ArchipelagoManager(Randomizer& randomizer)
        : _randomizer(randomizer)
    {
    }

    void Connect() const;
    void OnFrame() const;

private:
    Randomizer& _randomizer;

    bool _connected;
};
