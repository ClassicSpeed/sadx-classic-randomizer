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

    DoorState GetDoorState(const EntranceId entranceId) override
    {
        if (entranceId == InvalidEntranceId)
            return DoorBlocked;
        const auto oppositeEntrance = _adventureFieldEntranceMap.GetReplacementConnection(entranceId);

        const int entranceValue = _options.GetEntranceEmblemValue(entranceId, oppositeEntrance);

        //Check if door leads to level for the player
        auto entrance = _adventureFieldEntranceMap.FindEntranceById(oppositeEntrance);
        //Static entrance
        if (entrance == nullptr)
            return _gameStatus.unlock.currentEmblems >= entranceValue ? DoorUnlocked : DoorBlocked;
        // Is level for character
        if (_adventureFieldEntranceMap.CalculateCorrectAct(entrance->levelAndActId) == LevelAndActIDs_HedgehogHammer)
            return DoorBlocked;

        // We prevent characters from using wrong entrances
        if (_options.entranceRandomizer == 0)
        {
            if (entranceId == SsMainToSpeedHighway)
                if (CurrentCharacter == Characters_Knuckles)
                    return DoorBlocked;
            if (entranceId == CityHallToSpeedHighway)
                if (CurrentCharacter != Characters_Knuckles)
                    return DoorBlocked;
            if (entranceId == JungleToLostWorld)
                if (CurrentCharacter == Characters_Knuckles)
                    return DoorBlocked;
            if (entranceId == JungleToLostWorldAlternative)
                if (CurrentCharacter != Characters_Knuckles)
                    return DoorBlocked;
            if (entranceId == FinalEggTowerToFinalEgg)
                if (CurrentCharacter == Characters_Gamma)
                    return DoorBlocked;
            if (entranceId == FinalEggTowerToFinalEggAlternative)
                if (CurrentCharacter != Characters_Gamma)
                    return DoorBlocked;
            if (entranceId == BridgeToSkyDeck)
                if (CurrentCharacter == Characters_Knuckles)
                    return DoorBlocked;
            if (entranceId == PoolToSkyDeck)
                if (CurrentCharacter != Characters_Knuckles)
                    return DoorBlocked;
        }


        if (entranceValue <= 0)
            return DoorOpen;

        return _gameStatus.unlock.currentEmblems >= entranceValue ? DoorUnlocked : DoorLocked;
    }

private:
    Options& _options;
    GameStatus& _gameStatus;
    AdventureFieldEntranceMap& _adventureFieldEntranceMap;
};
