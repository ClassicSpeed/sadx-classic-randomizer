#pragma once
#include <map>
#include "../../application/structs/LocationData.h"


class LocationRepository
{
public:
    LocationRepository();
    LocationData SetLocationChecked(int checkId);
    LocationData GetLocation(int checkId);
    std::map<int, LocationData> GetLocations();
    std::vector<LifeBoxLocationData> GetLifeCapsules();

private:
    std::string GetLocationName(Characters character, LevelIDs levelId, int mission);
    LocationData GetLocationFromUpgrade(EventFlags eventFlags, const char* str, int i);
    LocationData GetLocationFromLevel(Characters character, LevelIDs levelId, int mission);
    LocationData GetLocationFromSubLevel(EventFlags eventFlags, const char* str, int i);
    LocationData GetLocationFromFieldEmblem(EventFlags eventFlags, const char* str, int i);
    LocationData GetLocationFromEvent(EventFlags eventFlags, const char* str, int i);
    std::map<int, LocationData> _checkData;
    std::vector<LifeBoxLocationData> _lifeCapsules;
};
