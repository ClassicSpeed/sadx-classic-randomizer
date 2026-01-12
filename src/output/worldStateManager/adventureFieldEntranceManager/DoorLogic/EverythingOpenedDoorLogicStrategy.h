#include "IDoorLogicStrategy.h"

class EverythingOpenedDoorLogicStrategy : public IDoorLogicStrategy
{
public:
    EverythingOpenedDoorLogicStrategy()
    {
    }

    bool IsDoorOpen(const EntranceId entranceId) override
    {
        return true;
    }

    bool ShowDisableDoorIndicator(EntranceId entranceId) override
    {
        return !IsDoorOpen(entranceId);
    }
};
