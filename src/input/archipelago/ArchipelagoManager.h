#pragma once
#include "../../application/Randomizer.h"

class ArchipelagoManager
{
public:
    explicit ArchipelagoManager(Randomizer& randomizer);

    void Connect();
    void OnFrame();

private:
    Randomizer& _randomizer;

    bool _connected;
};
