#pragma once
#include <map>
#include "../../configuration/gameStatus/GameStatus.h"
#include "../../application/structs/LocationData.h"
#include "../../configuration/options/Options.h"


class LocationRepository
{
public:
    static LocationRepository& Init(Options& options, GameStatus& gameStatus)
    {
        if (_instance == nullptr)
            _instance = new LocationRepository(options, gameStatus);
        return *_instance;
    }

    LocationData SetLocationChecked(int checkId);
    LocationData GetLocation(int checkId);
    void UpdateStatus();
    std::map<int, LocationData> GetLocations();
    std::vector<CapsuleLocationData> GetCapsuleLocations();
    std::vector<EnemyLocationData> GetEnemyLocations();

private:
    explicit LocationRepository(Options& options, GameStatus& gameStatus);
    inline static LocationRepository* _instance = nullptr;
    Options& _options;
    GameStatus& _gameStatus;
    std::map<int, LocationData> _checkData;
    std::vector<EnemyLocationData> _enemies;
    std::vector<CapsuleLocationData> _capsules;
    void UpdateLevelStatus();
    void UpdateMissionStatus();
    void UpdateBossesStatus();
    void UpdateChaoStatus();
    void UpdateEnemySanity();
    void UpdateCapsuleSanity();
    void UpdateFishSanity();
};
