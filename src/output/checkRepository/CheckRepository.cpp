#include "CheckRepository.h"
#include "SADXModLoader.h"

CheckRepository::CheckRepository()
{
    _checkData[0] = CheckData(EventFlags_Tails_JetAnklet, "Tails's Jet Anklet", 0);
    _checkData[1] = CheckData(EventFlags_Tails_RhythmBadge, "Tails's Rhythm Badge", 1);
    _checkData[2] = CheckData(EventFlags_TailsUnlockedAdventure, "Tails's Story", 5);
}


CheckData CheckRepository::SetChecked(const int checkId)
{
    _checkData[checkId].checked = true;
    return _checkData[checkId];
}

CheckData CheckRepository::GetCheck(const int checkId)
{
    return _checkData[checkId];
}

std::map<int, CheckData> CheckRepository::GetChecks()
{
    return _checkData;
}
