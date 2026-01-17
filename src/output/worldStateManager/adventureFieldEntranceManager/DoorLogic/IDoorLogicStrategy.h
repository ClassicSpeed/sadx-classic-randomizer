#pragma once
#include "../AdventureFieldEntranceMap.h"
#include "../src/configuration/gameStatus/GameStatus.h"
#include "../src/configuration/options/Options.h"

class IDoorLogicStrategy
{
public:
    virtual ~IDoorLogicStrategy() = default;
    virtual bool IsDoorOpen(EntranceId entranceId) = 0;
    virtual bool ShowDisableDoorIndicator(EntranceId entranceId) = 0;
};
