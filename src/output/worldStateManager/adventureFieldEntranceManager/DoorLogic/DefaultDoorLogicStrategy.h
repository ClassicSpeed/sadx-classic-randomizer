#include "IDoorLogicStrategy.h"

class DefaultDoorLogicStrategy : public IDoorLogicStrategy
{
public:
    bool IsDoorOpen(EntranceId entranceId) override
    {
        return true;
    }

    bool ShowDisableDoorIndicator(EntranceId entranceId) override
    {
        return !IsDoorOpen(entranceId);
    }
};

//TODO: Implement normal gameplay with key items
//TODO: Implement normal gameplay with emblems
//TODO: Implement random gameplay with emblems
