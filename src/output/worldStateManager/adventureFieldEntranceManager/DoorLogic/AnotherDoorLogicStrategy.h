#include "IDoorLogicStrategy.h"

class AnotherDoorLogicStrategy : public IDoorLogicStrategy
{
public:
    bool IsDoorOpen(EntranceId entranceId) override
    {
        // Example logic
        return entranceId % 3 != 0;
    }

    bool ShowDisableDoorIndicator(EntranceId entranceId) override
    {
        return !IsDoorOpen(entranceId);
    }
};
