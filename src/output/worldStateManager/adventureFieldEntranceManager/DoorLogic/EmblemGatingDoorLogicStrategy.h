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
        const auto oppositeEntrance = _adventureFieldEntranceMap.GetReplacementConnection(entranceId, false);

        if (entranceValue == _options.entranceEmblemValueMap.end())
            entranceValue = _options.entranceEmblemValueMap.find(oppositeEntrance);

        //Check if door leads to level for the player
        auto entrance = _adventureFieldEntranceMap.FindEntranceById(oppositeEntrance);

        //Static entrance
        if (entrance == nullptr)
            return _gameStatus.unlock.currentEmblems >= entranceValue->second;
        // Is level for character
        if (_adventureFieldEntranceMap.CalculateCorrectAct(entrance->levelAndActId) == LevelAndActIDs_HedgehogHammer)
            return false;

        // We prevent characters from using wrong entrances
        if (_options.entranceRandomizer == 0)
        {
            if (entranceId == SsMainToSpeedHighway)
                if (CurrentCharacter == Characters_Knuckles)
                    return false;
            if (entranceId == CityHallToSpeedHighway)
                if (CurrentCharacter != Characters_Knuckles)
                    return false;
            if (entranceId == JungleToLostWorld)
                if (CurrentCharacter == Characters_Knuckles)
                    return false;
            if (entranceId == JungleToLostWorldAlternative)
                if (CurrentCharacter != Characters_Knuckles)
                    return false;
            if (entranceId == FinalEggTowerToFinalEgg)
                if (CurrentCharacter == Characters_Gamma)
                    return false;
            if (entranceId == FinalEggTowerToFinalEggAlternative)
                if (CurrentCharacter != Characters_Gamma)
                    return false;
            if (entranceId == BridgeToSkyDeck)
                if (CurrentCharacter == Characters_Knuckles)
                    return false;
            if (entranceId == PoolToSkyDeck)
                if (CurrentCharacter != Characters_Knuckles)
                    return false;
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
