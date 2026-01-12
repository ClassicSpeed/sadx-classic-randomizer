#include "IDoorLogicStrategy.h"

class EverythingClosedDoorLogicStrategy : public IDoorLogicStrategy
{
public:
    EverythingClosedDoorLogicStrategy()
    {
    }

    bool IsDoorOpen(const EntranceId entranceId) override
    {
        return false;
    }

    bool ShowDisableDoorIndicator(EntranceId entranceId) override
    {
        return !IsDoorOpen(entranceId);
    }
};
