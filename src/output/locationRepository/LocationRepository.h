#pragma once
#include <map>
#include "../../application/structs/LocationData.h"
#include "../../application/structs/Options.h"
#include "../../application/structs/LevelStatus.h"
#include "../../application/structs/MissionStatus.h"
#include "../../application/structs/BossesStatus.h"



class LocationRepository
{
public:
    LocationRepository();
    LocationData SetLocationChecked(int checkId);
    LocationData GetLocation(int checkId);
    std::map<int, LocationData> GetLocations();
    std::vector<LifeBoxLocationData> GetLifeCapsules();
    LevelStatus GetLevelStatus(Options options);
    MissionStatus GetMissionStatus(Options options);
    BossesStatus GetBossesStatus(const Options& options);

private:
    std::map<int, LocationData> _checkData;
    std::vector<LifeBoxLocationData> _lifeCapsules;
};
