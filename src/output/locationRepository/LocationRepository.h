#pragma once
#include <map>
#include "../../application/structs/LocationData.h"
#include "../../application/structs/Options.h"
#include "../../application/structs/LevelStatus.h"



class LocationRepository
{
public:
    LocationRepository();
    LocationData SetLocationChecked(int checkId);
    LocationData GetLocation(int checkId);
    std::map<int, LocationData> GetLocations();
    std::vector<LifeBoxLocationData> GetLifeCapsules();
    bool CompletedAllLevels(Options options);
    LevelStatus GetLevelStatus(Options options);

private:
    std::map<int, LocationData> _checkData;
    std::vector<LifeBoxLocationData> _lifeCapsules;
};
