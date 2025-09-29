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
        if (entranceValue == _options.entranceEmblemValueMap.end())
        {
            //TODO: Check EC transformation
            const auto oppositeEntrance = _adventureFieldEntranceMap.GetReplacementConnection(entranceId, false);
            entranceValue = _options.entranceEmblemValueMap.find(oppositeEntrance);
        }

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
