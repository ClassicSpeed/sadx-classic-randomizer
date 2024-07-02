#pragma once
#include <map>
#include "../../application/structs/LocationData.h"


class LocationRepository
{
public:
    LocationRepository();
    LocationData SetChecked(int checkId);
    LocationData GetCheck(int checkId);
    std::map<int, LocationData> GetChecks();

private:
    std::map<int, LocationData> _checkData;
};
