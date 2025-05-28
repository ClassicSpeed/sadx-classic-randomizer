#pragma once
#include <map>
#include "../../application/structs/LocationData.h"
#include "../../configuration/Options.h"
#include "../../application/structs/LevelStatus.h"
#include "../../application/structs/MissionStatus.h"
#include "../../application/structs/BossesStatus.h"
#include "../../application/structs/ChaoStatus.h"



class LocationRepository
{
public:
    LocationRepository();
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
    std::map<int, LocationData> _checkData;
    std::vector<EnemyLocationData> _enemies;
    std::vector<CapsuleLocationData> _capsules;
};
