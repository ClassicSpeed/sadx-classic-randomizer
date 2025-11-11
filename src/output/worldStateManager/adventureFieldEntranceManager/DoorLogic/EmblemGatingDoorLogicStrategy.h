#include "IDoorLogicStrategy.h"

class EmblemGatingDoorLogicStrategy : public IDoorLogicStrategy
{
public:
    EmblemGatingDoorLogicStrategy(Options& options, GameStatus& gameStatus,
                                  AdventureFieldEntranceMap& adventureFieldEntranceMap)
        : _options(options),
          _gameStatus(gameStatus), _adventureFieldEntranceMap(adventureFieldEntranceMap)
    {
    }

    bool IsDoorOpen(const EntranceId entranceId) override
    {
        auto entranceValue = _options.entranceEmblemValueMap.find(entranceId);
        //TODO: Check EC transformation
        const auto oppositeEntrance = _adventureFieldEntranceMap.GetReplacementConnection(entranceId, false);

        if (entranceValue == _options.entranceEmblemValueMap.end())
            entranceValue = _options.entranceEmblemValueMap.find(oppositeEntrance);

        //Check if door leads to level for the player
        auto entrance = _adventureFieldEntranceMap.FindEntranceById(oppositeEntrance);
        if (entrance == nullptr)
            return true;
        if (_adventureFieldEntranceMap.CalculateCorrectAct(entrance->levelAndActId) == LevelAndActIDs_HedgehogHammer)
            return false;

        if (entranceValue != _options.entranceEmblemValueMap.end())
            return _gameStatus.unlock.currentEmblems >= entranceValue->second;

        return true;
    }

    bool ShowDisableDoorIndicator(EntranceId entranceId) override
    {
        return !IsDoorOpen(entranceId);
    }

private:
    Options& _options;
    GameStatus& _gameStatus;
    AdventureFieldEntranceMap& _adventureFieldEntranceMap;
};
