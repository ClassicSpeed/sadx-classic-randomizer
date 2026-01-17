#include "IDoorLogicStrategy.h"

class EverythingOpenedDoorLogicStrategy : public IDoorLogicStrategy
{
public:
    EverythingOpenedDoorLogicStrategy(AdventureFieldEntranceMap& adventureFieldEntranceMap) :
        _adventureFieldEntranceMap(adventureFieldEntranceMap)
    {
    }

    bool IsDoorOpen(const EntranceId entranceId) override
    {
        const auto oppositeEntrance = _adventureFieldEntranceMap.GetReplacementConnection(entranceId, false);

        auto entrance = _adventureFieldEntranceMap.FindEntranceById(oppositeEntrance);
        if (_adventureFieldEntranceMap.CalculateCorrectAct(entrance->levelAndActId) == LevelAndActIDs_HedgehogHammer)
            return false;
        return true;
    }

    bool ShowDisableDoorIndicator(EntranceId entranceId) override
    {
        return !IsDoorOpen(entranceId);
    }

private:
    AdventureFieldEntranceMap& _adventureFieldEntranceMap;
};
