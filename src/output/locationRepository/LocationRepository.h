#pragma once
#include <map>
#include "../../application/structs/LocationData.h"
#include "../../configuration/options/Options.h"
#include "../../application/structs/LevelStatus.h"
#include "../../application/structs/MissionStatus.h"
#include "../../application/structs/BossesStatus.h"
#include "../../application/structs/ChaoStatus.h"



class LocationRepository
{
public:
    static LocationRepository& Init()
    {
        if (_instance == nullptr)
            _instance = new LocationRepository();
        return *_instance;
    }
    LocationData SetLocationChecked(int checkId);
    LocationData GetLocation(int checkId);
    std::map<int, LocationData> GetLocations();
    std::vector<CapsuleLocationData> GetCapsuleLocations();
    std::vector<EnemyLocationData> GetEnemyLocations();
    LevelStatus GetLevelStatus(Options options);
    MissionStatus GetMissionStatus(Options options);
    BossesStatus GetBossesStatus(const Options& options);
    ChaoStatus GetChaoStatus();

private:
    LocationRepository();
    inline static LocationRepository* _instance = nullptr;
    std::map<int, LocationData> _checkData;
    std::vector<EnemyLocationData> _enemies;
    std::vector<CapsuleLocationData> _capsules;
};
