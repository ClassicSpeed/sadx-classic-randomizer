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

private:
    std::string GetLocationName(Characters character, LevelIDs levelId, int mission);
    LocationData GetLocationFromLevel(Characters character, LevelIDs levelId, int mission);
    LocationData GetLocationFromCharacter(EventFlags eventFlags, const char* str, int i);
    LocationData GetLocationFromUpgrade(EventFlags eventFlags, const char* str, int i);
    std::map<int, LocationData> _checkData;
    std::unordered_map<int, std::string> _charactersMap;
    std::unordered_map<int, std::string> _levelsMap;
};
