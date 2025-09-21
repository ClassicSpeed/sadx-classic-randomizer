#pragma once
#include "../AdventureFieldEntranceMap.h"
#include "../../../configuration/gameStatus/GameStatus.h"
#include "../../../configuration/options/Options.h"
#include "../../../configuration/settings/Settings.h"

class IDoorLogicStrategy
{
public:
    virtual ~IDoorLogicStrategy() = default;
    virtual bool IsDoorOpen(EntranceId entranceId) = 0;
    virtual bool ShowDisableDoorIndicator(EntranceId entranceId) = 0;
};
