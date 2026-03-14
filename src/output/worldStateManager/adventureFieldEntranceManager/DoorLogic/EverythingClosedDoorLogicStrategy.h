#include "IDoorLogicStrategy.h"

class EverythingClosedDoorLogicStrategy : public IDoorLogicStrategy
{
public:
    EverythingClosedDoorLogicStrategy()
    {
    }

    DoorState GetDoorState(const EntranceId entranceId) override
    {
        return DoorBlocked;
    }
};
