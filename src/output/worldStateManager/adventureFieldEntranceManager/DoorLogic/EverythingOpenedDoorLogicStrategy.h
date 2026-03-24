#include "IDoorLogicStrategy.h"

class EverythingOpenedDoorLogicStrategy : public IDoorLogicStrategy
{
public:
    EverythingOpenedDoorLogicStrategy(AdventureFieldEntranceMap& adventureFieldEntranceMap) :
        _adventureFieldEntranceMap(adventureFieldEntranceMap)
    {
    }

    DoorState GetDoorState(const EntranceId entranceId) override
    {
        const auto oppositeEntrance = _adventureFieldEntranceMap.GetReplacementConnection(entranceId);

        auto entrance = _adventureFieldEntranceMap.FindEntranceById(oppositeEntrance);
        if (entrance == nullptr)
            return DoorLocked;
        if (_adventureFieldEntranceMap.CalculateCorrectAct(entrance->levelAndActId) == LevelAndActIDs_HedgehogHammer)
            return DoorBlocked;
        return DoorOpen;
    }

private:
    AdventureFieldEntranceMap& _adventureFieldEntranceMap;
};
