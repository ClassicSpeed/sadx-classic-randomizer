#pragma once
#include "../AdventureFieldEntranceMap.h"
#include "../src/configuration/gameStatus/GameStatus.h"
#include "../src/configuration/options/Options.h"


enum DoorState
{
    DoorLocked = 0, // Door is locked by emblems or key items, but can be unlocked by the player
    DoorBlocked, // Door is blocked and can't be used by the current character
    DoorOpen, // Door is open
    DoorUnlocked // Door is open but used to be locked
};

class IDoorLogicStrategy
{
public:
    virtual ~IDoorLogicStrategy() = default;
    virtual DoorState GetDoorState(EntranceId entranceId) = 0;
};
