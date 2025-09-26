#include "IDoorLogicStrategy.h"

class AnotherDoorLogicStrategy : public IDoorLogicStrategy
{
public:
    AnotherDoorLogicStrategy(Options& options, GameStatus& gameStatus)
        : _options(options),
          _gameStatus(gameStatus)
    {
    }

    bool IsDoorOpen(const EntranceId entranceId) override
    {
        const auto entranceValue = _options.entranceEmblemValueMap.find(entranceId);
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
};
